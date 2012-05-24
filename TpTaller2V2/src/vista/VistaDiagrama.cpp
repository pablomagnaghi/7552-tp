/*
 * Diagrama.cpp
 *
 *  Created on: 02/04/2012
 *      Author: Guagnini Enzo 88325
 */

#include "VistaDiagrama.h"

VistaDiagrama::VistaDiagrama(string nom) :
	Diagrama(nom) {
	this->zoom = ZOOM_DEFECTO;
	this->ancho = A4_ANCHO * zoom;
	this->alto = A4_ALTO * zoom;
	this->set_size_request(this->ancho, this->alto);
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
