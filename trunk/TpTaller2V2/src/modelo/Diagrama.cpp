/* Diagrama.cpp
 *  Created on: 30/04/2012
 *      Author: Gonzalo Ferrero 89657
 */

#include "Diagrama.h"

Diagrama::Diagrama(){

}

Diagrama::Diagrama(const std::string nombre):
	nombre (nombre) {

}

Diagrama::~Diagrama() {
	this->borrarDiagramasHijos();
	this->borrarEntidadesNuevas();
	this->borrarEntidadesGlobales();
	this->borrarRelaciones();
	this->borrarJerarquias();
}

void Diagrama::setNombre(const std::string nombre){
	this->nombre = nombre;
}

std::string Diagrama::getNombre() const{
	return this->nombre;
}

void Diagrama::setEstado(const std::string estado){
	this->estado = estado;
}

std::string Diagrama::getEstado() const{
	return this->estado;
}

void Diagrama::setDiagramaAncestro(Diagrama* diagramaAncestro){
	this->diagramaAncestro = diagramaAncestro;
}

Diagrama* Diagrama::getDiagramaAncestro() const{
	return this->diagramaAncestro;
}

void Diagrama::agregarDiagramaHijo(Diagrama* diagramaHijo){
	this->diagramasHijos.push_back(diagramaHijo);
}

void Diagrama::quitarDiagramaHijo(Diagrama* diagramaHijo){
	std::vector<Diagrama*>::iterator e;
	e = find(this->diagramasHijos.begin(), this->diagramasHijos.end(), diagramaHijo);
	if (*e == diagramaHijo){
		this->diagramasHijos.erase(e);
	}
}

void Diagrama::agregarComponente(Componente* componente){
	this->componentes.push_back(componente);
}

void Diagrama::quitarComponente(Componente* componente){
	std::vector<Componente*>::iterator e;
	e = find(this->componentes.begin(), this->componentes.end(), componente);
	if (*e == componente){
		this->componentes.erase(e);
	}
}

void Diagrama::agregarEntidadNueva(EntidadNueva* entidadNueva){
	this->entidadesNuevas.push_back(entidadNueva);
	this->agregarComponente(entidadNueva);
}

void Diagrama::quitarEntidadNueva(EntidadNueva* entidadNueva){
	std::vector<EntidadNueva*>::iterator e;
	e = find(this->entidadesNuevas.begin(), this->entidadesNuevas.end(), entidadNueva);
	if (*e == entidadNueva){
		this->entidadesNuevas.erase(e);
	}
	this->quitarComponente(entidadNueva);
}

void Diagrama::agregarEntidadGlobal(EntidadGlobal* entidadGlobal){
	this->entidadesGlobales.push_back(entidadGlobal);
	this->agregarComponente(entidadGlobal);
}

void Diagrama::quitarEntidadGlobal(EntidadGlobal* entidadGlobal){
	std::vector<EntidadGlobal*>::iterator e;
	e = find(this->entidadesGlobales.begin(), this->entidadesGlobales.end(), entidadGlobal);
	if (*e == entidadGlobal){
		this->entidadesGlobales.erase(e);
	}
	this->quitarComponente(entidadGlobal);
}

void Diagrama::agregarRelacion(Relacion* relacion){
	this->relaciones.push_back(relacion);
	this->agregarComponente(relacion);
}

void Diagrama::quitarRelacion(Relacion* relacion){
	std::vector<Relacion*>::iterator e;
	e = find(this->relaciones.begin(), this->relaciones.end(), relacion);
	if (*e == relacion){
		this->relaciones.erase(e);
	}
	this->quitarComponente(relacion);
}

void Diagrama::agregarJerarquia(Jerarquia* jerarquia){
	this->jerarquias.push_back(jerarquia);
	this->agregarComponente(jerarquia);
}

void Diagrama::quitarJerarquia(Jerarquia* jerarquia){
	std::vector<Jerarquia*>::iterator e;
	e = find(this->jerarquias.begin(), this->jerarquias.end(), jerarquia);
	if (*e == jerarquia){
		this->jerarquias.erase(e);
	}
	this->quitarComponente(jerarquia);
}

std::vector<Diagrama*>::iterator Diagrama::diagramasHijosBegin(){
	return this->diagramasHijos.begin();
}

std::vector<Diagrama*>::iterator Diagrama::diagramasHijosEnd(){
	return this->diagramasHijos.end();
}

std::vector<EntidadNueva*>::iterator Diagrama::entidadesNuevasBegin(){
	return this->entidadesNuevas.begin();
}

std::vector<EntidadNueva*>::iterator Diagrama::entidadesNuevasEnd(){
	return this->entidadesNuevas.end();
}

std::vector<EntidadGlobal*>::iterator Diagrama::entidadesGlobalesBegin(){
	return this->entidadesGlobales.begin();
}

std::vector<EntidadGlobal*>::iterator Diagrama::entidadesGlobalesEnd(){
	return this->entidadesGlobales.end();
}

std::vector<Relacion*>::iterator Diagrama::relacionesBegin(){
	return this->relaciones.begin();
}

std::vector<Relacion*>::iterator Diagrama::relacionesEnd(){
	return this->relaciones.end();
}

std::vector<Jerarquia*>::iterator Diagrama::jerarquiasBegin(){
	return this->jerarquias.begin();
}

std::vector<Jerarquia*>::iterator Diagrama::jerarquiasEnd(){
	return this->jerarquias.end();
}

std::vector<Componente*>::iterator Diagrama::componentesBegin(){
	return this->componentes.begin();
}

std::vector<Componente*>::iterator Diagrama::componentesEnd(){
	return this->componentes.end();
}

void Diagrama::borrarDiagramasHijos(){
	std::vector<Diagrama*>::iterator it = this->diagramasHijos.begin();
	while (it != this->diagramasHijos.end()) {
		delete (*it);
		it++;
	}
	this->diagramasHijos.clear();
}

void Diagrama::borrarEntidadesNuevas(){
	std::vector<EntidadNueva*>::iterator it = this->entidadesNuevas.begin();
	while (it != this->entidadesNuevas.end()) {
		delete (*it);
		it++;
	}
	this->entidadesNuevas.clear();
}

void Diagrama::borrarEntidadesGlobales(){
	std::vector<EntidadGlobal*>::iterator it = this->entidadesGlobales.begin();
	while (it != this->entidadesGlobales.end()) {
		delete (*it);
		it++;
	}
	this->entidadesGlobales.clear();
}

void Diagrama::borrarRelaciones(){
	std::vector<Relacion*>::iterator it = this->relaciones.begin();
	while (it != this->relaciones.end()) {
		delete (*it);
		it++;
	}
	this->relaciones.clear();
}

void Diagrama::borrarJerarquias(){
	std::vector<Jerarquia*>::iterator it = this->jerarquias.begin();
	while (it != this->jerarquias.end()) {
		delete (*it);
		it++;
	}
	this->jerarquias.end();
}

/*
void Hoja::obtenerObjetosGraficos ( XmlNodo* nodo) {
	while (nodo->esValido()) {
		if ( nodo->getNombre() == "objetoLista" ) {
			ObjetoLista* objeto = new ObjetoLista (nodo);
			this->agregarObjeto(objeto);
		}
		if ( nodo->getNombre() == "linea" ) {
      Linea* objeto = new Linea (nodo);
      this->agregarObjeto(objeto);
	}
	*nodo = nodo->getHermano();
  }
}*/
