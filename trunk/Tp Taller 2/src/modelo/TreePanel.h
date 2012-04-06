/*
 * TreePanel.h
 *
 *  Created on: 02/04/2012
 *      Author: Guagnini Enzo 88325
 */

#ifndef TREEPANEL_H_
#define TREEPANEL_H_

#include "Proyecto.h"
#include <iostream>
#include "../Constantes.h"
using namespace std;

class Proyecto;

typedef GtkRequisition Requisition;

class TreePanel : Gtk::TreeView{
private:
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
	Proyecto* proyecto;
	void enlazarWidgets();
	void regenerarRecur(Diagrama* diag, Gtk::TreeModel::Row *row);
	virtual bool on_button_press_event(GdkEventButton* event);
public:
	TreePanel(Proyecto* proy);
	virtual ~TreePanel();
	void regenerar();
};

#endif /* TREEPANEL_H_ */
