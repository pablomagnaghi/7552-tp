/*
 * EjemploDeCarga.cpp
 *
 *  Created on: 18/06/2012
 *      Author: pablo
 */

#include "modelo/Modelo.h"
#include <iostream>

int main5(int argc, char* argv[]){

	Proyecto* proyecto = new Proyecto("BoleteriaTeatro");

	Diagrama* diagramaPrincipal = new Diagrama("Principal");
	proyecto->setDiagramaPrincipal(diagramaPrincipal);

	// prueba persistencia
	diagramaPrincipal->abrirXmlCOMP("Prueba2-DiagramaPrincipal.xml");

	diagramaPrincipal->guardarDiagramaXmlCOMP("PruebaCarga2-DiagramaPrincipal.xml");

	Diagrama* diagramaHijo = new Diagrama("Hijo");

	diagramaHijo->abrirXmlCOMP("Prueba2-DiagramaHijo.xml");

	diagramaHijo->guardarDiagramaXmlCOMP("PruebaCarga2-DiagramaHijo.xml");

	diagramaPrincipal->agregarDiagramaHijo(diagramaHijo);

	delete proyecto;

	std::cout << "Apertura del xml OK" << std::endl;

	return 0;
}
