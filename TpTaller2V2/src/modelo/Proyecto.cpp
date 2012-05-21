/*
 * Proyecto.cpp
 *
 *  Created on: 02/04/2012
 *      Author: Guagnini Enzo 88325
 */

#include "Proyecto.h"

Proyecto::Proyecto() {

}

Proyecto::Proyecto(std::string nombre)
	: nombre (nombre) {

}

Proyecto::~Proyecto() {
}

std::string Proyecto::getNombre(){
	return this->nombre;
}

void Proyecto::setNombre(std::string nombre){
	this->nombre = nombre;
}

Diagrama* Proyecto::getDiagramaPrincipal(){
	return this->diagramaPrincipal;
}

void Proyecto::setDiagramaPrincipal(Diagrama* diagramaPrincipal){
	this->diagramaPrincipal = diagramaPrincipal;
}