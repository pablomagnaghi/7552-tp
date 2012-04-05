/*
 * Proyecto.h
 *
 *  Created on: 02/04/2012
 *      Author: Guagnini Enzo 88325
 */

#ifndef PROYECTO_H_
#define PROYECTO_H_

#include "Diagrama.h"
#include <list>
#include <string>
#include "../Constantes.h"
using namespace std;

class TreePanel;

class Proyecto {
private:
	string nombre;
	Diagrama d_principal;

	Diagrama *diag_actual;

	TreePanel* treePanel;

	const Glib::RefPtr<Gtk::Builder>& Ide_builder;
	void cargarDiagrama(Diagrama* diagrama);

	void testCargarDiagramas();

	friend class TreePanel;

public:
	Proyecto(const Glib::RefPtr<Gtk::Builder>& builder);
	virtual ~Proyecto();

	inline string getNombre(){return this->nombre;}
	inline void setNombre(string nom){this->nombre = nom;}
};

#endif /* PROYECTO_H_ */
