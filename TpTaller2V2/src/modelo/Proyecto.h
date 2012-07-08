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
	// Modelo
	std::string nombre;
	Diagrama * diagramaPrincipal;

	// Este tendría que tener todos los diagramas, por más que estén los hijos en cada diagrama
	// Sería el administrador de diagramas
	std::vector<Diagrama * > diagramas;

public:

	Proyecto(Diagrama * diagrama);
	Proyecto(const std::string&);
	virtual ~Proyecto();

	std::string getNombre() const;
	void setNombre(const std::string&);

	Diagrama* getDiagramaPrincipal();
	virtual void setDiagramaPrincipal(Diagrama*);

};

#endif /* PROYECTO_H_ */
