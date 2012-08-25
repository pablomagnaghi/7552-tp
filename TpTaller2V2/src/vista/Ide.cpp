/*
 * Ide.cpp
 *
 *  Created on: 02/04/2012
 *      Author: metal
 */


#include "Ide.h"
Ide * Ide::instancia = NULL;
//VistaDiagrama * Ide::diagactual = NULL;

Ide::Ide(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder) :
	Gtk::Window(cobject), m_builder(builder), treePanel(builder, this),
			controladorPanelHerramientas(builder,
					static_cast<Gtk::Window *> (this)) {

	this->enlazarWidgets();
	this->set_size_request(800, 600);
	//this->maximize();
	this->vproyecto = NULL;
	//this->diagactual = NULL;
	this->show();

	//TODO ESTO ES PARA PROBAR
	this->nuevoProyecto();
	ComponentsBuilder* c = ComponentsBuilder::getInstance();
	this->instancia = this;
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
	if (this->vproyecto == NULL) {
		this->vproyecto = new VistaProyecto(new Proyecto(new Diagrama("DiagramaPrincipal")));
		this->vproyecto->testCargarDiagramas();
		this->regenerarTreePanel();
		this->cargarDiagrama(this->vproyecto->getDiagramaPrincipal());
		this->controladorPanelHerramientas.activarBotones();
	} else {
		Gtk::MessageDialog mensaje(*this, "Error", false, Gtk::MESSAGE_ERROR,
				Gtk::BUTTONS_OK);
		mensaje.set_secondary_text("Ya existe un proyecto");
		mensaje.run();

	}
}

void Ide::cargarDiagrama(VistaDiagrama* diagrama) {
	Gtk::Layout* contenedorDiag;
	this->m_builder->get_widget("contenedor_diag", contenedorDiag);

	//Primero tengo que sacar el diag actual
	if (diagactual != NULL) {
		contenedorDiag->remove(*(diagactual));
	}

#ifdef DEBUG
	cout << "ANCHO:" << diagrama->getAncho();
	cout << "ALTO:" << diagrama->getAlto() << endl;
#endif

	contenedorDiag->set_size_request(diagrama->getAncho(), diagrama->getAlto());
	contenedorDiag->put(*diagrama, 0, 0);
	diagactual = diagrama;

	//diagrama->show();
	contenedorDiag->show_all();
}

VistaDiagrama* Ide::getDiagActual(){
	VistaDiagrama *d = diagactual;
	return d;
}

Ide * Ide::getInstance() {
	if (Ide::instancia != NULL) {
		return Ide::instancia;
	} else {
		return Ide::instancia;
	}
}

void Ide::regenerarTreePanel(){
	this->treePanel.regenerar();
}
