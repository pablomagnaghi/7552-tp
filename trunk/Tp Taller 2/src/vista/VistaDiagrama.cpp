/*
 * Diagrama.cpp
 *
 *  Created on: 02/04/2012
 *      Author: Guagnini Enzo 88325
 */

#include "VistaDiagrama.h"

using namespace Cairo;

VistaDiagrama::VistaDiagrama(string nom) :
	nombre(nom) {
	this->zoom = ZOOM_DEFECTO;
	this->ancho = A4_ANCHO * zoom;
	this->alto = A4_ALTO * zoom;
	this->set_size_request(this->ancho, this->alto);
}

VistaDiagrama::~VistaDiagrama() {
	// TODO Auto-generated destructor stub
}

bool VistaDiagrama::on_expose_event(GdkEventExpose* event) {
	this->set_size_request(this->ancho, this->alto);

	// Gonzalo : TEST
	Glib::RefPtr<Gdk::Window> window = get_window();
	if (window) {
		Gtk::Allocation allocation = get_allocation();
		const int width = allocation.get_width();
		const int height = allocation.get_height();

		// coordinates for the center of the window
		int xc, yc;
		xc = width / 2;
		yc = height / 2;

		Cairo::RefPtr<Cairo::Context> cr = window->create_cairo_context();
		cr->set_line_width(10.0);

		// clip to the area indicated by the expose event so that we only redraw
		// the portion of the window that needs to be redrawn
		cr->rectangle(event->area.x, event->area.y, event->area.width,
				event->area.height);
		cr->clip();

		// draw red lines out from the center of the window
		cr->set_line_cap(Cairo::LINE_CAP_ROUND);
		cr->set_source_rgb(0.8, 0.0, 0.0);
		cr->move_to(20, 20);
		cr->line_to(xc, yc);
		cr->line_to(20, height - 20);

		cr->move_to(xc, yc);
		cr->line_to(width - 20, yc);
		cr->stroke();

		//RefPtr<Context> cr = this->get_window()->create_cairo_context();
		/*cr->set_source_rgba(1, 1, 1, 1); // white
		 cr->paint();
		 cr->set_source_rgba(0, 0, 0, 1); // negro

		 cr->move_to(0, 0);
		 cr->line_to(this->ancho, this->alto);

		 VistaEntidad * entidad = new VistaEntidad();

		 entidad->setposfin(10, 10);
		 entidad->setposfin(20, 20);

		 entidad->dibujar(cr);*/
	}

	//delete entidad;
	return true;
}

bool VistaDiagrama::on_button_press_event(GdkEventButton* event) {
	/*//Dependiendo del boton seleccionado en el panel ejecutamos diferentes acciones
	 int accion = this->panelAcciones->getBotonSeleccionado();
	 (this->*acciones[accion])(event);
	 this->redibujar();
	 return true;*/
}

bool VistaDiagrama::on_button_release_event(GdkEventButton* event) {
	/*//Dependiendo del boton seleccionado en el panel ejecutamos diferentes acciones
	 int accion = this->panelAcciones->getBotonSeleccionado();
	 (this->*acciones[accion])(event);
	 return true;*/
}

VistaDiagrama* VistaDiagrama::crearSubdiagrama(string nombre) {
	VistaDiagrama* diag = new VistaDiagrama(nombre);
	this->l_sub_diagramas.push_back(diag);
	return diag;
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

