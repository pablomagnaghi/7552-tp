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
#include "ComponentsBuilder.h"
#include <vector>

class VistaRelacion;
class VistaEntidadNueva;
//class VistaAtributo;
class VistaDiagrama;

class AsistenteRelacion: public Gtk::Window {
private:
	friend class Gtk::Builder;
	VistaRelacion * vrelacion;
	//VistaDiagrama * vdiagrama;
	Glib::RefPtr<Gtk::Builder> m_builder;
	Gtk::Entry * entryNombreRelacion;
	VistaDiagrama *diagramaActual;

	static AsistenteRelacion * instancia;

	//Tree model columns:
	class ModeloColumnas: public Gtk::TreeModel::ColumnRecord {
	public:
		ModeloColumnas() {
			add(m_col_Nombre);
			add(m_col_selected);
			add(m_col_vEnt_Pointer);
		}

		Gtk::TreeModelColumn<string> m_col_Nombre;
		Gtk::TreeModelColumn<bool> m_col_selected;
		Gtk::TreeModelColumn<VistaEntidadNueva*> m_col_vEnt_Pointer;
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
	void limpiarLista();
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
