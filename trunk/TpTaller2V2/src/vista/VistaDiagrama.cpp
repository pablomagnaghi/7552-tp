/*
 * Diagrama.cpp
 *
 *  Created on: 02/04/2012
 *      Author: Guagnini Enzo 88325
 */

#include "VistaDiagrama.h"
#include <gdkmm.h>
#include <iostream>
using namespace std;

VistaDiagrama::VistaDiagrama(string nom) :
	Diagrama(nom) {
	this->zoom = ZOOM_DEFECTO;
	this->ancho = A4_ANCHO * zoom;
	this->alto = A4_ALTO * zoom;
	this->set_size_request(this->ancho, this->alto);

	this->estaRedimensionandoElemento = false;

	// Habilito el evento de apretar el boton del mouse
	this->add_events(Gdk::BUTTON_PRESS_MASK | Gdk::POINTER_MOTION_MASK);

	this->signal_button_press_event().connect(sigc::mem_fun(*this,
			&VistaDiagrama::on_button_press_event));
	this->signal_button_release_event().connect(sigc::mem_fun(*this,
			&VistaDiagrama::on_button_release_event));
	this->signal_motion_notify_event().connect(sigc::mem_fun(*this,
			&VistaDiagrama::on_mouse_motion_event));

	test_cargar_componentes_visuales();

	configurar_drag_and_drop();

	cout << "Diagrama" << endl;
}

VistaDiagrama::~VistaDiagrama() {
	// TODO Auto-generated destructor stub
}

void VistaDiagrama::test_cargar_componentes_visuales() {
	VistaComponente * componenteNuevo;
	VistaEntidad * entidadDebil;
	VistaEntidad * entidad;
	VistaRelacion * relacion;
	VistaAtributo * atributo;
	VistaUnion * vUnion;

	entidad = new VistaEntidad();
	entidad->setNombre("Alumno");
	entidad->setposini(10, 10);
	entidad->setposfin(60, 50);
	this->componentes.push_back(entidad);

	entidadDebil = new VistaEntidad();
	entidadDebil->setNombre("Entidad Debil");
	entidadDebil->setposini(180, 10);
	entidadDebil->setposfin(60, 50);
	entidadDebil->setEsDebil(true);
	this->componentes.push_back(entidadDebil);

	relacion = new VistaRelacion();
	relacion->setNombre("Cursa");
	relacion->setposini(70, 10);
	relacion->setposfin(120, 60);
	this->componentes.push_back(relacion);

	atributo = new VistaAtributo();
	atributo->setposini(130, 20);
	atributo->setposfin(138, 28);
	this->componentes.push_back(atributo);

	vUnion = new VistaUnion();
	vUnion->setposini(150, 20);
	vUnion->setposfin(170, 30);
	this->componentes.push_back(vUnion);

}

bool VistaDiagrama::on_expose_event(GdkEventExpose* e) {
	this->set_size_request(this->ancho, this->alto);
	Cairo::RefPtr<Cairo::Context> cr;
	cr = this->get_window()->create_cairo_context();
	cr->set_source_rgba(1, 1, 1, 1); // white
	cr->paint();

	std::vector<VistaComponente *>::iterator componenteActual;

	for (componenteActual = this->componentes.begin(); componenteActual
			!= this->componentes.end(); componenteActual++) {
		(*componenteActual)->dibujar(cr);
	}

	//Glib::RefPtr < Pango::Layout > layout = this->create_pango_layout("Hola");
	//	layout
	//cr->move_to(100, 100);
	//layout->update_from_cairo_context(cr);
	//layout->show_in_cairo_context(cr);

	return true;
}

bool VistaDiagrama::on_button_press_event(GdkEventButton* event) {

	cout << "X= " << event->x << " Y=" << event->y << endl;

	seleccionar_componente_clickeado(event->x, event->y);

	this->x_button_press = event->x;
	this->y_button_press = event->y;

	// Para redibujar el area de dibujo
	this->queue_draw();
	return true;
}

bool VistaDiagrama::on_button_release_event(GdkEventButton* event) {

	cout << "X= " << event->x << " Y=" << event->y << endl;

	this->queue_draw();
	return true;
}

