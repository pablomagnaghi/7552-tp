/* VistaRelacion.cpp
 *  Created on: 24/05/2012
 *      Author: Gonzalo Ferrero 89657
 */

#include "VistaRelacion.h"

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
	cr->set_source_rgba(0, 0, 0, 1); // negro

	//TODO IF(ES DEBIL)

	double mitad_x, mitad_y;

	mitad_x = (this->pos_fin_x + this->pos_ini_x)/2;
	mitad_y = (this->pos_fin_y + this->pos_ini_y)/2;

	cr->move_to(mitad_x,this->pos_ini_y);
	cr->line_to(this->pos_fin_x,mitad_y);
	cr->line_to(mitad_x, this->pos_fin_y);
	cr->line_to(this->pos_ini_x, mitad_y);
	cr->line_to(mitad_x,this->pos_ini_y);

	//cr->rectangle(this->pos_ini_x, this->pos_ini_y, this->pos_fin_x
		//	- this->pos_ini_x, this->pos_fin_y - this->pos_ini_y);
	cr->stroke();
}

bool VistaRelacion::esSeleccionado(double x, double y) {
	return false;
}

void VistaRelacion::finSeleccionado(double x, double y) {

}
