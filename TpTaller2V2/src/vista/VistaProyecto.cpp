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
	this->getDiagramaPrincipal()->crearDiagramaHijo("Sub Diag Prueba1");
	(*(this->getDiagramaPrincipal()->diagramasHijosBegin()))->crearDiagramaHijo("SUB SUB DIAG 1");
	VistaDiagrama *diag = this->getDiagramaPrincipal()->crearDiagramaHijo("Sub Diag Prueba2 0.75");
	diag->setZoom(0.75);
}

VistaDiagrama* VistaProyecto::getDiagramaPrincipal(){
	return (VistaDiagrama*)Proyecto::getDiagramaPrincipal();
}
