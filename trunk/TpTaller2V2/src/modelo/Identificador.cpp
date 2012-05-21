/* Identificador.cpp
 *  Created on: 30/04/2012
 *      Author: Gonzalo Ferrero 89657
 */

#include "Identificador.h"
#include "Relacion.h"

Identificador::Identificador() {

}

Identificador::~Identificador() {

}

void Identificador::agregarAtributo(Atributo* atributo){
	this->atributos.push_back(atributo);
}

void Identificador::quitarAtributo(Atributo* atributo){
	std::vector<Atributo*>::iterator e;
	e = find(this->atributos.begin(), this->atributos.end(), atributo);
	if (*e == atributo){
		this->atributos.erase(e);
	}
}

void Identificador::agregarRelacion(Relacion* relacion){
	this->relaciones.push_back(relacion);
}

void Identificador::quitarRelacion(Relacion* relacion){
	std::vector<Relacion*>::iterator e;
	e = find(this->relaciones.begin(), this->relaciones.end(), relacion);
	if (*e == relacion){
		this->relaciones.erase(e);
	}
}

std::vector<Atributo*>::iterator Identificador::atributosBegin(){
	return this->atributos.begin();
}

std::vector<Atributo*>::iterator Identificador::atributosEnd(){
	return this->atributos.end();
}

std::vector<Relacion*>::iterator Identificador::relacionesBegin(){
	return this->relaciones.begin();
}

std::vector<Relacion*>::iterator Identificador::relacionesEnd(){
	return this->relaciones.end();
}

