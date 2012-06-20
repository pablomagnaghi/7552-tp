/* Atributo.cpp
 *  Created on: 30/04/2012
 *      Author: Gonzalo Ferrero 89657
 */

#include "Atributo.h"

Atributo::Atributo() :
	cardinalidadMinima ("1"),
	cardinalidadMaxima ("1") {
}

Atributo::~Atributo() {
	this->borrarAtributosDerivables();
}

std::string Atributo::getTipo() const {
	return this->tipo;
}

void Atributo::setTipo(const std::string& tipo) {
	this->tipo = tipo;
}

std::string Atributo::getExpresion() const {
	return this->expresion;
}

void Atributo::setExpresion(const std::string& expresion) {
	this->expresion = expresion;
}

std::string Atributo::getCardinalidadMinima() const {
	return this->cardinalidadMinima;
}

void Atributo::setCardinalidadMinima(const std::string& cardinalidadMinima) {
	this->cardinalidadMinima = cardinalidadMinima;
}

std::string Atributo::getCardinalidadMaxima() const {
	return this->cardinalidadMaxima;
}

void Atributo::setCardinalidadMaxima(const std::string& cardinalidadMaxima) {
	this->cardinalidadMaxima = cardinalidadMaxima;
}

void Atributo::agregarAtributoDerivable(Atributo* atributo) {
	this->atributosDerivables.push_back(atributo);
}

void Atributo::quitarAtributoDerivable(Atributo* atributo) {
	std::vector<Atributo*>::iterator e;
	e = find(this->atributosDerivables.begin(), this->atributosDerivables.end(), atributo);
	if (*e == atributo){
		this->atributosDerivables.erase(e);
	}
}

std::vector<Atributo*>::iterator Atributo::atributosDerivablesBegin() {
	return this->atributosDerivables.begin();
}

std::vector<Atributo*>::iterator Atributo::atributosDerivablesEnd() {
	return this->atributosDerivables.end();
}

void Atributo::borrarAtributosDerivables() {
	std::vector<Atributo*>::iterator it = this->atributosDerivables.begin();
	while ( it != this->atributosDerivables.end() ) {
		delete (*it);
		it++;
	}
	this->atributosDerivables.clear();
}

// PERSISTENCIA COMP

Atributo::Atributo(XmlNodo* nodo) {
	this->obtenerPropiedadesXmlCOMP(nodo);
	XmlNodo nodoAux = nodo->getHijo();

	this->obtenerComponentesXmlCOMP(&nodoAux);
}

void Atributo::obtenerPropiedadesXmlCOMP(XmlNodo* nodo) {
	Componente::obtenerPropiedadesXmlCOMP(nodo);

	this->tipo = nodo->getPropiedad("tipo");
	this->expresion = nodo->getPropiedad("expresion");
	this->cardinalidadMinima = nodo->getPropiedad("cardinalidad_minima");
	this->cardinalidadMaxima = nodo->getPropiedad("cardinalidad_maxima");
}

void Atributo::obtenerComponentesXmlCOMP(XmlNodo* nodo) {
	while (nodo->esValido()) {
		if (nodo->getNombre() == "atributo") {
	  		Atributo *atributo = new Atributo (nodo);
			this->agregarAtributoDerivable(atributo);
		}
		*nodo = nodo->getHermano();
	}
}

void Atributo::agregarPropiedadesXmlCOMP(XmlNodo* nodo) {
	Componente::agregarPropiedadesXmlCOMP(nodo);
	nodo->setPropiedad("tipo",this->tipo);
	// si son nulos los siguientes atributos, no poner
	if (this->expresion.size())
		nodo->setPropiedad("expresion",this->expresion);
	if (this->cardinalidadMinima.size())
		nodo->setPropiedad("cardinalidad_minima",this->cardinalidadMinima);
	if (this->cardinalidadMaxima.size())
		nodo->setPropiedad("cardinalidad_maxima",this->cardinalidadMaxima);
}

XmlNodo Atributo::guardarXmlCOMP() {
	XmlNodo nodo("atributo");

	this->agregarPropiedadesXmlCOMP(&nodo);

	std::vector<Atributo*>::iterator i;

	for(i = this->atributosDerivables.begin(); i != this->atributosDerivables.end(); ++i)
		nodo.agregarHijo((*i)->guardarXmlCOMP());

	return nodo;
}
