#include "VistaEntidadGlobal.h"

VistaEntidadGlobal::VistaEntidadGlobal(EntidadGlobal * eg) {
	this->entidad = eg;
}

VistaEntidadGlobal::~VistaEntidadGlobal() {

}

std::string VistaEntidadGlobal::getNombre() const {
	return this->entidad->getNombre();
}

void VistaEntidadGlobal::setNombre(const std::string & nombre) {
	this->entidad->setNombre(nombre);
}

bool VistaEntidadGlobal::contieneEsteComponente(Componente * c) {
	return this->entidad == c;
}

bool VistaEntidadGlobal::lanzarProp() {
	return false;
}

void VistaEntidadGlobal::dibujar(Cairo::RefPtr<Cairo::Context> cr) {

}

bool VistaEntidadGlobal::esSeleccionado(double x, double y) {
	return false;
}

void VistaEntidadGlobal::finSeleccionado(double x, double y) {

}

bool VistaEntidadGlobal::contieneAEstePunto(double x, double y) {

	return false;
}

void VistaEntidadGlobal::calcularDimensionesAPartirDeTexto(Cairo::TextExtents * textExtents) {

}

bool VistaEntidadGlobal::esPuntoDeRedimension(double x, double y) {
	return false;
}

void VistaEntidadGlobal::setMouseArriba(double x, double y) {

}

void VistaEntidadGlobal::redimensionar(double x, double y) {

}

