#ifndef VALIDACIONDIAGRAMAS_H_
#define VALIDACIONDIAGRAMAS_H_

#include <gtkmm.h>
#include <string>

class ValidacionDiagramas: public Gtk::Dialog {
private:

	friend class Gtk::Builder;
	//VistaDiagrama * vdiagrama;
	Glib::RefPtr<Gtk::Builder> m_builder;

	//Tree model columns:
	class ModeloColumnas: public Gtk::TreeModel::ColumnRecord {
	public:

		ModeloColumnas() {
			add(m_col_Nombre);
			add (m_col_modeloValido);
			add (m_col_vistaValida);
		}

		Gtk::TreeModelColumn<std::string> m_col_Nombre;
		Gtk::TreeModelColumn<std::string> m_col_modeloValido;
		Gtk::TreeModelColumn<std::string> m_col_vistaValida;
	};

	ModeloColumnas m_Columnas;
	Gtk::TreeView treeView;
	Glib::RefPtr<Gtk::ListStore> refTreeModel;

	void on_botonAceptar_click();

public:
	ValidacionDiagramas(BaseObjectType* cobject,
			const Glib::RefPtr<Gtk::Builder>& builder);
	virtual ~ValidacionDiagramas();

	void cargar_datos(std::vector<std::string> & nombres, std::vector<bool>& estado_modelo,
			std::vector<bool> & estado_vista);
};

#endif /* VALIDACIONDIAGRAMAS_H_ */
