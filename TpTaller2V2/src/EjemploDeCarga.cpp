/*
 * EjemploDeCarga.cpp
 *
 *  Created on: 18/06/2012
 *      Author: pablo
 */

#include "modelo/Modelo.h"
#include <iostream>

int main2(int argc, char* argv[]){

	Proyecto* proyecto = new Proyecto("BoleteriaTeatro");

	Diagrama* diagramaPrincipal = new Diagrama("Principal");
	proyecto->setDiagramaPrincipal(diagramaPrincipal);

	// prueba persistencia
	diagramaPrincipal->abrirXmlCOMP("Prueba1-EjemploBoleteriaTeatro.xml");

	diagramaPrincipal->guardarDiagramaXmlCOMP("PruebaDeCarga.xml");

	std::cout << "Apertura del xml OK" << std::endl;

	return 0;
}
