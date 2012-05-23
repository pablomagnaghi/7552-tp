/*
 * Entidad.cpp
 *
 *  Created on: 02/04/2012
 *      Author: Guagnini Enzo 88325
 */

#include "VistaEntidad.h"

VistaEntidad::VistaEntidad() {

}

VistaEntidad::~VistaEntidad() {

}

/********* Implemento metodos derivados de Vista Componente **********/

void VistaEntidad::dibujar(Cairo::RefPtr<Cairo::Context> cr) {

	// Dibujo el cuadrado en el contexto
	//cr->rectangle(this->pos_ini_x, this->pos_ini_y, this->pos_fin_x
	//		- this->pos_ini_x, this->pos_fin_y - this->pos_ini_y);

	// Ancho de linea arbitrario
	cr->set_line_width(1);
	cr->set_source_rgba(1, 1, 1, 0.9); // negro

	cr->move_to(this->pos_ini_x, this->pos_ini_y);
	cr->line_to(this->pos_fin_x,this->pos_ini_y);
	cr->line_to(this->pos_fin_y,this->pos_fin_y);
	cr->line_to(this->pos_ini_x,this->pos_ini_y);
	cr->line_to(this->pos_ini_x,this->pos_ini_y);

	cr->stroke();

}

bool VistaEntidad::esSeleccionado(double x, double y) {

}

void VistaEntidad::finSeleccionado(double x, double y) {

}

void VistaEntidad::lanzarProp(GdkEventButton* event) {

}
