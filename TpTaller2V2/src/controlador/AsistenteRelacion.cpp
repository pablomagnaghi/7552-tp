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
	this->inicializarAsistente();
}

void AsistenteRelacion::enlazarWidgets() {
	Gtk::Button* bAceptar = 0;
	Gtk::Button* bCancelar = 0;
	Gtk::Button *bAAtributo = 0, *bMAtributo = 0, *bEAtributo = 0;
	Gtk::ScrolledWindow *scrollEntidades = 0, *scrollAtributos = 0;
	Gtk::VBox *vbox=0;

	this->m_builder->get_widget("bAceptar", bAceptar);
	this->m_builder->get_widget("bCancelar", bCancelar);
	this->m_builder->get_widget("bAAtributo", bAAtributo);
	this->m_builder->get_widget("bMAtributo", bMAtributo);
	this->m_builder->get_widget("bEAtributo", bEAtributo);
	this->m_builder->get_widget("entryNombreRelacion", entryNombreRelacion);
	this->m_builder->get_widget("vbox5", vbox);

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
	this->treeViewEntidades.append_column_editable("Car Min",
					this->m_ColumnasEntidades.m_col_CMin);
	this->treeViewEntidades.append_column_editable("Car Max",
						this->m_ColumnasEntidades.m_col_CMax);

	//Combobox
	vbox->pack_end(this->comboTipo);

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
	VistaUnionEntidadRelacion *vuer=NULL;
	bool musthide = false;
	int countSelected=0;
	Gtk::Entry *entryNombre = 0;

	this->m_builder->get_widget("entryNombreRelacion", entryNombre);
	string nom =entryNombre->get_text();

	if ( nom != "") {
		this->vrelacion->setNombre(nom);
		this->vrelacion->ajustarTamanioAlTexto();
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
			//seteo tipo
			string tipo = this->comboTipo.get_active_text();
			this->vrelacion->getRelacion()->setTipo(tipo);
			//cargo las entidades a la relacion
			children = this->refTreeModelEntidades->children();
			iter = children.begin();
			iter1 = children.end();
			while (iter != iter1){
				Gtk::TreeModel::Row row = *iter;
				// si esta seleccionada la agrego
				if (row[this->m_ColumnasEntidades.m_col_selected] == true) {
					ventidad = row[this->m_ColumnasEntidades.m_col_vEnt_Pointer];
					//Verifico si la union ya esta creada en cuyo caso actualizare
					vuer = this->vrelacion->unidaConEntidad(ventidad);
					if (vuer == NULL){
						//Genero la union
						vuer = ComponentsBuilder::getInstance()->crearUnionEntidadRelacion(this->vdiagrama,ventidad,this->vrelacion,NULL);
						string cardMax = row[this->m_ColumnasEntidades.m_col_CMax];
						string cardMin = row[this->m_ColumnasEntidades.m_col_CMin];
						vuer->setCardinalidadMaxima(cardMax);
						vuer->setCardinalidadMinima(cardMin);
					}else{
						//Actualizo
						vuer->setCardinalidadMaxima(row[this->m_ColumnasEntidades.m_col_CMax]);
						vuer->setCardinalidadMinima(row[this->m_ColumnasEntidades.m_col_CMin]);
					}
					double x,y;
					this->vrelacion->getposini(x,y);
					if (x==0 or y==0){
						this->vrelacion->setposini(30, 30);
						this->vrelacion->setposfin(80, 120);
					}


				}else{
					//Si no esta seleccionada tengo que ver que = no exista la union por que podia estar de antes
					vuer = this->vrelacion->unidaConEntidad(ventidad);
					if (vuer != NULL){
						this->vdiagrama->quitarComponente(vuer);
						//TODO echo ELMINAR VistaunionEntidadRelacion
					}
				}
				iter++;
			}
			musthide = true;
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
	this->vrelacion->resetearLanzarProp();
	this->hide();
}

void AsistenteRelacion::on_botonAgregarAtributo_click() {
	//creo el nuevo atributo
	double xi, yi, xf, yf;
	//cout<<"llego1"<<endl;
	VistaAtributo *atrib = ComponentsBuilder::getInstance()->crearAtributoEnRelacion(
			Ide::getInstance()->getDiagActual(), this->vrelacion, NULL);
	if (this->vrelacion != NULL) {
		this->vrelacion->getposini(xi, yi);
		this->vrelacion->getposfin(xf, yf);
		atrib->mover(xf + 15, yi);
	}

	//cout<<"llego2"<<endl;
	//Lo incormoramos en la lista
	Gtk::TreeModel::Row row = *(this->refTreeModelAtrib->append());
	row[this->m_ColumnasAtrib.m_col_Nombre] = atrib->getNombre();
	row[this->m_ColumnasAtrib.m_col_Atrib_Pointer] = atrib;
	//cout<<"llego3"<<endl;
	if (atrib->lanzarProp()) {
	} else {
		delete atrib;
	}
	//cout<<"llego4"<<endl;
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
		this->vdiagrama->quitarComponente(atrib);
		this->refTreeModelAtrib->erase(iter);
	}
}

void AsistenteRelacion::inicializarAsistente() {
	this->entryNombreRelacion->set_text(this->vrelacion->getNombre());
	this->inicializarListaEntidades();
	this->iniicializarListaAtributos();

	this->comboTipo.append_text(TIPO_RELACION_ASOCIACION);
	this->comboTipo.append_text(TIPO_RELACION_COMPOSICION);
	if (this->vrelacion->getRelacion()->getTipo() == TIPO_RELACION_ASOCIACION){
		this->comboTipo.set_active(0);
	}
	if (this->vrelacion->getRelacion()->getTipo() == TIPO_RELACION_COMPOSICION){
			this->comboTipo.set_active(1);
		}

}

void AsistenteRelacion::inicializarListaEntidades(){
	VistaEntidad * ve;
	Gtk::TreeModel::Row row;
	VistaUnionEntidadRelacion *vu = NULL;
	typedef Gtk::TreeModel::Children type_children;
	type_children children = this->refTreeModelEntidades->children();
	type_children::iterator iter = children.begin();
	type_children::iterator iter1 = children.end();
	while (iter != iter1) {
		row = *iter;
		ve = row[this->m_ColumnasEntidades.m_col_vEnt_Pointer];
		vu = this->vrelacion->unidaConEntidad(ve);
		if (vu!=NULL){
			row[this->m_ColumnasEntidades.m_col_selected] = true;
			row[this->m_ColumnasEntidades.m_col_CMax] = vu->getCardinalidadMaxima();
			row[this->m_ColumnasEntidades.m_col_CMin] = vu->getCardinalidadMinima();
		}
		vu = NULL;
		iter++;
	}
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

void AsistenteRelacion::iniicializarListaAtributos(){
	std::vector<VistaAtributo*>::iterator it1 = this->vrelacion->atributosBegin();
	std::vector<VistaAtributo*>::iterator it2 = this->vrelacion->atributosEnd();
	while (it1 != it2) {
		Gtk::TreeModel::Row row = *(this->refTreeModelAtrib->append());
		row[this->m_ColumnasAtrib.m_col_Nombre] = (*it1)->getNombre();
		row[this->m_ColumnasAtrib.m_col_Atrib_Pointer] = *it1;
		it1++;
	}
}

