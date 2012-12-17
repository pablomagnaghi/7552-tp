/*
 * AsistenteIdentificador.cpp
 *
 *  Created on: 30/04/2012
 *      Author: Guagnini Enzo 88325
 */

#include "AsistenteIdentificador.h"
#include "../vista/Ide.h"

AsistenteIdentificador::AsistenteIdentificador(BaseObjectType* cobject,
		const Glib::RefPtr<Gtk::Builder>& builder) :
		Gtk::Window(cobject), m_builder(builder) {
	this->ventidad= NULL;
	this->enlazarWidgets();
	this->setDiagrama(Ide::getInstance()->getDiagActual());
}

AsistenteIdentificador::~AsistenteIdentificador() {

}

void AsistenteIdentificador::setEntidad(VistaEntidadNueva* vent) {
	this->ventidad= vent;
	this->inicializarAsistente();
}

void AsistenteIdentificador::enlazarWidgets() {
	Gtk::Button* bAceptar = 0;
	Gtk::Button* bCancelar = 0;
	Gtk::Button *bAIdentificador = 0, *bEIdentificador = 0;
	Gtk::ScrolledWindow *scrollRelaciones = 0, *scrollAtributos = 0, *scrollIdentificadores = 0;

	this->m_builder->get_widget("bAceptar", bAceptar);
	this->m_builder->get_widget("bAIdentificador", bAIdentificador);
	this->m_builder->get_widget("bEIdentificador", bEIdentificador);

	bAceptar->signal_clicked().connect(
			sigc::mem_fun(*this, &AsistenteIdentificador::on_botonAceptar_click));
	bAIdentificador->signal_clicked().connect(
			sigc::mem_fun(*this, &AsistenteIdentificador::on_botonAgregarIdentificador_click));
	bEIdentificador->signal_clicked().connect(
			sigc::mem_fun(*this, &AsistenteIdentificador::on_botonEliminarIdentificador_click));
	this->signal_hide().connect(sigc::mem_fun(*this, &AsistenteIdentificador::on_about_hide));

	//Lista
	this->m_builder->get_widget("scrollAtributos", scrollAtributos);
	scrollAtributos->add(this->treeViewAtrib);
	this->refTreeModelAtrib = Gtk::ListStore::create(this->m_ColumnasAtrib);

	//Agrego modelo
	this->treeViewAtrib.set_model(this->refTreeModelAtrib);
	this->treeViewAtrib.append_column("Nombre", this->m_ColumnasAtrib.m_col_Nombre);
	this->treeViewAtrib.append_column_editable("Selected",
				this->m_ColumnasAtrib.m_col_selected);

	//ListaAtributos
	this->m_builder->get_widget("scrollRelaciones", scrollRelaciones);
	scrollRelaciones->add(this->treeViewRel);
	this->refTreeModelRel = Gtk::ListStore::create(this->m_ColumnasRel);

	//Agrego modelo a treeview
	this->treeViewRel.set_model(this->refTreeModelRel);
	this->treeViewRel.append_column("Nombre", this->m_ColumnasRel.m_col_Nombre);
	this->treeViewRel.append_column_editable("Selected",
				this->m_ColumnasRel.m_col_selected);

	this->m_builder->get_widget("scrollIdentificadores", scrollIdentificadores);
	scrollIdentificadores->add(this->treeViewIdent);
	this->refTreeModelIdent = Gtk::ListStore::create(this->m_ColumnasIdent);

	//Agrego modelo a treeview
	this->treeViewIdent.set_model(this->refTreeModelIdent);
	this->treeViewIdent.append_column("Nombre", this->m_ColumnasIdent.m_col_Nombre);

	this->treeViewIdent.show();
	this->treeViewRel.show();
	this->treeViewAtrib.show();
}

void AsistenteIdentificador::on_botonAceptar_click() {
	this->ventidad->resetearLanzarIdent();
	this->hide();
}

void AsistenteIdentificador::on_botonCancelar_click() {

}

void AsistenteIdentificador::on_botonEliminarIdentificador_click() {
	Glib::RefPtr<Gtk::TreeSelection> refTreeSelection = this->treeViewIdent.get_selection();
	Gtk::TreeModel::iterator iter = refTreeSelection->get_selected();
	if (iter) //If anything is selected
	{
		Gtk::TreeModel::Row row = *iter;
		VistaIdentificador *ident = row[this->m_ColumnasIdent.m_col_Ident_Pointer];

		//TODO echo ELIMINAR IDENT
		this->vdiagrama->quitarComponente(ident);
		this->llenarListaIdentificadores();
	}
}

void AsistenteIdentificador::on_botonAgregarIdentificador_click() {
	VistaIdentificador * vi = NULL;
	VistaUnionEntidadRelacion *vuer=NULL;
	VistaAtributo* va= NULL;
	typedef Gtk::TreeModel::Children type_children;
	type_children children = this->refTreeModelAtrib->children();
	type_children::iterator iter = children.begin();
	type_children::iterator iter1 = children.end();
	Gtk::TreeModel::Row row;
	if (this->validar()){
		vi = ComponentsBuilder::getInstance()->crearIdentificadorEnEntidad(this->vdiagrama,this->ventidad,NULL);
		Gtk::TreeModel::Row row;
		while (iter != iter1){
			row = *iter;
			if(row[this->m_ColumnasAtrib.m_col_selected] == true){
				va = row[this->m_ColumnasAtrib.m_col_Atrib_Pointer];
				ComponentsBuilder::getInstance()->agregarAtributoAIdentificador(vi,va);
			}
			iter++;
		}

		children = this->refTreeModelRel->children();
		iter = children.begin();
		iter1 = children.end();
		while (iter != iter1){
			row = *iter;
			if(row[this->m_ColumnasRel.m_col_selected] == true){
				vuer = row[this->m_ColumnasRel.m_col_Rel_Pointer];
				ComponentsBuilder::getInstance()->agregarEntidadFuerteAIdentificador(vi,vuer);
			}
			iter++;
		}
	}
	this->llenarListaIdentificadores();
}

