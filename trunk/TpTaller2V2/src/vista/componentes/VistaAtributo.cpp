/*
 * Atributo.cpp
 *
 *  Created on: 02/04/2012
 *      Author: Guagnini Enzo 88325
 */

#include "VistaAtributo.h"

VistaAtributo::VistaAtributo() {
	// TODO Auto-generated constructor stub

}

VistaAtributo::~VistaAtributo() {
	// TODO Auto-generated destructor stub
}

void VistaAtributo::lanzarProp(GdkEventButton* event) {

}

void VistaAtributo::dibujar(Cairo::RefPtr<Cairo::Context> cr) {
	// Dibujo el cuadrado en el contexto
	// Ancho de linea arbitrario
	cr->set_line_width(1);
	cr->set_source_rgba(0, 0, 0, 1); // negro

	double centro_x, centro_y, radio;

	centro_x = (this->pos_fin_x + this->pos_ini_x) / 2;
	centro_y = (this->pos_fin_y + this->pos_ini_y) / 2;

	radio = this->pos_fin_x - centro_x;

	//cr->move_to(centro_x, this->pos_ini_y);
	cr->arc(centro_x, centro_y, radio, 0, 2*M_PI);
	// TODO if es parte de una clave candidata FILL
	//cr->fill();
	cr->stroke();
}

bool VistaAtributo::esSeleccionado(double x, double y) {
	return false;
}

void VistaAtributo::finSeleccionado(double x, double y) {

}
