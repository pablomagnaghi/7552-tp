/*
 * AsistenteEntidad.h
 *
 *  Created on: 30/04/2012
 *      Author: Guagnini Enzo 88325
 */

#ifndef ASISTENTEENTIDAD_H_
#define ASISTENTEENTIDAD_H_
#include <gtkmm.h>
#include "../vista/componentes/VistaEntidad.h"

class VistaEntidad;

class AsistenteEntidad: public Gtk::Window {
private:
	VistaEntidad* entidad;
	Glib::RefPtr<Gtk::Builder> m_builder;

	//Tree model columns:
	class ModeloColumnas: public Gtk::TreeModel::ColumnRecord {
	public:

		ModeloColumnas() {
			add(m_col_Nombre);
			add(m_col_esVisible);
			add(m_col_esImprimible);
		}

		Gtk::TreeModelColumn<string> m_col_Nombre;
		Gtk::TreeModelColumn<bool> m_col_esVisible;
		Gtk::TreeModelColumn<bool> m_col_esImprimible;
	};

	ModeloColumnas m_Columnas;
	Gtk::TreeView treeView;
	Glib::RefPtr<Gtk::ListStore> refTreeModel;

	void on_clicked_bAceptar();
	void on_clicked_bCancelar();
	void on_clicked_bAAtributo();
	void on_clicked_bMAtributo();
	void on_clicked_bEAtributo();
	void enlazarWidgets();

public:
	AsistenteEntidad(BaseObjectType* cobject,
			const Glib::RefPtr<Gtk::Builder>& builder);
	virtual ~AsistenteEntidad();
	void setEntidad(VistaEntidad* ent);
};

#endif /* ASISTENTEENTIDAD_H_ */
