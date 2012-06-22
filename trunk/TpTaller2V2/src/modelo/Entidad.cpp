/* Entidad.cpp
 *  Created on: 30/04/2012
 *      Author: Gonzalo Ferrero 89657
 */

#include "Entidad.h"

Entidad::Entidad() {

}

Entidad::~Entidad() {

}

void Entidad::agregarCodigoRelacion(int codigoRelacion){
	this->codigoRelaciones.push_back(codigoRelacion);
}

void Entidad::quitarCodigoRelacion(int codigoRelacion){
	std::vector<int>::iterator e;
	e = find(this->codigoRelaciones.begin(), this->codigoRelaciones.end(), codigoRelacion);
	if (*e == codigoRelacion){
		this->codigoRelaciones.erase(e);
	}
}

std::vector<int>::iterator Entidad::codigoRelacionesBegin(){
	return this->codigoRelaciones.begin();
}

std::vector<int>::iterator Entidad::codigoRelacionesEnd(){
	return this->codigoRelaciones.end();
}

void Entidad::setEsDebil(bool esDebil){
	this->esDebil = esDebil;
}

// PERSISTENCIA COMP

void Entidad::guardarRelacionesXmlCOMP(XmlNodo *nodo) {
	std::vector<int>::iterator i;

	for(i = this->codigoRelaciones.begin(); i != this->codigoRelaciones.end(); ++i) {
		XmlNodo nodoRelacion("relacion");
		nodoRelacion.setContenido(*i);
		nodo->agregarHijo(nodoRelacion);
	}
}
