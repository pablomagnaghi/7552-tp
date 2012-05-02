/*
 * Atributo.h
 *
 *  Created on: 02/04/2012
 *      Author: Guagnini Enzo 88325
 */

#ifndef VISTAATRIBUTO_H_
#define VISTAATRIBUTO_H_
#include "VistaComponente.h"
#include <list>

class VistaAtributo : public VistaComponente  {
private:
	string nombre;
	list<VistaAtributo*> l_atrib_deri;
public:
	VistaAtributo();
	virtual ~VistaAtributo();

	inline string getNombre() {
		return this->nombre;
	}
	inline void setNombre(string nom) {
		this->nombre = nom;
	}
};

#endif /* VISTAATRIBUTO_H_ */
