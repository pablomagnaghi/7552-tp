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

class Ide: public Gtk::Window {

private:

	Gtk::Fixed * fijacionTreePanel;
	Gtk::HPaned * panelHorizontal;
	bool expandido;
	int posicion_anterior;
	Gtk::ToggleButton * botonEsconderPanel;
	Gtk::Image * flecha_izquierda;
	Gtk::Image * flecha_derecha;
	Gtk::ScrolledWindow * scrolledTreePanel;

	Glib::RefPtr<Gtk::Builder> m_builder;

	//Posee un proyecto por vez
	VistaProyecto * vproyecto;

	VistaDiagrama * diagramaActual;

	Gtk::Layout* contenedorDiag;

	//Posee un treePanel
	TreePanel treePanel;

	ControladorPanelHerramientas controladorPanelHerramientas;

	static Ide *instancia;

	//Posee un panel de acciones
	//PanelAcciones panelAcciones;

	// ARCHIVOS

	std::string carpetaProyecto; // Path al proyecto

	// LOS METODOS QUE COMIENZAN CON debug SON PARA PRUEBAS

	void debugInformarValorVariable(const std::string & nombreVariable, const std::string & valor);

	void on_panel_horizontal_size_request(Gtk::Requisition* const & requisition);
	void on_boton_esconder_panel_toggle();
	/*
	 * Enlaza todos los widgets que forman al Ide con las respectivas funciones.
	 */
	//void enlazarWidgets();
	//Devuelve true si hay un proyecto cargado
	bool hayProyecto();

public:
	Ide(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);
	static Ide * getInstance();
	virtual ~Ide();

	//Proyecto

	// MANEJO DE ARCHIVOS
	bool abrir_proyecto();
	bool guardar_proyecto(bool guardarComo);
	void cargarDiagrama(VistaDiagrama* diagrama);
	void exportar_diagrama();

	void regenerarTreePanel();

	bool crearNuevoProyecto();

	bool cerrarProyecto();

	inline VistaProyecto* getProyecto() {
		return this->vproyecto;
	}
	VistaDiagrama* getDiagActual();


};

#endif /* IDE_H_ */
