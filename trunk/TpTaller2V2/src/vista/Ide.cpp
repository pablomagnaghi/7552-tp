/*
 * Ide.cpp
 *
 *  Created on: 02/04/2012
 *      Author: metal
 */
#include "VistaDiagrama.h"
#include "Ide.h"

Ide::Ide(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder) :
	Gtk::Window(cobject), m_builder(builder), treePanel(builder, this),
			panelAcciones(builder, this) {
	this->enlazarWidgets();
	this->set_size_request(800,600);
	//this->maximize();
	this->vproyecto = NULL;
	this->diag_actual = NULL;
	this->show();

	//TODO ESTO ES PARA PROBAR
	this->nuevoProyecto();

}

Ide::~Ide() {
	// TODO Auto-generated destructor stub
}

bool Ide::hayProyecto() {
	if (this->vproyecto == NULL) {
		Gtk::MessageDialog mensaje(*this, "Error.", false, Gtk::MESSAGE_ERROR,
				Gtk::BUTTONS_OK);
		mensaje.set_secondary_text(
				"No Hay proyecto cargado, operacion Imposible.");
		mensaje.run();
		return false;
	}
	return true;
}

void Ide::enlazarWidgets() {

}

void Ide::abrir_proyecto(string path) {

}

void Ide::guardar_proyecto() {

}

//TODO nuevo Proyecto
void Ide::nuevoProyecto() {
	this->vproyecto = new VistaProyecto();
	this->treePanel.regenerar();
	this->cargarDiagrama(this->vproyecto->getDiagramaPrincipal());
}

void Ide::cargarDiagrama(VistaDiagrama* diagrama) {
	Gtk::Layout* contenedorDiag;
	this->m_builder->get_widget("contenedor_diag", contenedorDiag);

	//Primero tengo que sacar el diag actual
	if (this->diag_actual != NULL) {
		contenedorDiag->remove(*(this->diag_actual));
	}

	cout << "ANCHO:" << diagrama->getAncho();
	cout << "ALTO:" << diagrama->getAlto() << endl;

	contenedorDiag->set_size_request(diagrama->getAncho(), diagrama->getAlto());
	contenedorDiag->put(*diagrama, 0, 0);
	this->diag_actual = diagrama;

	//diagrama->show();
	contenedorDiag->show_all();
}
