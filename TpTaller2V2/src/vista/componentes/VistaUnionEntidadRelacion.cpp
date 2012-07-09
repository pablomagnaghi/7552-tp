#include "VistaUnionEntidadRelacion.h"

VistaUnionEntidadRelacion::VistaUnionEntidadRelacion(
		UnionEntidadRelacion * unionModelo, VistaEntidadNueva * vEntidad,
		VistaRelacion * vRelacion) {

	this->unionModelo = unionModelo;
	this->entidad = vEntidad;
	this->relacion = vRelacion;
}

VistaUnionEntidadRelacion::~VistaUnionEntidadRelacion() {
	// TODO Auto-generated destructor stub
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
		cr->set_source_rgb(colorDeSeleccion.get_red_p(),
				colorDeSeleccion.get_green_p(), colorDeSeleccion.get_blue_p());
	}
	double x0, x1, x2, x3, y0, y1, y2, y3;
	this->entidad->getposini(x0, y0);
	this->entidad->getposfin(x1, y1);
	this->relacion->getposini(x2, y2);
	this->relacion->getposfin(x3, y3);

	this->pos_ini_x = (x0 + x1) / 2;
	this->pos_fin_x = (x2 + x3) / 2;
	this->pos_ini_y = (y0 + y1) / 2;
	this->pos_fin_y = (y2 + y3) / 2;

	cr->move_to(this->pos_ini_x, this->pos_ini_y);
	cr->line_to(this->pos_fin_x, this->pos_fin_y);

	//cr->rectangle(this->pos_ini_x, this->pos_ini_y, this->pos_fin_x
	//	- this->pos_ini_x, this->pos_fin_y - this->pos_ini_y);
	cr->stroke();
}

bool VistaUnionEntidadRelacion::esSeleccionado(double x, double y) {
	return false;
}

void VistaUnionEntidadRelacion::finSeleccionado(double x, double y) {

}

bool VistaUnionEntidadRelacion::contieneAEstePunto(double x, double y) {
	return false;
}

void VistaUnionEntidadRelacion::calcularDimensionesAPartirDeTexto(
		Cairo::TextExtents * textExtents) {

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
