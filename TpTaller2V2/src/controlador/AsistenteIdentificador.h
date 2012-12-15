/*
 * AsistenteIdentificador.h
 *
 *  Created on: 30/04/2012
 *      Author: Guagnini Enzo 88325
 */

#ifndef AsistenteIdentificador_H_
#define AsistenteIdentificador_H_
#include <gtkmm.h>
#include "../vista/componentes/VistaRelacion.h"
#include "../vista/componentes/VistaEntidadNueva.h"
#include "../vista/componentes/VistaAtributo.h"
#include "../vista/componentes/VistaIdentificador.h"
#include "ComponentsBuilder.h"

class VistaRelacion;
class VistaEntidadNueva;
class VistaAtributo;
class VistaDiagrama;
class VistaIdentificador;

class AsistenteIdentificador: public Gtk::Window {
private:
	friend class Gtk::Builder;
	VistaEntidadNueva * ventidad;
	VistaDiagrama * vdiagrama;
	Glib::RefPtr<Gtk::Builder> m_builder;

	//Tree model columns:
		class ModeloColumnasIdent: public Gtk::TreeModel::ColumnRecord {
		public:

			ModeloColumnasIdent() {
				add(m_col_Nombre);
				add(m_col_Ident_Pointer);
			}

			Gtk::TreeModelColumn<string> m_col_Nombre;
			Gtk::TreeModelColumn<VistaIdentificador*> m_col_Ident_Pointer;
		};

		ModeloColumnasIdent m_ColumnasIdent;
		Gtk::TreeView treeViewIdent;
		Glib::RefPtr<Gtk::ListStore> refTreeModelIdent;

	//Tree model Atributes columns:
	class ModeloColumnasAtrib: public Gtk::TreeModel::ColumnRecord {
	public:

		ModeloColumnasAtrib() {
			add(m_col_Nombre);
			add(m_col_selected);
			add(m_col_Atrib_Pointer);
		}

		Gtk::TreeModelColumn<string> m_col_Nombre;
		Gtk::TreeModelColumn<bool> m_col_selected;
		Gtk::TreeModelColumn<VistaAtributo*> m_col_Atrib_Pointer;
	};
	ModeloColumnasAtrib m_ColumnasAtrib;
	Gtk::TreeView treeViewAtrib;
	Glib::RefPtr<Gtk::ListStore> refTreeModelAtrib;

	class ModeloColumnasRel: public Gtk::TreeModel::ColumnRecord {
		public:

			ModeloColumnasRel() {
				add(m_col_Nombre);
				add(m_col_selected);
				add(m_col_Rel_Pointer);
			}

			Gtk::TreeModelColumn<string> m_col_Nombre;
			Gtk::TreeModelColumn<bool> m_col_selected;
			Gtk::TreeModelColumn<VistaUnionEntidadRelacion*> m_col_Rel_Pointer;
		};
		ModeloColumnasRel m_ColumnasRel;
		Gtk::TreeView treeViewRel;
		Glib::RefPtr<Gtk::ListStore> refTreeModelRel;

	void on_botonAceptar_click();
	void on_botonCancelar_click();
	void on_botonEliminarIdentificador_click();
	void on_botonAgregarIdentificador_click();
	void enlazarWidgets();
	bool validar();

	void inicializarAsistente();
	void limpiarListaAtributos();
	void setDiagrama(VistaDiagrama * diag);
	void llenarListaAtributos();
	void llenarListaRelaciones();
	void llenarListaIdentificadores();

protected:
	virtual void on_about_hide();

public:
	AsistenteIdentificador(BaseObjectType* cobject,
				const Glib::RefPtr<Gtk::Builder>& builder);
		virtual ~AsistenteIdentificador();
	//static AsistenteIdentificador * getInstance(const Glib::RefPtr<Gtk::Builder>& builder);
	//static AsistenteIdentificador * getInstance();
	void setEntidad(VistaEntidadNueva* vent);
	//void setDiagrama(VistaDiagrama* diag);
};

#endif /* AsistenteIdentificador_H_ */
