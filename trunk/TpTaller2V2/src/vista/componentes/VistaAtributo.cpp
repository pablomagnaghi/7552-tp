/*
 * Atributo.cpp
 *
 *  Created on: 02/04/2012
 *      Author: Guagnini Enzo 88325
 */

#include "VistaAtributo.h"

#include <iostream>
using namespace std;

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
	if (!this->seleccionado) {
		cr->set_source_rgb(colorNegro.get_red_p(), colorNegro.get_green_p(),
				colorNegro.get_blue_p());
	} else {
		cr->set_source_rgb(colorDeSeleccion.get_red_p(),
				colorDeSeleccion.get_green_p(), colorDeSeleccion.get_blue_p());
	}

	double centro_x, centro_y, radio;

	centro_x = (this->pos_fin_x + this->pos_ini_x) / 2;
	centro_y = (this->pos_fin_y + this->pos_ini_y) / 2;

	radio = this->pos_fin_x - centro_x;

	//cr->move_to(centro_x, this->pos_ini_y);
	cr->arc(centro_x, centro_y, radio, 0, 2 * M_PI);
	// TODO if es parte de una clave candidata FILL
	//cr->fill();
	cr->stroke();
}

bool VistaAtributo::esSeleccionado(double x, double y) {
	return false;
}

void VistaAtributo::finSeleccionado(double x, double y) {

}

bool VistaAtributo::contieneAEstePunto(double x, double y) {
	if (x > this->pos_ini_x && x < this->pos_fin_x) {
		if (y > this->pos_ini_y && y < this->pos_fin_y) {
			return true;
		}
	}
	return false;
}

void VistaAtributo::calcularDimensionesAPartirDeTexto(Cairo::TextExtents * textExtents){

}
