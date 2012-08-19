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
//#include "../vista/Ide.h"
using namespace std;

class VistaJerarquia;
class VistaDiagrama;


class AsistenteJerarquia : public Gtk::Window{
private:
		friend class Gtk::Builder;
		VistaJerarquia *vjerarquia;
		VistaDiagrama * diagrama;
		Glib::RefPtr<Gtk::Builder> m_builder;

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
			Gtk::TreeModelColumn<VistaEntidad*> m_col_vEnt_Pointer;

		};

		ModeloColumnas m_Columnas;
		Gtk::TreeView treeView;
		Glib::RefPtr<Gtk::ListStore> refTreeModel;

		void on_botonAceptar_click();
		void on_botonCancelar_click();
		void enlazarWidgets();
		void llenarListaEntidades();

		void inicializarAsistente();
protected:
	virtual void on_about_hide();
public:
	AsistenteJerarquia(BaseObjectType* cobject,const Glib::RefPtr<Gtk::Builder>& builder);
	virtual ~AsistenteJerarquia();

	void setJerarquia(VistaJerarquia* jer);
	void setDiagrama(VistaDiagrama * diag);
};

#endif /* ASISTENTEJERARQUIA_H_ */
