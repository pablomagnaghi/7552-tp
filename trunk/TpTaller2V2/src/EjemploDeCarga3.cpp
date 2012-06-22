/*
 * EjemploDeCarga3.cpp
 *
 *  Created on: 22/06/2012
 *      Author: pablo
 */

#include "modelo/Modelo.h"
#include <iostream>

int main(int argc, char* argv[]){

	Proyecto* proyecto = new Proyecto("BoleteriaTeatro");

	Diagrama* diagramaPrincipal = new Diagrama("Principal");
	proyecto->setDiagramaPrincipal(diagramaPrincipal);

	// prueba persistencia
	diagramaPrincipal->abrirXmlCOMP("Prueba3-EjemploCreacion.xml");

	diagramaPrincipal->guardarDiagramaXmlCOMP("PruebaCarga3-EjemploCreacion.xml");

	delete proyecto;

	std::cout << "Apertura del xml OK" << std::endl;

	return 0;
}
