/*
 * AsistenteJerarquia.cpp
 *
 *  Created on: 24/07/2012
 *      Author: Guagnini Enzo 88325
 */

#include "AsistenteJerarquia.h"

AsistenteJerarquia::AsistenteJerarquia(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder) :
	Gtk::Window(cobject), m_builder(builder) {
	//this->hide();
	this->vjerarquia = NULL;
	this->show();
	this->enlazarWidgets();
	this->diagrama = NULL;
}

AsistenteJerarquia::~AsistenteJerarquia() {

}

void AsistenteJerarquia::setJerarquia(VistaJerarquia* jer) {

	// TODO CARGAR DATOS DE ENTIDAD NUEVA
	this->vjerarquia = jer;
	this->inicializarAsistente();

}


void AsistenteJerarquia::setDiagrama(VistaDiagrama * diag){
	this->diagrama = diag;
	this->llenarListaEntidades();
}
void AsistenteJerarquia::enlazarWidgets() {
	Gtk::Button* bAceptar = 0;
	Gtk::Button* bCancelar = 0;
	Gtk::Entry *entryNombre = 0;
	Gtk::ScrolledWindow* scrollLista = 0;

	this->m_builder->get_widget("bAceptar", bAceptar);
	this->m_builder->get_widget("bCancelar", bCancelar);
	this->m_builder->get_widget("entryNombre", entryNombre);

	bAceptar->signal_clicked().connect(sigc::mem_fun(*this,
			&AsistenteJerarquia::on_botonAceptar_click));
	bCancelar->signal_clicked().connect(sigc::mem_fun(*this,
			&AsistenteJerarquia::on_botonCancelar_click));

	this->signal_hide().connect(sigc::mem_fun(*this,
						&AsistenteJerarquia::on_about_hide));

	//Lista
	this->m_builder->get_widget("scrollLista", scrollLista);
	scrollLista->add(this->treeView);
	this->refTreeModel = Gtk::ListStore::create(this->m_Columnas);

	//Agrego modelo a treeview
	this->treeView.set_model(this->refTreeModel);
	this->treeView.append_column("Nombre",
			this->m_Columnas.m_col_Nombre);
	this->treeView.append_column_editable("Selected",
			this->m_Columnas.m_col_selected);


	/*Gtk::ComboBoxText* comboTipo = manage(new Gtk::ComboBoxText());
	this->comboTipo = comboTipo;
	this->m_builder->get_widget("vboxDerecha", vbox);
	vbox->add(*comboTipo);
	comboTipo->append_text("Caracterizacion");
	comboTipo->append_text("Copiado");
	comboTipo->append_text("Calculado");
	comboTipo->set_active(1);
	comboTipo->show();*/
	//this->llenarListaEntidades();
	this->treeView.show();
}

void AsistenteJerarquia::llenarListaEntidades(){
	/*cout<<"LLEGO2222!!!"<<endl;
	//vector<VistaEntidadNueva*>::iterator it1 =Ide::diagactual->vEntidadesBegin();
	cout<<"LLEGO2222!!!"<<endl;
	//vector<VistaEntidadNueva*>::iterator it2 = Ide::diagactual->vEntidadesEnd();
	Gtk::TreeModel::Row row;

	while (it1 != it2){
		row = *(this->refTreeModel->append());
		row[this->m_Columnas.m_col_Nombre] = (*it1)->getNombre();
		row[this->m_Columnas.m_col_vEnt_Pointer] = *(it1);
		row[this->m_Columnas.m_col_selected] =false;
		it1++;
	}*/
}

void AsistenteJerarquia::on_botonAceptar_click() {
	/*Gtk::Entry * entryCardMin = 0;
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
	this->hide();*/
}

void AsistenteJerarquia::on_botonCancelar_click() {
	// TODO BORRAR LOS DATOS CONTENIDOS EN LA LISTA Y EN EL ENTRY
	this->vjerarquia->resetearLanzarProp();
	this->hide();
}



void AsistenteJerarquia::inicializarAsistente() {
	/*Gtk::Entry * entryCardMin = 0;
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
	for (int i =0;i<3;i++){
		if (tipo != this->comboTipo->get_active_text()){
			this->comboTipo->set_active(i+1);
		}
	}*/
}

void AsistenteJerarquia::on_about_hide()
{
	this->vjerarquia->resetearLanzarProp();
}

