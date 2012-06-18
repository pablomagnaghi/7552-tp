/* Componente.cpp
 *  Created on: 30/04/2012
 *      Author: gonzalo
 */

#include "Componente.h"

Componente::~Componente() {

}

int Componente::getCodigo() const {
	return codigo;
}

void Componente::setCodigo(int codigo) {
	this->codigo = codigo;
}

std::string Componente::getNombre() const {
	return nombre;
}

void Componente::setNombre(const std::string& nombre) {
	this->nombre = nombre;
}

// PERSISTENCIA PARA DATOS
void Componente::agregarPropiedadesXmlDER(XmlNodo* nodo) {
	nodo->setPropiedad("codigo",this->codigo);
	nodo->setPropiedad("nombre",this->nombre);
}

void Componente::obtenerPropiedadesXmlDER(XmlNodo* nodo) {
	this->codigo = nodo->getPropiedadInt("codigo");
	this->nombre = nodo->getPropiedad("nombre");
}
