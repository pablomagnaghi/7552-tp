/* Diagrama.cpp
 *  Created on: 30/04/2012
 *      Author: Gonzalo Ferrero 89657
 */

#include "Diagrama.h"

Diagrama::Diagrama(const std::string nombre):
	nombre (nombre) {

}

Diagrama::~Diagrama() {
	std::vector<Componente*>::iterator it = this->componentes.begin();
	while (it != this->componentes.end()) {
		delete (*it);
		it++;
	}
	// TODO definir quien borra los diagramas hijos.
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

void Diagrama::agregarEntidad(Entidad* entidad){
	this->entidades.push_back(entidad);
	this->agregarComponente(entidad);
}

void Diagrama::quitarEntidad(Entidad* entidad){
	std::vector<Entidad*>::iterator e;
	e = find(this->entidades.begin(), this->entidades.end(), entidad);
	if (*e == entidad){
		this->entidades.erase(e);
	}
	this->quitarComponente(entidad);
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

std::vector<Componente*>::iterator Diagrama::componentesBegin(){
	return this->componentes.begin();
}

std::vector<Componente*>::iterator Diagrama::componentesEnd(){
	return this->componentes.end();
}

std::vector<Diagrama*>::iterator Diagrama::diagramasHijosBegin(){
	return this->diagramasHijos.begin();
}

std::vector<Diagrama*>::iterator Diagrama::diagramasHijosEnd(){
	return this->diagramasHijos.end();
}

Diagrama* Diagrama::crearDiagramaHijo(std::string nombre){
	Diagrama* diagramaHijo = new Diagrama(nombre);
	this->diagramasHijos.push_back(diagramaHijo);
	return diagramaHijo;
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
