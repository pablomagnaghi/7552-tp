/*
 * Entidad.h
 *
 *  Created on: 02/04/2012
 *      Author: Guagnini Enzo 88325
 */

#ifndef ENTIDAD_H_
#define ENTIDAD_H_
#include "VistaComponente.h"
#include "VistaAtributo.h"
#include <list>

class VistaEntidad: public VistaComponente {
private:
	list<VistaAtributo*> l_atributos;
	string nombre;
public:
	VistaEntidad();
	virtual ~VistaEntidad();

	inline string getNombre() {
		return this->nombre;
	}
	inline void setNombre(string nom) {
		this->nombre = nom;
	}
};

#endif /* ENTIDAD_H_ */
