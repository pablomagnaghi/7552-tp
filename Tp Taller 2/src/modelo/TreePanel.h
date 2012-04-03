/*
 * TreePanel.h
 *
 *  Created on: 02/04/2012
 *      Author: Guagnini Enzo 88325
 */

#ifndef TREEPANEL_H_
#define TREEPANEL_H_
#include "Proyecto.h"

class TreePanel : Gtk::TreeView{
private:
	//Tree model columns:
		  class ModeloColumnas : public Gtk::TreeModel::ColumnRecord
		  {
		  public:

		    ModeloColumnas()
		    { add(m_col_Nombre);}

		    Gtk::TreeModelColumn<string> m_col_Nombre;
		  };

		  ModeloColumnas m_Columnas;
		  Glib::RefPtr<Gtk::TreeStore> refTreeModel;
		  Proyecto* proyecto;

public:
	TreePanel(Proyecto* proy);
	virtual ~TreePanel();
	void regenerar();
};

#endif /* TREEPANEL_H_ */
