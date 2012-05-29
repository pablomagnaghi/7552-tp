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


/* PERSISTENCIA DER

Jerarquia::Jerarquia(XmlNodo* nodo) {
	this->obtenerPropiedadesXmlDER(nodo);

	XmlNodo nodoAux = nodo->getHijo();

	this->obtenerComponentesXmlDER(&nodoAux);
}

void Jerarquia::obtenerPropiedadesXmlDER(XmlNodo* nodo) {
	this->cobertura = nodo->getPropiedad("cobertura");
	this->interseccion = nodo->getPropiedad("interseccion");
}

void Jerarquia::obtenerComponentesXmlDER (XmlNodo* nodo) {
	while (nodo->esValido()) {
		if (nodo->getNombre() == "entidad_general") {
	  		EntidadNueva *entidadGeneral = new EntidadNueva (nodo);
		}
		if (nodo->getNombre() == "entidad_especializada") {
	  		EntidadNueva *entidadNueva = new EntidadNueva (nodo);
			this->agregarEntidadEspecializada(entidadNueva);
		}
		*nodo = nodo->getHermano();
	}
}

void Jerarquia::agregarPropiedadesXmlDER(XmlNodo* nodo) {
	nodo->setPropiedad("cobertura",this->cobertura);
	nodo->setPropiedad("interseccion",this->interseccion);
}

XmlNodo Jerarquia::guardarXmlDER() {
	XmlNodo nodo("jerarquia");

	this->agregarPropiedadesXmlDER(&nodo);

	std::vector<Atributo*>::iterator i;

	nodo->agregarHijo(entidadGeneral->guardarXmlDER());

	for(i = this->entidadesEspecializadas.begin(); i != this->entidadesEspecializadas.end(); ++i)
		nodo->agregarHijo((*i)->guardarXmlDER());

	return nodo;
}
*/