void AsistenteIdentificador::inicializarAsistente() {
	this->llenarListaAtributos();
	this->llenarListaRelaciones();
	this->llenarListaIdentificadores();
}

void AsistenteIdentificador::llenarListaAtributos() {
	std::vector<VistaAtributo*>::iterator it = this->ventidad->atributosBegin();
	std::vector<VistaAtributo*>::iterator it1 = this->ventidad->atributosEnd();
	VistaAtributo *vatrib = NULL;
	while(it != it1){
		vatrib = *it;
		Gtk::TreeModel::Row row = *(this->refTreeModelAtrib->append());
		row[this->m_ColumnasAtrib.m_col_Nombre] = vatrib->getNombre();
		row[this->m_ColumnasAtrib.m_col_selected] = false;
		row[this->m_ColumnasAtrib.m_col_Atrib_Pointer] = vatrib;
		it++;
	}
}

void AsistenteIdentificador::llenarListaRelaciones() {
	std::vector<VistaUnionEntidadRelacion*>::iterator it = this->vdiagrama->vUnionEntidadRelacionBegin();
	std::vector<VistaUnionEntidadRelacion*>::iterator it1 = this->vdiagrama->vUnionEntidadRelacionEnd();
	std::vector<VistaUnionEntidadRelacion*>::iterator it2;
	std::vector<VistaUnionEntidadRelacion*>::iterator it3;
	VistaUnionEntidadRelacion *vuer = NULL;
	VistaUnionEntidadRelacion *vuer2 = NULL;
	VistaRelacion *vrel = NULL;
	while(it != it1){
		vuer = *it;
		if (vuer->getEntidad() == this->ventidad){
			//agrego todas las demas uniones de esa relacion
			vrel = vuer->getRelacion();
			it2 = vrel->unionesBegin();
			it3 = vrel->unionesEnd();
			while (it2!=it3){
				vuer2 = *it2;
				if (vuer2->getEntidad() != this->ventidad){
					Gtk::TreeModel::Row row = *(this->refTreeModelRel->append());
					row[this->m_ColumnasRel.m_col_Nombre] = vuer2->getEntidad()->getNombre();
					row[this->m_ColumnasAtrib.m_col_selected] = false;
					row[this->m_ColumnasRel.m_col_Rel_Pointer] = vuer2;
				}
				it2++;
			}

		}
		it++;
	}
}

void AsistenteIdentificador::llenarListaIdentificadores(){
	this->refTreeModelIdent->clear();
	VistaIdentificador* ident  = NULL;
	std::vector<VistaIdentificador*>::iterator it = this->ventidad->identificadoresBegin();
	std::vector<VistaIdentificador*>::iterator it1 = this->ventidad->identificadoresEnd();
	while ( it != it1){
		ident = *it;
		Gtk::TreeModel::Row row = *(this->refTreeModelIdent->append());
		row[this->m_ColumnasIdent.m_col_Nombre] = ident->to_s();
		row[this->m_ColumnasIdent.m_col_Ident_Pointer] = ident;
		it++;
	}

}

void AsistenteIdentificador::limpiarListaAtributos() {
	this->refTreeModelAtrib->clear();
}

void AsistenteIdentificador::on_about_hide() {
	this->ventidad->resetearLanzarIdent();
}

void AsistenteIdentificador::setDiagrama(VistaDiagrama * diag){
	this->vdiagrama = diag;
}

bool AsistenteIdentificador::validar(){
	int countAtribSelected = 0;
	int countEntSelected = 0;
	typedef Gtk::TreeModel::Children type_children;
	type_children children = this->refTreeModelAtrib->children();
	type_children::iterator iter = children.begin();
	type_children::iterator iter1 = children.end();
	VistaAtributo * atrib;
	Gtk::TreeModel::Row row;
	while (iter != iter1){
		row = *iter;
		if(row[this->m_ColumnasAtrib.m_col_selected] == true){
			countAtribSelected++;
		}
		iter++;
	}
	if (countAtribSelected == 0){
		Gtk::MessageDialog err_dialog(*this, "Seleccionar al menos un atributo", false,
													Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK, true);
		err_dialog.run();
		return false;
	}

	children = this->refTreeModelRel->children();
	iter = children.begin();
	iter1 = children.end();
	while (iter != iter1){
		row = *iter;
		if(row[this->m_ColumnasRel.m_col_selected] == true){
			countEntSelected++;
		}
		iter++;
	}
	if (countEntSelected > 1){
		Gtk::MessageDialog err_dialog(*this, "Seleccionar maximo una entidad fuerte.", false,
													Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK, true);
		err_dialog.run();
		return false;
	}
	return true;
}


