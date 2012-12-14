/*
 * AsistenteEntGlobal.h
 *
 *  Created on: 24/07/2012
 *      Author: Guagnini Enzo 88325
 */

#ifndef AsistenteEntGlobal_H_
#define AsistenteEntGlobal_H_
#include "../vista/componentes/VistaEntidadNueva.h"
#include "../vista/componentes/VistaEntidadGlobal.h"
#include <gtkmm.h>
#include "ComponentsBuilder.h"
#include <vector>
#include "../vista/VistaDiagrama.h"
#include <iostream>

using namespace std;

class VistaDiagrama;
class VistaEntidadGlobal;
class VistaEntidadNueva;

class AsistenteEntGlobal : public Gtk::Window{
private:
		friend class Gtk::Builder;
		VistaDiagrama * vdiagrama;
		Glib::RefPtr<Gtk::Builder> m_builder;

		static AsistenteEntGlobal * instancia;

		//Tree model columns:
		class ModeloColumnasDiag: public Gtk::TreeModel::ColumnRecord {
		public:
			ModeloColumnasDiag() {
				add(m_col_Nombre);
				add(m_col_vDiag_Pointer);
			}
			Gtk::TreeModelColumn<string> m_col_Nombre;
			Gtk::TreeModelColumn<VistaDiagrama*> m_col_vDiag_Pointer;
		};

		ModeloColumnasDiag m_ColumnasDiagramas;
		Gtk::TreeView treeViewDiagramas;
		Glib::RefPtr<Gtk::ListStore> refTreeModelDiagramas;

		//Tree model columns For Combo Box:
		//Tree modelEntidades columns:
		class ModeloColumnasEntidades: public Gtk::TreeModel::ColumnRecord {
		public:
			ModeloColumnasEntidades() {
				add(m_col_Nombre);
				add(m_col_vEnt_Pointer);
			}

			Gtk::TreeModelColumn<string> m_col_Nombre;
			Gtk::TreeModelColumn<VistaEntidadNueva*> m_col_vEnt_Pointer;
		};

		ModeloColumnasEntidades m_ColumnasEntidades;
		Gtk::TreeView treeViewEntidades;
		Glib::RefPtr<Gtk::ListStore> refTreeModelEntidades;

		void on_botonAceptar_click();
		void on_botonCancelar_click();
		void on_bSelecDiag_click();
		void enlazarWidgets();
		void llenarListaEntidades(VistaDiagrama *diag);
		void llenarListaDiagramas();
		void limpiarListaEntidades();
		void inicializarAsistente();

protected:
	virtual void on_about_hide();
public:
	AsistenteEntGlobal(BaseObjectType* cobject,const Glib::RefPtr<Gtk::Builder>& builder);
	virtual ~AsistenteEntGlobal();

	void setEntidadGola(VistaJerarquia* jer);
	void setDiagrama(VistaDiagrama * diag);
};

#endif /* AsistenteEntGlobal_H_ */
