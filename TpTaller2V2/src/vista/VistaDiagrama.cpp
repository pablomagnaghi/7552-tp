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

	configurar_drag_and_drop();
}

VistaDiagrama::~VistaDiagrama() {
	// TODO Auto-generated destructor stub
}

bool VistaDiagrama::on_expose_event(GdkEventExpose* e) {
	this->set_size_request(this->ancho, this->alto);
	Cairo::RefPtr<Cairo::Context> cr =
			this->get_window()->create_cairo_context();
	cr->set_source_rgba(1, 1, 1, 1); // white
	cr->paint();

	// Dibujo una entidad
	VistaEntidad * entidad = new VistaEntidad();
	entidad->setposini(10, 10);
	entidad->setposfin(60, 50);
	entidad->dibujar(cr);

	// Dibujo una relacion
	VistaRelacion * relacion = new VistaRelacion();
	relacion->setposini(70, 10);
	relacion->setposfin(120, 60);
	relacion->dibujar(cr);

	// Dibujo un atributo
	VistaAtributo * atributo = new VistaAtributo();
	atributo->setposini(130, 20);
	atributo->setposfin(140, 30);
	atributo->dibujar(cr);

	// Dibujo una union (Flecha)
	VistaUnion * vistaunion = new VistaUnion();
	vistaunion->setposini(150, 20);
	vistaunion->setposfin(170, 30);
	vistaunion->dibujar(cr);

	return true;
}

bool VistaDiagrama::on_button_press_event(GdkEventButton* event) {
	/*//Dependiendo del boton seleccionado en el panel ejecutamos diferentes acciones
	 int accion = this->panelAcciones->getBotonSeleccionado();
	 (this->*acciones[accion])(event);
	 this->redibujar();*/
	return true;
}

bool VistaDiagrama::on_button_release_event(GdkEventButton* event) {
	/*//Dependiendo del boton seleccionado en el panel ejecutamos diferentes acciones
	 int accion = this->panelAcciones->getBotonSeleccionado();
	 (this->*acciones[accion])(event);*/
	return true;
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
	this->signal_drag_data_delete().connect(sigc::mem_fun(*this,
			&VistaDiagrama::drag_data_delete));
	this->signal_drag_data_get().connect(sigc::mem_fun(*this,
			&VistaDiagrama::drag_data_get));
	this->signal_drag_drop().connect(sigc::mem_fun(*this,
			&VistaDiagrama::drag_drop));
	this->signal_drag_end().connect(sigc::mem_fun(*this,
			&VistaDiagrama::drag_end));
	this->signal_drag_failed().connect(sigc::mem_fun(*this,
			&VistaDiagrama::drag_failed));
	this->signal_drag_leave().connect(sigc::mem_fun(*this,
			&VistaDiagrama::drag_leave));

	// Configuro el widget destino
	this->drag_dest_set(listaDeTargets, Gtk::DEST_DEFAULT_ALL, Gdk::ACTION_MOVE);
	this->signal_drag_data_received().connect(sigc::mem_fun(*this,
			&VistaDiagrama::drag_data_received));
}

void VistaDiagrama::drag_begin(const Glib::RefPtr<Gdk::DragContext>&context) {
	Glib::ustring seleccion = context->get_selection();
	cout << "DRAG_BEGIN " << seleccion << endl;
}

bool VistaDiagrama::drag_motion(const Glib::RefPtr<Gdk::DragContext>& context,
		gint x_actual, gint y_actual, guint timestamp) {
	cout << "DRAG_MOTION" << endl;
	return true;
}

void VistaDiagrama::drag_data_get(const Glib::RefPtr<Gdk::DragContext>&context,
		Gtk::SelectionData& selection_data, guint info, guint timestamp) {

	/* 8 bits format */
	/* 9 the length of I'm Data! in bytes */
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
