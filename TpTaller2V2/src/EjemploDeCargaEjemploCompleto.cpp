/*
 * EjemploDeCarga2.cpp
 *
 *  Created on: 22/06/2012
 *      Author: pablo
 */

#include "modelo/HeadersModelo.h"
#include <iostream>

int main(int argc, char* argv[]){

	Proyecto* proyecto = new Proyecto("BoleteriaTeatro");

	Diagrama* diagramaPrincipal = new Diagrama("Principal");
	proyecto->setDiagramaPrincipal(diagramaPrincipal);

	// prueba persistencia
	diagramaPrincipal->abrirXmlCOMP("Prueba2-DiagramaPrincipal.xml");

	diagramaPrincipal->guardarDiagramaXmlCOMP("PruebaCarga2-DiagramaPrincipal.xml");

	// Diagrama* diagramaHijo = new Diagrama("Hijo");

	//diagramaHijo->abrirXmlCOMP("Prueba2-DiagramaHijo.xml");

	//diagramaHijo->guardarDiagramaXmlCOMP("PruebaCarga2-DiagramaHijo.xml");

	// diagramaPrincipal->agregarDiagramaHijo(diagramaHijo);

	delete proyecto;

	std::cout << "Apertura del xml OK" << std::endl;

	return 0;
}
