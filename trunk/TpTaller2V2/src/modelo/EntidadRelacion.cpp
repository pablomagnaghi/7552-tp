/*
 * EntidadRelacion.cpp
 *
 *  Created on: 20/05/2012
 */

#include "EntidadRelacion.h"

EntidadRelacion::EntidadRelacion() :
	cardinalidadMinima ("1"),
	cardinalidadMaxima ("1"){
	this->entidad = NULL;
}

EntidadRelacion::~EntidadRelacion() {
	if (this->entidad)
		delete this->entidad;
}

Entidad* EntidadRelacion::getEntidad() const {
	return this->entidad;
}

void EntidadRelacion::setEntidad(Entidad* entidad) {
	this->entidad = entidad;
}

std::string EntidadRelacion::getCardinalidadMinima() const {
	return this->cardinalidadMinima;
}

void EntidadRelacion::setCardinalidadMinima(const std::string cardinalidadMinima) {
	this->cardinalidadMinima = cardinalidadMinima;
}

std::string EntidadRelacion::getCardinalidadMaxima() const {
	return this->cardinalidadMaxima;
}

void EntidadRelacion::setCardinalidadMaxima(const std::string cardinalidadMaxima) {
	this->cardinalidadMaxima = cardinalidadMaxima;
}

std::string EntidadRelacion::getRol() const {
	return this->rol;
}

void EntidadRelacion::setRol(const std::string rol) {
	this->rol = rol;
}

// PERSISTENCIA DER

EntidadRelacion::EntidadRelacion(XmlNodo* nodo) {
	Entidad *entidad = new Entidad();
	entidad->setCodigo(nodo->getPropiedadInt("entidad"));
	this->entidad = entidad;
	this->cardinalidadMinima = nodo->getPropiedad("cardinalidad_minima");
	this->cardinalidadMaxima = nodo->getPropiedad("cardinalidad_maxima");
	this->rol = nodo->getPropiedad("rol");
}

XmlNodo EntidadRelacion::guardarXmlDER() {
	XmlNodo nodo("entidad_relacion");

	nodo.setPropiedad("entidad",this->entidad->getCodigo());
	nodo.setPropiedad("cardinalidad_minima",this->cardinalidadMinima);
	nodo.setPropiedad("cardinalidad_maxima",this->cardinalidadMaxima);
	if (this->rol.size())
		nodo.setPropiedad("rol",this->rol);

	return nodo;
}
