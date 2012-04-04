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
	this->cargarDprincipal();
}

Proyecto::~Proyecto() {
	// TODO Auto-generated destructor stub
}

void Proyecto::cargarDprincipal(){
	Gtk::Layout* contenedorDiag;
	this->Ide_builder->get_widget("contenedor_diag", contenedorDiag);
	contenedorDiag->set_size_request(A4_ANCHO, A4_ALTO);
	contenedorDiag->put(this->d_principal, 0, 0);
	this->d_principal.show();
}


void Proyecto::testCargarDiagramas(){
	this->d_principal.crearSubdiagrama("Sub Diag Prueba1");
	this->d_principal.crearSubdiagrama("Sub Diag Prueba2");
}
