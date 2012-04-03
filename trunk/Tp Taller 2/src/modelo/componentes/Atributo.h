/*
 * Atributo.h
 *
 *  Created on: 02/04/2012
 *      Author: Guagnini Enzo 88325
 */

#ifndef ATRIBUTO_H_
#define ATRIBUTO_H_
#include "Componente.h"
#include <list>

class Atributo : public Componente  {
private:
	string nombre;
	list<Atributo*> l_atrib_deri;
public:
	Atributo();
	virtual ~Atributo();

	inline string getNombre() {
		return this->nombre;
	}
	inline void setNombre(string nom) {
		this->nombre = nom;
	}
};

#endif /* ATRIBUTO_H_ */
