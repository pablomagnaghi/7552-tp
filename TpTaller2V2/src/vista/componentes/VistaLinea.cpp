/* VistaLinea.cpp
 *  Created on: 12/07/2012
 *      Author: Gonzalo Ferrero 89657
 */

#include "VistaLinea.h"

VistaLinea::VistaLinea() {
	// TODO Auto-generated constructor stub
}

VistaLinea::~VistaLinea() {
	// TODO Auto-generated destructor stub
}

void VistaLinea::dibujar(Cairo::RefPtr<Cairo::Context> cr) {
	double x0, x1, x2, x3, y0, y1, y2, y3;
	cr->set_line_width(1);

	if (!this->seleccionado) {
		cr->set_source_rgb(colorNegro.get_red_p(), colorNegro.get_green_p(),
				colorNegro.get_blue_p());
	} else {
		cr->set_source_rgb(colorDeSeleccion.get_red_p(), colorDeSeleccion.get_green_p(),
				colorDeSeleccion.get_blue_p());
	}

	this->desde->getposini(x0, y0);
	this->desde->getposfin(x1, y1);
	this->hasta->getposini(x2, y2);
	this->hasta->getposfin(x3, y3);

	this->pos_ini_x = (x0 + x1) / 2;
	this->pos_fin_x = (x2 + x3) / 2;
	this->pos_ini_y = (y0 + y1) / 2;
	this->pos_fin_y = (y2 + y3) / 2;

	this->desde->obtenerInterseccionConLinea(this->pos_ini_x, this->pos_ini_y, this->pos_fin_x,
			this->pos_fin_y, this->pos_ini_x, this->pos_ini_y);
	this->hasta->obtenerInterseccionConLinea(this->pos_ini_x, this->pos_ini_y, this->pos_fin_x,
			this->pos_fin_y, this->pos_fin_x, this->pos_fin_y);

	cr->move_to(this->pos_ini_x, this->pos_ini_y);
	cr->line_to(this->pos_fin_x, this->pos_fin_y);

	cr->stroke();
}

void VistaLinea::setComponenteDesde(VistaComponente *comp) {
	this->desde = comp;
}

void VistaLinea::setComponenteHasta(VistaComponente *comp) {
	this->hasta = comp;
}

bool VistaLinea::esSeleccionado(double x, double y) {
	return false;
}

//indica q sucede con el objeto cuando deja de ser seleccionado
void VistaLinea::finSeleccionado(double x, double y) {

}

//Lanza el asistente de prpiedades del objeto en cuestion.
bool VistaLinea::lanzarProp() {
	return false;
}

// Verifica si el punto cae dentro de este componente
bool VistaLinea::contieneAEstePunto(double x, double y) {
	return false;
}

void VistaLinea::calcularDimensionesAPartirDeTexto(Cairo::TextExtents * textExtents) {

}

// Verifica si el punto cae dentro de un punto para redimensionar el elemento
bool VistaLinea::esPuntoDeRedimension(double x, double y) {
return false;
}

void VistaLinea::setMouseArriba(double x, double y) {

}

void VistaLinea::redimensionar(double x, double y) {

}

std::string VistaLinea::getNombre()const {
	return "Linea";
}

bool VistaLinea::contieneEsteComponente(Componente *) {
	return false;
}

bool VistaLinea::obtenerInterseccionConLinea(double pos_ini_x, double pos_ini_y, double pos_fin_x,
		double pos_fin_y, double & x, double & y) {
	return false;
}
