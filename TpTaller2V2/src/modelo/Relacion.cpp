/* Relacion.cpp
 *  Created on: 30/04/2012
 *      Author: Gonzalo Ferrero 89657
 */

#include "Relacion.h"

Relacion::Relacion() {

}

Relacion::~Relacion() {
	this->borrarAtributos();
	this->borrarEntidadesRelacion();
}

std::string Relacion::getTipo() const {
	return this->tipo;
}

void Relacion::setTipo(const std::string& tipo) {
	this->tipo = tipo;
}

void Relacion::agregarEntidadRelacion(UnionEntidadRelacion* entidadRelacion){
	this->entidadesRelacion.push_back(entidadRelacion);
}

void Relacion::quitarEntidadRelacion(UnionEntidadRelacion* entidadRelacion){
	std::vector<UnionEntidadRelacion*>::iterator e;
	e = find(this->entidadesRelacion.begin(), this->entidadesRelacion.end(), entidadRelacion);
	if (*e == entidadRelacion){
		this->entidadesRelacion.erase(e);
	}
}

void Relacion::agregarAtributo(Atributo* atributo){
	this->atributos.push_back(atributo);
}

void Relacion::quitarAtributo(Atributo* atributo){
	std::vector<Atributo*>::iterator e;
	e = find(this->atributos.begin(), this->atributos.end(), atributo);
	if (*e == atributo){
		this->atributos.erase(e);
	}
}

std::vector<UnionEntidadRelacion*>::iterator Relacion::entidadesRelacionBegin(){
	return this->entidadesRelacion.begin();
}

std::vector<UnionEntidadRelacion*>::iterator Relacion::entidadesRelacionEnd(){
	return this->entidadesRelacion.end();
}

std::vector<Atributo*>::iterator Relacion::atributosBegin(){
	return this->atributos.begin();
}

std::vector<Atributo*>::iterator Relacion::atributosEnd(){
	return this->atributos.end();
}

void Relacion::borrarAtributos(){
	std::vector<Atributo*>::iterator it = this->atributos.begin();
	while (it != this->atributos.end()){
		delete (*it);
		it++;
	}
	this->atributos.clear();
}

void Relacion::borrarEntidadesRelacion(){
	std::vector<UnionEntidadRelacion*>::iterator it = this->entidadesRelacion.begin();
	while (it != this->entidadesRelacion.end()){
		delete (*it);
		it++;
	}
	this->entidadesRelacion.clear();
}


// PERSISTENCIA COMP
/*
Relacion::Relacion(XmlNodo* nodo) {
	this->obtenerPropiedadesXmlCOMP(nodo);

	XmlNodo nodoAux = nodo->getHijo();

	this->obtenerComponentesXmlCOMP(&nodoAux);
}

void Relacion::obtenerPropiedadesXmlCOMP(XmlNodo* nodo) {
	Componente::obtenerPropiedadesXmlCOMP(nodo);
	this->tipo = nodo->getPropiedad("tipo");
}

void Relacion::obtenerComponentesXmlCOMP(XmlNodo* nodo) {
	while (nodo->esValido()) {
		if (nodo->getNombre() == "entidad_relacion") {
	  		EntidadRelacion *entidadRelacion = new EntidadRelacion(nodo);
			this->agregarEntidadRelacion(entidadRelacion);
		}
		if (nodo->getNombre() == "atributo") {
	  		Atributo *atributo = new Atributo(nodo);
			this->agregarAtributo(atributo);
		}
		*nodo = nodo->getHermano();
	}
}

void Relacion::agregarPropiedadesXmlCOMP(XmlNodo* nodo) {
	Componente::agregarPropiedadesXmlCOMP(nodo);
	if (this->tipo.size())
		nodo->setPropiedad("tipo",this->tipo);

}

void Relacion::guardarEntidadesRelacionesXmlCOMP(XmlNodo *nodo) {
	std::vector<EntidadRelacion*>::iterator i;

	for(i = this->entidadesRelacionBegin(); i != this->entidadesRelacionEnd(); ++i)
		nodo->agregarHijo((*i)->guardarXmlCOMP());
}

void Relacion::guardarAtributosXmlCOMP(XmlNodo *nodo) {
	std::vector<Atributo*>::iterator i;

	for(i = this->atributosBegin(); i != this->atributosEnd(); ++i)
		nodo->agregarHijo((*i)->guardarXmlCOMP());
}

XmlNodo Relacion::guardarXmlCOMP() {
	XmlNodo nodo("relacion");

	this->agregarPropiedadesXmlCOMP(&nodo);

	this->guardarEntidadesRelacionesXmlCOMP(&nodo);
	this->guardarAtributosXmlCOMP(&nodo);

	return nodo;
}
*/
