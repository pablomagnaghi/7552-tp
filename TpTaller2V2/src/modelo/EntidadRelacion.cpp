/*
 * EntidadRelacion.cpp
 *
 *  Created on: 20/05/2012
 */

#include "EntidadRelacion.h"

EntidadRelacion::EntidadRelacion() :
	cardinalidadMinima ("1"),
	cardinalidadMaxima ("1"){

}

EntidadRelacion::~EntidadRelacion() {

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


/* PERSISTENCIA DER

Atributo::Atributo(XmlNodo* nodo) {
	this->entidad.setCodigo(nodo->getPropiedad("entidad"));
	this->cardinalidadMinima = nodo->getPropiedad("cardinalidad_Minima");
	this->cardinalidadMaxima = nodo->getPropiedad("cardinalidad_Maxima");
	this->rol = nodo->getPropiedad("rol");
}


XmlNodo Entidad::guardarXmlDER() {
	XmlNodo nodo("entidad_nueva");

	nodo->setPropiedad("entidad",this->entidad.getCodigo());
	nodo->setPropiedad("cardinalidad_Minima",this->cardinalidadMinima);
	nodo->setPropiedad("cardinalidad_Maxima",this->cardinalidadMaxima);
	if (this->rol)
		nodo->setPropiedad("rol",this->rol);

	return nodo;
}
*/

