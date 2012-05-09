/* Entidad.cpp
 *  Created on: 30/04/2012
 *      Author: Gonzalo Ferrero 89657
 */

#include "Entidad.h"

Entidad::Entidad() {

}

Entidad::~Entidad() {
	this->borrarComponentes();
	this->borrarIdentificadores();
}

std::string Entidad::getTipo() const {
	return tipo;
}

void Entidad::setTipo(const std::string& tipo) {
	this->tipo = tipo;
}

// componentes
void Entidad::agregarComponente(Componente *componente) {
	this->componentes.push_back(componente);
}

void Entidad::quitarComponente(Componente *componente) {
	std::vector<Componente*>::iterator e;

	e = find(this->componentes.begin(), this->componentes.end(), componente);
	if (*e == componente)
		this->componentes.erase(e);
}

std::vector<Componente*>::iterator Entidad::componenteBegin() {
	return this->componentes.begin();
}

std::vector<Componente*>::iterator Entidad::componenteEnd() {
	return this->componentes.end();
}

void Entidad::borrarComponentes() {
	std::vector<Componente*>::iterator it = this->componentes.begin();

	while ( it != this->componentes.end() ) {
		delete (*it);
		it++;
	}

	this->componentes.clear();
}


// identificadores
void Entidad::agregarIdentificador(Identificador *identificador) {
	this->identificadores.push_back(identificador);
}

void Entidad::quitarIdentificador(Identificador *identificador) {
	std::vector<Identificador*>::iterator e;

	e = find(this->identificadores.begin(), this->identificadores.end(), identificador);
	if (*e == identificador)
		this->identificadores.erase(e);
}

std::vector<Identificador*>::iterator Entidad::identificadorBegin() {
	return this->identificadores.begin();
}

std::vector<Identificador*>::iterator Entidad::identificadorEnd() {
	return this->identificadores.end();
}

void Entidad::borrarIdentificadores() {
	std::vector<Identificador*>::iterator it = this->identificadores.begin();

	while ( it != this->identificadores.end() ) {
		delete (*it);
		it++;
	}

	this->identificadores.clear();
}

/* PERSISTENCIA PARA DATOS

Entidad::Entidad(XmlNodo* nodo) {
	this->obtenerPropiedadesDER(nodo);

	XmlNodo nodoAux = nodo->getHijo();

	this->obtenerComponentesDER(&nodoAux);
}

void Entidad::obtenerComponentesDER (XmlNodo* nodo) {
	while (nodo->esValido()) {
		if (nodo->getNombre() == "atributo") {
	  		Componente *componente = new Atributo (nodo);
			this->agregarComponente(componente);
		}
		if (nodo->getNombre() == "identificador") {
			Componente *componente = new Identificador (nodo);
			this->agregarComponente(componente);
		}
		if (nodo->getNombre() == "relacion")	{
			Componente *componente = new Relacion (nodo);
			this->agregarComponente(componente);
		}
		if ( nodo->getNombre() == "jerarquia" )	{
			Componente *componente = new Jerarquia (nodo);
			this->agregarComponente(componente);
		}
		*nodo = nodo->getHermano();
	}
}

void Entidad::agregarPropiedadesDER(XmlNodo* nodo) {
	nodo->setPropiedad("tipo",this->tipo);
}

void Entidad::obtenerPropiedadesDER(XmlNodo* nodo) {
	this->tipo = nodo->getPropiedad("tipo");
}

void guardarComponentesXmlDER(XmlNodo *nodo) {
	std::vector<Componente*>::iterator i;

	for(i = this->componentes.begin(); i != this->componentes.end(); ++i)
		nodo->agregarHijo((*i)->guardarXml());
}

void guardarIdentificadoresXmlDER(XmlNodo *nodo) {
	std::vector<Identificador*>::iterator i;

	for(i = this->identificadores.begin(); i != this->identificadores.end(); ++i)
		nodo->agregarHijo((*i)->guardarXml());
}

XmlNodo Entidad::guardarXmlDER() {
	XmlNodo nodo("entidad_nueva");

	this->agregarPropiedades(&nodo);

	this->guardarComponentesXmlDER(&nodo);
	this->guardarIdentificadoresXmlDER(&nodo);

	return nodo;
}
*/
