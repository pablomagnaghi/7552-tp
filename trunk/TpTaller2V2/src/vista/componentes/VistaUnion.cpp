/* VistaUnion.cpp
 *  Created on: 24/05/2012
 *      Author: Gonzalo Ferrero 89657
 */

#include "VistaUnion.h"

VistaUnion::VistaUnion() {
	// TODO Auto-generated constructor stub

}

VistaUnion::~VistaUnion() {
	// TODO Auto-generated destructor stub
}


void VistaUnion::lanzarProp(GdkEventButton* event) {

}

void VistaUnion::dibujar(Cairo::RefPtr<Cairo::Context> cr) {
	// Dibujo el cuadrado en el contexto
	// Ancho de linea arbitrario
	cr->set_line_width(1);
	cr->set_source_rgba(0, 0, 0, 1); // negro

	cr->move_to(this->pos_ini_x,this->pos_ini_y);
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
