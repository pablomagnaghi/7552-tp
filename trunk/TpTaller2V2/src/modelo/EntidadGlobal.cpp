/*
 * EntidadGlobal.cpp
 *
 *  Created on: 14/05/2012
 */

#include "EntidadGlobal.h"

EntidadGlobal::EntidadGlobal() {
	// TODO Auto-generated constructor stub

}

EntidadGlobal::~EntidadGlobal() {
	// TODO Auto-generated destructor stub
}

void EntidadGlobal::setDiagrama(std::string diagramaAncestro){
	this->diagramaAncestro = diagramaAncestro;
}

std::string EntidadGlobal::getDiagramaAncestro(){
	return this->diagramaAncestro;
}

