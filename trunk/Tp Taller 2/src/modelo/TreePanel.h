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

class TreePanel{
private:
	//Tree model columns:
	class ModeloColumnas: public Gtk::TreeModel::ColumnRecord {
	public:

		ModeloColumnas() {
			add(m_col_Nombre);
		}

		Gtk::TreeModelColumn<string> m_col_Nombre;
	};

	ModeloColumnas m_Columnas;
	Glib::RefPtr<Gtk::TreeStore> refTreeModel;
	Gtk::TreeView treeView;
	Proyecto* proyecto;
	void enlazarWidgets();
	void regenerarRecur(Diagrama* diag, Gtk::TreeModel::Row *row);
public:
	TreePanel(Proyecto* proy);
	virtual ~TreePanel();
	void regenerar();
};

#endif /* TREEPANEL_H_ */
