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
	this->llenarListaEntidades(NULL);
	this->llenarComboBox();
}
void AsistenteJerarquia::enlazarWidgets() {
	Gtk::Button* bAceptar = 0;
	Gtk::Button* bCancelar = 0;
	Gtk::Entry *entryNombre = 0;
	Gtk::ScrolledWindow* scrollLista = 0;
	Gtk::Fixed * fixed = 0;

	this->m_builder->get_widget("bAceptar", bAceptar);
	this->m_builder->get_widget("bCancelar", bCancelar);
	this->m_builder->get_widget("entryNombre", entryNombre);
	this->m_builder->get_widget("fixed3", fixed);

	bAceptar->signal_clicked().connect(sigc::mem_fun(*this,
			&AsistenteJerarquia::on_botonAceptar_click));
	bCancelar->signal_clicked().connect(sigc::mem_fun(*this,
			&AsistenteJerarquia::on_botonCancelar_click));
	this->comboBox.signal_changed().connect(sigc::mem_fun(*this,
			&AsistenteJerarquia::on_ComboBox_click));

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

	this->refTreeModelCombo = Gtk::ListStore::create(this->m_ColumnasCombo);
	this->comboBox.set_model(this->refTreeModelCombo);
	this->comboBox.pack_start(this->m_ColumnasCombo.m_col_Nombre);
	this->comboBox.set_active(0);
	this->comboBox.set_size_request(120,25);
	fixed->put(this->comboBox,200,50);

	this->treeView.show();
	this->show_all();
}

void AsistenteJerarquia::llenarListaEntidades(VistaEntidadNueva * omitir){
	this->limpiarLista();
	std::vector<VistaEntidadNueva *>::iterator it1 =  this->diagrama->vEntidadesBegin();
	std::vector<VistaEntidadNueva *>::iterator it2 =  this->diagrama->vEntidadesEnd();
	while (it1 != it2){
		if ((*it1) != omitir){
			Gtk::TreeModel::Row row = *(this->refTreeModel->append());
			row[this->m_Columnas.m_col_Nombre] = (*it1)->getNombre();
			row[this->m_Columnas.m_col_selected] = false;
			row[this->m_Columnas.m_col_vEnt_Pointer] = *it1;
		}
		it1++;
	}
}

void AsistenteJerarquia::llenarComboBox(){
	std::vector<VistaEntidadNueva *>::iterator it1 =  this->diagrama->vEntidadesBegin();
	std::vector<VistaEntidadNueva *>::iterator it2 =  this->diagrama->vEntidadesEnd();
	while (it1 != it2){
		//Veo que la entidad ya no tenga
		if ((*it1)->getEntidad()->getJerarquiaHija()!=NULL){
			Gtk::TreeModel::Row row = *(this->refTreeModelCombo->append());
			row[this->m_ColumnasCombo.m_col_Nombre] = (*it1)->getNombre();
			row[this->m_ColumnasCombo.m_col_vEnt_Pointer] = *it1;
			it1++;
		}
	}
}

void AsistenteJerarquia::on_ComboBox_click(){
	Gtk::TreeModel::iterator iter = this->comboBox.get_active();
	if(iter)
	{
	  Gtk::TreeModel::Row row = *iter;
	  VistaEntidadNueva* omitir = row[this->m_ColumnasCombo.m_col_vEnt_Pointer];
	  this->llenarListaEntidades(omitir);
	}
}

void AsistenteJerarquia::on_botonAceptar_click() {
	VistaEntidadNueva* entidadPadre = NULL;
	VistaEntidadNueva* entidad = NULL;
	Gtk::Entry *entryNombre = 0;
	this->m_builder->get_widget("entryNombre", entryNombre);
	string nom =entryNombre->get_text();
	if ( nom != "") {
		this->vjerarquia->setNombre(nom);
		Gtk::TreeModel::iterator iter = this->comboBox.get_active();
		if (iter) {
			this->m_builder->get_widget("entryNombre", entryNombre);

			Gtk::TreeModel::Row row = *iter;
			entidadPadre = row[this->m_ColumnasCombo.m_col_vEnt_Pointer];
			this->vjerarquia->setEntidadPadre(entidadPadre);
			entidadPadre->getEntidad()->setJerarquiaHija(this->vjerarquia->getJerarquia());
			//Ahora seteo las entidades hijas
			typedef Gtk::TreeModel::Children type_children;
			type_children children = this->refTreeModel->children();
			type_children::iterator iter = children.begin();
			type_children::iterator iter1 = children.end();
			while (iter != iter1) {
				Gtk::TreeModel::Row row = *iter;
				// si esta seleccionada la agrego
				if (row[this->m_Columnas.m_col_selected] == true) {
					entidad = row[this->m_Columnas.m_col_vEnt_Pointer];
					this->vjerarquia->agregarEntidadEspecializada(entidad);
					entidad->getEntidadNueva()->agregarJerarquiaPadre(this->vjerarquia->getJerarquia());
				}
				iter++;
			}
		}
	} else {
		//NOMBRe VACIO
		entryNombre->set_text("Ingrese un nombre");
	}
	this->hide();
}

void AsistenteJerarquia::on_botonCancelar_click() {
	// TODO BORRAR LOS DATOS CONTENIDOS EN LA LISTA Y EN EL ENTRY
	this->vjerarquia->resetearLanzarProp();
	this->hide();
}



void AsistenteJerarquia::inicializarAsistente() {

}

void AsistenteJerarquia::on_about_hide()
{
	this->vjerarquia->resetearLanzarProp();
}

void AsistenteJerarquia::limpiarLista() {
	this->refTreeModel->clear();
}

