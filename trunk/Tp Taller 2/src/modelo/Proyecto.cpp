/*
 * Proyecto.cpp
 *
 *  Created on: 02/04/2012
 *      Author: Guagnini Enzo 88325
 */

#include "Proyecto.h"
#include "TreePanel.h"

Proyecto::Proyecto(const Glib::RefPtr<Gtk::Builder>& builder) :
Ide_builder(builder), d_principal("Principal") {
	//Prueba
	this->testCargarDiagramas();
	//
	this->treePanel = new TreePanel(this);
	this->cargarDiagrama(&this->d_principal);
}

Proyecto::~Proyecto() {
	// TODO Auto-generated destructor stub
}

void Proyecto::cargarDiagrama(Diagrama* diagrama){
	Gtk::Layout* contenedorDiag;
	this->Ide_builder->get_widget("contenedor_diag", contenedorDiag);
	contenedorDiag->set_size_request(diagrama->getAncho(), diagrama->getAlto());
	contenedorDiag->put(*diagrama, 0, 0);
	diagrama->show();
}


void Proyecto::testCargarDiagramas(){
	this->d_principal.crearSubdiagrama("Sub Diag Prueba1");
	(*(this->d_principal.l_sub_diagramas.begin()))->crearSubdiagrama("SUB SUB DIAG 1");
	Diagrama *diag = this->d_principal.crearSubdiagrama("Sub Diag Prueba2 0.75");
	diag->setZoom(0.75);
}
