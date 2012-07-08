#include "Entidad.h"

Entidad::Entidad() {

}

Entidad::~Entidad() {

}


void Entidad::setEsDebil(bool esDebil){
	this->esDebil = esDebil;
}

bool Entidad::getEsDebil(){
	return this->esDebil;
}

// PERSISTENCIA COMP
/*
void Entidad::guardarRelacionesXmlCOMP(XmlNodo *nodo) {
	std::vector<int>::iterator i;

	for(i = this->codigoRelaciones.begin(); i != this->codigoRelaciones.end(); ++i) {
		XmlNodo nodoRelacion("relacion");
		nodoRelacion.setContenido(*i);
		nodo->agregarHijo(nodoRelacion);
	}
}
*/