void VistaDiagrama::seleccionar_componente_clickeado(gdouble x, gdouble y) {

	std::vector<VistaComponente *>::iterator componenteActual;

	// IF NOT APRETO CONTROL
	componentes_seleccionados.clear();

	for (componenteActual = this->componentes.begin(); componenteActual
			!= this->componentes.end(); componenteActual++) {
		if ((*componenteActual)->contieneAEstePunto(x, y)) {
			(*componenteActual)->seleccionar(x, y);
			componentes_seleccionados.push_back((*componenteActual));
			if ((*componenteActual)->esPuntoDeRedimension(x, y)) {
				this->estaRedimensionandoElemento = true;
			} else {
				this->estaRedimensionandoElemento = false;
			}
			componenteActual++;
			// if(!apreto_control){
			break;
			//} else {
			//return;
			//}
		} else {
			(*componenteActual)->deseleccionar();
		}
		//(*componenteActual)->dibujar(cr);
	}

	while (componenteActual != this->componentes.end()) {
		(*componenteActual)->deseleccionar();
		componenteActual++;
	}
}

void VistaDiagrama::setZoom(double z) {
	if ((z >= ZOOM_MIN) && (z <= ZOOM_MAX)) {
		this->zoom = z;
		this->ancho = A4_ANCHO * z;
		this->alto = A4_ALTO * z;
	}
}

int VistaDiagrama::getAlto() {
	return this->alto;
}

int VistaDiagrama::getAncho() {
	return this->ancho;
}

VistaDiagrama* VistaDiagrama::crearDiagramaHijo(string nombre) {
	VistaDiagrama* diagramaHijo = new VistaDiagrama(nombre);
	this->agregarDiagramaHijo(diagramaHijo);
	return diagramaHijo;
}

bool VistaDiagrama::on_mouse_motion_event(GdkEventMotion * event) {
	std::vector<VistaComponente *>::iterator componenteActual;

	for (componenteActual = this->componentes.begin(); componenteActual
			!= this->componentes.end(); componenteActual++) {
		(*componenteActual)->setMouseArriba(event->x, event->y);
		// VIEJO
		/*if ((*componenteActual)->contieneAEstePunto(event->x, event->y)) {
			(*componenteActual)->setMouseArriba(true);
		} else {
			(*componenteActual)->setMouseArriba(false);
		}*/
		//(*componenteActual)->dibujar(cr);
	}

	cout << "Mouse Motion X= " << event->x << " Y= " << event->y << endl;
	this->queue_draw();
	return true;
}

void VistaDiagrama::configurar_drag_and_drop() {
	// Drag And Drop

	// Defino las cosas que se pueden arrastrar
	std::vector<Gtk::TargetEntry> listaDeTargets;
	listaDeTargets.push_back(Gtk::TargetEntry("Entidad"));
	listaDeTargets.push_back(Gtk::TargetEntry("Relacion"));
	listaDeTargets.push_back(Gtk::TargetEntry("Union"));
	// TODO crear Comentarios
	listaDeTargets.push_back(Gtk::TargetEntry("Comentario"));

	// Configuro el widget origen
	this->drag_source_set(listaDeTargets, Gdk::BUTTON1_MASK, Gdk::ACTION_MOVE);
	this->signal_drag_begin().connect(sigc::mem_fun(*this,
			&VistaDiagrama::drag_begin));
	this->signal_drag_motion().connect(sigc::mem_fun(*this,
			&VistaDiagrama::drag_motion));
	//this->signal_drag_data_delete().connect(sigc::mem_fun(*this,
	//		&VistaDiagrama::drag_data_delete));
	//this->signal_drag_data_get().connect(sigc::mem_fun(*this,
	//		&VistaDiagrama::drag_data_get));
	//this->signal_drag_drop().connect(sigc::mem_fun(*this,
	//		&VistaDiagrama::drag_drop));
	//this->signal_drag_end().connect(sigc::mem_fun(*this,
	//		&VistaDiagrama::drag_end));
	//this->signal_drag_failed().connect(sigc::mem_fun(*this,
	//		&VistaDiagrama::drag_failed));
	//this->signal_drag_leave().connect(sigc::mem_fun(*this,
	//		&VistaDiagrama::drag_leave));

	// Configuro el widget destino
	this->drag_dest_set(listaDeTargets, Gtk::DEST_DEFAULT_ALL, Gdk::ACTION_MOVE);
	//this->signal_drag_data_received().connect(sigc::mem_fun(*this,
	//		&VistaDiagrama::drag_data_received));
}

