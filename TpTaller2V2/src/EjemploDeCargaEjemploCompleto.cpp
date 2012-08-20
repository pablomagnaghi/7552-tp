/*
 * EjemploDeCarga2.cpp
 *
 *  Created on: 22/06/2012
 *      Author: pablo
 */
/*
#include "modelo/HeadersModelo.h"
#include <iostream>

int main(int argc, char* argv[]){

	Proyecto* proyecto = new Proyecto("BoleteriaTeatro");

	Diagrama* diagramaPrincipal = new Diagrama("Principal");
	proyecto->setDiagramaPrincipal(diagramaPrincipal);

	// prueba persistencia
	diagramaPrincipal->abrirXmlCOMP("Principal.xml");

	diagramaPrincipal->guardarDiagramaXmlCOMP("PruebaCarga2-Principal.xml");

	std::vector<Diagrama*>::iterator it = diagramaPrincipal->diagramasHijosBegin();

	while (it != diagramaPrincipal->diagramasHijosEnd()) {
		std::string nombre = "PruebaCarga2-Hijo.xml";
		(*it)->guardarDiagramaXmlCOMP(nombre);
		it++;
		nombre += "x";
	}

	delete proyecto;

	std::cout << "Apertura del xml OK" << std::endl;

	return 0;
}*/
