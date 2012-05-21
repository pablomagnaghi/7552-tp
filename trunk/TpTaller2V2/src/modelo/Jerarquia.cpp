/* Jerarquia.cpp
 *  Created on: 30/04/2012
 *      Author: Gonzalo Ferrero 89657
 */

#include "Jerarquia.h"

Jerarquia::Jerarquia() {

}

Jerarquia::~Jerarquia() {

}

Entidad* Jerarquia::getEntidadGeneral() const {
	return this->entidadGeneral;
}

void Jerarquia::setEntidadGeneral(Entidad* entidadGeneral) {
	this->entidadGeneral = entidadGeneral;
}

void Jerarquia::agregarEntidadEspecializada(Entidad* entidadEspecializada){
	this->entidadesEspecializadas.push_back(entidadEspecializada);
}

void Jerarquia::quitarEntidadEspecializada(Entidad* entidadEspecializada){
	std::vector<Entidad*>::iterator e;
	e = find(this->entidadesEspecializadas.begin(), this->entidadesEspecializadas.end(), entidadEspecializada);
	if (*e == entidadEspecializada){
		this->entidadesEspecializadas.erase(e);
	}
}

std::string Jerarquia::getCobertura() const {
	return this->cobertura;
}

void Jerarquia::setCobertura(const std::string cobertura) {
	this->cobertura = cobertura;
}

std::string Jerarquia::getInterseccion() const {
	return this->interseccion;
}

void Jerarquia::setInterseccion(const std::string interseccion) {
	this->interseccion = interseccion;
}

std::vector<Entidad*>::iterator Jerarquia::entidadesEspecializadasBegin(){
	return this->entidadesEspecializadas.begin();
}

std::vector<Entidad*>::iterator Jerarquia::entidadesEspecializadasEnd(){
	return this->entidadesEspecializadas.end();
}

