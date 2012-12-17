/*
 * AsistenteJerarquia.cpp
 *
 *  Created on: 24/07/2012
 *      Author: Guagnini Enzo 88325
 */

#include "AsistenteJerarquia.h"
#include "../vista/Ide.h"

AsistenteJerarquia::AsistenteJerarquia(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder) :
	Gtk::Window(cobject), m_builder(builder) {
	//this->hide();
	this->vjerarquia = NULL;
	this->show();
	this->enlazarWidgets();
	this->diagrama = NULL;
	this->setDiagrama(Ide::getInstance()->getDiagActual());
}

AsistenteJerarquia::~AsistenteJerarquia() {

}

void AsistenteJerarquia::setJerarquia(VistaJerarquia* jer) {
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

void AsistenteJerarquia::llenarListaEntidades(VistaEntidad * omitir){
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
		//if ((*it1)->getEntidad()->getJerarquiaHija()==NULL){
			Gtk::TreeModel::Row row = *(this->refTreeModelCombo->append());
			row[this->m_ColumnasCombo.m_col_Nombre] = (*it1)->getNombre();
			row[this->m_ColumnasCombo.m_col_vEnt_Pointer] = *it1;
		//}
		it1++;
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
	VistaEntidad * vep = NULL;
	Gtk::RadioButton* radio = NULL;
	bool musthide = false;
	int countSelected=0;
	Gtk::Entry *entryNombre = 0;
	this->m_builder->get_widget("entryNombre", entryNombre);
	string nom =entryNombre->get_text();
	if ( nom != "") {
		this->vjerarquia->setNombre(nom);
		Gtk::TreeModel::iterator iter = this->comboBox.get_active();
		if (iter) {
			//Si esta nodificando y ya tenia un padre
			vep = this->vjerarquia->getEntidadPadre();
			if (vep != NULL){
				vep->getEntidad()->quitarJerarquiaHija();
			}
			Gtk::TreeModel::Row row = *iter;
			entidadPadre = row[this->m_ColumnasCombo.m_col_vEnt_Pointer];
			this->vjerarquia->setEntidadPadre(entidadPadre);
			entidadPadre->getEntidad()->setJerarquiaHija(this->vjerarquia->getJerarquia());

			//cobertura, interseccion
			this->m_builder->get_widget("radioParcial", radio);
			if (radio->get_active() == true){
				this->vjerarquia->getJerarquia()->setCobertura(TIPO_COBERTURA_PARCIAL);
			}else{
				this->vjerarquia->getJerarquia()->setCobertura(TIPO_COBERTURA_TOTAL);
			}
			this->m_builder->get_widget("radioExclusiva", radio);
			if (radio->get_active() == true){
				this->vjerarquia->getJerarquia()->setInterseccion(TIPO_INTERSECCION_EXCLUSIVA);
			}else{
				this->vjerarquia->getJerarquia()->setInterseccion(TIPO_INTERSECCION_SUPERPUESTA);
			}

			//Ahora seteo las entidades hijas
			typedef Gtk::TreeModel::Children type_children;
			type_children children = this->refTreeModel->children();
			type_children::iterator iter = children.begin();
			type_children::iterator iter1 = children.end();
			while (iter != iter1) {
				Gtk::TreeModel::Row row = *iter;
				// si esta seleccionada la agrego o actualizo
				if (row[this->m_Columnas.m_col_selected] == true) {
					countSelected++;
					if (this->vjerarquia->unidaConEntidad(row[this->m_Columnas.m_col_vEnt_Pointer]) == false){
						entidad = row[this->m_Columnas.m_col_vEnt_Pointer];
						this->vjerarquia->agregarEntidadEspecializada(entidad);
						this->vjerarquia->getJerarquia()->agregarEntidadEspecializada(entidad->getEntidadNueva());
						entidad->getEntidadNueva()->agregarJerarquiaPadre(this->vjerarquia->getJerarquia());
					}
				}else{
					if (this->vjerarquia->unidaConEntidad(row[this->m_Columnas.m_col_vEnt_Pointer]) == true){
						this->vjerarquia->removerEntidadEspecializada(row[this->m_Columnas.m_col_vEnt_Pointer]);
					}
				}
				iter++;
			}
			if (countSelected>0){
				musthide = true;
			}else{
				Gtk::MessageDialog err_dialog1(*this, "Select at least one children", false,
										Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK, true);
				err_dialog1.run();
			}
		}else{
			Gtk::MessageDialog err_dialog2(*this, "Select the father", false,
													Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK, true);
							err_dialog2.run();
		}
	} else {
		Gtk::MessageDialog err_dialog(*this, "No name", false,
						Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK, true);
		err_dialog.run();
	}
	if (musthide==true){
		this->vjerarquia->resetearLanzarProp();
		this->hide();
	}
}

void AsistenteJerarquia::on_botonCancelar_click() {
	// TODO BORRAR LOS DATOS CONTENIDOS EN LA LISTA Y EN EL ENTRY
	this->vjerarquia->resetearLanzarProp();
	// todo if esta creando
	this->diagrama->quitarComponente(this->vjerarquia);
	this->hide();
}



void AsistenteJerarquia::inicializarAsistente() {
	if (this->vjerarquia->getEntidadPadre() != NULL){
		Gtk::Entry *entryNombre = 0;
		Gtk::RadioButton* radio =NULL;
		if (this->vjerarquia->getJerarquia()->getCobertura() == TIPO_COBERTURA_PARCIAL){
			this->m_builder->get_widget("radioParcial", radio);
			radio->set_active(true);
		}else{
			this->m_builder->get_widget("radioTotal", radio);
			radio->set_active(true);
		}
		if (this->vjerarquia->getJerarquia()->getInterseccion() == TIPO_INTERSECCION_EXCLUSIVA){
			this->m_builder->get_widget("radioExclusiva", radio);
			radio->set_active(true);
		}else{
			this->m_builder->get_widget("radioSuperpuesta", radio);
			radio->set_active(true);
		}

		this->m_builder->get_widget("entryNombre", entryNombre);
		entryNombre->set_text(this->vjerarquia->getNombre());
		this->inicializarListaEntidades();
	}
}

void AsistenteJerarquia::on_about_hide()
{
	this->vjerarquia->resetearLanzarProp();
}

void AsistenteJerarquia::limpiarLista() {
	this->refTreeModel->clear();
}

void AsistenteJerarquia::inicializarListaEntidades(){
	VistaEntidadNueva * ve = NULL;
	VistaEntidad *vep = NULL;
	Gtk::TreeModel::Row row;
	bool unida = false;
	typedef Gtk::TreeModel::Children type_children;
	//primero el combo box luego actualizo la lista de entidades menos el padre y despues inicializo esa lista
	vep = this->vjerarquia->getEntidadPadre();
	type_children children = this->refTreeModelCombo->children();
	type_children::iterator iter = children.begin();
	type_children::iterator iter1 = children.end();
	while ( iter != iter1){
		row = *iter;
		if (row[this->m_ColumnasCombo.m_col_vEnt_Pointer] == vep){
			this->comboBox.set_active(iter);
		}
		iter++;
	}

	this->llenarListaEntidades(vep);

	children = this->refTreeModel->children();
	iter = children.begin();
	iter1 = children.end();
	while (iter != iter1) {
		row = *iter;
		ve = row[this->m_Columnas.m_col_vEnt_Pointer];
		unida = this->vjerarquia->unidaConEntidad(ve);
		if (unida == true){
			row[this->m_Columnas.m_col_selected] = true;
		}
		unida = false;
		iter++;
	}
}
