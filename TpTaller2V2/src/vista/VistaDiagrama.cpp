#include "VistaDiagrama.h"
#include <gdkmm.h>
#include <iostream>
using namespace std;

VistaDiagrama::VistaDiagrama(Diagrama * diagramaModelo) {

	this->diagrama = diagramaModelo;
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

	//test_cargar_componentes_visuales();

	configurar_drag_and_drop();

	//cout << "Diagrama" << endl;
}

VistaDiagrama::~VistaDiagrama() {
	std::vector<VistaComponente*>::iterator it = this->componentes.begin();
	while (it != this->componentes.end()) {
		delete (*it);
		it++;
	}
	this->componentes.clear();
}

void VistaDiagrama::test_cargar_componentes_visuales() {
	//VistaComponente * componenteNuevo;
	EntidadNueva * a;
	EntidadNueva * b;
	EntidadGlobal * h;
	Relacion * c;
	Atributo * d;
	Atributo * i;
	Atributo * k;
	Atributo * l;
	Atributo * l1;
	Atributo * l2;
	Atributo * l3;
	UnionEntidadRelacion * f;
	UnionEntidadRelacion * g;
	Jerarquia * j;

	VistaEntidadNueva * entidadDebil;
	VistaEntidadNueva * entidad;
	VistaRelacion * relacion;
	VistaAtributo * atributo;
	VistaAtributo * atributo1;
	VistaAtributo * atributo2;
	VistaAtributo * atributoCompuesto;
	VistaAtributo * atributoCompuesto1;
	VistaAtributo * atributoCompuesto2;
	VistaAtributo * atributoCompuesto3;
	VistaUnionEntidadRelacion * vUnion;
	VistaLinea * lineaEntidadAtributo;
	VistaJerarquia * jerarquia;
	VistaEntidadNueva * entidadPadre;
	VistaEntidadGlobal * entidadGlobal;

	// Creo el modelo
	a = new EntidadNueva();
	b = new EntidadNueva();
	c = new Relacion();
	d = new Atributo();
	i = new Atributo();
	k = new Atributo();
	l1 = new Atributo();
	l2 = new Atributo();
	l3 = new Atributo();
	l = new Atributo();
	f = new UnionEntidadRelacion(a, c);
	g = new UnionEntidadRelacion(b, c);
	j = new Jerarquia();
	h = new EntidadGlobal();

	entidad = new VistaEntidadNueva(a);
	entidad->setNombre("Alumno A");
	entidad->setposini(60, 200);
	entidad->setposfin(110, 260);
	this->componentes.push_back(entidad);

	entidadDebil = new VistaEntidadNueva(b);
	entidadDebil->setNombre("Entidad Debil");
	entidadDebil->setposini(60, 400);
	entidadDebil->setposfin(120, 450);
	entidadDebil->setEsDebil(true);
	this->componentes.push_back(entidadDebil);

	relacion = new VistaRelacion(c);
	relacion->setNombre("Cursa");
	relacion->setposini(60, 300);
	relacion->setposfin(110, 380);
	this->componentes.push_back(relacion);

	atributo = new VistaAtributo(d);
	atributo->setposini(20, 220);
	atributo->setposfin(28, 228);
	this->componentes.push_back(atributo);

	// Obtengo la vista Entidad a partir de la Vista Relacion
	std::vector<VistaEntidadNueva *> vistasEntidaes;
	std::vector<UnionEntidadRelacion *> uniones;
	obtenerVistaAPartirDeRelacion(relacion, vistasEntidaes, uniones);

	for (unsigned int i = 0; i < vistasEntidaes.size(); i++) {
		vUnion = new VistaUnionEntidadRelacion(uniones[i], vistasEntidaes[i], relacion);
		this->componentes.push_back(vUnion);
	}

	lineaEntidadAtributo = new VistaLinea();
	lineaEntidadAtributo->setComponenteDesde(entidad);
	lineaEntidadAtributo->setComponenteHasta(atributo);
	this->componentes.push_back(lineaEntidadAtributo);

	atributo1 = new VistaAtributo(i);
	atributo1->setposini(20, 240);
	atributo1->setposfin(28, 248);
	atributo2 = new VistaAtributo(k);
	atributoCompuesto = new VistaAtributo(l);
	atributoCompuesto1 = new VistaAtributo(l1);
	atributoCompuesto2 = new VistaAtributo(l2);
	atributoCompuesto3 = new VistaAtributo(l3);

	lineaEntidadAtributo = new VistaLinea();
	lineaEntidadAtributo->setComponenteDesde(entidad);
	lineaEntidadAtributo->setComponenteHasta(atributo1);
	this->componentes.push_back(atributo1);
	this->componentes.push_back(lineaEntidadAtributo);

	entidadPadre = new VistaEntidadNueva(new EntidadNueva());
	entidadPadre->setNombre("Padre");
	entidadPadre->setposini(60, 100);
	entidadPadre->setposfin(110, 150);
	this->componentes.push_back(entidadPadre);

	jerarquia = new VistaJerarquia(j);
	jerarquia->agregarEntidadEspecializada(entidad);
	jerarquia->setEntidadPadre(entidadPadre);

	entidad = new VistaEntidadNueva(new EntidadNueva());
	entidad->setNombre("Alumno B");
	entidad->setposini(140, 200);
	entidad->setposfin(190, 260);
	this->componentes.push_back(entidad);
	jerarquia->agregarEntidadEspecializada(entidad);

	entidad = new VistaEntidadNueva(new EntidadNueva());
	entidad->setNombre("Alumno C");
	entidad->setposini(220, 190);
	entidad->setposfin(270, 260);
	this->componentes.push_back(entidad);

	jerarquia->agregarEntidadEspecializada(entidad);
	this->componentes.push_back(jerarquia);

	entidadGlobal = new VistaEntidadGlobal(h);
	this->componentes.push_back(entidadGlobal);

}

