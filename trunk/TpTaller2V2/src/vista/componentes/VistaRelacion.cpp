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
	double mitad_x, mitad_y;
	Cairo::TextExtents textExtents;

	cr->set_line_width(2); // Ancho de linea arbitrario
	if (!this->seleccionado) {
		cr->set_source_rgb(colorNegro.get_red_p(), colorNegro.get_green_p(),
				colorNegro.get_blue_p());
	} else {
		cr->set_source_rgb(colorDeSeleccion.get_red_p(),
				colorDeSeleccion.get_green_p(), colorDeSeleccion.get_blue_p());
	}

	//TODO IF(ES DEBIL)

	cr->get_text_extents(this->getNombre(), textExtents);

	this->calcularDimensionesAPartirDeTexto(&textExtents);

	mitad_x = (this->pos_fin_x + this->pos_ini_x) / 2;
	mitad_y = (this->pos_fin_y + this->pos_ini_y) / 2;

	this->dibujarNombreCentrado(cr, this->nombre);

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
	return Geometria::estaContenidoEnRectangulo(x, y, this->pos_ini_x,
			this->pos_ini_y, this->pos_fin_x, this->pos_fin_y);
}

void VistaRelacion::calcularDimensionesAPartirDeTexto(
		Cairo::TextExtents * textExtents) {
	double alto, ancho;
	ancho = textExtents->width;
	alto = textExtents->height;

	this->pos_fin_x = this->pos_ini_x + ancho + 6 * ESPACIO_ENTRE_TEXTO_Y_BORDE;
	this->pos_fin_y = this->pos_ini_y + alto + 6 * ESPACIO_ENTRE_TEXTO_Y_BORDE;

}

bool VistaRelacion::esPuntoDeRedimension(double x, double y) {

}

void VistaRelacion::setMouseArriba(double x, double y) {

}
