/*
 * AsistenteRelacion.cpp
 *
 *  Created on: 30/04/2012
 *      Author: Guagnini Enzo 88325
 */

#include "AsistenteRelacion.h"
#include "../vista/Ide.h"

AsistenteRelacion * AsistenteRelacion::instancia = NULL;

AsistenteRelacion::AsistenteRelacion(BaseObjectType* cobject,
		const Glib::RefPtr<Gtk::Builder>& builder) :
		Gtk::Window(cobject), m_builder(builder) {
	this->vrelacion = NULL;
	this->enlazarWidgets();
	this->setDiagrama(Ide::getInstance()->getDiagActual());
}

AsistenteRelacion::~AsistenteRelacion() {

}

void AsistenteRelacion::setRelacion(VistaRelacion* rel) {
	this->vrelacion = rel;
	//this->inicializarAsistente();
}

void AsistenteRelacion::enlazarWidgets() {
	Gtk::Button* bAceptar = 0;
	Gtk::Button* bCancelar = 0;
	Gtk::Button *bAAtributo = 0, *bMAtributo = 0, *bEAtributo = 0;
	Gtk::ScrolledWindow *scrollEntidades = 0, *scrollAtributos = 0;

	this->m_builder->get_widget("bAceptar", bAceptar);
	this->m_builder->get_widget("bCancelar", bCancelar);
	this->m_builder->get_widget("bAAtributo", bAAtributo);
	this->m_builder->get_widget("bMAtributo", bMAtributo);
	this->m_builder->get_widget("bEAtributo", bEAtributo);
	this->m_builder->get_widget("entryNombreRelacion", entryNombreRelacion);

	bAceptar->signal_clicked().connect(
			sigc::mem_fun(*this, &AsistenteRelacion::on_botonAceptar_click));
	bCancelar->signal_clicked().connect(
			sigc::mem_fun(*this, &AsistenteRelacion::on_botonCancelar_click));
	bAAtributo->signal_clicked().connect(
			sigc::mem_fun(*this, &AsistenteRelacion::on_botonAgregarAtributo_click));
	bMAtributo->signal_clicked().connect(
			sigc::mem_fun(*this, &AsistenteRelacion::on_botonModificarAtributo_click));
	bEAtributo->signal_clicked().connect(
			sigc::mem_fun(*this, &AsistenteRelacion::on_botonEliminarAtributo_click));
	this->signal_hide().connect(sigc::mem_fun(*this, &AsistenteRelacion::on_about_hide));

	//ListaEntidades
	this->m_builder->get_widget("scrollEntidades", scrollEntidades);
	scrollEntidades->add(this->treeViewEntidades);
	this->refTreeModelEntidades = Gtk::ListStore::create(this->m_ColumnasEntidades);

	//Agrego modelo a treeviewEntidades
	this->treeViewEntidades.set_model(this->refTreeModelEntidades);
	this->treeViewEntidades.append_column("Nombre", this->m_ColumnasEntidades.m_col_Nombre);
	this->treeViewEntidades.append_column_editable("Selected",
				this->m_ColumnasEntidades.m_col_selected);

	//ListaAtributos
	this->m_builder->get_widget("scrollAtributos", scrollAtributos);
	scrollAtributos->add(this->treeViewAtrib);
	this->refTreeModelAtrib = Gtk::ListStore::create(this->m_ColumnasAtrib);

	//Agrego modelo a treeview
	this->treeViewAtrib.set_model(this->refTreeModelAtrib);
	this->treeViewAtrib.append_column("Nombre", this->m_ColumnasAtrib.m_col_Nombre);

	this->treeViewEntidades.show();
	this->treeViewAtrib.show();

}

