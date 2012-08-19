/*
 * AsistenteAtributo.h
 *
 *  Created on: 30/04/2012
 *      Author: Guagnini Enzo 88325
 */

#ifndef AsistenteAtributo_H_
#define AsistenteAtributo_H_
#include <gtkmm.h>
#include "../vista/componentes/VistaAtributo.h"
#include "../modelo/componentes/Atributo.h"

#include "ComponentsBuilder.h"

class VistaAtributo;


class AsistenteAtributo: public Gtk::Window {
private:
	friend class Gtk::Builder;
	VistaAtributo * vatributo;
	Glib::RefPtr<Gtk::Builder> m_builder;
	Gtk::Entry * entryNombre;
	Gtk::ComboBoxText* comboTipo;
	VistaDiagrama *diagramaActual;

	static AsistenteAtributo * instancia;

	//Tree model columns:
	class ModeloColumnas: public Gtk::TreeModel::ColumnRecord {
	public:

		ModeloColumnas() {
			add(m_col_Nombre);
			add(m_col_esVisible);
			add(m_col_esImprimible);
			add(m_col_Atrib_Pointer);
		}

		Gtk::TreeModelColumn<string> m_col_Nombre;
		Gtk::TreeModelColumn<bool> m_col_esVisible;
		Gtk::TreeModelColumn<bool> m_col_esImprimible;
		Gtk::TreeModelColumn<VistaAtributo*> m_col_Atrib_Pointer;
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

	void inicializarAsistente();
protected:
	virtual void on_about_hide();

public:
	AsistenteAtributo(BaseObjectType* cobject,
			const Glib::RefPtr<Gtk::Builder>& builder);
	virtual ~AsistenteAtributo();
	//static AsistenteAtributo * getInstance(const Glib::RefPtr<Gtk::Builder>& builder);
	//static AsistenteAtributo * getInstance();
	void setAtributo(VistaAtributo* atrib);
	void setDiagActual(VistaDiagrama *vdiagActual);
};

#endif /* AsistenteAtributo_H_ */
