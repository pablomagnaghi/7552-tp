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
	Gtk::Dialog(cobject), m_builder(builder) {
	//this->hide();
	this->entidad = NULL;
	this->enlazarWidgets();
}

AsistenteEntidad::~AsistenteEntidad() {

}

void AsistenteEntidad::setEntidad(VistaEntidadNueva* ent) {

	// TODO CARGAR DATOS DE ENTIDAD NUEVA
	this->inicializarDialogo();
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

void AsistenteEntidad::on_botonAceptar_click() {
	//Gtk::Entry *entryPath = 0;
	//this->m_builder->get_widget("entryPath", entryPath);
	this->entidad->setNombre(this->entryNombreEntidad->get_text());
	this->entidad->setposini(20, 20);
	//this->entidad->ajustarTamanioAlTexto();
	/* 	if (entryPath->get_text() == "") {
	 Gtk::MessageDialog mensaje(*this, "Error.", false, Gtk::MESSAGE_ERROR,
	 Gtk::BUTTONS_OK);
	 mensaje.set_secondary_text("No ingreso XPath de la lista.");
	 mensaje.run();
	 } else {
	 this->lista->path = entryPath->get_text();
	 typedef Gtk::TreeModel::Children type_children;
	 type_children children = this->refTreeModel->children();
	 type_children::iterator iter = children.begin();
	 type_children::iterator iter1 = children.end();
	 if (iter != iter1) {
	 this->lista->vaciarLista();
	 while (iter != iter1) {
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
	// TODO BORRAR LOS DATOS CONTENIDOS EN LA LISTA Y EN EL ENTRY
	this->hide();
}

void AsistenteEntidad::on_botonCancelar_click() {
	// TODO BORRAR LOS DATOS CONTENIDOS EN LA LISTA Y EN EL ENTRY
	this->hide();
}

void AsistenteEntidad::on_botonAgregarAtributo_click() {
	/*Gtk::TreeModel::Row row = *(this->refTreeModel->append());
	 row[this->m_Columnas.m_col_Nombre] = "NuevaColumna";
	 row[this->m_Columnas.m_col_esCalculable] = false;
	 row[this->m_Columnas.m_col_DatoCalculo] = "Ingrese Dato";*/
}

void AsistenteEntidad::on_botonModificarAtributo_click() {
	/*Gtk::TreeModel::Row row = *(this->refTreeModel->append());
	 row[this->m_Columnas.m_col_Nombre] = "NuevaColumna";
	 row[this->m_Columnas.m_col_esCalculable] = true;
	 row[this->m_Columnas.m_col_DatoCalculo] = "Ingrese Calculo";*/
}

void AsistenteEntidad::on_botonEliminarAtributo_click() {
	Glib::RefPtr<Gtk::TreeSelection> refTreeSelection =
			this->treeView.get_selection();
	Gtk::TreeModel::iterator iter = refTreeSelection->get_selected();

	if (iter) //If anything is selected
	{
		//Gtk::TreeModel::Row row = *iter;
		this->refTreeModel->erase(iter);
	}
}

void AsistenteEntidad::inicializarDialogo() {
	this->entryNombreEntidad->set_text("");
}

AsistenteEntidad * AsistenteEntidad::getInstance(const Glib::RefPtr<
		Gtk::Builder>& builder) {
	if (AsistenteEntidad::instancia == NULL) {
		builder->get_widget_derived("PropEntidad", AsistenteEntidad::instancia);
	}
	return AsistenteEntidad::instancia;
}

AsistenteEntidad * AsistenteEntidad::getInstance() {
	if (AsistenteEntidad::instancia != NULL) {
		return AsistenteEntidad::instancia;
	} else {
#ifdef DEBUG
		cout << "Error Instancia No creada" << endl;
#endif
	}
	return NULL;
}
