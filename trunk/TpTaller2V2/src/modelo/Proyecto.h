/*
 * Proyecto.h
 *
 *  Created on: 02/04/2012
 *      Author: Guagnini Enzo 88325
 */

#ifndef PROYECTO_H_
#define PROYECTO_H_

#include "Diagrama.h"
#include <list>
#include <string>
using namespace std;

class Proyecto {
protected:

	string nombre;

	Diagrama* d_principal;

public:
	Proyecto();
	Proyecto(string nom);
	virtual ~Proyecto();

	inline string getNombre(){return this->nombre;}
	inline void setNombre(string nom){this->nombre = nom;}
	virtual Diagrama* getDiagramaPrincipal();
};

#endif /* PROYECTO_H_ */
