/*
 * TreePanel.h
 *
 *  Created on: 02/04/2012
 *      Author: Guagnini Enzo 88325
 */

#ifndef TREEPANEL_H_
#define TREEPANEL_H_

#include <iostream>

#include <gtkmm.h>
#include "VistaConstantes.h"
#include "VistaDiagrama.h"

#include "./componentes/VistaComponente.h"
#include "VistaDiagrama.h"
using namespace std;

class VistaDiagrama;

typedef GtkRequisition Requisition;

class Ide;


// public Para que no tire error cuando se conecta la señal
// del menu popup
class TreePanel: public Gtk::TreeView {
private:
	Ide *ide;
	const Glib::RefPtr<Gtk::Builder>& Ide_builder;
	//Tree model columns:
	class ModeloColumnas: public Gtk::TreeModel::ColumnRecord {
	public:

		ModeloColumnas() {
			add(m_col_Nombre);
			add(m_col_vDiag_Pointer);
			add(m_col_vComp_Pointer);
			add(m_col_esDiag);
		}

		Gtk::TreeModelColumn<string> m_col_Nombre;
		Gtk::TreeModelColumn<VistaDiagrama*> m_col_vDiag_Pointer;
		Gtk::TreeModelColumn<VistaComponente*> m_col_vComp_Pointer;
		Gtk::TreeModelColumn<bool> m_col_esDiag;
	};

	ModeloColumnas m_Columnas;
	Glib::RefPtr<Gtk::TreeStore> refTreeModel;
	void enlazarWidgets();
	void regenerarRecur(VistaDiagrama* diag, Gtk::TreeModel::Row *row);
	virtual bool on_button_press_event(GdkEventButton* event);
	bool hayProyecto();
	void limpiar();

	void lanzarPopup(GdkEventButton* event);

	void on_popup_boton_agregar_diagrama_hijo();
	void on_popup_boton_eliminar_diagrama();

public:


	TreePanel(const Glib::RefPtr<Gtk::Builder>& Ide_b, Ide* i);
	virtual ~TreePanel();
	bool regenerar();
};

#endif /* TREEPANEL_H_ */
