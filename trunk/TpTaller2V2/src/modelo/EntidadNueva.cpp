/*
 * EntidadNueva.cpp
 *
 *  Created on: 25/05/2012
 */

#include "EntidadNueva.h"
#include "Jerarquia.h"

EntidadNueva::EntidadNueva() {

}

EntidadNueva::~EntidadNueva() {
	this->borrarAtributos();
	this->borrarIdentificadores();
	this->borrarRelaciones();
	this->borrarJerarquias();
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

void EntidadNueva::agregarJerarquia(Jerarquia* jerarquia) {
	this->jerarquias.push_back(jerarquia);
}

void EntidadNueva::quitarJerarquia(Jerarquia* jerarquia) {
	std::vector<Jerarquia*>::iterator e;
	e = find(this->jerarquias.begin(), this->jerarquias.end(), jerarquia);
	if (*e == jerarquia){
		this->jerarquias.erase(e);
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

std::vector<Jerarquia*>::iterator EntidadNueva::jerarquiasBegin() {
	return this->jerarquias.begin();
}

std::vector<Jerarquia*>::iterator EntidadNueva::jerarquiasEnd() {
	return this->jerarquias.end();
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

void EntidadNueva::borrarRelaciones() {
	std::vector<Relacion*>::iterator it = this->relaciones.begin();
	while ( it != this->relaciones.end() ) {
		delete (*it);
		it++;
	}
	this->relaciones.clear();
}

void EntidadNueva::borrarJerarquias() {
	std::vector<Jerarquia*>::iterator it = this->jerarquias.begin();
	while ( it != this->jerarquias.end() ) {
		delete (*it);
		it++;
	}
	this->jerarquias.clear();
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

// PERSISTENCIA PARA DATOS

EntidadNueva::EntidadNueva(XmlNodo* nodo) {

	this->obtenerPropiedadesXmlDER(nodo);

	XmlNodo nodoAux = nodo->getHijo();

	this->obtenerComponentesXmlDER(&nodoAux);
}

void EntidadNueva::obtenerComponentesXmlDER (XmlNodo* nodo) {
	while (nodo->esValido()) {
		if (nodo->getNombre() == "atributo") {
	  		Atributo *atributo = new Atributo (nodo);
			this->agregarAtributo(atributo);
		}
		if (nodo->getNombre() == "identificador") {
			Identificador *identificador = new Identificador (nodo);
			this->agregarIdentificador(identificador);
		}
		if (nodo->getNombre() == "relacion")	{
			Relacion *relacion = new Relacion ();
			relacion->setCodigo(nodo->getContenidoInt());
			this->agregarRelacion(relacion);
		}
		if ( nodo->getNombre() == "jerarquia" )	{
			Jerarquia *jerarquia = new Jerarquia ();
			jerarquia->setCodigo(nodo->getContenidoInt());
			this->agregarJerarquia(jerarquia);
		}
		*nodo = nodo->getHermano();
	}
}

void EntidadNueva::agregarPropiedadesXmlDER(XmlNodo* nodo) {
	Componente::agregarPropiedadesXmlDER(nodo);
	nodo->setPropiedad("tipo",this->tipo);
}

void EntidadNueva::obtenerPropiedadesXmlDER(XmlNodo* nodo) {
	Componente::obtenerPropiedadesXmlDER(nodo);
	this->tipo = nodo->getPropiedad("tipo");
}

void EntidadNueva::guardarAtributosXmlDER(XmlNodo *nodo) {
	std::vector<Atributo*>::iterator i;

	for(i = this->atributos.begin(); i != this->atributos.end(); ++i)
		nodo->agregarHijo((*i)->guardarXmlDER());
}

void EntidadNueva::guardarIdentificadoresXmlDER(XmlNodo *nodo) {
	std::vector<Identificador*>::iterator i;

	for(i = this->identificadores.begin(); i != this->identificadores.end(); ++i)
		nodo->agregarHijo((*i)->guardarXmlDER());
}

void EntidadNueva::guardarJerarquiasXmlDER(XmlNodo *nodo) {
	std::vector<Jerarquia*>::iterator i;

	for(i = this->jerarquias.begin(); i != this->jerarquias.end(); ++i) {
		XmlNodo nodoJerarquia("jerarquia");
		nodoJerarquia.setContenido((*i)->getCodigo());
		nodo->agregarHijo(nodoJerarquia);
	}
}

XmlNodo EntidadNueva::guardarXmlDER() {
	XmlNodo nodo("entidad_nueva");

	this->agregarPropiedadesXmlDER(&nodo);

	this->guardarAtributosXmlDER(&nodo);
	this->guardarIdentificadoresXmlDER(&nodo);
	this->guardarRelacionesXmlDER(&nodo);
	this->guardarJerarquiasXmlDER(&nodo);

	return nodo;
}

