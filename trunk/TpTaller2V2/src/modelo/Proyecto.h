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
	Proyecto(const std::string&);
	virtual ~Proyecto();

	std::string getNombre() const;
	void setNombre(const std::string&);

	virtual Diagrama* getDiagramaPrincipal();
	virtual void setDiagramaPrincipal(Diagrama*);

};

#endif /* PROYECTO_H_ */
