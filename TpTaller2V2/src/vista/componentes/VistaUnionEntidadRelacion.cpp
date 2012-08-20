#include "VistaUnionEntidadRelacion.h"

#include <iostream>
using namespace std;

VistaUnionEntidadRelacion::VistaUnionEntidadRelacion(UnionEntidadRelacion * unionModelo,
		VistaEntidadNueva * vEntidad, VistaRelacion * vRelacion) {

	this->unionModelo = unionModelo;
	this->entidad = vEntidad;
	this->relacion = vRelacion;
	this->dibujar_cardinalidad = true;

	// Persistencia REP
	this->codigoREP = unionModelo->getCodigo();
}

VistaUnionEntidadRelacion::~VistaUnionEntidadRelacion() {
	// TODO Auto-generated destructor stub
}

void VistaUnionEntidadRelacion::actualizar_coordenadas() {
	double x0, x1, x2, x3, y0, y1, y2, y3;
	this->entidad->getposini(x0, y0);
	this->entidad->getposfin(x1, y1);
	this->relacion->getposini(x2, y2);
	this->relacion->getposfin(x3, y3);

	this->pos_ini_x = (x0 + x1) / 2;
	this->pos_fin_x = (x2 + x3) / 2;
	this->pos_ini_y = (y0 + y1) / 2;
	this->pos_fin_y = (y2 + y3) / 2;
}

std::string VistaUnionEntidadRelacion::getNombre() const {
	return this->unionModelo->getNombre();
}

bool VistaUnionEntidadRelacion::lanzarProp() {
	return false;
}

void VistaUnionEntidadRelacion::dibujar(Cairo::RefPtr<Cairo::Context> cr) {
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
	double x0, x1, x2, x3, y0, y1, y2, y3;
	this->entidad->getposini(x0, y0);
	this->entidad->getposfin(x1, y1);
	this->relacion->getposini(x2, y2);
	this->relacion->getposfin(x3, y3);

	this->actualizar_coordenadas();

	if (!this->entidad->esDebil()) {

		this->entidad->obtenerInterseccionConLinea(this->pos_ini_x, this->pos_ini_y,
				this->pos_fin_x, this->pos_fin_y, this->pos_ini_x, this->pos_ini_y);
		this->relacion->obtenerInterseccionConLinea(this->pos_ini_x, this->pos_ini_y,
				this->pos_fin_x, this->pos_fin_y, this->pos_fin_x, this->pos_fin_y);

		cr->move_to(this->pos_ini_x, this->pos_ini_y);
		cr->line_to(this->pos_fin_x, this->pos_fin_y);

		cr->stroke();
	} else {

		Geometria::obtenerLineasParalelas(this->pos_ini_x, this->pos_ini_y, this->pos_fin_x,
				this->pos_fin_y, 1.6, x0, y0, x1, y1, x2, y2, x3, y3);

		this->entidad->obtenerInterseccionConLinea(x0, y0, x1, y1, x0, y0);
		this->relacion->obtenerInterseccionConLinea(x0, y0, x1, y1, x1, y1);
		this->entidad->obtenerInterseccionConLinea(x2, y2, x3, y3, x2, y2);
		this->relacion->obtenerInterseccionConLinea(x2, y2, x3, y3, x3, y3);

		cr->move_to(x0, y0);
		cr->line_to(x1, y1);
		cr->stroke();

		cr->move_to(x2, y2);
		cr->line_to(x3, y3);
		cr->stroke();

	}

	if (this->dibujar_cardinalidad) {
		Cairo::TextExtents textExtents;
		std::string texto;
		texto = "(";
		texto.append(this->unionModelo->getCardinalidadMinima());
		texto.append(";");
		texto.append(this->unionModelo->getCardinalidadMaxima());
		texto.append(")");
		if (this->unionModelo->getRol() != "") {
			texto.append(":");
			texto.append(this->unionModelo->getRol());
		}
		cr->get_text_extents(texto, textExtents);
		double x_texto, y_texto;
		Geometria::obtenerPuntoDeDibujoDeTextoCentradoEnLinea(this->pos_ini_x, this->pos_ini_y, this->pos_fin_x,
				this->pos_fin_y, textExtents.width, textExtents.height, x_texto, y_texto);
		cr->move_to(x_texto, y_texto);
		cr->show_text(texto);
		cr->stroke();

	}
}

bool VistaUnionEntidadRelacion::esSeleccionado(double x, double y) {
	return false;
}

void VistaUnionEntidadRelacion::finSeleccionado(double x, double y) {

}

bool VistaUnionEntidadRelacion::contieneAEstePunto(double x, double y) {
	return false;
}

void VistaUnionEntidadRelacion::calcularDimensionesAPartirDeTexto(Cairo::TextExtents * textExtents) {

}

bool VistaUnionEntidadRelacion::esPuntoDeRedimension(double x, double y) {
	return false;
}

void VistaUnionEntidadRelacion::setMouseArriba(double x, double y) {

}

void VistaUnionEntidadRelacion::redimensionar(double x, double y) {

}

bool VistaUnionEntidadRelacion::contieneEsteComponente(Componente *) {
	return false;
}

bool VistaUnionEntidadRelacion::obtenerInterseccionConLinea(double pos_ini_x, double pos_ini_y,
		double pos_fin_x, double pos_fin_y, double & x, double & y) {
	return false;
}

void VistaUnionEntidadRelacion::getPuntoMedioLinea(double &x, double &y) {
	this->actualizar_coordenadas();
	x = (this->pos_ini_x + this->pos_fin_x) / 2;
	y = (this->pos_ini_y + this->pos_fin_y) / 2;
}

