#include "Entidad.h"

#include <algorithm>

Entidad::Entidad() {
}

Entidad::~Entidad() {

}

void Entidad::agregarUnion(UnionEntidadRelacion *u) throw (NullPointer) {
	if (u == NULL) {
		throw NullPointer("Puntero nulo en agregarUnion de Entidad");
	}
	this->unionesARelaciones.push_back(u);
}

void Entidad::removerUnion(UnionEntidadRelacion *u) throw (NullPointer) {
	if (u == NULL) {
		throw NullPointer("Puntero nulo en agregarUnion de Entidad");
	}
	remove(this->unionesARelaciones.begin(), this->unionesARelaciones.end(), u);
}

std::vector<UnionEntidadRelacion *>::iterator Entidad::unionesBegin() {
	return this->unionesARelaciones.begin();
}

std::vector<UnionEntidadRelacion *>::iterator Entidad::unionesEnd() {
	return this->unionesARelaciones.end();
}

void Entidad::setJerarquiaHija(Jerarquia * jHija) throw (NullPointer) {
	if (jHija == NULL) {
		throw NullPointer("Puntero nulo en setJerarquiaHija de Entidad");
	}
	this->jerarquiaHija = jHija;
}

Jerarquia * Entidad::getJerarquiaHija()const {
	return this->jerarquiaHija;
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