void VistaDiagrama::test_cargar_componentes_visuales_atributo() {
	EntidadNueva * a = new EntidadNueva();
	VistaEntidadNueva * entidad = new VistaEntidadNueva(a);
	Atributo * b = new Atributo();
	VistaAtributo * atributo = new VistaAtributo(b);
	Atributo * c = new Atributo();
	VistaAtributo * atributo1 = new VistaAtributo(c);
	Atributo * d = new Atributo();
	VistaAtributo * atributo2 = new VistaAtributo(d);
	Atributo * e = new Atributo();
	VistaAtributo * atributoCompuesto = new VistaAtributo(e);
	Atributo * e1 = new Atributo();
	VistaAtributo * atributoCompuesto1 = new VistaAtributo(e1);
	Atributo * e2 = new Atributo();
	VistaAtributo * atributoCompuesto2 = new VistaAtributo(e2);
	Atributo * e3 = new Atributo();
	VistaAtributo * atributoCompuesto3 = new VistaAtributo(e3);
	VistaLinea * lineaEntidadAtributo;
	Identificador * id1 = new Identificador();
	VistaIdentificador * identificador1 = new VistaIdentificador(id1);
	Identificador * id2 = new Identificador();
	VistaIdentificador * identificador2 = new VistaIdentificador(id2);
	Identificador * id3 = new Identificador();
	VistaIdentificador * identificador3 = new VistaIdentificador(id2);
	Relacion * f = new Relacion();
	VistaRelacion * relacion = new VistaRelacion(f);
	UnionEntidadRelacion *g = new UnionEntidadRelacion(a, f);
	VistaUnionEntidadRelacion * unionEntidadRelacionDebil = new VistaUnionEntidadRelacion(g,
			entidad, relacion);
	EntidadNueva * h = new EntidadNueva();
	VistaEntidadNueva * entidadFuerte = new VistaEntidadNueva(h);
	UnionEntidadRelacion *i = new UnionEntidadRelacion(h, f);
	VistaUnionEntidadRelacion * unionEntidadRelacionFuerte = new VistaUnionEntidadRelacion(i,
			entidadFuerte, relacion);

	entidad->setposini(150, 100);
	entidad->setposfin(240, 110);
	entidad->setNombre("Entidad");
	this->componentes.push_back(entidad);

	atributo->setposini(130, 60);
	b->setNombre("A1");
	a->agregarAtributo(b);
	entidad->agregarAtributo(atributo);
	this->componentes.push_back(atributo);
	lineaEntidadAtributo = new VistaLinea();
	lineaEntidadAtributo->setComponenteDesde(atributo);
	lineaEntidadAtributo->setComponenteHasta(entidad);
	this->componentes.push_back(lineaEntidadAtributo);
	id1->agregarCodigoAtributo(b->getCodigo());
	identificador1->agregarAtributo(atributo);
	atributo->setLinea(lineaEntidadAtributo);
	this->componentes.push_back(identificador1);

	atributo1->setposini(170, 60);
	a->agregarAtributo(c);
	entidad->agregarAtributo(atributo1);
	this->componentes.push_back(atributo1);
	lineaEntidadAtributo = new VistaLinea();
	lineaEntidadAtributo->setComponenteDesde(atributo1);
	lineaEntidadAtributo->setComponenteHasta(entidad);
	atributo1->setLinea(lineaEntidadAtributo);
	this->componentes.push_back(lineaEntidadAtributo);

	atributo2->setposini(210, 60);
	a->agregarAtributo(d);
	entidad->agregarAtributo(atributo2);
	this->componentes.push_back(atributo2);
	lineaEntidadAtributo = new VistaLinea();
	lineaEntidadAtributo->setComponenteDesde(atributo2);
	lineaEntidadAtributo->setComponenteHasta(entidad);
	atributo2->setLinea(lineaEntidadAtributo);
	this->componentes.push_back(lineaEntidadAtributo);

	id2->agregarCodigoAtributo(c->getCodigo());
	identificador2->agregarAtributo(atributo1);
	id2->agregarCodigoAtributo(d->getCodigo());
	identificador2->agregarAtributo(atributo2);

	atributoCompuesto->setposini(142, 155);
	//atributoCompuesto->setposfin(202, 185);
	a->agregarAtributo(e);
	e->setNombre("Compuesto");
	entidad->agregarAtributo(atributoCompuesto);
	this->componentes.push_back(atributoCompuesto);
	lineaEntidadAtributo = new VistaLinea();
	lineaEntidadAtributo->setComponenteDesde(atributoCompuesto);
	lineaEntidadAtributo->setComponenteHasta(entidad);
	atributoCompuesto->setLinea(lineaEntidadAtributo);
	this->componentes.push_back(lineaEntidadAtributo);
	id3->agregarCodigoAtributo(e->getCodigo());
	identificador3->agregarAtributo(atributoCompuesto);
	this->componentes.push_back(identificador3);

	atributoCompuesto1->setposini(130, 210);
	e->agregarAtributo(e1);
	atributoCompuesto->agregarAtributo(atributoCompuesto1);
	this->componentes.push_back(atributoCompuesto1);
	lineaEntidadAtributo = new VistaLinea();
	lineaEntidadAtributo->setComponenteDesde(atributoCompuesto);
	lineaEntidadAtributo->setComponenteHasta(atributoCompuesto1);
	atributoCompuesto1->setLinea(lineaEntidadAtributo);
	this->componentes.push_back(lineaEntidadAtributo);

	atributoCompuesto2->setposini(172, 210);
	e->agregarAtributo(e2);
	atributoCompuesto->agregarAtributo(atributoCompuesto2);
	this->componentes.push_back(atributoCompuesto2);
	lineaEntidadAtributo = new VistaLinea();
	lineaEntidadAtributo->setComponenteDesde(atributoCompuesto);
	lineaEntidadAtributo->setComponenteHasta(atributoCompuesto2);
	atributoCompuesto2->setLinea(lineaEntidadAtributo);
	this->componentes.push_back(lineaEntidadAtributo);

	atributoCompuesto3->setposini(210, 210);
	e->agregarAtributo(e3);
	atributoCompuesto->agregarAtributo(atributoCompuesto3);
	this->componentes.push_back(atributoCompuesto3);
	lineaEntidadAtributo = new VistaLinea();
	lineaEntidadAtributo->setComponenteDesde(atributoCompuesto);
	lineaEntidadAtributo->setComponenteHasta(atributoCompuesto3);
	atributoCompuesto3->setLinea(lineaEntidadAtributo);
	this->componentes.push_back(lineaEntidadAtributo);

	entidadFuerte->setposini(250,50);
	entidadFuerte->setposfin(350,65);
	this->componentes.push_back(entidadFuerte);
	relacion->setNombre("Relacion");
	relacion->setposini(250,100);
	relacion->setposfin(350,120);
	this->componentes.push_back(relacion);
	this->componentes.push_back(unionEntidadRelacionDebil);
	this->componentes.push_back(unionEntidadRelacionFuerte);

	id2->agregarCodigoRelacion(f->getCodigo());
	identificador2->agregarEntidadFuerte(unionEntidadRelacionFuerte);

	this->componentes.push_back(identificador2);
}

