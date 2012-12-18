/*
 * ModeloVisitor.cpp
 *
 *  Created on: 04/11/2012
 */

#include "ModeloVisitor.h"

ModeloVisitor::ModeloVisitor() :
		validacionTotal(false) {

}

ModeloVisitor::~ModeloVisitor() {
	this->archivo.close();
}

void ModeloVisitor::imprimirMensaje(std::string mensaje){
	this->archivo << mensaje << std::endl;
}

bool ModeloVisitor::validarTotalmente(){
	return this->validacionTotal;
}
