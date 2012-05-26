/* Entidad.cpp
 *  Created on: 30/04/2012
 *      Author: Gonzalo Ferrero 89657
 */

#include "Entidad.h"
#include "Relacion.h"

Entidad::~Entidad() {

}

void Entidad::agregarRelacion(Relacion* relacion){
	this->relaciones.push_back(relacion);
}

void Entidad::quitarRelacion(Relacion* relacion){
	std::vector<Relacion*>::iterator e;
	e = find(this->relaciones.begin(), this->relaciones.end(), relacion);
	if (*e == relacion){
		this->relaciones.erase(e);
	}
}

