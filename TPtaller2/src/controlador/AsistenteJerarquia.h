/*
 * AsistenteJerarquia.h
 *
 *  Created on: 24/07/2012
 *      Author: Guagnini Enzo 88325
 */

#ifndef ASISTENTEJERARQUIA_H_
#define ASISTENTEJERARQUIA_H_
#include "../vista/componentes/VistaEntidadNueva.h"
#include <gtkmm.h>
#include "ComponentsBuilder.h"
#include <vector>
#include "../vista/componentes/VistaJerarquia.h"
#include "../vista/VistaDiagrama.h"
#include <iostream>

using namespace std;

class VistaJerarquia;
class VistaDiagrama;
class VistaEntidadNueva;

class AsistenteJerarquia : public Gtk::Window{
private:
		friend class Gtk::Builder;
		VistaJerarquia *vjerarquia;
		VistaDiagrama * diagrama;
		Glib::RefPtr<Gtk::Builder> m_builder;
		bool esNuevo;

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

		//Tree model columns For Combo Box:
				class ModeloColumnasCombo: public Gtk::TreeModel::ColumnRecord {
				public:
					ModeloColumnasCombo() {
						add(m_col_Nombre);
						add(m_col_vEnt_Pointer);
					}

					Gtk::TreeModelColumn<string> m_col_Nombre;
					Gtk::TreeModelColumn<VistaEntidad*> m_col_vEnt_Pointer;
				};

		ModeloColumnas m_Columnas;
		ModeloColumnasCombo m_ColumnasCombo;
		Gtk::TreeView treeView;
		Gtk::ComboBox comboBox;
		Glib::RefPtr<Gtk::ListStore> refTreeModel;
		Glib::RefPtr<Gtk::ListStore> refTreeModelCombo;

		void on_botonAceptar_click();
		void on_botonCancelar_click();
		void on_ComboBox_click();
		void enlazarWidgets();
		void llenarListaEntidades(VistaEntidad * omitir);
		void llenarComboBox();
		void limpiarLista();

		void inicializarAsistente();
		void inicializarListaEntidades();
protected:
	virtual void on_about_hide();
public:
	AsistenteJerarquia(BaseObjectType* cobject,const Glib::RefPtr<Gtk::Builder>& builder);
	virtual ~AsistenteJerarquia();

	void setJerarquia(VistaJerarquia* jer);
	void setDiagrama(VistaDiagrama * diag);
	void setEsNuevo();
};

#endif /* ASISTENTEJERARQUIA_H_ */
