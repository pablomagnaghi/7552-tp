/*
 * Atributo.cpp
 *
 *  Created on: 02/04/2012
 *      Author: Guagnini Enzo 88325
 */

#include "VistaAtributo.h"

#include <iostream>
using namespace std;

VistaAtributo::VistaAtributo(Atributo * atributoModelo) {
	// TODO Auto-generated constructor stub
	this->atributo = atributoModelo;
	this->prop_lanzada = false;

}

VistaAtributo::~VistaAtributo() {
	// TODO Auto-generated destructor stub
}

bool VistaAtributo::lanzarProp() {
	if (!this->prop_lanzada) {
		AsistenteAtributo* nuevaProp;
		Glib::RefPtr<Gtk::Builder> nHbuilder = Gtk::Builder::create_from_file(
				ARCH_GLADE_ATRIB);
		nHbuilder->get_widget_derived("PropAtributo", nuevaProp);
		nuevaProp->setAtributo(this);
		this->prop_lanzada = true;
		nuevaProp->show();
		return true;
	}
	return false;
}

void VistaAtributo::dibujar(Cairo::RefPtr<Cairo::Context> cr) {
	// Dibujo el cuadrado en el contexto
	// Ancho de linea arbitrario
	cr->set_line_width(1);
	if (!this->seleccionado) {
		cr->set_source_rgb(colorNegro.get_red_p(), colorNegro.get_green_p(),
				colorNegro.get_blue_p());
	} else {
		cr->set_source_rgb(colorDeSeleccion.get_red_p(), colorDeSeleccion.get_green_p(),
				colorDeSeleccion.get_blue_p());
	}

	double centro_x, centro_y, radio;

	radio = 3;

	centro_x = this->pos_ini_x + radio;
	centro_y = this->pos_ini_y + radio;

	this->pos_fin_x = centro_x + radio;
	this->pos_fin_y = centro_y + radio;

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

void VistaAtributo::calcularDimensionesAPartirDeTexto(Cairo::TextExtents * textExtents) {

}

bool VistaAtributo::esPuntoDeRedimension(double x, double y) {
	return false;
}

void VistaAtributo::setMouseArriba(double x, double y) {

}

void VistaAtributo::redimensionar(double x, double y) {

}

std::string VistaAtributo::getNombre() const {
	return this->atributo->getNombre();
}

bool VistaAtributo::contieneEsteComponente(Componente * c) {
	return this->atributo == c;
}

bool VistaAtributo::obtenerInterseccionConLinea(double pos_ini_x, double pos_ini_y,
		double pos_fin_x, double pos_fin_y, double & x, double & y) {
	double xInterseccion, yInterseccion;
	double centro_x, centro_y, radio;

	centro_x = (this->pos_fin_x + this->pos_ini_x) / 2;
	centro_y = (this->pos_fin_y + this->pos_ini_y) / 2;

	radio = this->pos_fin_x - centro_x;

	if (Geometria::hayInterseccionDeLineaConCirculo(pos_ini_x, pos_ini_y, pos_fin_x, pos_fin_y,
			centro_x, centro_y, radio, xInterseccion, yInterseccion)) {
		x = xInterseccion;
		y = yInterseccion;
		return true;
	}

	return false;
}

bool VistaAtributo		::agregarAtributo(VistaAtributo* atributo) {
	if (atributo == NULL) {
		return false;
	}
	this->vistaAtributos.push_back(atributo);
	return true;
}

bool VistaAtributo::quitarAtributo(VistaAtributo* atributo) {
	if (atributo == NULL) {
		return false;
	}
	remove(this->vistaAtributos.begin(), this->vistaAtributos.end(), atributo);
}

std::vector<VistaAtributo*>::iterator VistaAtributo::atributosBegin() {
	return this->vistaAtributos.begin();
}

std::vector<VistaAtributo*>::iterator VistaAtributo::atributosEnd() {
	return this->vistaAtributos.end();
}

Atributo* VistaAtributo::getAtributo(){
	return this->atributo;
}

void VistaAtributo::resetearLanzarProp(){
	this->prop_lanzada = false;
}
