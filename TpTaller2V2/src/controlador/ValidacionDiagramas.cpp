/*
 * ValidacionDiagramas.cpp
 *
 *  Created on: 16/12/2012
 *      Author: gonzalo
 */

#include "ValidacionDiagramas.h"

ValidacionDiagramas::ValidacionDiagramas(BaseObjectType* cobject,
		const Glib::RefPtr<Gtk::Builder>& builder) :
		Gtk::Dialog(cobject), m_builder(builder) {
	// TODO Auto-generated constructor stub
	Gtk::ScrolledWindow* scrollLista = 0;
	this->m_builder->get_widget("scrolledwindow2", scrollLista);
	scrollLista->add(this->treeView);
	this->refTreeModel = Gtk::ListStore::create(this->m_Columnas);
	this->treeView.set_model(this->refTreeModel);
	this->treeView.append_column("Nombre Diagrama", this->m_Columnas.m_col_Nombre);
	this->treeView.append_column("Modelo", this->m_Columnas.m_col_modeloValido);
	this->treeView.append_column("Vista", this->m_Columnas.m_col_vistaValida);
	this->treeView.show();

	Gtk::Button * botonAceptar;
	this->m_builder->get_widget("button1", botonAceptar);
	botonAceptar->signal_clicked().connect(
			sigc::mem_fun(*this, &ValidacionDiagramas::on_botonAceptar_click));
}

ValidacionDiagramas::~ValidacionDiagramas() {
	// TODO Auto-generated destructor stub
}

void ValidacionDiagramas::cargar_datos(std::vector<std::string> & nombres,
		std::vector<bool>& estado_modelo, std::vector<bool> & estado_vista) {
	size_t i;

	this->refTreeModel->clear();
	for (i = 0; i < nombres.size(); ++i) {
		Gtk::TreeModel::Row row = *(this->refTreeModel->append());
		row[this->m_Columnas.m_col_Nombre] = nombres[i];
		row[this->m_Columnas.m_col_modeloValido] = estado_modelo[i] ? "Valido" : "Invalido";
		row[this->m_Columnas.m_col_vistaValida] = estado_vista[i] ? "Valida" : "Invalida";
	}
}

void ValidacionDiagramas::on_botonAceptar_click() {
	this->hide();
}
