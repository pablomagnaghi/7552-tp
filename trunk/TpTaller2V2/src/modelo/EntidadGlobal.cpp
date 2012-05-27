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

