/* Jerarquia.cpp
 *  Created on: 30/04/2012
 *      Author: Gonzalo Ferrero 89657
 */

#include "Jerarquia.h"

Jerarquia::Jerarquia() {

}

Jerarquia::~Jerarquia() {

}

int Jerarquia::getCodigoEntidadGeneral() const {
	return this->codigoEntidadGeneral;
}

void Jerarquia::setCodigoEntidadGeneral(int codigoEntidadGeneral) {
	this->codigoEntidadGeneral = codigoEntidadGeneral;
}

void Jerarquia::agregarCodigoEntidadEspecializada(int codigoEntidadEspecializada){
	this->codigosEntidadesEspecializadas.push_back(codigoEntidadEspecializada);
}

void Jerarquia::quitarCodigoEntidadEspecializada(int codigoEntidadEspecializada){
	std::vector<int>::iterator e;
	e = find(this->codigosEntidadesEspecializadas.begin(), this->codigosEntidadesEspecializadas.end(), codigoEntidadEspecializada);
	if (*e == codigoEntidadEspecializada){
		this->codigosEntidadesEspecializadas.erase(e);
	}
}

std::string Jerarquia::getCobertura() const {
	return this->cobertura;
}

void Jerarquia::setCobertura(const std::string& cobertura) {
	this->cobertura = cobertura;
}

std::string Jerarquia::getInterseccion() const {
	return this->interseccion;
}

void Jerarquia::setInterseccion(const std::string& interseccion) {
	this->interseccion = interseccion;
}

std::vector<int>::iterator Jerarquia::codigosEntidadesEspecializadasBegin(){
	return this->codigosEntidadesEspecializadas.begin();
}

std::vector<int>::iterator Jerarquia::codigosEntidadesEspecializadasEnd(){
	return this->codigosEntidadesEspecializadas.end();
}

void Jerarquia::borrarEntidadesEspecializadas() {
	this->codigosEntidadesEspecializadas.clear();
}

// PERSISTENCIA COMP

Jerarquia::Jerarquia(XmlNodo* nodo) {
	this->obtenerPropiedadesXmlCOMP(nodo);

	XmlNodo nodoAux = nodo->getHijo();

	this->obtenerComponentesXmlCOMP(&nodoAux);
}

void Jerarquia::obtenerPropiedadesXmlCOMP(XmlNodo* nodo) {
	Componente::obtenerPropiedadesXmlCOMP(nodo);
	this->cobertura = nodo->getPropiedad("cobertura");
	this->interseccion = nodo->getPropiedad("interseccion");
}

void Jerarquia::obtenerComponentesXmlCOMP(XmlNodo* nodo) {
	while (nodo->esValido()) {
		if (nodo->getNombre() == "entidad_general") {
			this->codigoEntidadGeneral = nodo->getContenidoInt();
		}
		if (nodo->getNombre() == "entidad_especializada") {
			this->codigosEntidadesEspecializadas.push_back(nodo->getContenidoInt());
		}
		*nodo = nodo->getHermano();
	}
}

void Jerarquia::agregarPropiedadesXmlCOMP(XmlNodo* nodo) {
	Componente::agregarPropiedadesXmlCOMP(nodo);
	nodo->setPropiedad("cobertura",this->cobertura);
	nodo->setPropiedad("interseccion",this->interseccion);
}

void Jerarquia::agregarCodigoEntidadGeneralXmlCOMP(XmlNodo* nodo) {
	XmlNodo nodoEntidadGeneral("entidad_general");
	nodoEntidadGeneral.setContenido(this->codigoEntidadGeneral);
	nodo->agregarHijo(nodoEntidadGeneral);
}

void Jerarquia::agregarCodigosEntidadEspecializadasXmlCOMP(XmlNodo* nodo) {
	std::vector<int>::iterator i;

	for(i = this->codigosEntidadesEspecializadas.begin(); i != this->codigosEntidadesEspecializadas.end(); ++i) {
		XmlNodo nodoEntidadEspecializada("entidad_especializada");
		nodoEntidadEspecializada.setContenido((*i));
		nodo->agregarHijo(nodoEntidadEspecializada);
	}
}

XmlNodo Jerarquia::guardarXmlCOMP() {
	XmlNodo nodo("jerarquia");

	this->agregarPropiedadesXmlCOMP(&nodo);
	this->agregarCodigoEntidadGeneralXmlCOMP(&nodo);
	this->agregarCodigosEntidadEspecializadasXmlCOMP(&nodo);

	return nodo;
}
