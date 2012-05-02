/*
 * AsistenteEntidad.cpp
 *
 *  Created on: 30/04/2012
 *      Author: Guagnini Enzo 88325
 */

#include "AsistenteEntidad.h"

AsistenteEntidad::AsistenteEntidad(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder)
: Gtk::Window(cobject),
m_builder(builder) {
	this->entidad = NULL;
	this->enlazarWidgets();
}

AsistenteEntidad::~AsistenteEntidad() {
	// TODO Auto-generated destructor stub
}

void AsistenteEntidad::setEntidad(VistaEntidad* ent) {
	this->entidad = ent;

}

void AsistenteEntidad::enlazarWidgets() {
	Gtk::Button* bAceptar = 0;
	Gtk::Button* bCancelar = 0;
	Gtk::Button *bAAtributo = 0, *bMAtributo = 0, *bEAtributo = 0;
	Gtk::ScrolledWindow* scrollLista = 0;

	this->m_builder->get_widget("bAceptar", bAceptar);
	this->m_builder->get_widget("bCancelar", bCancelar);
	this->m_builder->get_widget("bAAtributo", bAAtributo);
	this->m_builder->get_widget("bMAtributo", bMAtributo);
	this->m_builder->get_widget("bEAtributo", bEAtributo);

	bAceptar->signal_clicked().connect(sigc::mem_fun(*this,
			&AsistenteEntidad::on_clicked_bAceptar));
	bCancelar->signal_clicked().connect(sigc::mem_fun(*this,
			&AsistenteEntidad::on_clicked_bCancelar));
	bAAtributo->signal_clicked().connect(sigc::mem_fun(*this,
			&AsistenteEntidad::on_clicked_bAAtributo));
	bMAtributo->signal_clicked().connect(sigc::mem_fun(*this,
			&AsistenteEntidad::on_clicked_bMAtributo));
	bEAtributo->signal_clicked().connect(sigc::mem_fun(*this,
			&AsistenteEntidad::on_clicked_bEAtributo));

	//Lista
	this->m_builder->get_widget("scrollLista", scrollLista);
	scrollLista->add(this->treeView);
	this->refTreeModel = Gtk::ListStore::create(this->m_Columnas);

	//Agrego modelo a treeview
	this->treeView.set_model(this->refTreeModel);
	this->treeView.append_column_editable("Nombre",
			this->m_Columnas.m_col_Nombre);
	this->treeView.append_column_editable("Visible",
			this->m_Columnas.m_col_esVisible);
	this->treeView.append_column_editable("Imprimible",
			this->m_Columnas.m_col_esImprimible);
	this->treeView.show();
}

void AsistenteEntidad::on_clicked_bAceptar(){
	/*Gtk::Entry *entryNombre = 0, *entryPath = 0;
	this->m_builder->get_widget("entryNombre", entryNombre);
	this->m_builder->get_widget("entryPath", entryPath);
	this->lista->nombre = entryNombre->get_text();
	if (entryPath->get_text() ==""){
		Gtk::MessageDialog mensaje(*this, "Error.", false,
						Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK);
				mensaje.set_secondary_text("No ingreso XPath de la lista.");
				mensaje.run();
	}else{
	this->lista->path = entryPath->get_text();
	typedef Gtk::TreeModel::Children type_children;
	type_children children = this->refTreeModel->children();
	type_children::iterator iter = children.begin();
	type_children::iterator iter1 = children.end();
	if (iter != iter1){
		this->lista->vaciarLista();
		while (iter != iter1){
			Gtk::TreeModel::Row row = *iter;
			string nombre = row[this->m_Columnas.m_col_Nombre];
			string datocalculo = row[this->m_Columnas.m_col_DatoCalculo];
			bool escalc = row[this->m_Columnas.m_col_esCalculable];
			this->lista->agregarColumna(nombre, datocalculo, escalc);
			iter++;
		}
	}
	this->lista->hoja->redibujar();
	this->hide_all();
	}*/
}

void AsistenteEntidad::on_clicked_bCancelar(){
	this->hide_all();
}

void AsistenteEntidad::on_clicked_bAAtributo(){
	/*Gtk::TreeModel::Row row = *(this->refTreeModel->append());
	row[this->m_Columnas.m_col_Nombre] = "NuevaColumna";
	row[this->m_Columnas.m_col_esCalculable] = false;
	row[this->m_Columnas.m_col_DatoCalculo] = "Ingrese Dato";*/
}

void AsistenteEntidad::on_clicked_bMAtributo(){
	/*Gtk::TreeModel::Row row = *(this->refTreeModel->append());
	row[this->m_Columnas.m_col_Nombre] = "NuevaColumna";
	row[this->m_Columnas.m_col_esCalculable] = true;
	row[this->m_Columnas.m_col_DatoCalculo] = "Ingrese Calculo";*/
}

void AsistenteEntidad::on_clicked_bEAtributo(){
	Glib::RefPtr<Gtk::TreeSelection> refTreeSelection =this->treeView.get_selection();
	Gtk::TreeModel::iterator iter = refTreeSelection->get_selected();

	if(iter) //If anything is selected
	{
	  //Gtk::TreeModel::Row row = *iter;
	  this->refTreeModel->erase(iter);
	}
}
