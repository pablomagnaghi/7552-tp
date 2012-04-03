/*
 * Entidad.h
 *
 *  Created on: 02/04/2012
 *      Author: Guagnini Enzo 88325
 */

#ifndef ENTIDAD_H_
#define ENTIDAD_H_
#include "Componente.h"
#include "Atributo.h"
#include <list>

class Entidad: public Componente {
private:
	list<Atributo*> l_atributos;
	string nombre;
public:
	Entidad();
	virtual ~Entidad();

	inline string getNombre() {
		return this->nombre;
	}
	inline void setNombre(string nom) {
		this->nombre = nom;
	}
};

#endif /* ENTIDAD_H_ */
