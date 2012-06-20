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

// PERSISTENCIA COMP

EntidadGlobal::EntidadGlobal(XmlNodo* nodo) {
	this->obtenerPropiedadesXmlCOMP(nodo);

	XmlNodo nodoAux = nodo->getHijo();

	this->obtenerComponentesXmlCOMP(&nodoAux);
}

void EntidadGlobal::obtenerPropiedadesXmlCOMP(XmlNodo* nodo) {
	this->diagramaAncestro = nodo->getPropiedad("diagrama_ancestro");
	this->codigoEntidadNueva = nodo->getPropiedadInt("codigo_entidad_nueva");
}

void EntidadGlobal::obtenerComponentesXmlCOMP(XmlNodo* nodo) {
	while (nodo->esValido()) {
		if (nodo->getNombre() == "relacion")	{
			//Relacion *relacion = new Relacion ();
			//relacion->setCodigo(nodo->getContenidoInt());
			//this->agregarRelacion(relacion);
		}
		*nodo = nodo->getHermano();
	}
}

void EntidadGlobal::agregarPropiedadesXmlCOMP(XmlNodo* nodo) {
	nodo->setPropiedad("diagrama_ancestro",this->diagramaAncestro);
	nodo->setPropiedad("codigo_entidad_nueva", this->codigoEntidadNueva);
}

XmlNodo EntidadGlobal::guardarXmlCOMP() {
	XmlNodo nodo("entidad_global");

	this->agregarPropiedadesXmlCOMP(&nodo);

	this->guardarRelacionesXmlCOMP(&nodo);

	return nodo;
}
