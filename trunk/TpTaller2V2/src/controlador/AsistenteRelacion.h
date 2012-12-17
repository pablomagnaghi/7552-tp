/*
 * AsistenteRelacion.h
 *
 *  Created on: 30/04/2012
 *      Author: Guagnini Enzo 88325
 */

#ifndef ASISTENTERELACION_H_
#define ASISTENTERELACION_H_
#include <gtkmm.h>
#include "../modelo/componentes/Relacion.h"
#include "../vista/componentes/VistaRelacion.h"
#include "../vista/componentes/VistaEntidadNueva.h"
#include "../vista/componentes/VistaAtributo.h"
#include "ComponentsBuilder.h"

class VistaRelacion;
class VistaEntidadNueva;
class VistaAtributo;
class VistaDiagrama;

class AsistenteRelacion: public Gtk::Window {
private:
	friend class Gtk::Builder;
	VistaRelacion * vrelacion;
	VistaDiagrama * vdiagrama;
	Glib::RefPtr<Gtk::Builder> m_builder;
	Gtk::Entry * entryNombreRelacion;
	VistaDiagrama *diagramaActual;
	Gtk::ComboBoxText comboTipo;

	static AsistenteRelacion * instancia;

	//Tree modelEntidades columns:
	class ModeloColumnasEntidades: public Gtk::TreeModel::ColumnRecord {
	public:
		ModeloColumnasEntidades() {
			add(m_col_Nombre);
			add(m_col_CMin);
			add(m_col_CMax);
			add(m_col_selected);
			add(m_col_vEnt_Pointer);
		}

		Gtk::TreeModelColumn<string> m_col_Nombre;
		Gtk::TreeModelColumn<string> m_col_CMin;
		Gtk::TreeModelColumn<string> m_col_CMax;
		Gtk::TreeModelColumn<bool> m_col_selected;
		Gtk::TreeModelColumn<VistaEntidad*> m_col_vEnt_Pointer;
	};

	ModeloColumnasEntidades m_ColumnasEntidades;
	Gtk::TreeView treeViewEntidades;
	Glib::RefPtr<Gtk::ListStore> refTreeModelEntidades;

	//Tree model Atributes columns:
	class ModeloColumnasAtrib: public Gtk::TreeModel::ColumnRecord {
	public:

		ModeloColumnasAtrib() {
			add(m_col_Nombre);
			add(m_col_Atrib_Pointer);
		}

		Gtk::TreeModelColumn<string> m_col_Nombre;
		Gtk::TreeModelColumn<VistaAtributo*> m_col_Atrib_Pointer;
	};
	ModeloColumnasAtrib m_ColumnasAtrib;
	Gtk::TreeView treeViewAtrib;
	Glib::RefPtr<Gtk::ListStore> refTreeModelAtrib;

	void on_botonAceptar_click();
	void on_botonCancelar_click();
	void on_botonAgregarAtributo_click();
	void on_botonModificarAtributo_click();
	void on_botonEliminarAtributo_click();
	void enlazarWidgets();

	void inicializarAsistente();
	void limpiarListaEntidades();
	void setDiagrama(VistaDiagrama * diag);
	void llenarListaEntidades();
	void inicializarListaEntidades();
	void iniicializarListaAtributos();
protected:
	virtual void on_about_hide();

public:
	AsistenteRelacion(BaseObjectType* cobject,
				const Glib::RefPtr<Gtk::Builder>& builder);
		virtual ~AsistenteRelacion();
	//static AsistenteRelacion * getInstance(const Glib::RefPtr<Gtk::Builder>& builder);
	//static AsistenteRelacion * getInstance();
	void setRelacion(VistaRelacion* rel);
	//void setDiagrama(VistaDiagrama* diag);
};

#endif /* ASISTENTERELACION_H_ */
