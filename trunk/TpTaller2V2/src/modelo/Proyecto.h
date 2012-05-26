/*
 * Proyecto.h
 *
 *  Created on: 02/04/2012
 *      Author: Guagnini Enzo 88325
 */

#ifndef PROYECTO_H_
#define PROYECTO_H_

#include <list>
#include <string>
#include "Diagrama.h"

class Proyecto {

protected:

	std::string nombre;
	Diagrama* diagramaPrincipal;

public:

	Proyecto();
	Proyecto(std::string nombre);
	virtual ~Proyecto();

	std::string getNombre();
	void setNombre(std::string);

	virtual Diagrama* getDiagramaPrincipal();
	virtual void setDiagramaPrincipal(Diagrama*);

};

#endif /* PROYECTO_H_ */
