/* Diagrama.cpp
 *  Created on: 30/04/2012
 *      Author: Gonzalo Ferrero 89657
 */

#include "Diagrama.h"

Diagrama::Diagrama(string nombre) {
	this->nombre = nombre;
}

Diagrama::~Diagrama() {
	// TODO Auto-generated destructor stub
}


Diagrama* Diagrama::crearSubdiagrama(string nombre){
	Diagrama* diag = new Diagrama(nombre);
	this->l_sub_diagramas.push_back(diag);
	return diag;
}
