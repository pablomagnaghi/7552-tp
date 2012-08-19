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
#include "../modelo/componentes/Atributo.h"
#include "../vista/componentes/VistaAtributo.h"
#include "ComponentsBuilder.h"
#include <vector>

class VistaEntidadNueva;
class VistaAtributo;
class VistaDiagrama;

class AsistenteEntidad: public Gtk::Window {
private:
	friend class Gtk::Builder;
	VistaEntidadNueva * ventidad;
	//VistaDiagrama * vdiagrama;
	Glib::RefPtr<Gtk::Builder> m_builder;
	Gtk::Entry * entryNombreEntidad;
	VistaDiagrama *diagramaActual;

	static AsistenteEntidad * instancia;

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
	void limpiarLista();
protected:
	virtual void on_about_hide();

public:
	AsistenteEntidad(BaseObjectType* cobject,
				const Glib::RefPtr<Gtk::Builder>& builder);
		virtual ~AsistenteEntidad();
	//static AsistenteEntidad * getInstance(const Glib::RefPtr<Gtk::Builder>& builder);
	//static AsistenteEntidad * getInstance();
	void setEntidad(VistaEntidadNueva* ent);
	//void setDiagrama(VistaDiagrama* diag);
};

#endif /* ASISTENTEENTIDAD_H_ */
