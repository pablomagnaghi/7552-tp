/*
 * Proyecto.h
 *
 *  Created on: 02/04/2012
 *      Author: Guagnini Enzo 88325
 */

#ifndef PROYECTO_H_
#define PROYECTO_H_

#include "VistaDiagrama.h"
#include <list>
#include <string>
#include "VistaConstantes.h"
using namespace std;

class TreePanel;

class VistaProyecto {
private:
	string nombre;
	VistaDiagrama d_principal;

	VistaDiagrama *diag_actual;

	TreePanel* treePanel;

	const Glib::RefPtr<Gtk::Builder>& Ide_builder;
	void cargarDiagrama(VistaDiagrama* diagrama);

	void testCargarDiagramas();

	friend class TreePanel;

public:
	VistaProyecto(const Glib::RefPtr<Gtk::Builder>& builder);
	virtual ~VistaProyecto();

	inline string getNombre(){return this->nombre;}
	inline void setNombre(string nom){this->nombre = nom;}
};

#endif /* PROYECTO_H_ */
