/*
 * Entidad.cpp
 *
 *  Created on: 02/04/2012
 *      Author: Guagnini Enzo 88325
 */

#include "VistaEntidad.h"

VistaEntidad::VistaEntidad() {
	// TODO Auto-generated constructor stub

}

VistaEntidad::~VistaEntidad() {
	// TODO Auto-generated destructor stub
}

void VistaEntidad::lanzarProp(GdkEventButton* event){
	AsistenteEntidad* nuevaProp;
	Glib::RefPtr<Gtk::Builder> nHbuilder = Gtk::Builder::create_from_file(
			ARCH_GLADE_APENTIDAD);
	nHbuilder->get_widget_derived("PropEntidad", nuevaProp);
	nuevaProp->setEntidad(this);
}


void VistaEntidad::dibujar(Cairo::RefPtr<Cairo::Context> cr) {

}

bool VistaEntidad::esSeleccionado(double x, double y) {

}

void VistaEntidad::finSeleccionado(double x, double y) {

}
