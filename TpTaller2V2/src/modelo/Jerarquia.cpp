/* Jerarquia.cpp
 *  Created on: 30/04/2012
 *      Author: Gonzalo Ferrero 89657
 */

#include "Jerarquia.h"

Jerarquia::Jerarquia() {
	this->entidadGeneral = NULL;
}

Jerarquia::~Jerarquia() {
	if (this->entidadGeneral)
		delete this->entidadGeneral;
	this->borrarEntidadesEspecializadas();
}

EntidadNueva* Jerarquia::getEntidadGeneral() const {
	return this->entidadGeneral;
}

void Jerarquia::setEntidadGeneral(EntidadNueva* entidadGeneral) {
	this->entidadGeneral = entidadGeneral;
}

void Jerarquia::agregarEntidadEspecializada(EntidadNueva* entidadEspecializada){
	this->entidadesEspecializadas.push_back(entidadEspecializada);
}

void Jerarquia::quitarEntidadEspecializada(EntidadNueva* entidadEspecializada){
	std::vector<EntidadNueva*>::iterator e;
	e = find(this->entidadesEspecializadas.begin(), this->entidadesEspecializadas.end(), entidadEspecializada);
	if (*e == entidadEspecializada){
		this->entidadesEspecializadas.erase(e);
	}
}

std::string Jerarquia::getCobertura() const {
	return this->cobertura;
}

void Jerarquia::setCobertura(const std::string cobertura) {
	this->cobertura = cobertura;
}

std::string Jerarquia::getInterseccion() const {
	return this->interseccion;
}

void Jerarquia::setInterseccion(const std::string interseccion) {
	this->interseccion = interseccion;
}

std::vector<EntidadNueva*>::iterator Jerarquia::entidadesEspecializadasBegin(){
	return this->entidadesEspecializadas.begin();
}

std::vector<EntidadNueva*>::iterator Jerarquia::entidadesEspecializadasEnd(){
	return this->entidadesEspecializadas.end();
}

void Jerarquia::borrarEntidadesEspecializadas() {
	std::vector<EntidadNueva*>::iterator it = this->entidadesEspecializadas.begin();
	while ( it != this->entidadesEspecializadas.end() ) {
		delete (*it);
		it++;
	}
	this->entidadesEspecializadas.clear();
}

// PERSISTENCIA COMP

Jerarquia::Jerarquia(XmlNodo* nodo) {
	this->obtenerPropiedadesXmlCOMP(nodo);

	XmlNodo nodoAux = nodo->getHijo();

	this->obtenerComponentesXmlCOMP(&nodoAux);
}

void Jerarquia::obtenerPropiedadesXmlCOMP(XmlNodo* nodo) {
	this->cobertura = nodo->getPropiedad("cobertura");
	this->interseccion = nodo->getPropiedad("interseccion");
}

void Jerarquia::obtenerComponentesXmlCOMP(XmlNodo* nodo) {
	while (nodo->esValido()) {
		if (nodo->getNombre() == "entidad_general") {
	  		EntidadNueva *entidadGeneral = new EntidadNueva(nodo);
	  		this->entidadGeneral = entidadGeneral;
		}
		if (nodo->getNombre() == "entidad_especializada") {
	  		EntidadNueva *entidadNueva = new EntidadNueva(nodo);
			this->agregarEntidadEspecializada(entidadNueva);
		}
		*nodo = nodo->getHermano();
	}
}

void Jerarquia::agregarPropiedadesXmlCOMP(XmlNodo* nodo) {
	nodo->setPropiedad("cobertura",this->cobertura);
	nodo->setPropiedad("interseccion",this->interseccion);
}

XmlNodo Jerarquia::guardarXmlCOMP() {
	XmlNodo nodo("jerarquia");

	this->agregarPropiedadesXmlCOMP(&nodo);

	std::vector<EntidadNueva*>::iterator i;

	nodo.agregarHijo(entidadGeneral->guardarXmlCOMP());

	for(i = this->entidadesEspecializadas.begin(); i != this->entidadesEspecializadas.end(); ++i)
		nodo.agregarHijo((*i)->guardarXmlCOMP());

	return nodo;
}
