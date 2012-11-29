/*
 * AsistenteAtributo.cpp
 *
 *  Created on: 30/04/2012
 *      Author: Guagnini Enzo 88325
 */

#include "AsistenteAtributo.h"
#include "../vista/Ide.h"

AsistenteAtributo * AsistenteAtributo::instancia = NULL;

AsistenteAtributo::AsistenteAtributo(BaseObjectType* cobject,
		const Glib::RefPtr<Gtk::Builder>& builder) :
		Gtk::Window(cobject), m_builder(builder) {
	//this->hide();
	this->vatributo = NULL;
	this->enlazarWidgets();
	this->diagramaActual = Ide::getInstance()->getDiagActual();
}

AsistenteAtributo::~AsistenteAtributo() {

}

void AsistenteAtributo::setDiagActual(VistaDiagrama *vdiagActual) {
	this->diagramaActual = vdiagActual;
}

void AsistenteAtributo::setAtributo(VistaAtributo* attrib) {
	// TODO CARGAR DATOS DE ENTIDAD NUEVA
	this->vatributo = attrib;
	this->inicializarAsistente();
}

void AsistenteAtributo::enlazarWidgets() {
	Gtk::VBox* vbox = 0;
	Gtk::Button* bAceptar = 0;
	Gtk::Button* bCancelar = 0;
	Gtk::Button *bAAtributo = 0, *bMAtributo = 0, *bEAtributo = 0;
	Gtk::ScrolledWindow* scrollLista = 0;

	this->m_builder->get_widget("bAceptar", bAceptar);
	this->m_builder->get_widget("bCancelar", bCancelar);
	this->m_builder->get_widget("bAAtributo", bAAtributo);
	this->m_builder->get_widget("bMAtributo", bMAtributo);
	this->m_builder->get_widget("bEAtributo", bEAtributo);
	this->m_builder->get_widget("entryNombre", entryNombre);

	bAceptar->signal_clicked().connect(
			sigc::mem_fun(*this, &AsistenteAtributo::on_botonAceptar_click));
	bCancelar->signal_clicked().connect(
			sigc::mem_fun(*this, &AsistenteAtributo::on_botonCancelar_click));
	bAAtributo->signal_clicked().connect(
			sigc::mem_fun(*this, &AsistenteAtributo::on_botonAgregarAtributo_click));
	bMAtributo->signal_clicked().connect(
			sigc::mem_fun(*this, &AsistenteAtributo::on_botonModificarAtributo_click));
	bEAtributo->signal_clicked().connect(
			sigc::mem_fun(*this, &AsistenteAtributo::on_botonEliminarAtributo_click));

	this->signal_hide().connect(sigc::mem_fun(*this, &AsistenteAtributo::on_about_hide));

	//Lista
	this->m_builder->get_widget("scrollLista", scrollLista);
	scrollLista->add(this->treeView);
	this->refTreeModel = Gtk::ListStore::create(this->m_Columnas);

	//Agrego modelo a treeview
	this->treeView.set_model(this->refTreeModel);
	this->treeView.append_column("Nombre", this->m_Columnas.m_col_Nombre);
	/*this->treeView.append_column_editable("Visible",
	 this->m_Columnas.m_col_esVisible);
	 this->treeView.append_column_editable("Imprimible",
	 this->m_Columnas.m_col_esImprimible);*/

	Gtk::ComboBoxText* comboTipo = manage(new Gtk::ComboBoxText());
	this->comboTipo = comboTipo;
	this->m_builder->get_widget("vboxDerecha", vbox);
	vbox->add(*comboTipo);
	comboTipo->append_text("Caracterizacion");
	comboTipo->append_text("Copiado");
	comboTipo->append_text("Calculado");
	comboTipo->set_active(1);
	comboTipo->show();
	this->treeView.show();
}

