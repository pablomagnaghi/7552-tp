/*
 * GeneradorCodigo.cpp
 *
 *  Created on: 26/05/2012
 */

#include "GeneradorCodigo.h"

GeneradorCodigo* GeneradorCodigo::instance = NULL;

GeneradorCodigo::GeneradorCodigo() :
	codigo (0) {
}

GeneradorCodigo* GeneradorCodigo::getInstance(){
	if (instance == NULL){
		instance = new GeneradorCodigo();
	}
	return instance;
}

void GeneradorCodigo::destruir(){
	if (instance != NULL){
		delete instance;
	}
}

void GeneradorCodigo::setCodigo(int codigo){
	this->codigo = codigo;
}

int GeneradorCodigo::getCodigo() const{
	return this->codigo;
}

int GeneradorCodigo::getSiguienteCodigo(){
	return ++(this->codigo);
}

int GeneradorCodigo::siguienteCodigo(){
	return GeneradorCodigo::getInstance()->getSiguienteCodigo();
}
