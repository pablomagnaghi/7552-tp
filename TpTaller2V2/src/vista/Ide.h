/*
 * Ide.h
 *
 *  Created on: 02/04/2012
 *      Author: metal
 */

#ifndef IDE_H_
#define IDE_H_
#include "TreePanel.h"
#include "VistaProyecto.h"
#include <gtkmm.h>
#include <iostream>
#include "../controlador/ControladorPanelHerramientas.h"
using namespace std;

//#define DEBUG 1

class Ide : public Gtk::Window {
private:

	Glib::RefPtr<Gtk::Builder> m_builder;
	//Posse un proyecto por vez
	VistaProyecto* vproyecto;

	VistaDiagrama *diag_actual;

	//Posse un treePanel
	TreePanel treePanel;

	ControladorPanelHerramientas controladorPanelHerramientas;

	//Posee un panel de acciones
	//PanelAcciones panelAcciones;

	/*
	 * Enlaza todos los widgets que forman al Ide con las respectivas funciones.
	 */
	void enlazarWidgets();

	//Devuelve true si hay un proyecto cargado
	bool hayProyecto();

public:
	Ide(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);
	virtual ~Ide();

	//Proyecto
	void nuevoProyecto();
	void abrir_proyecto(string path);
	void guardar_proyecto();
	void cargarDiagrama(VistaDiagrama* diagrama);
	inline VistaProyecto* getProyecto(){return this->vproyecto;}
	inline VistaDiagrama* getDiagActual(){return this->diag_actual;}
};

#endif /* IDE_H_ */
