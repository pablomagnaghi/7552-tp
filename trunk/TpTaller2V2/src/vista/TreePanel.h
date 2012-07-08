/*
 * TreePanel.h
 *
 *  Created on: 02/04/2012
 *      Author: Guagnini Enzo 88325
 */

#ifndef TREEPANEL_H_
#define TREEPANEL_H_

#include "VistaProyecto.h"
#include <iostream>
#include <gtkmm.h>
#include "VistaConstantes.h"
using namespace std;

class Ide;

typedef GtkRequisition Requisition;

class TreePanel : Gtk::TreeView{
private:
	Ide *ide;
	const Glib::RefPtr<Gtk::Builder>& Ide_builder;
	//Tree model columns:
	class ModeloColumnas: public Gtk::TreeModel::ColumnRecord {
	public:

		ModeloColumnas() {
			add(m_col_Nombre);
			add(m_col_Diag_Pointer);
			add(m_col_Comp_Pointer);
			add(m_col_esDiag);
		}

		Gtk::TreeModelColumn<string> m_col_Nombre;
		Gtk::TreeModelColumn<Diagrama*> m_col_Diag_Pointer;
		Gtk::TreeModelColumn<Componente*> m_col_Comp_Pointer;
		Gtk::TreeModelColumn<bool> m_col_esDiag;
	};

	ModeloColumnas m_Columnas;
	Glib::RefPtr<Gtk::TreeStore> refTreeModel;
	VistaProyecto* vproyecto;
	void enlazarWidgets();
	void regenerarRecur(Diagrama* diag, Gtk::TreeModel::Row *row);
	virtual bool on_button_press_event(GdkEventButton* event);
	bool hayProyecto();
public:
	TreePanel(const Glib::RefPtr<Gtk::Builder>& Ide_b, Ide* i);
	virtual ~TreePanel();
	bool regenerar();
};

#endif /* TREEPANEL_H_ */
