/*
 * Proyecto.cpp
 *
 *  Created on: 02/04/2012
 *      Author: Guagnini Enzo 88325
 */

#include "VistaProyecto.h"
#include "TreePanel.h"

VistaProyecto::VistaProyecto(const Glib::RefPtr<Gtk::Builder>& builder) :
Ide_builder(builder), d_principal("Principal") {
	//Prueba
	this->testCargarDiagramas();
	//
	this->treePanel = new TreePanel(this);
	this->diag_actual = NULL;
	this->cargarDiagrama(&this->d_principal);
}

VistaProyecto::~VistaProyecto() {
	// TODO Auto-generated destructor stub
}

void VistaProyecto::cargarDiagrama(VistaDiagrama* diagrama){
	Gtk::Layout* contenedorDiag;
	this->Ide_builder->get_widget("contenedor_diag", contenedorDiag);
	//Primero tengo que sacar el diag actual
	if (this->diag_actual != NULL){
		contenedorDiag->remove(*(this->diag_actual));
	}
	cout<<"ANCHO:"<<diagrama->getAncho()<<"ALTO:"<<diagrama->getAlto()<<endl;
	contenedorDiag->set_size_request(diagrama->getAncho(), diagrama->getAlto());
	contenedorDiag->put(*diagrama, 0, 0);
	this->diag_actual = diagrama;
	diagrama->show();
}


void VistaProyecto::testCargarDiagramas(){
	this->d_principal.crearSubdiagrama("Sub Diag Prueba1");
	(*(this->d_principal.l_sub_diagramas.begin()))->crearSubdiagrama("SUB SUB DIAG 1");
	VistaDiagrama *diag = this->d_principal.crearSubdiagrama("Sub Diag Prueba2 0.75");
	diag->setZoom(0.75);
}
