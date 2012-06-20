/* Entidad.cpp
 *  Created on: 30/04/2012
 *      Author: Gonzalo Ferrero 89657
 */

#include "Entidad.h"

Entidad::Entidad() {

}

Entidad::~Entidad() {

}

void Entidad::agregarRelacion(Relacion* relacion){
	this->relaciones.push_back(relacion);
}

void Entidad::quitarRelacion(Relacion* relacion){
	std::vector<Relacion*>::iterator e;
	e = find(this->relaciones.begin(), this->relaciones.end(), relacion);
	if (*e == relacion){
		this->relaciones.erase(e);
	}
}

std::vector<Relacion*>::iterator Entidad::relacionesBegin(){
	return this->relaciones.begin();
}

std::vector<Relacion*>::iterator Entidad::relacionesEnd(){
	return this->relaciones.end();
}

Relacion* Entidad::getRelacionByCodigo(int codigo){
	Relacion* relacion = NULL;
	std::vector<Relacion*>::iterator it = this->relaciones.begin();
	while (it != this->relaciones.end()) {
		if ((*it)->getCodigo() == codigo){
			relacion = *it;
		}
		it++;
	}
	return relacion;
}

void Entidad::setEsDebil(bool esDebil){
	this->esDebil = esDebil;
}

// PERSISTENCIA COMP
void Entidad::guardarRelacionesXmlCOMP(XmlNodo *nodo) {
	std::vector<Relacion*>::iterator i;

	for(i = this->relaciones.begin(); i != this->relaciones.end(); ++i) {
		XmlNodo nodoRelacion("relacion");
		nodoRelacion.setContenido((*i)->getCodigo());
		nodo->agregarHijo(nodoRelacion);
	}
}
