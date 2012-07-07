/*
 * AsistenteEntidad.h
 *
 *  Created on: 30/04/2012
 *      Author: Guagnini Enzo 88325
 */

#ifndef ASISTENTEENTIDAD_H_
#define ASISTENTEENTIDAD_H_
#include <gtkmm.h>
#include "../vista/componentes/VistaEntidadNueva.h"

class VistaEntidadNueva;

// SINGLETON

class AsistenteEntidad: public Gtk::Dialog {
private:
	friend class Gtk::Builder;
	VistaEntidadNueva * entidad;
	Glib::RefPtr<Gtk::Builder> m_builder;
	Gtk::Entry * entryNombreEntidad;

	static AsistenteEntidad * instancia;

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

	void on_botonAceptar_click();
	void on_botonCancelar_click();
	void on_botonAgregarAtributo_click();
	void on_botonModificarAtributo_click();
	void on_botonEliminarAtributo_click();
	void enlazarWidgets();

	void inicializarDialogo();

	AsistenteEntidad(BaseObjectType* cobject,
			const Glib::RefPtr<Gtk::Builder>& builder);
	virtual ~AsistenteEntidad();

public:
	static AsistenteEntidad * getInstance(const Glib::RefPtr<Gtk::Builder>& builder);
	static AsistenteEntidad * getInstance();
	void setEntidad(VistaEntidadNueva* ent);
};

#endif /* ASISTENTEENTIDAD_H_ */
