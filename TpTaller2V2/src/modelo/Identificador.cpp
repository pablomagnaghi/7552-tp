/* Identificador.cpp
 *  Created on: 30/04/2012
 *      Author: Gonzalo Ferrero 89657
 */

#include "Identificador.h"
#include "Relacion.h"

Identificador::Identificador() {

}

Identificador::~Identificador() {
	this->borrarAtributos();
	this->borrarRelaciones();
}

void Identificador::agregarAtributo(Atributo* atributo){
	this->atributos.push_back(atributo);
}

void Identificador::quitarAtributo(Atributo* atributo){
	std::vector<Atributo*>::iterator e;
	e = find(this->atributos.begin(), this->atributos.end(), atributo);
	if (*e == atributo){
		this->atributos.erase(e);
	}
}

void Identificador::agregarRelacion(Relacion* relacion){
	this->relaciones.push_back(relacion);
}

void Identificador::quitarRelacion(Relacion* relacion){
	std::vector<Relacion*>::iterator e;
	e = find(this->relaciones.begin(), this->relaciones.end(), relacion);
	if (*e == relacion){
		this->relaciones.erase(e);
	}
}

std::vector<Atributo*>::iterator Identificador::atributosBegin(){
	return this->atributos.begin();
}

std::vector<Atributo*>::iterator Identificador::atributosEnd(){
	return this->atributos.end();
}

std::vector<Relacion*>::iterator Identificador::relacionesBegin(){
	return this->relaciones.begin();
}

std::vector<Relacion*>::iterator Identificador::relacionesEnd(){
	return this->relaciones.end();
}


void Identificador::borrarAtributos() {
	std::vector<Atributo*>::iterator it = this->atributos.begin();
	while ( it != this->atributos.end() ) {
		delete (*it);
		it++;
	}
	this->atributos.clear();
}

void Identificador::borrarRelaciones() {
	std::vector<Relacion*>::iterator it = this->relaciones.begin();
	while ( it != this->relaciones.end() ) {
		delete (*it);
		it++;
	}
	this->relaciones.clear();
}

// PERSISTENCIA COMP
void Identificador::guardarAtributosXmlCOMP(XmlNodo *nodo) {
	std::vector<Atributo*>::iterator i;

	for(i = this->atributos.begin(); i != this->atributos.end(); ++i) {
		XmlNodo nodoAtributo("atributo");
		nodoAtributo.setContenido((*i)->getCodigo());
		nodo->agregarHijo(nodoAtributo);
	}
}

void Identificador::guardarRelacionesXmlCOMP(XmlNodo *nodo) {
	std::vector<Relacion*>::iterator i;

	for(i = this->relaciones.begin(); i != this->relaciones.end(); ++i) {
		XmlNodo nodoRelacion("relacion");
		nodoRelacion.setContenido((*i)->getCodigo());
		nodo->agregarHijo(nodoRelacion);
	}
}

XmlNodo Identificador::guardarXmlCOMP() {
	XmlNodo nodo("identificador");

	this->guardarAtributosXmlCOMP(&nodo);
	this->guardarRelacionesXmlCOMP(&nodo);

	return nodo;
}
