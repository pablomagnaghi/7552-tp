/* VistaLinea.cpp
 *  Created on: 12/07/2012
 *      Author: Gonzalo Ferrero 89657
 */

#include "VistaLinea.h"

VistaLinea::VistaLinea() {
	this->desde = NULL;
	this->hasta = NULL;
	// TODO Auto-generated constructor stub
}

VistaLinea::~VistaLinea() {
	// TODO Auto-generated destructor stub
#if DEBUG_QUITAR==1
	std::cout << "delete VistaLinea" << std::endl;
#endif
}

void VistaLinea::actualizar_coordenadas() {
	double x0, x1, x2, x3, y0, y1, y2, y3;
	if (this->desde != NULL) {
		this->desde->getposini(x0, y0);
		this->desde->getposfin(x1, y1);
	}
	if (this->hasta != NULL) {
		this->hasta->getposini(x2, y2);
		this->hasta->getposfin(x3, y3);
	}
	this->pos_ini_x = (x0 + x1) / 2;
	this->pos_fin_x = (x2 + x3) / 2;
	this->pos_ini_y = (y0 + y1) / 2;
	this->pos_fin_y = (y2 + y3) / 2;
}

void VistaLinea::dibujar(Cairo::RefPtr<Cairo::Context> cr) {
	cr->set_line_width(1);

	if (!this->seleccionado) {
		cr->set_source_rgb(colorNegro.get_red_p(), colorNegro.get_green_p(),
				colorNegro.get_blue_p());
	} else {
		cr->set_source_rgb(colorDeSeleccion.get_red_p(), colorDeSeleccion.get_green_p(),
				colorDeSeleccion.get_blue_p());
	}

	this->actualizar_coordenadas();

	this->desde->obtenerInterseccionConLinea(this->pos_ini_x, this->pos_ini_y, this->pos_fin_x,
			this->pos_fin_y, this->pos_ini_x, this->pos_ini_y);
	this->hasta->obtenerInterseccionConLinea(this->pos_ini_x, this->pos_ini_y, this->pos_fin_x,
			this->pos_fin_y, this->pos_fin_x, this->pos_fin_y);

	cr->move_to(this->pos_ini_x, this->pos_ini_y);
	cr->line_to(this->pos_fin_x, this->pos_fin_y);
	cr->stroke();

	if (!this->texto.empty()) {
		Cairo::TextExtents textExtents;
		cr->get_text_extents(this->texto, textExtents);
		double x_texto, y_texto;
		Geometria::obtenerPuntoDeDibujoDeTextoCentradoEnLinea(this->pos_ini_x, this->pos_ini_y,
				this->pos_fin_x, this->pos_fin_y, textExtents.width, textExtents.height, x_texto,
				y_texto);
		cr->move_to(x_texto, y_texto);
		cr->show_text(texto);
		cr->stroke();
	}
}

void VistaLinea::setComponenteDesde(VistaComponente *comp) {
	this->desde = comp;
	this->actualizar_coordenadas();
}

void VistaLinea::setComponenteHasta(VistaComponente *comp) {
	this->hasta = comp;
	this->actualizar_coordenadas();
}

//Lanza el asistente de prpiedades del objeto en cuestion.
bool VistaLinea::lanzarProp(bool esNuevo) {
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

std::string VistaLinea::getNombre() const {
	return "Linea";
}

bool VistaLinea::esContenidoPorEsteComponente(VistaComponente *) {
	return false;
}

bool VistaLinea::obtenerInterseccionConLinea(double pos_ini_x, double pos_ini_y, double pos_fin_x,
		double pos_fin_y, double & x, double & y) {
	return false;
}

void VistaLinea::setTexto(const std::string &txt) {
	this->texto = txt;
}
std::string VistaLinea::getTexto() {
	return this->texto;
}

void VistaLinea::setNombre(const std::string & nombre) {
}

void VistaLinea::eliminarComponentesAdyacentes(Diagrama * diagrama,
		std::vector<VistaComponente *> & componentes, VistaComponente * componenteEliminado) {
this->eliminando = true;
}

bool VistaLinea::hayQueEliminarlo(){
	return this->eliminando;
}

bool VistaLinea::hayInterseccion(VistaComponente * componente) {
	return false;
}

bool VistaLinea::probarInterseccionConRectangulo(double x0, double y0, double x1, double y1) {
	return false;
}
