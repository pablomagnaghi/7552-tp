/*
 * Ide.h
 *
 *  Created on: 02/04/2012
 *      Author: metal
 */

#ifndef IDE_H_
#define IDE_H_
#include "VistaProyecto.h"
#include <gtkmm.h>
#include <iostream>
using namespace std;

class Ide : public Gtk::Window {
private:
	Glib::RefPtr<Gtk::Builder> m_builder;
	//Posse un proyecto por vez
	VistaProyecto* proyecto;

public:
	Ide(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);
	virtual ~Ide();

	//Proyecto
	void abrir_proyecto(string path);
	void guardar_proyecto();

	void testCargarProyecto();
};

#endif /* IDE_H_ */