void VistaDiagrama::obtenerVistaAPartirDeRelacion(VistaRelacion * vRelacion, std::vector<
		VistaEntidadNueva *> &vistasEntidadesACrear,
		std::vector<UnionEntidadRelacion *> &unionesACrear) {
	vistasEntidadesACrear.clear();
	unionesACrear.clear();

	std::vector<UnionEntidadRelacion *> uniones = vRelacion->getUniones();
	std::vector<UnionEntidadRelacion *>::iterator i;
	std::vector<VistaComponente *>::iterator j;
	Componente * componente;
	for (i = uniones.begin(); i != uniones.end(); i++) {
		componente = (*i)->getEntidad();
		for (j = this->componentes.begin(); j != this->componentes.end(); j++) {
			if ((*j)->contieneEsteComponente(componente)) {
				vistasEntidadesACrear.push_back(dynamic_cast<VistaEntidadNueva *> (*j));
				unionesACrear.push_back(*i);
				cout << "A" << endl;
				break;
			}
		}
	}
}

bool VistaDiagrama::on_expose_event(GdkEventExpose* e) {
	this->set_size_request(this->ancho, this->alto);
	Cairo::RefPtr<Cairo::Context> cr;
	cr = this->get_window()->create_cairo_context();
	cr->set_source_rgba(1, 1, 1, 1); // white
	cr->paint();

	std::vector<VistaComponente *>::iterator componenteActual;

	for (componenteActual = this->componentes.begin(); componenteActual != this->componentes.end(); componenteActual++) {
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
	VistaComponente * componente;
	cout << "X= " << event->x << " Y=" << event->y << endl;
	cout << "Event button: " << event->button << endl;

	if ((event->type == GDK_BUTTON_PRESS) && (event->button == 3)) {
		componente = obtenerComponenteEnPos(event->x, event->y);
		if (componente != NULL) {
			componente->lanzarMenuPopUp(event);
		}
	} else {
		seleccionar_componente_clickeado(event->x, event->y);

		if (this->componentes_seleccionados.size() == 1
				&& this->componentes_seleccionados[0]->esPuntoDeRedimension(event->x, event->y)) {
			this->estaRedimensionandoElemento = true;
		} else {
			this->estaRedimensionandoElemento = false;
		}
	}

	this->x_button_press = event->x;
	this->y_button_press = event->y;

	// Para redibujar el area de dibujo
	this->queue_draw();
	return true;
}

bool VistaDiagrama::on_button_release_event(GdkEventButton* event) {

	this->estaRedimensionandoElemento = false;
	cout << "Release X= " << event->x << " Y= " << event->y << endl;

	this->queue_draw();
	return true;
}

void VistaDiagrama::seleccionar_componente_clickeado(gdouble x, gdouble y) {

	std::vector<VistaComponente *>::iterator componenteActual;

	// IF NOT APRETO CONTROL
	componentes_seleccionados.clear();

	for (componenteActual = this->componentes.begin(); componenteActual != this->componentes.end(); componenteActual++) {
		if ((*componenteActual)->contieneAEstePunto(x, y)) {
			(*componenteActual)->seleccionar(x, y);
			componentes_seleccionados.push_back((*componenteActual));
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
	Diagrama * nuevoDiagrama = new Diagrama();
	nuevoDiagrama->setNombre(nombre);
	this->diagrama->agregarDiagramaHijo(nuevoDiagrama);
	VistaDiagrama* diagramaHijo = new VistaDiagrama(nuevoDiagrama);
	this->diagramas.push_back(diagramaHijo);
	return diagramaHijo;
}

bool VistaDiagrama::on_mouse_motion_event(GdkEventMotion * event) {
	std::vector<VistaComponente *>::iterator componenteActual;

	if (!this->estaRedimensionandoElemento) {
		for (componenteActual = this->componentes.begin(); componenteActual
				!= this->componentes.end(); componenteActual++) {
			(*componenteActual)->setMouseArriba(event->x, event->y);
		}
	}
#ifdef DEBUG
	cout << "Mouse Motion X= " << event->x << " Y= " << event->y << endl;
#endif
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
	this->signal_drag_begin().connect(sigc::mem_fun(*this, &VistaDiagrama::drag_begin));
	this->signal_drag_motion().connect(sigc::mem_fun(*this, &VistaDiagrama::drag_motion));
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
	Cairo::RefPtr<Cairo::ImageSurface> imSur = Cairo::ImageSurface::create(Cairo::FORMAT_RGB24, 1,
			1);
	Glib::RefPtr<Gdk::Pixbuf> pixbuf = Gdk::Pixbuf::create_from_data(imSur->get_data(),
			Gdk::COLORSPACE_RGB, false, 8, 1, 1, imSur->get_stride());

	context->set_icon(pixbuf, 0, 0);
#ifdef DEBUG
	cout << "DRAG_BEGIN " << seleccion << endl;
#endif
}

bool VistaDiagrama::drag_motion(const Glib::RefPtr<Gdk::DragContext>& context, gint x_actual,
		gint y_actual, guint timestamp) {

	std::vector<VistaComponente *>::iterator componenteSeleccionado;

	if (!this->estaRedimensionandoElemento) {
		for (componenteSeleccionado = componentes_seleccionados.begin(); componenteSeleccionado
				!= componentes_seleccionados.end(); componenteSeleccionado++) {
			(*componenteSeleccionado)->mover(x_actual, y_actual);
			//(*componenteSeleccionado)->setposini(x_actual, y_actual);
			//(*componenteSeleccionado)->setposfin(x_actual + 50, y_actual + 40);
		}
#ifdef DEBUG
		cout << "Arrastrando X= " << x_actual << " Y= " << y_actual << endl;
#endif
	} else {
		this->componentes_seleccionados[0]->redimensionar(x_actual, y_actual);
		//context->drag_finish(true, true, timestamp);
		cout << "Redimensionando X= " << x_actual << " Y= " << y_actual << endl;
	}

	this->queue_draw();
	return true;
}

void VistaDiagrama::drag_data_get(const Glib::RefPtr<Gdk::DragContext>&context,
		Gtk::SelectionData& selection_data, guint info, guint timestamp) {

	// 8 bits format
	// 9 the length of I'm Data! in bytes
	selection_data.set(selection_data.get_target(), 8, (const guchar*) "I'm Data!", 9);
#ifdef DEBUG
	cout << "DRAG_DATA_GET " << endl;
#endif
}

bool VistaDiagrama::drag_drop(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y,
		guint timestamp) {
#ifdef DEBUG
	cout << "DRAG_DROP" << endl;
#endif
	return true;
}

void VistaDiagrama::drag_end(const Glib::RefPtr<Gdk::DragContext>&context) {
	cout << "DRAG_END" << endl;
}

void VistaDiagrama::drag_data_delete(const Glib::RefPtr<Gdk::DragContext>&context) {
	cout << "DRAG_DELETE" << endl;
}

bool VistaDiagrama::drag_failed(const Glib::RefPtr<Gdk::DragContext>&context,
		Gtk::DragResult result) {
	cout << "DRAG_FAILED" << endl;
	return true;
}

void VistaDiagrama::drag_leave(const Glib::RefPtr<Gdk::DragContext>&context, guint timestamp) {
	cout << "DRAG_LEAVE" << endl;
}

void VistaDiagrama::drag_data_received(const Glib::RefPtr<Gdk::DragContext>& context,
		gint x_dropped, gint y_dropped, const Gtk::SelectionData& selection_data, guint info,
		guint timestamp) {
	const int length = selection_data.get_length();
	if ((length >= 0) && (selection_data.get_format() == 8)) {
		std::cout << "Received \"" << selection_data.get_data_as_string() << "\" in label "
				<< std::endl;
	}

	context->drag_finish(false, false, timestamp);
	cout << "DRAG_DATA_RECEIVED " << endl;
}

void VistaDiagrama::agregarComponente(VistaComponente * componente) {
	if (componente != NULL) {
		this->componentes.push_back(componente);
		this->queue_draw();
	}
}

void VistaDiagrama::agregarVistaEntidadNueva(VistaEntidadNueva *ven) {
	if (ven != NULL) {
		this->vistaentidades.push_back(ven);
	}
}

// PERSISTENCIA REP
/*
 // Abre un archivo xml, y carga un diagrama con la informacion que contenga.
 void VistaDiagrama::abrirREP(const std::string& path) {

 this->diagramaValidoREP = false;

 try {
 // Abro el archivo
 Xml docXml(path);
 this->diagramaValidoREP = true;

 XmlNodo* nodoRaiz = docXml.getNodoRaiz();

 XmlNodo::verificarNombre(NOMBRE_DIAGRAMA, *nodoRaiz );

 // archivo listo para cargar el diagrama
 // se cargan los componentes del doc.
 this->obtenerPropiedadesXmlREP(nodoRaiz);

 XmlNodo nodo = nodoRaiz->getHijo();

 this->obtenerComponentesXmlREP(&nodo);
 }
 catch ( XmlArchivoInexistenteExc* ex ) {
 delete ex;
 throw new DiagramaArchivoInexistenteExc( path );
 }
 catch ( XmlArchivoInvalidoExc* ex ) {
 delete ex;
 throw new DiagramaInvalidoExc( path );
 }
 }*/
/*
 void VistaDiagrama::obtenerPropiedadesXmlREP(XmlNodo* nodo) {
 this->estado = nodo->getPropiedad("estado");
 }

 void VistaDiagrama::obtenerComponentesXmlREP (XmlNodo* nodo) {
 while (nodo->esValido()) {
 if (nodo->getNombre() == "componente") {
 //VistaComponente *vistaComponente = new VistaComponente(nodo);
 //this->agregarComponente(vistaComponente);
 }
 *nodo = nodo->getHermano();
 }
 }

 void VistaDiagrama::agregarPropiedadesXmlREP(XmlNodo* nodo) {
 nodo->setPropiedad(XMLNS, INSTANCE);
 nodo->setPropiedad(XSI, COMPOSICION);
 nodo->setPropiedad("estado",this->estado);
 }

 void VistaDiagrama::guardarComponentesXmlREP(XmlNodo *nodo) {
 std::vector<VistaComponente*>::iterator i;

 for(i = this->componentes.begin(); i != this->componentes.end(); ++i)
 nodo->agregarHijo((*i)->guardarXmlREP());
 }

 XmlNodo VistaDiagrama::guardarXmlREP() {
 XmlNodo nodo("diagrama");

 this->agregarPropiedadesXmlREP(&nodo);

 this->guardarComponentesXmlREP(&nodo);

 return nodo;
 }

 // Devuelve true si se logró abrir y cargar el documento.

 bool VistaDiagrama::isOpenREP() const {
 return this->diagramaValidoREP;
 }
 */
// Guarda el Diagrama
/*
 void VistaDiagrama::guardarDiagramaREP(const std::string& path) {
 Xml docXml;
 docXml.nuevoDoc();
 XmlNodo nodoDoc = this->guardarXmlREP();
 docXml.setNodoRaiz(nodoDoc);
 docXml.guardar(path);
 }
 */
std::string VistaDiagrama::getNombre() const {
	return this->diagrama->getNombre();
}

std::vector<VistaComponente*>::iterator VistaDiagrama::componentesBegin() {
	return this->componentes.begin();
}

std::vector<VistaComponente*>::iterator VistaDiagrama::componentesEnd() {
	return this->componentes.end();
}

std::vector<VistaDiagrama*>::iterator VistaDiagrama::vdiagramasBegin() {
	return this->diagramas.begin();
}

std::vector<VistaDiagrama*>::iterator VistaDiagrama::vdiagramasEnd() {
	return this->diagramas.end();
}

std::vector<VistaEntidadNueva*>::iterator VistaDiagrama::vEntidadesBegin() {
	return this->vistaentidades.begin();
}
std::vector<VistaEntidadNueva*>::iterator VistaDiagrama::vEntidadesEnd() {
	return this->vistaentidades.end();
}

VistaComponente * VistaDiagrama::obtenerComponenteEnPos(gdouble x, gdouble y) {
	std::vector<VistaComponente *>::iterator i;
	for (i = this->componentes.begin(); i != this->componentes.end(); i++) {
		if ((*i)->contieneAEstePunto(x, y)) {
			return *i;
		}
	}
	return NULL;
}

Diagrama * VistaDiagrama::getDiagrama() {
	return this->diagrama;
}
