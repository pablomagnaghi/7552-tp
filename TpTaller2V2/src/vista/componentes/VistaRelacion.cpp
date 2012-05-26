/* VistaRelacion.cpp
 *  Created on: 24/05/2012
 *      Author: Gonzalo Ferrero 89657
 */

#include "VistaRelacion.h"
#include <iostream>
using namespace std;

VistaRelacion::VistaRelacion() {
	// TODO Auto-generated constructor stub

}

VistaRelacion::~VistaRelacion() {
	// TODO Auto-generated destructor stub
}

void VistaRelacion::lanzarProp(GdkEventButton* event) {

}

void VistaRelacion::dibujar(Cairo::RefPtr<Cairo::Context> cr) {
	// Dibujo el cuadrado en el contexto
	// Ancho de linea arbitrario
	cr->set_line_width(2);
	if (!this->seleccionado) {
		cr->set_source_rgb(colorNegro.get_red_p(), colorNegro.get_green_p(),
				colorNegro.get_blue_p());
	} else {
		cr->set_source_rgb(colorDeSeleccion.get_red_p(),
				colorDeSeleccion.get_green_p(), colorDeSeleccion.get_blue_p());
	}

	//TODO IF(ES DEBIL)

	double mitad_x, mitad_y;

	mitad_x = (this->pos_fin_x + this->pos_ini_x) / 2;
	mitad_y = (this->pos_fin_y + this->pos_ini_y) / 2;

	cr->move_to(mitad_x, this->pos_ini_y);
	cr->line_to(this->pos_fin_x, mitad_y);
	cr->line_to(mitad_x, this->pos_fin_y);
	cr->line_to(this->pos_ini_x, mitad_y);
	cr->line_to(mitad_x, this->pos_ini_y);

	//cr->rectangle(this->pos_ini_x, this->pos_ini_y, this->pos_fin_x
	//	- this->pos_ini_x, this->pos_fin_y - this->pos_ini_y);
	cr->stroke();
}

bool VistaRelacion::esSeleccionado(double x, double y) {
	return false;
}

void VistaRelacion::finSeleccionado(double x, double y) {

}

bool VistaRelacion::contieneAEstePunto(double x, double y) {
	if (x > this->pos_ini_x && x < this->pos_fin_x) {
		if (y > this->pos_ini_y && y < this->pos_fin_y) {
			return true;
		}
	}

	return false;
}