void AsistenteAtributo::on_botonAceptar_click() {
	Gtk::Entry * entryCardMin = 0;
	Gtk::Entry * entryCardMax = 0;
	Gtk::Entry * entryExpresion = 0;
	this->m_builder->get_widget("entryCardMin", entryCardMin);
	this->m_builder->get_widget("entryCardMax", entryCardMax);
	this->m_builder->get_widget("entryExpresion", entryExpresion);

	this->vatributo->getAtributo()->setNombre(this->entryNombre->get_text());
	this->vatributo->getAtributo()->setCardinalidadMinima(entryCardMin->get_text());
	this->vatributo->getAtributo()->setCardinalidadMaxima(entryCardMax->get_text());
	this->vatributo->getAtributo()->setExpresion(entryExpresion->get_text());
	this->vatributo->getAtributo()->setTipo(this->comboTipo->get_active_text());

	this->vatributo->resetearLanzarProp();
	this->hide();
}

void AsistenteAtributo::on_botonCancelar_click() {
	// TODO BORRAR LOS DATOS CONTENIDOS EN LA LISTA Y EN EL ENTRY
	this->vatributo->resetearLanzarProp();
	this->hide();
}

void AsistenteAtributo::on_botonAgregarAtributo_click() {
	//creo el nuevo atributo
	VistaAtributo *atrib = ComponentsBuilder::getInstance()->crearAtributoEnAtributo(
			this->diagramaActual, this->vatributo, NULL);
	//Lo incormoramos en la lista
	Gtk::TreeModel::Row row = *(this->refTreeModel->append());
	row[this->m_Columnas.m_col_Nombre] = atrib->getNombre();
	row[this->m_Columnas.m_col_Atrib_Pointer] = atrib;
	if (atrib->lanzarProp()) {
	} else {
		delete atrib;
	}

}

void AsistenteAtributo::on_botonModificarAtributo_click() {
	Glib::RefPtr<Gtk::TreeSelection> refTreeSelection = this->treeView.get_selection();
	Gtk::TreeModel::iterator iter = refTreeSelection->get_selected();
	if (iter) //If anything is selected
	{
		Gtk::TreeModel::Row row = *iter;
		VistaAtributo *atrib = row[this->m_Columnas.m_col_Atrib_Pointer];
		atrib->lanzarProp();
	}
}

void AsistenteAtributo::on_botonEliminarAtributo_click() {
	Glib::RefPtr<Gtk::TreeSelection> refTreeSelection = this->treeView.get_selection();
	Gtk::TreeModel::iterator iter = refTreeSelection->get_selected();
	if (iter) //If anything is selected
	{
		Gtk::TreeModel::Row row = *iter;
		VistaAtributo *atrib = row[this->m_Columnas.m_col_Atrib_Pointer];
		//TODO Borro el atributo Mediante El builder
		this->refTreeModel->erase(iter);
	}
}

void AsistenteAtributo::inicializarAsistente() {
	Gtk::Entry * entryCardMin = 0;
	Gtk::Entry * entryCardMax = 0;
	Gtk::Entry * entryExpresion = 0;
	this->entryNombre->set_text(this->vatributo->getNombre());
	//Cargo la lista;
	std::vector<VistaAtributo*>::iterator it1 = this->vatributo->atributosBegin();
	std::vector<VistaAtributo*>::iterator it2 = this->vatributo->atributosEnd();
	while (it1 != it2) {
		Gtk::TreeModel::Row row = *(this->refTreeModel->append());
		row[this->m_Columnas.m_col_Nombre] = (*it1)->getNombre();
		row[this->m_Columnas.m_col_Atrib_Pointer] = *it1;
		it1++;
	}
	//cargo cardinalidades
	this->m_builder->get_widget("entryCardMin", entryCardMin);
	entryCardMin->set_text(this->vatributo->getAtributo()->getCardinalidadMinima());
	this->m_builder->get_widget("entryCardMax", entryCardMax);
	entryCardMax->set_text(this->vatributo->getAtributo()->getCardinalidadMaxima());
	this->m_builder->get_widget("entryExpresion", entryExpresion);
	entryExpresion->set_text(this->vatributo->getAtributo()->getExpresion());
	//Cargo el typo
	string tipo = this->vatributo->getAtributo()->getTipo();

	this->comboTipo->set_active(1);
	for (int i = 0; i < 3; i++) {
		if (tipo != this->comboTipo->get_active_text()) {
			this->comboTipo->set_active(i + 1);
		}
	}
}

void AsistenteAtributo::on_about_hide() {
	this->vatributo->resetearLanzarProp();
}
