/* Jerarquia.cpp
 *  Created on: 30/04/2012
 *      Author: Gonzalo Ferrero 89657
 */

#include "Jerarquia.h"

Jerarquia::Jerarquia() {

}

Jerarquia::~Jerarquia() {

}

EntidadNueva* Jerarquia::getEntidadGeneral() const {
	return this->entidadGeneral;
}

void Jerarquia::setEntidadGeneral(EntidadNueva* entidadGeneral) {
	this->entidadGeneral = entidadGeneral;
}

void Jerarquia::agregarEntidadEspecializada(EntidadNueva* entidadEspecializada){
	this->entidadesEspecializadas.push_back(entidadEspecializada);
}

void Jerarquia::quitarEntidadEspecializada(EntidadNueva* entidadEspecializada){
	std::vector<EntidadNueva*>::iterator e;
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

std::vector<EntidadNueva*>::iterator Jerarquia::entidadesEspecializadasBegin(){
	return this->entidadesEspecializadas.begin();
}

std::vector<EntidadNueva*>::iterator Jerarquia::entidadesEspecializadasEnd(){
	return this->entidadesEspecializadas.end();
}

