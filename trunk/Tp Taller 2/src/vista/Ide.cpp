/*
 * Ide.cpp
 *
 *  Created on: 02/04/2012
 *      Author: metal
 */

#include "Ide.h"

Ide::Ide(BaseObjectType* cobject,
		const Glib::RefPtr<Gtk::Builder>& builder) :
	Gtk::Window(cobject), m_builder(builder){
	this->maximize();
	this->show();
	this->testCargarProyecto();

}

Ide::~Ide() {

}

void Ide::abrir_proyecto(string path){
	// Abre un proyecto en un archivo y lo carga en el programa
}
void Ide::guardar_proyecto(){
	// Guarda el proyecto en un archivo
}

void Ide::testCargarProyecto(){
	this->proyecto = new VistaProyecto(this->m_builder);
}
