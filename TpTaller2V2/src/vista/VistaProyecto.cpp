/*
 * Proyecto.cpp
 *
 *  Created on: 02/04/2012
 *      Author: Guagnini Enzo 88325
 */

#include "VistaProyecto.h"
#include "TreePanel.h"

VistaProyecto::VistaProyecto(Proyecto * proyectoModelo)  {
	//Prueba
	this->proyecto = proyectoModelo;
	this->diagramaPrincipal = new VistaDiagrama(proyectoModelo->getDiagramaPrincipal());
	//this->testCargarDiagramas();
}

VistaProyecto::~VistaProyecto() {
	// TODO Auto-generated destructor stub
}

void VistaProyecto::testCargarDiagramas(){
	VistaDiagrama* diagrama = new VistaDiagrama(new Diagrama("Sub Diag Prueba1"));
	this->getDiagramaPrincipal()->getDiagrama()->agregarDiagramaHijo(diagrama->getDiagrama());

	diagrama = new VistaDiagrama(new Diagrama("SUB SUB DIAG 1"));
	(*(this->getDiagramaPrincipal()->getDiagrama()->diagramasHijosBegin()))->agregarDiagramaHijo(diagrama->getDiagrama());

	diagrama = new VistaDiagrama(new Diagrama("Sub Diag Prueba2 0.75"));
	diagrama->setZoom(0.75);
	this->getDiagramaPrincipal()->getDiagrama()->agregarDiagramaHijo(diagrama->getDiagrama());

	this->diagramaPrincipal->test_cargar_componentes_visuales();
}

VistaDiagrama* VistaProyecto::getDiagramaPrincipal(){
	return this->diagramaPrincipal;
}
