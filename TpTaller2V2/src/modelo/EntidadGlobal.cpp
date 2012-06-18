/*
 * EntidadGlobal.cpp
 *
 *  Created on: 14/05/2012
 */

#include "EntidadGlobal.h"

EntidadGlobal::EntidadGlobal() {

}

EntidadGlobal::~EntidadGlobal() {
	std::vector<Relacion*>::iterator it = this->relaciones.begin();
	while ( it != this->relaciones.end() ) {
		delete (*it);
		it++;
	}
	this->relaciones.clear();
}

void EntidadGlobal::setDiagramaAncestro(const std::string diagramaAncestro){
	this->diagramaAncestro = diagramaAncestro;
}

std::string EntidadGlobal::getDiagramaAncestro() const{
	return this->diagramaAncestro;
}

void EntidadGlobal::setCodigoEntidadNueva(int codigoEntidadNueva) {
	this->codigoEntidadNueva = codigoEntidadNueva;
}

int EntidadGlobal::getCodigoEntidadNueva() const {
	return this->codigoEntidadNueva;
}

// PERSISTENCIA PARA DATOS

EntidadGlobal::EntidadGlobal(XmlNodo* nodo) {
	this->obtenerPropiedadesXmlDER(nodo);

	XmlNodo nodoAux = nodo->getHijo();

	this->obtenerComponentesXmlDER(&nodoAux);
}

void EntidadGlobal::obtenerPropiedadesXmlDER(XmlNodo* nodo) {
	this->diagramaAncestro = nodo->getPropiedad("diagrama_ancestro");
	this->codigoEntidadNueva = nodo->getPropiedadInt("codigo_entidad_nueva");
}

void EntidadGlobal::obtenerComponentesXmlDER (XmlNodo* nodo) {
	while (nodo->esValido()) {
		if (nodo->getNombre() == "relacion")	{
			Relacion *relacion = new Relacion (nodo);
			this->agregarRelacion(relacion);
		}
		*nodo = nodo->getHermano();
	}
}

void EntidadGlobal::agregarPropiedadesXmlDER(XmlNodo* nodo) {
	nodo->setPropiedad("diagrama_ancestro",this->diagramaAncestro);
	nodo->setPropiedad("codigo_entidad_nueva", this->codigoEntidadNueva);
}


XmlNodo EntidadGlobal::guardarXmlDER() {
	XmlNodo nodo("entidad_global");

	this->agregarPropiedadesXmlDER(&nodo);

	this->guardarRelacionesXmlDER(&nodo);

	return nodo;
}
