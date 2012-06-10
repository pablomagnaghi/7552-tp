/* VistaUnion.cpp
 *  Created on: 24/05/2012
 *      Author: Gonzalo Ferrero 89657
 */

#include "VistaUnion.h"

#include <iostream>
using namespace std;

VistaUnion::VistaUnion() {
	// TODO Auto-generated constructor stub

}

VistaUnion::~VistaUnion() {
	// TODO Auto-generated destructor stub
}

bool VistaUnion::lanzarProp() {
	return false;
}

void VistaUnion::dibujar(Cairo::RefPtr<Cairo::Context> cr) {
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

	cr->move_to(this->pos_ini_x, this->pos_ini_y);
	cr->line_to(this->pos_fin_x, this->pos_fin_y);

	//cr->rectangle(this->pos_ini_x, this->pos_ini_y, this->pos_fin_x
	//	- this->pos_ini_x, this->pos_fin_y - this->pos_ini_y);
	cr->stroke();
}

bool VistaUnion::esSeleccionado(double x, double y) {
	return false;
}

void VistaUnion::finSeleccionado(double x, double y) {

}

bool VistaUnion::contieneAEstePunto(double x, double y) {
	return false;
}

void VistaUnion::calcularDimensionesAPartirDeTexto(
		Cairo::TextExtents * textExtents) {

}

bool VistaUnion::esPuntoDeRedimension(double x, double y) {
	return false;
}

void VistaUnion::setMouseArriba(double x, double y) {

}

void VistaUnion::redimensionar(double x, double y) {

}
