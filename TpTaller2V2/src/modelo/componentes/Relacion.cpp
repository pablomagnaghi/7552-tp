#include "Relacion.h"

#include <algorithm>

Relacion::Relacion() {

}

Relacion::~Relacion() {
	this->borrarAtributos();
	this->borrarUnionesAEntidad();
}

std::string Relacion::getTipo() const {
	return this->tipo;
}

void Relacion::setTipo(const std::string& tipo) {
	this->tipo = tipo;
}

void Relacion::agregarUnionAEntidad(UnionEntidadRelacion* entidadRelacion) throw (NullPointer) {
	if (entidadRelacion == NULL) {
		throw NullPointer("Puntero nulo en agregarUnionAEntidad en Relacion");
	}
	this->unionesAEntidad.push_back(entidadRelacion);
}

void Relacion::quitarUnionAEntidad(UnionEntidadRelacion* entidadRelacion) throw (NullPointer) {
	if (entidadRelacion == NULL) {
		throw NullPointer("Puntero nulo en quitarUnionAEntidad en Relacion");
	}
	remove(this->unionesAEntidad.begin(), this->unionesAEntidad.end(), entidadRelacion);
}

void Relacion::agregarAtributo(Atributo* atributo) throw (NullPointer) {
	if (atributo == NULL) {
		throw NullPointer("Puntero nulo en agregarAtributo en Relacion");
	}
	this->atributos.push_back(atributo);
}

void Relacion::quitarAtributo(Atributo* atributo) throw (NullPointer) {
	if (atributo == NULL) {
		throw NullPointer("Puntero nulo en quitarAtributo en Relacion");
	}
	remove(this->atributos.begin(), this->atributos.end(), atributo);
}

std::vector<UnionEntidadRelacion*>::iterator Relacion::unionesAEntidadBegin() {
	return this->unionesAEntidad.begin();
}

std::vector<UnionEntidadRelacion*>::iterator Relacion::unionesAEntidadEnd() {
	return this->unionesAEntidad.end();
}

std::vector<Atributo*>::iterator Relacion::atributosBegin() {
	return this->atributos.begin();
}

std::vector<Atributo*>::iterator Relacion::atributosEnd() {
	return this->atributos.end();
}

void Relacion::borrarAtributos() {
	std::vector<Atributo*>::iterator it = this->atributos.begin();
	while (it != this->atributos.end()) {
		delete (*it);
		it++;
	}
	this->atributos.clear();
}

void Relacion::borrarUnionesAEntidad() {
	std::vector<UnionEntidadRelacion*>::iterator it = this->unionesAEntidad.begin();
	while (it != this->unionesAEntidad.end()) {
		delete (*it);
		it++;
	}
	this->unionesAEntidad.clear();
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
