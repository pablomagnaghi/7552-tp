/*
 * Proyecto.cpp
 *
 *  Created on: 02/04/2012
 *      Author: Guagnini Enzo 88325
 */

#include "Proyecto.h"

Proyecto::Proyecto() {

}

Proyecto::Proyecto(string nom) : nombre(nom){

}

Proyecto::~Proyecto() {
	// TODO Auto-generated destructor stub
}

Diagrama* Proyecto::getDiagramaPrincipal(){
	return this->d_principal;
}
