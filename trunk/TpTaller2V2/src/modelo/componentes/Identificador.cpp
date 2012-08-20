#include "Identificador.h"

Identificador::Identificador() {

}

Identificador::~Identificador() {

}

void Identificador::agregarCodigoAtributo(int codigoAtributo){
	this->codigoAtributos.push_back(codigoAtributo);
}

void Identificador::quitarCodigoAtributo(int codigoAtributo){
	std::vector<int>::iterator e;
	e = find(this->codigoAtributos.begin(), this->codigoAtributos.end(), codigoAtributo);
	if (*e == codigoAtributo){
		this->codigoAtributos.erase(e);
	}
}

void Identificador::agregarCodigoRelacion(int codigoRelacion){
	this->codigoRelaciones.push_back(codigoRelacion);
}

void Identificador::quitarCodigoRelacion(int codigoRelacion){
	std::vector<int>::iterator e;
	e = find(this->codigoRelaciones.begin(), this->codigoRelaciones.end(), codigoRelacion);
	if (*e == codigoRelacion){
		this->codigoRelaciones.erase(e);
	}
}

std::vector<int>::iterator Identificador::codigoAtributosBegin(){
	return this->codigoAtributos.begin();
}

std::vector<int>::iterator Identificador::codigoAtributosEnd(){
	return this->codigoAtributos.end();
}

std::vector<int>::iterator Identificador::codigoRelacionesBegin(){
	return this->codigoRelaciones.begin();
}

std::vector<int>::iterator Identificador::codigoRelacionesEnd(){
	return this->codigoRelaciones.end();
}
