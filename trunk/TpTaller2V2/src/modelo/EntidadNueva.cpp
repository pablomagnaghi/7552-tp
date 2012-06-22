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

// PERSISTENCIA COMP
/*
EntidadNueva::EntidadNueva(XmlNodo* nodo, const std::vector<Relacion*>&, const std::vector<Jerarquia*>&) {

	this->obtenerPropiedadesXmlCOMP(nodo);

	XmlNodo nodoAux = nodo->getHijo();

	this->obtenerComponentesXmlCOMP(&nodoAux);
}*/

void EntidadNueva::obtenerComponentesIdentificadorXmlCOMP(Identificador* identificador, XmlNodo* nodo) {
	XmlNodo nodoAux = nodo->getHijo();

	while (nodoAux.esValido()) {
		if (nodoAux.getNombre() == "atributo") {
			identificador->agregarAtributo(this->getAtributoByCodigo(nodoAux.getContenidoInt()));
		}
		if (nodoAux.getNombre() == "relacion")	{
			//this->codigoIdentificador.push_back((nodoAux.getContenidoInt()));
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
			//Relacion *relacion = new Relacion();
			//relacion->setCodigo(nodo->getContenidoInt());
			//this->agregarRelacion(relacion);
		}
		if ( nodo->getNombre() == "jerarquia" )	{
			//Jerarquia *jerarquia = new Jerarquia ();
			//jerarquia->setCodigo(nodo->getContenidoInt());
			//this->agregarJerarquia(jerarquia);
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
	std::vector<Jerarquia*>::iterator i;

	for(i = this->jerarquias.begin(); i != this->jerarquias.end(); ++i) {
		XmlNodo nodoJerarquia("jerarquia");
		nodoJerarquia.setContenido((*i)->getCodigo());
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
