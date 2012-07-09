/* VistaEntidadGlobal.cpp
 *  Created on: 07/07/2012
 *      Author: Gonzalo Ferrero 89657
 */

#include "VistaEntidadGlobal.h"

VistaEntidadGlobal::VistaEntidadGlobal() {
	// TODO Auto-generated constructor stub

}

VistaEntidadGlobal::~VistaEntidadGlobal() {
	// TODO Auto-generated destructor stub
}

std::string VistaEntidadGlobal::getNombre() const{
	return this->entidad->getNombre();
}

bool VistaEntidadGlobal::contieneEsteComponente(Componente * c){
	return this->entidad == c;
}
