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
