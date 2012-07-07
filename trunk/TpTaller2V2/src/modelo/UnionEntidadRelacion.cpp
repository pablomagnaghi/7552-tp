/*
 * EntidadRelacion.cpp
 *
 *  Created on: 20/05/2012
 */

#include "UnionEntidadRelacion.h"

UnionEntidadRelacion::UnionEntidadRelacion() :
	cardinalidadMinima ("1"),
	cardinalidadMaxima ("1"){

}

UnionEntidadRelacion::~UnionEntidadRelacion() {

}

int UnionEntidadRelacion::getCodigoEntidad() const {
	return this->codigoEntidad;
}

void UnionEntidadRelacion::setCodigoEntidad(int codigoEntidad) {
	this->codigoEntidad = codigoEntidad;
}

std::string UnionEntidadRelacion::getCardinalidadMinima() const {
	return this->cardinalidadMinima;
}

void UnionEntidadRelacion::setCardinalidadMinima(const std::string& cardinalidadMinima) {
	this->cardinalidadMinima = cardinalidadMinima;
}

std::string UnionEntidadRelacion::getCardinalidadMaxima() const {
	return this->cardinalidadMaxima;
}

void UnionEntidadRelacion::setCardinalidadMaxima(const std::string& cardinalidadMaxima) {
	this->cardinalidadMaxima = cardinalidadMaxima;
}

std::string UnionEntidadRelacion::getRol() const {
	return this->rol;
}

void UnionEntidadRelacion::setRol(const std::string& rol) {
	this->rol = rol;
}

// PERSISTENCIA COMP
/*
EntidadRelacion::EntidadRelacion(XmlNodo* nodo) {
	this->codigoEntidad = nodo->getPropiedadInt("entidad");
	this->cardinalidadMinima = nodo->getPropiedad("cardinalidad_minima");
	this->cardinalidadMaxima = nodo->getPropiedad("cardinalidad_maxima");
	this->rol = nodo->getPropiedad("rol");
}

XmlNodo EntidadRelacion::guardarXmlCOMP() {
	XmlNodo nodo("entidad_relacion");

	nodo.setPropiedad("entidad",this->codigoEntidad);
	nodo.setPropiedad("cardinalidad_minima",this->cardinalidadMinima);
	nodo.setPropiedad("cardinalidad_maxima",this->cardinalidadMaxima);
	if (this->rol.size())
		nodo.setPropiedad("rol",this->rol);

	return nodo;
}
*/
