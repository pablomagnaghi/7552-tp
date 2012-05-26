/*
 * Proyecto.cpp
 *
 *  Created on: 02/04/2012
 *      Author: Guagnini Enzo 88325
 */

#include "VistaProyecto.h"
#include "TreePanel.h"

VistaProyecto::VistaProyecto()  {
	//Prueba
	this->diagramaPrincipal = new VistaDiagrama("Principal");
	this->testCargarDiagramas();
}

VistaProyecto::~VistaProyecto() {
	// TODO Auto-generated destructor stub
}



void VistaProyecto::testCargarDiagramas(){
	VistaDiagrama* diagrama = new VistaDiagrama("Sub Diag Prueba1");
	this->getDiagramaPrincipal()->agregarDiagramaHijo(diagrama);

	diagrama = new VistaDiagrama("SUB SUB DIAG 1");
	(*(this->getDiagramaPrincipal()->diagramasHijosBegin()))->agregarDiagramaHijo(diagrama);

	diagrama = new VistaDiagrama("Sub Diag Prueba2 0.75");
	diagrama->setZoom(0.75);
	this->getDiagramaPrincipal()->agregarDiagramaHijo(diagrama);
}

VistaDiagrama* VistaProyecto::getDiagramaPrincipal(){
	return (VistaDiagrama*)Proyecto::getDiagramaPrincipal();
}
