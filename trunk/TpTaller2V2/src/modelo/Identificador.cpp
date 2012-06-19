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

// PERSISTENCIA PARA DATOS

Identificador::Identificador(XmlNodo* nodo) {
	XmlNodo nodoAux = nodo->getHijo();

	this->obtenerComponentesXmlDER(&nodoAux);
}

void Identificador::obtenerComponentesXmlDER (XmlNodo* nodo) {
	while (nodo->esValido()) {
		if (nodo->getNombre() == "atributo") {
	  		Atributo *atributo = new Atributo ();
	  		atributo->setCodigo(nodo->getContenidoInt());
			this->agregarAtributo(atributo);
		}
		if (nodo->getNombre() == "relacion")	{
			Relacion *relacion = new Relacion();
			relacion->setCodigo(nodo->getContenidoInt());
			this->agregarRelacion(relacion);
		}

		*nodo = nodo->getHermano();
	}
}

void Identificador::guardarAtributosXmlDER(XmlNodo *nodo) {
	std::vector<Atributo*>::iterator i;

	for(i = this->atributos.begin(); i != this->atributos.end(); ++i) {
		XmlNodo nodoAtributo("atributo");
		nodoAtributo.setContenido((*i)->getCodigo());
		nodo->agregarHijo(nodoAtributo);
	}
}

void Identificador::guardarRelacionesXmlDER(XmlNodo *nodo) {
	std::vector<Relacion*>::iterator i;

	for(i = this->relaciones.begin(); i != this->relaciones.end(); ++i) {
		XmlNodo nodoRelacion("relacion");
		nodoRelacion.setContenido((*i)->getCodigo());
		nodo->agregarHijo(nodoRelacion);
	}
}

XmlNodo Identificador::guardarXmlDER() {
	XmlNodo nodo("identificador");

	this->guardarAtributosXmlDER(&nodo);
	this->guardarRelacionesXmlDER(&nodo);

	return nodo;
}
