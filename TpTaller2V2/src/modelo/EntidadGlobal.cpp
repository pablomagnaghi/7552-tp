/*
 * EntidadGlobal.cpp
 *
 *  Created on: 14/05/2012
 */

#include "EntidadGlobal.h"

EntidadGlobal::EntidadGlobal() {

}

EntidadGlobal::~EntidadGlobal() {

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

/* PERSISTENCIA PARA DATOS

EntidadGlobal::EntidadGlobal(XmlNodo* nodo) {
	this->obtenerPropiedadesDER(nodo);

	XmlNodo nodoAux = nodo->getHijo();

	this->obtenerComponentesDER(&nodoAux);
}

void EntidadGlobal::obtenerPropiedadesDER(XmlNodo* nodo) {
	this->diagramaAncestro.setNombre( nodo->getPropiedad("diagrama_ancestro"));
	this->codigoEntidadNueva = nodo->getPropiedad("codigo_entidad_nueva");
}

void EntidadNueva::obtenerComponentesDER (XmlNodo* nodo) {
	while (nodo->esValido()) {
		if (nodo->getNombre() == "relacion")	{
			Relacion *relacion = new Relacion (nodo);
			this->agregarRelacion(relacion);
		}
		*nodo = nodo->getHermano();
	}
}

void EntidadGlobal::agregarPropiedadesDER(XmlNodo* nodo) {
	nodo->setPropiedad("diagrama_ancestro",this->diagramaAncetro.getNombre());
	nodo->setPropiedad("codigo_entidad_nueva", this->codigoEntidadNueva);
}


XmlNodo EntidadGlobal::guardarXmlDER() {
	XmlNodo nodo("entidad_nueva");

	this->agregarPropiedades(&nodo);

	this->guardarRelacionesXmlDER(&nodo);

	return nodo;
}
*/