void VistaDiagrama::drag_begin(const Glib::RefPtr<Gdk::DragContext>&context) {
	Glib::ustring seleccion = context->get_selection();
	//Glib::RefPtr<Gdk::Pixbuf> icono = Gdk::Pixbuf::create_from_inline(0,NULL,false);
	// Le saco el icono
	Cairo::RefPtr<Cairo::ImageSurface> imSur = Cairo::ImageSurface::create(
			Cairo::FORMAT_RGB24, 1, 1);
	Glib::RefPtr<Gdk::Pixbuf> pixbuf = Gdk::Pixbuf::create_from_data(
			imSur->get_data(), Gdk::COLORSPACE_RGB, false, 8, 1, 1,
			imSur->get_stride());

	context->set_icon(pixbuf, 0, 0);
	cout << "DRAG_BEGIN " << seleccion << endl;
}

bool VistaDiagrama::drag_motion(const Glib::RefPtr<Gdk::DragContext>& context,
		gint x_actual, gint y_actual, guint timestamp) {

	std::vector<VistaComponente *>::iterator componenteSeleccionado;

	if (!this->estaRedimensionandoElemento) {

		for (componenteSeleccionado = componentes_seleccionados.begin(); componenteSeleccionado
				!= componentes_seleccionados.end(); componenteSeleccionado++) {
			(*componenteSeleccionado)->mover(x_actual, y_actual);
			//(*componenteSeleccionado)->setposini(x_actual, y_actual);
			//(*componenteSeleccionado)->setposfin(x_actual + 50, y_actual + 40);
		}
		cout << "DRAG_MOTION" << endl;

	}
	this->queue_draw();
	return true;
}

void VistaDiagrama::drag_data_get(const Glib::RefPtr<Gdk::DragContext>&context,
		Gtk::SelectionData& selection_data, guint info, guint timestamp) {

	// 8 bits format
	// 9 the length of I'm Data! in bytes
	selection_data.set(selection_data.get_target(), 8,
			(const guchar*) "I'm Data!", 9);

	cout << "DRAG_DATA_GET " << endl;
}

bool VistaDiagrama::drag_drop(const Glib::RefPtr<Gdk::DragContext>& context,
		int x, int y, guint timestamp) {
	cout << "DRAG_DROP" << endl;
	return true;
}

void VistaDiagrama::drag_end(const Glib::RefPtr<Gdk::DragContext>&context) {
	cout << "DRAG_END" << endl;
}

void VistaDiagrama::drag_data_delete(
		const Glib::RefPtr<Gdk::DragContext>&context) {
	cout << "DRAG_DELETE" << endl;
}

bool VistaDiagrama::drag_failed(const Glib::RefPtr<Gdk::DragContext>&context,
		Gtk::DragResult result) {
	cout << "DRAG_FAILED" << endl;
	return true;
}

void VistaDiagrama::drag_leave(const Glib::RefPtr<Gdk::DragContext>&context,
		guint timestamp) {
	cout << "DRAG_LEAVE" << endl;
}

void VistaDiagrama::drag_data_received(
		const Glib::RefPtr<Gdk::DragContext>& context, gint x_dropped,
		gint y_dropped, const Gtk::SelectionData& selection_data, guint info,
		guint timestamp) {
	const int length = selection_data.get_length();
	if ((length >= 0) && (selection_data.get_format() == 8)) {
		std::cout << "Received \"" << selection_data.get_data_as_string()
				<< "\" in label " << std::endl;
	}

	context->drag_finish(false, false, timestamp);
	cout << "DRAG_DATA_RECEIVED " << endl;
}
