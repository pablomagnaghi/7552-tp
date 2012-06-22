/* Identificador.cpp
 *  Created on: 30/04/2012
 *      Author: Gonzalo Ferrero 89657
 */

#include "Identificador.h"

Identificador::Identificador() {

}

Identificador::~Identificador() {

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

void Identificador::agregarCodigoRelacion(int codigoRelacion){
	this->codigoRelaciones.push_back(codigoRelacion);
}

void Identificador::quitarCodigoRelacion(int codigoRelacion){
	std::vector<int>::iterator e;
	e = find(this->codigoRelaciones.begin(), this->codigoRelaciones.end(), codigoRelacion);
	if (*e == codigoRelacion){
		this->codigoRelaciones.erase(e);
	}
}

std::vector<Atributo*>::iterator Identificador::atributosBegin(){
	return this->atributos.begin();
}

std::vector<Atributo*>::iterator Identificador::atributosEnd(){
	return this->atributos.end();
}

std::vector<int>::iterator Identificador::codigoRelacionesBegin(){
	return this->codigoRelaciones.begin();
}

std::vector<int>::iterator Identificador::codigoRelacionesEnd(){
	return this->codigoRelaciones.end();
}


void Identificador::borrarAtributos() {
	std::vector<Atributo*>::iterator it = this->atributos.begin();
	while ( it != this->atributos.end() ) {
		delete (*it);
		it++;
	}
	this->atributos.clear();
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
	std::vector<int>::iterator i;

	for(i = this->codigoRelaciones.begin(); i != this->codigoRelaciones.end(); ++i) {
		XmlNodo nodoRelacion("relacion");
		nodoRelacion.setContenido(*i);
		nodo->agregarHijo(nodoRelacion);
	}
}

XmlNodo Identificador::guardarXmlCOMP() {
	XmlNodo nodo("identificador");

	this->guardarAtributosXmlCOMP(&nodo);
	this->guardarRelacionesXmlCOMP(&nodo);

	return nodo;
}
