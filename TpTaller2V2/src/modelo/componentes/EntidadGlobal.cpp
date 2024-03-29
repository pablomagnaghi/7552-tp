#include "EntidadGlobal.h"
#include "../validacion/ModeloVisitor.h"

EntidadGlobal::EntidadGlobal() {

}

EntidadGlobal::~EntidadGlobal() {

}

void EntidadGlobal::setDiagramaAncestro(const std::string& diagramaAncestro){
	this->diagramaAncestro = diagramaAncestro;
}

std::string EntidadGlobal::getDiagramaAncestro() const{
	return this->diagramaAncestro;
}

void EntidadGlobal::setEntidadNueva(EntidadNueva * entidadNueva)throw (NullPointer){
	if(entidadNueva==NULL){
		throw NullPointer("Puntero nulo en setEntidadNueva en EntidadGlobal");
	}
	this->entidadNueva = entidadNueva;
}

EntidadNueva * EntidadGlobal::getEntidadNueva() const{
	return this->entidadNueva;
}

bool EntidadGlobal::getEsDebil(){
	return this->entidadNueva->getEsDebil();
}

int EntidadGlobal::getCodigoEntidadNueva() {
	return this->codigoEntidadNueva;
}

void EntidadGlobal::accept(ModeloVisitor* modeloVisitor){
	modeloVisitor->visit(this);
}

// PERSISTENCIA COMP

// CARGAR
EntidadGlobal::EntidadGlobal(XmlNodo* nodo) {
	this->obtenerPropiedadesXmlCOMP(nodo);
}

void EntidadGlobal::obtenerPropiedadesXmlCOMP(XmlNodo* nodo) {
	Componente::obtenerPropiedadesXmlCOMP(nodo);
	this->diagramaAncestro = nodo->getPropiedad("diagrama_ancestro");
	this->codigoEntidadNueva = nodo->getPropiedadInt("codigo_entidad_nueva");
}

// GUARDAR
XmlNodo EntidadGlobal::guardarXmlCOMP() {
	XmlNodo nodo("entidad_global");
	this->agregarPropiedadesXmlCOMP(&nodo);
	return nodo;
}

void EntidadGlobal::agregarPropiedadesXmlCOMP(XmlNodo* nodo) {
	Componente::agregarPropiedadesXmlCOMP(nodo);
	nodo->setPropiedad("diagrama_ancestro",this->diagramaAncestro);
	nodo->setPropiedad("codigo_entidad_nueva", this->entidadNueva->getCodigo());
}
