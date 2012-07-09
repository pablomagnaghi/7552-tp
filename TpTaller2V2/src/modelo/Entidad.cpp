#include "Entidad.h"

Entidad::Entidad() {
	this->esDebil=false;
}

Entidad::~Entidad() {

}


void Entidad::setEsDebil(bool esDebil){
	this->esDebil = esDebil;
}

bool Entidad::getEsDebil(){
	return this->esDebil;
}

void Entidad::agregarUnion(UnionEntidadRelacion *u){
	this->unionesARelaciones.push_back(u);
}
void Entidad::removerUnion(UnionEntidadRelacion *u){
	// TODO REMOVER LA UNION
}

std::vector<UnionEntidadRelacion *> Entidad::getUniones(){
	 return this->unionesARelaciones;
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
