/*
 * Proyecto.h
 *
 *  Created on: 02/04/2012
 *      Author: Guagnini Enzo 88325
 */

#ifndef VISTAPROYECTO_H_
#define VISTAPROYECTO_H_

#include "VistaDiagrama.h"
#include <list>
#include <string>
#include "VistaConstantes.h"
#include "../modelo/Proyecto.h"
using namespace std;

class VistaDiagrama;

class VistaProyecto  {
private:

	VistaDiagrama * diagramaPrincipal;
	Proyecto * proyecto;



public:
	VistaProyecto(Proyecto * proyectoModelo);
	virtual ~VistaProyecto();
	void testCargarDiagramas();
	 VistaDiagrama* getDiagramaPrincipal();
};

#endif /* VISTAPROYECTO_H_ */
