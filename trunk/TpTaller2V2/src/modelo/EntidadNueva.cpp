/*
 * EntidadNueva.cpp
 *
 *  Created on: 25/05/2012
 */

#include "EntidadNueva.h"

EntidadNueva::EntidadNueva() {

}

EntidadNueva::~EntidadNueva() {
	this->borrarAtributos();
	this->borrarIdentificadores();
}

std::string EntidadNueva::getTipo() const {
	return tipo;
}

void EntidadNueva::setTipo(const std::string& tipo) {
	this->tipo = tipo;
}

void EntidadNueva::agregarAtributo(Atributo* atributo) {
	this->atributos.push_back(atributo);
}

void EntidadNueva::quitarAtributo(Atributo* atributo) {
	std::vector<Atributo*>::iterator e;
	e = find(this->atributos.begin(), this->atributos.end(), atributo);
	if (*e == atributo){
		this->atributos.erase(e);
	}
}

void EntidadNueva::agregarCodigoJerarquia(int codigoJerarquia) {
	this->codigoJerarquias.push_back(codigoJerarquia);
}

void EntidadNueva::quitarCodigoJerarquia(int codigoJerarquia) {
	std::vector<int>::iterator e;
	e = find(this->codigoJerarquias.begin(), this->codigoJerarquias.end(), codigoJerarquia);
	if (*e == codigoJerarquia){
		this->codigoJerarquias.erase(e);
	}
}

void EntidadNueva::agregarIdentificador(Identificador *identificador) {
	this->identificadores.push_back(identificador);
}

void EntidadNueva::quitarIdentificador(Identificador *identificador) {
	std::vector<Identificador*>::iterator e;
	e = find(this->identificadores.begin(), this->identificadores.end(), identificador);
	if (*e == identificador){
		this->identificadores.erase(e);
	}
}

std::vector<Atributo*>::iterator EntidadNueva::atributosBegin() {
	return this->atributos.begin();
}

std::vector<Atributo*>::iterator EntidadNueva::atributosEnd() {
	return this->atributos.end();
}

std::vector<int>::iterator EntidadNueva::codigoJerarquiasBegin() {
	return this->codigoJerarquias.begin();
}

std::vector<int>::iterator EntidadNueva::codigoJerarquiasEnd() {
	return this->codigoJerarquias.end();
}

std::vector<Identificador*>::iterator EntidadNueva::identificadoresBegin() {
	return this->identificadores.begin();
}

std::vector<Identificador*>::iterator EntidadNueva::identificadoresEnd() {
	return this->identificadores.end();
}

void EntidadNueva::borrarAtributos() {
	std::vector<Atributo*>::iterator it = this->atributos.begin();
	while ( it != this->atributos.end() ) {
		delete (*it);
		it++;
	}
	this->atributos.clear();
}

void EntidadNueva::borrarIdentificadores() {
	std::vector<Identificador*>::iterator it = this->identificadores.begin();
	while ( it != this->identificadores.end() ) {
		delete (*it);
		it++;
	}
	this->identificadores.clear();
}

Atributo* EntidadNueva::getAtributoByCodigo(int codigo){
	Atributo* atributo = NULL;
	std::vector<Atributo*>::iterator it = this->atributos.begin();
	while (it != this->atributos.end()) {
		if ((*it)->getCodigo() == codigo){
			atributo = *it;
		}
		it++;
	}
	return atributo;
}

// PERSISTENCIA COMP

EntidadNueva::EntidadNueva(XmlNodo* nodo) {

	this->obtenerPropiedadesXmlCOMP(nodo);

	XmlNodo nodoAux = nodo->getHijo();

	this->obtenerComponentesXmlCOMP(&nodoAux);
}

void EntidadNueva::obtenerComponentesIdentificadorXmlCOMP(Identificador* identificador, XmlNodo* nodo) {
	XmlNodo nodoAux = nodo->getHijo();

	while (nodoAux.esValido()) {
		if (nodoAux.getNombre() == "atributo") {
			identificador->agregarAtributo(this->getAtributoByCodigo(nodoAux.getContenidoInt()));
		}
		if (nodoAux.getNombre() == "relacion")	{
			identificador->agregarCodigoRelacion(nodoAux.getContenidoInt());
		}
		nodoAux = nodoAux.getHermano();
	}
}

void EntidadNueva::obtenerComponentesXmlCOMP(XmlNodo* nodo) {
	while (nodo->esValido()) {
		if (nodo->getNombre() == "atributo") {
	  		Atributo *atributo = new Atributo(nodo);
			this->agregarAtributo(atributo);
		}
		if (nodo->getNombre() == "identificador") {
			Identificador *identificador = new Identificador();
			this->obtenerComponentesIdentificadorXmlCOMP(identificador, nodo);
			this->agregarIdentificador(identificador);
		}
		if (nodo->getNombre() == "relacion")	{
			this->agregarCodigoRelacion(nodo->getContenidoInt());
		}
		if ( nodo->getNombre() == "jerarquia" )	{
			this->agregarCodigoJerarquia(nodo->getContenidoInt());
		}
		*nodo = nodo->getHermano();
	}
}

void EntidadNueva::agregarPropiedadesXmlCOMP(XmlNodo* nodo) {
	Componente::agregarPropiedadesXmlCOMP(nodo);
	nodo->setPropiedad("tipo",this->tipo);
}

void EntidadNueva::obtenerPropiedadesXmlCOMP(XmlNodo* nodo) {
	Componente::obtenerPropiedadesXmlCOMP(nodo);
	this->tipo = nodo->getPropiedad("tipo");
}

void EntidadNueva::guardarAtributosXmlCOMP(XmlNodo *nodo) {
	std::vector<Atributo*>::iterator i;

	for(i = this->atributos.begin(); i != this->atributos.end(); ++i)
		nodo->agregarHijo((*i)->guardarXmlCOMP());
}

void EntidadNueva::guardarIdentificadoresXmlCOMP(XmlNodo *nodo) {
	std::vector<Identificador*>::iterator i;

	for(i = this->identificadores.begin(); i != this->identificadores.end(); ++i)
		nodo->agregarHijo((*i)->guardarXmlCOMP());
}

void EntidadNueva::guardarJerarquiasXmlCOMP(XmlNodo *nodo) {
	std::vector<int>::iterator i;

	for(i = this->codigoJerarquias.begin(); i != this->codigoJerarquias.end(); ++i) {
		XmlNodo nodoJerarquia("jerarquia");
		nodoJerarquia.setContenido(*i);
		nodo->agregarHijo(nodoJerarquia);
	}
}

XmlNodo EntidadNueva::guardarXmlCOMP() {
	XmlNodo nodo("entidad_nueva");

	this->agregarPropiedadesXmlCOMP(&nodo);

	this->guardarAtributosXmlCOMP(&nodo);
	this->guardarIdentificadoresXmlCOMP(&nodo);
	this->guardarRelacionesXmlCOMP(&nodo);
	this->guardarJerarquiasXmlCOMP(&nodo);

	return nodo;
}
