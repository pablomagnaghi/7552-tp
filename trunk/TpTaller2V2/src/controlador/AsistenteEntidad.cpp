/*
 * AsistenteEntidad.cpp
 *
 *  Created on: 30/04/2012
 *      Author: Guagnini Enzo 88325
 */

#include "AsistenteEntidad.h"

AsistenteEntidad * AsistenteEntidad::instancia = NULL;

AsistenteEntidad::AsistenteEntidad(BaseObjectType* cobject, const Glib::RefPtr<
		Gtk::Builder>& builder) :
	Gtk::Window(cobject), m_builder(builder) {
	this->ventidad = NULL;
	this->enlazarWidgets();
}

AsistenteEntidad::~AsistenteEntidad() {

}

void AsistenteEntidad::setEntidad(VistaEntidadNueva* ent) {
	this->ventidad = ent;
	this->inicializarAsistente();
}

/*
void AsistenteEntidad::setDiagrama(VistaDiagrama* diag) {
	this->vdiagrama = diag;
}*/

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
	this->m_builder->get_widget("entryNombreEntidad", entryNombreEntidad);

	bAceptar->signal_clicked().connect(sigc::mem_fun(*this,
			&AsistenteEntidad::on_botonAceptar_click));
	bCancelar->signal_clicked().connect(sigc::mem_fun(*this,
			&AsistenteEntidad::on_botonCancelar_click));
	bAAtributo->signal_clicked().connect(sigc::mem_fun(*this,
			&AsistenteEntidad::on_botonAgregarAtributo_click));
	bMAtributo->signal_clicked().connect(sigc::mem_fun(*this,
			&AsistenteEntidad::on_botonModificarAtributo_click));
	bEAtributo->signal_clicked().connect(sigc::mem_fun(*this,
			&AsistenteEntidad::on_botonEliminarAtributo_click));
	this->signal_hide().connect(sigc::mem_fun(*this,
							&AsistenteEntidad::on_about_hide));

	//Lista
	this->m_builder->get_widget("scrollLista", scrollLista);
	scrollLista->add(this->treeView);
	this->refTreeModel = Gtk::ListStore::create(this->m_Columnas);

	//Agrego modelo a treeview
	this->treeView.set_model(this->refTreeModel);
	this->treeView.append_column("Nombre",
			this->m_Columnas.m_col_Nombre);
	this->treeView.show();
}

void AsistenteEntidad::on_botonAceptar_click() {
	this->ventidad->setNombre(this->entryNombreEntidad->get_text());
	//this->ventidad->setposini(20, 20);
	this->ventidad->ajustarTamanioAlTexto();
	this->ventidad->resetearLanzarProp();
	this->hide();
}

void AsistenteEntidad::on_botonCancelar_click() {
	// TODO BORRAR LOS DATOS CONTENIDOS EN LA LISTA Y EN EL ENTRY
	this->ventidad->resetearLanzarProp();
	this->hide();
}

void AsistenteEntidad::on_botonAgregarAtributo_click() {
	//creo el nuevo atributo
	VistaAtributo *atrib = ComponentsBuilder::getInstance()->crearAtributoEnEntidad(this->ventidad);
	//Lo incormoramos en la lista
	Gtk::TreeModel::Row row = *(this->refTreeModel->append());
	row[this->m_Columnas.m_col_Nombre] = atrib->getNombre();
	row[this->m_Columnas.m_col_Atrib_Pointer] = atrib;
	if (atrib->lanzarProp()) {
	} else {
		delete atrib;
	}
}

void AsistenteEntidad::on_botonModificarAtributo_click() {
	Glib::RefPtr<Gtk::TreeSelection> refTreeSelection =
			this->treeView.get_selection();
	Gtk::TreeModel::iterator iter = refTreeSelection->get_selected();
	if (iter) //If anything is selected
	{
		Gtk::TreeModel::Row row = *iter;
		VistaAtributo *atrib = row[this->m_Columnas.m_col_Atrib_Pointer];
		atrib->lanzarProp();
	}

	this->inicializarAsistente();
}

void AsistenteEntidad::on_botonEliminarAtributo_click() {
	Glib::RefPtr<Gtk::TreeSelection> refTreeSelection =
			this->treeView.get_selection();
	Gtk::TreeModel::iterator iter = refTreeSelection->get_selected();
	if (iter) //If anything is selected
	{
		Gtk::TreeModel::Row row = *iter;
		VistaAtributo *atrib = row[this->m_Columnas.m_col_Atrib_Pointer];
		//TODO Borro el atributo Mediante El builder
		this->refTreeModel->erase(iter);
	}
}

void AsistenteEntidad::inicializarAsistente() {
	this->entryNombreEntidad->set_text(this->ventidad->getNombre());
	//Cargo la lista;
	limpiarLista();
	std::vector<VistaAtributo*>::iterator it1 = this->ventidad->atributosBegin();
	std::vector<VistaAtributo*>::iterator it2 = this->ventidad->atributosEnd();
	while (it1 != it2) {
		Gtk::TreeModel::Row row = *(this->refTreeModel->append());
		row[this->m_Columnas.m_col_Nombre] = (*it1)->getNombre();
		row[this->m_Columnas.m_col_Atrib_Pointer] = *it1;
		it1++;
	}
}

void AsistenteEntidad::limpiarLista() {
	this->refTreeModel->clear();
}

void AsistenteEntidad::on_about_hide()
{
	this->ventidad->resetearLanzarProp();
}

