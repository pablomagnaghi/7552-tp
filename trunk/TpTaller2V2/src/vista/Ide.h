/*
 * Ide.h
 *
 *  Created on: 02/04/2012
 *      Author: metal
 */

#ifndef IDE_H_
#define IDE_H_


#include "../controlador/ControladorPanelHerramientas.h"
#include "../controlador/ComponentsBuilder.h"
#include "VistaDiagrama.h"
#include "VistaProyecto.h"
#include <gtkmm.h>
#include <iostream>
#include "../excepciones/NullPointer.h"
#include "../excepciones/ArgumentoInvalido.h"
#include "TreePanel.h"
using namespace std;

//#define DEBUG 1

class VistaProyecto;
class VistaDiagrama;

class Ide : public Gtk::Window {

private:

	Glib::RefPtr<Gtk::Builder> m_builder;
	//Posse un proyecto por vez
	VistaProyecto* vproyecto;

	 VistaDiagrama *diagactual;

	//Posse un treePanel
	TreePanel treePanel;

	ControladorPanelHerramientas controladorPanelHerramientas;

	static Ide *instancia;

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
	static Ide * getInstance();
	virtual ~Ide();

	//Proyecto
	void nuevoProyecto();
	void abrir_proyecto(string path);
	void guardar_proyecto();
	void cargarDiagrama(VistaDiagrama* diagrama);
	void regenerarTreePanel();
	inline VistaProyecto* getProyecto(){return this->vproyecto;}
	VistaDiagrama* getDiagActual();


};

#endif /* IDE_H_ */
