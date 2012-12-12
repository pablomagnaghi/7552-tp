#include "Relacion.h"
#include "../validacion/ModeloVisitor.h"

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
	std::vector<UnionEntidadRelacion *>::iterator it_entidad;
	it_entidad = find(this->unionesAEntidad.begin(), this->unionesAEntidad.end(), entidadRelacion);
	this->unionesAEntidad.erase(it_entidad);
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
	std::vector<Atributo *>::iterator it_atributo;
	it_atributo = find(this->atributos.begin(), this->atributos.end(), atributo);
	this->atributos.erase(it_atributo);
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

void Relacion::accept(ModeloVisitor* modeloVisitor) {
	modeloVisitor->visit(this);
	std::vector<Atributo*>::iterator it = this->atributosBegin();
	while (it != this->atributosEnd()) {
		(*it)->accept(modeloVisitor);
		it++;
	}
}

// PERSISTENCIA COMP

// CARGAR
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
		if (nodo->getNombre() == "union_entidad_relacion") {
			UnionEntidadRelacion *unionEntidadRelacion = new UnionEntidadRelacion(nodo);
			this->agregarUnionAEntidad(unionEntidadRelacion);
		}
		if (nodo->getNombre() == "atributo") {
			Atributo *atributo = new Atributo(nodo);
			this->agregarAtributo(atributo);
		}
		*nodo = nodo->getHermano();
	}
}

// GUARDAR
XmlNodo Relacion::guardarXmlCOMP() {
	XmlNodo nodo("relacion");

	this->agregarPropiedadesXmlCOMP(&nodo);

	this->guardarUnionEntidadRelacionXmlCOMP(&nodo);
	this->guardarAtributosXmlCOMP(&nodo);

	return nodo;
}

void Relacion::agregarPropiedadesXmlCOMP(XmlNodo* nodo) {
	Componente::agregarPropiedadesXmlCOMP(nodo);
	if (this->tipo.size())
		nodo->setPropiedad("tipo", this->tipo);
}

void Relacion::guardarUnionEntidadRelacionXmlCOMP(XmlNodo *nodo) {
	std::vector<UnionEntidadRelacion*>::iterator i;

	for (i = this->unionesAEntidadBegin(); i != this->unionesAEntidadEnd(); ++i)
		nodo->agregarHijo((*i)->guardarXmlCOMP());
}

void Relacion::guardarAtributosXmlCOMP(XmlNodo *nodo) {
	std::vector<Atributo*>::iterator i;

	for (i = this->atributosBegin(); i != this->atributosEnd(); ++i)
		nodo->agregarHijo((*i)->guardarXmlCOMP());
}
