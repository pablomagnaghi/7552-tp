/* Atributo.cpp
 *  Created on: 30/04/2012
 *      Author: Gonzalo Ferrero 89657
 */

#include "Atributo.h"

Atributo::Atributo() {

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

void Atributo::agregarAtributoDerivable(Atributo *atributo) {
	this->atributosDerivables.push_back(atributo);
}

void Atributo::quitarAtributoDerivable(Atributo *atributo) {
	std::vector<Atributo*>::iterator e;

		e = find(this->atributosDerivables.begin(), this->atributosDerivables.end(), atributo);
		if (*e == atributo)
			this->atributosDerivables.erase(e);
}

std::vector<Atributo*>::iterator Atributo::atributoDerivableBegin() {
	return this->atributosDerivables.begin();
}

std::vector<Atributo*>::iterator Atributo::atributoDerivableEnd() {
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

/* PERSISTENCIA PARA DATOS

Atributo::Atributo(XmlNodo* nodo) {
	this->obtenerPropiedadesDER(nodo);

	XmlNodo nodoAux = nodo->getHijo();

	this->obtenerComponentesDER(&nodoAux);
}

void Entidad::obtenerComponentesDER (XmlNodo* nodo) {
	while (nodo->esValido()) {
		if (nodo->getNombre() == "atributo") {
	  		Atributo *atributo = new Atributo (nodo);
			this->agregarAtributoDerivable(atributo);
		}
		*nodo = nodo->getHermano();
	}
}

void Atributo::agregarPropiedadesDER(XmlNodo* nodo) {
	nodo->setPropiedad("tipo",this->tipo);
	// VER si son nulos los siguientes quizas no poner
	nodo->setPropiedad("expresion",this->expresion);
	nodo->setPropiedad("cardinalidad_minima",this->cardinalidadMinima);
	nodo->setPropiedad("cardinalidad_maxima",this->cardinalidadMaxima);
}

void Atributo::obtenerPropiedadesDER(XmlNodo* nodo) {
	this->tipo = nodo->getPropiedad("tipo");
	this->expresion = nodo->getPropiedad("tipo");
	this->cardinalidadMinima = nodo->getPropiedad("cardinalidad_Minima");
	this->cardinalidadMaxima = nodo->getPropiedad("cardinalidad_Maxima");
}


XmlNodo Entidad::guardarXmlDER() {
	XmlNodo nodo("entidad_nueva");

	this->agregarPropiedades(&nodo);

	std::vector<Atributo*>::iterator i;

	for(i = this->atributo.begin(); i != this->atributo.end(); ++i)
		nodo->agregarHijo((*i)->guardarXml());

	return nodo;
}
*/
