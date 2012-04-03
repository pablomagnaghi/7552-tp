/*
 * Proyecto.cpp
 *
 *  Created on: 02/04/2012
 *      Author: Guagnini Enzo 88325
 */

#include "Proyecto.h"

Proyecto::Proyecto(const Glib::RefPtr<Gtk::Builder>& builder) :
Ide_builder(builder){
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
