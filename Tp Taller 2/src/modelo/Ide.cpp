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
	// TODO Auto-generated destructor stub
}

void Ide::abrir_proyecto(string path){

}
void Ide::guardar_proyecto(){

}

void Ide::testCargarProyecto(){
	this->proyecto = new Proyecto(this->m_builder);
}