void AsistenteRelacion::on_botonAceptar_click() {
	VistaEntidadNueva* ventidad = NULL;
	bool musthide = false;
	int countSelected=0;
	Gtk::Entry *entryNombre = 0;

	this->m_builder->get_widget("entryNombreRelacion", entryNombre);
	string nom =entryNombre->get_text();

	if ( nom != "") {
		this->vrelacion->setNombre(nom);
		//Cuento mas de 2 entidades seleccionadas al menos
		typedef Gtk::TreeModel::Children type_children;
		type_children children = this->refTreeModelEntidades->children();
		type_children::iterator iter = children.begin();
		type_children::iterator iter1 = children.end();
		while ((iter != iter1) && (countSelected<2)) {
			Gtk::TreeModel::Row row = *iter;
			// si esta seleccionada la agrego
			if (row[this->m_ColumnasEntidades.m_col_selected] == true) {
				countSelected++;
			}
			iter++;
		}
		if (countSelected >= 2){
			//cargo las entidades a la relacion
			children = this->refTreeModelEntidades->children();
			iter = children.begin();
			iter1 = children.end();
			while (iter != iter1){
				Gtk::TreeModel::Row row = *iter;
				// si esta seleccionada la agrego
				//TODO SI fui a propiedades de una relacion(no es una nueva) hay que verificar y hacer un abm
				if (row[this->m_ColumnasEntidades.m_col_selected] == true) {
					//Genero la union
					ventidad = row[this->m_ColumnasEntidades.m_col_vEnt_Pointer];
					ComponentsBuilder::getInstance()->crearUnionEntidadRelacion(this->vdiagrama,ventidad,this->vrelacion,NULL);
					this->vrelacion->setposini(360, 150);
					this->vrelacion->setposfin(430, 175);
				}
				iter++;
			}

		}else{
			Gtk::MessageDialog err_dialog(*this, "Seleccionar al menos 2 entidades", false,
											Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK, true);
					err_dialog.run();
		}
	}else{
		Gtk::MessageDialog err_dialog(*this, "No name", false,
								Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK, true);
		err_dialog.run();
	}
	if (musthide==true){
		this->vrelacion->resetearLanzarProp();
		this->hide();
	}
}

void AsistenteRelacion::on_botonCancelar_click() {
	// TODO BORRAR LOS DATOS CONTENIDOS EN LA LISTA Y EN EL ENTRY
	this->vrelacion->resetearLanzarProp();

	this->hide();
}

void AsistenteRelacion::on_botonAgregarAtributo_click() {
	//creo el nuevo atributo
	cout<<"llego1"<<endl;
	VistaAtributo *atrib = ComponentsBuilder::getInstance()->crearAtributoEnRelacion(
			this->diagramaActual, this->vrelacion, NULL);
	cout<<"llego2"<<endl;
	//Lo incormoramos en la lista
	Gtk::TreeModel::Row row = *(this->refTreeModelAtrib->append());
	row[this->m_ColumnasAtrib.m_col_Nombre] = atrib->getNombre();
	row[this->m_ColumnasAtrib.m_col_Atrib_Pointer] = atrib;
	cout<<"llego3"<<endl;
	if (atrib->lanzarProp()) {
	} else {
		delete atrib;
	}
}

void AsistenteRelacion::on_botonModificarAtributo_click() {
	Glib::RefPtr<Gtk::TreeSelection> refTreeSelection = this->treeViewAtrib.get_selection();
	Gtk::TreeModel::iterator iter = refTreeSelection->get_selected();
	if (iter) //If anything is selected
	{
		Gtk::TreeModel::Row row = *iter;
		VistaAtributo *atrib = row[this->m_ColumnasAtrib.m_col_Atrib_Pointer];
		atrib->lanzarProp();
	}
}

void AsistenteRelacion::on_botonEliminarAtributo_click() {

	Glib::RefPtr<Gtk::TreeSelection> refTreeSelection = this->treeViewAtrib.get_selection();
	Gtk::TreeModel::iterator iter = refTreeSelection->get_selected();
	if (iter) //If anything is selected
	{
		Gtk::TreeModel::Row row = *iter;
		VistaAtributo *atrib = row[this->m_ColumnasAtrib.m_col_Atrib_Pointer];
		//TODO Borro el atributo Mediante El builder
		this->refTreeModelAtrib->erase(iter);
	}
}

void AsistenteRelacion::inicializarAsistente() {
	/*
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
	}*/
}

void AsistenteRelacion::limpiarListaEntidades() {
	this->refTreeModelEntidades->clear();
}

void AsistenteRelacion::on_about_hide() {
	this->vrelacion->resetearLanzarProp();
}

void AsistenteRelacion::setDiagrama(VistaDiagrama * diag){
	this->vdiagrama = diag;
	this->llenarListaEntidades();
}

void AsistenteRelacion::llenarListaEntidades(){
	this->limpiarListaEntidades();
	std::vector<VistaEntidadNueva *>::iterator it1 =  this->vdiagrama->vEntidadesBegin();
	std::vector<VistaEntidadNueva *>::iterator it2 =  this->vdiagrama->vEntidadesEnd();
	while (it1 != it2){
		Gtk::TreeModel::Row row = *(this->refTreeModelEntidades->append());
		row[this->m_ColumnasEntidades.m_col_Nombre] = (*it1)->getNombre();
		row[this->m_ColumnasEntidades.m_col_selected] = false;
		row[this->m_ColumnasEntidades.m_col_vEnt_Pointer] = *it1;
		it1++;
	}
}

