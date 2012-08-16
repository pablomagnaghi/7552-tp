#include "UnionEntidadRelacion.h"

UnionEntidadRelacion::UnionEntidadRelacion(Entidad * e, Relacion * r):
	entidad (e),
	relacion (r),
	cardinalidadMinima ("1"),
	cardinalidadMaxima ("1") {

	e->agregarUnionARelacion(this);
	r->agregarUnionAEntidad(this);
}

UnionEntidadRelacion::~UnionEntidadRelacion() {

}

const std::string UnionEntidadRelacion::getCardinalidadMinima() const {
	return this->cardinalidadMinima;
}

void UnionEntidadRelacion::setCardinalidadMinima(const std::string & cardinalidad) {
	this->cardinalidadMinima = cardinalidad;
}

const std::string UnionEntidadRelacion::getCardinalidadMaxima() const {
	return this->cardinalidadMaxima;
}

void UnionEntidadRelacion::setCardinalidadMaxima(const std::string & cardinalidad) {
	this->cardinalidadMaxima = cardinalidad;
}

const std::string UnionEntidadRelacion::getRol() const {
	return this->rol;
}

void UnionEntidadRelacion::setRol(const std::string & rol) {
	this->rol = rol;
}

Entidad * UnionEntidadRelacion::getEntidad(){
	return this->entidad;
}

Relacion * UnionEntidadRelacion::getRelacion(){
	return this->relacion;
}

// PERSISTENCIA COMP
/*
 EntidadRelacion::EntidadRelacion(XmlNodo* nodo) {
 this->codigoEntidad = nodo->getPropiedadInt("entidad");
 this->cardinalidadMinima = nodo->getPropiedad("cardinalidad_minima");
 this->cardinalidadMaxima = nodo->getPropiedad("cardinalidad_maxima");
 this->rol = nodo->getPropiedad("rol");
 }
*/

// GUARDAR
XmlNodo UnionEntidadRelacion::guardarXmlCOMP() {
	XmlNodo nodo("union_entidad_relacion ");

	Componente::agregarPropiedadesXmlCOMP(&nodo);

	nodo.setPropiedad("entidad",this->entidad->getCodigo());
	nodo.setPropiedad("cardinalidad_minima",this->cardinalidadMinima);
	nodo.setPropiedad("cardinalidad_maxima",this->cardinalidadMaxima);
	if (this->rol.size())
		nodo.setPropiedad("rol",this->rol);

	return nodo;
}

