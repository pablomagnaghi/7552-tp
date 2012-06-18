/*
 * EjemploDeCarga.cpp
 *
 *  Created on: 18/06/2012
 *      Author: pablo
 */

#include "modelo/Modelo.h"
#include <iostream>

int main(int argc, char* argv[]){

	Proyecto* proyecto = new Proyecto("BoleteriaTeatro");

	Diagrama* diagramaPrincipal = new Diagrama("Principal");
	proyecto->setDiagramaPrincipal(diagramaPrincipal);

	// prueba persistencia
	diagramaPrincipal->abrir("Prueba1-EjemploBoleteriaTeatro.xml");

	//diagramaPrincipal->guardarDiagrama("PruebaDeCarga.xml");

	//std::cout << "Apertura del xml OK" << std::endl;

	return 0;
}
