#ifndef ASISTENTERELACION_H_
#define ASISTENTERELACION_H_

#include "../vista/componentes/VistaEntidadNueva.h"
#include <gtkmm.h>
#include "ComponentsBuilder.h"
#include <vector>
#include "../vista/componentes/VistaRelacion.h"
#include "../vista/VistaDiagrama.h"
#include "AsistenteAtributo.h"
#include <iostream>

class AsistenteAtributo;
/*
class AsistenteRelacion: public Gtk::Window {
private:
private:
	friend class Gtk::Builder;
	VistaRelacion * vrelacion;
	Glib::RefPtr<Gtk::Builder> m_builder;
	Gtk::Entry * entryNombre;
	Gtk::ComboBoxText* comboTipo;
	VistaDiagrama *diagramaActual;

	static AsistenteAtributo * instancia;

	//Tree model columns:
	class ModeloColumnasAtributos: public Gtk::TreeModel::ColumnRecord {
	public:

		ModeloColumnasAtributos() {
			add(m_col_Nombre);
			add(m_col_esVisible);
			add(m_col_esImprimible);
			add(m_col_Atrib_Pointer);
		}

		Gtk::TreeModelColumn<string> m_col_Nombre;
		Gtk::TreeModelColumn<bool> m_col_esVisible;
		Gtk::TreeModelColumn<bool> m_col_esImprimible;
		Gtk::TreeModelColumn<VistaRelacion*> m_col_Atrib_Pointer;
	};

	class ModeloColumnasEntidades: public Gtk::TreeModel::ColumnRecord {
	public:

		ModeloColumnasEntidades() {
			add(m_col_Nombre);
			add(m_col_esVisible);
			add(m_col_esImprimible);
			add(m_col_Atrib_Pointer);
		}

		Gtk::TreeModelColumn<string> m_col_Nombre;
		Gtk::TreeModelColumn<bool> m_col_esVisible;
		Gtk::TreeModelColumn<bool> m_col_esImprimible;
		Gtk::TreeModelColumn<VistaRelacion*> m_col_Atrib_Pointer;
	};

	ModeloColumnasAtributos m_Columnas;
	Gtk::TreeView treeView;
	Glib::RefPtr<Gtk::ListStore> refTreeModel;
	Gtk::TreeView listView;
	Glib::RefPtr<Gtk::ListStore> refListModel;

	void on_botonAceptar_click();
	void on_botonCancelar_click();
	void on_botonAgregarAtributo_click();
	void on_botonModificarAtributo_click();
	void on_botonEliminarAtributo_click();
	void on_botonAgregarEntidad_click();
	void on_botonQuitarEntidad_click();
	void enlazarWidgets();

	void inicializarAsistente();

protected:
	virtual void on_about_hide();
public:
	AsistenteRelacion(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);
	virtual ~AsistenteRelacion();
	void setRelacion(VistaRelacion* rel);
	void setDiagrama(VistaDiagrama * diag);
};
*/
#endif /* ASISTENTERELACION_H_ */
