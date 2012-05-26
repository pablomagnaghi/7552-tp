/*
 * EntidadNueva.cpp
 *
 *  Created on: 25/05/2012
 */

#include "EntidadNueva.h"
#include "Jerarquia.h"

EntidadNueva::EntidadNueva() {

}

EntidadNueva::~EntidadNueva() {
	this->borrarAtributos();
	this->borrarIdentificadores();
}

std::string EntidadNueva::getTipo() const {
	return tipo;
}

void EntidadNueva::setTipo(const std::string& tipo) {
	this->tipo = tipo;
}

void EntidadNueva::agregarAtributo(Atributo* atributo) {
	this->atributos.push_back(atributo);
}

void EntidadNueva::quitarAtributo(Atributo* atributo) {
	std::vector<Atributo*>::iterator e;
	e = find(this->atributos.begin(), this->atributos.end(), atributo);
	if (*e == atributo){
		this->atributos.erase(e);
	}
}

void EntidadNueva::agregarJerarquia(Jerarquia* jerarquia) {
	this->jerarquias.push_back(jerarquia);
}

void EntidadNueva::quitarJerarquia(Jerarquia* jerarquia) {
	std::vector<Jerarquia*>::iterator e;
	e = find(this->jerarquias.begin(), this->jerarquias.end(), jerarquia);
	if (*e == jerarquia){
		this->jerarquias.erase(e);
	}
}

void EntidadNueva::agregarIdentificador(Identificador *identificador) {
	this->identificadores.push_back(identificador);
}

void EntidadNueva::quitarIdentificador(Identificador *identificador) {
	std::vector<Identificador*>::iterator e;
	e = find(this->identificadores.begin(), this->identificadores.end(), identificador);
	if (*e == identificador){
		this->identificadores.erase(e);
	}
}

std::vector<Atributo*>::iterator EntidadNueva::atributosBegin() {
	return this->atributos.begin();
}

std::vector<Atributo*>::iterator EntidadNueva::atributosEnd() {
	return this->atributos.end();
}

std::vector<Jerarquia*>::iterator EntidadNueva::jerarquiasBegin() {
	return this->jerarquias.begin();
}

std::vector<Jerarquia*>::iterator EntidadNueva::jerarquiasEnd() {
	return this->jerarquias.end();
}

std::vector<Identificador*>::iterator EntidadNueva::identificadoresBegin() {
	return this->identificadores.begin();
}

std::vector<Identificador*>::iterator EntidadNueva::identificadoresEnd() {
	return this->identificadores.end();
}

void EntidadNueva::borrarAtributos() {
	std::vector<Atributo*>::iterator it = this->atributos.begin();
	while ( it != this->atributos.end() ) {
		delete (*it);
		it++;
	}
	this->atributos.clear();
}

void EntidadNueva::borrarIdentificadores() {
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
