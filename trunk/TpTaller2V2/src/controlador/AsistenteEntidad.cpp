/*
 * AsistenteEntidad.cpp
 *
 *  Created on: 30/04/2012
 *      Author: Guagnini Enzo 88325
 */

#include "AsistenteEntidad.h"
#include "../vista/Ide.h"

AsistenteEntidad * AsistenteEntidad::instancia = NULL;

AsistenteEntidad::AsistenteEntidad(BaseObjectType* cobject,
		const Glib::RefPtr<Gtk::Builder>& builder) :
		Gtk::Window(cobject), m_builder(builder) {
	this->ventidad = NULL;
	this->enlazarWidgets();
	this->diagramaActual = Ide::getInstance()->getDiagActual();
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
	Gtk::VBox *vbox = 0;

	this->m_builder->get_widget("bAceptar", bAceptar);
	this->m_builder->get_widget("bCancelar", bCancelar);
	this->m_builder->get_widget("bAAtributo", bAAtributo);
	this->m_builder->get_widget("bMAtributo", bMAtributo);
	this->m_builder->get_widget("bEAtributo", bEAtributo);
	this->m_builder->get_widget("entryNombreEntidad", entryNombreEntidad);
	this->m_builder->get_widget("vbox4", vbox);

	bAceptar->signal_clicked().connect(
			sigc::mem_fun(*this, &AsistenteEntidad::on_botonAceptar_click));
	bCancelar->signal_clicked().connect(
			sigc::mem_fun(*this, &AsistenteEntidad::on_botonCancelar_click));
	bAAtributo->signal_clicked().connect(
			sigc::mem_fun(*this, &AsistenteEntidad::on_botonAgregarAtributo_click));
	bMAtributo->signal_clicked().connect(
			sigc::mem_fun(*this, &AsistenteEntidad::on_botonModificarAtributo_click));
	bEAtributo->signal_clicked().connect(
			sigc::mem_fun(*this, &AsistenteEntidad::on_botonEliminarAtributo_click));
	this->signal_hide().connect(sigc::mem_fun(*this, &AsistenteEntidad::on_about_hide));

	//Combobox
	vbox->pack_end(this->comboTipo);
	this->comboTipo.set_size_request(100, 60);

	//Lista
	this->m_builder->get_widget("scrollLista", scrollLista);
	scrollLista->add(this->treeView);
	this->refTreeModel = Gtk::ListStore::create(this->m_Columnas);

	//Agrego modelo a treeview
	this->treeView.set_model(this->refTreeModel);
	this->treeView.append_column("Nombre", this->m_Columnas.m_col_Nombre);
	this->treeView.show();
	this->comboTipo.show();
}

void AsistenteEntidad::on_botonAceptar_click() {
	string nombre = this->entryNombreEntidad->get_text();
	string tipo;
	if (nombre == "") {
		Gtk::MessageDialog err_dialog(*this, "Entidad sin nombre", false, Gtk::MESSAGE_ERROR,
				Gtk::BUTTONS_OK, true);
		err_dialog.run();
	} else {
		this->ventidad->setNombre(this->entryNombreEntidad->get_text());
		tipo = this->comboTipo.get_active_text();
		this->ventidad->getEntidadNueva()->setTipo(tipo);
		this->ventidad->setposini(50, 50);
		this->ventidad->ajustarTamanioAlTexto();
		this->ventidad->resetearLanzarProp();
		this->hide();
		Ide::getInstance()->getDiagActual()->queue_draw();
		Ide::getInstance()->regenerarTreePanel();
	}
}

void AsistenteEntidad::on_botonCancelar_click() {
	// TODO BORRAR LOS DATOS CONTENIDOS EN LA LISTA Y EN EL ENTRY
	this->ventidad->ajustarTamanioAlTexto();
	this->ventidad->resetearLanzarProp();
	// todo if esta creando
	//Ide::getInstance()->getDiagActual()->quitarComponente(this->ventidad);

	Ide::getInstance()->regenerarTreePanel();
	this->hide();
}

void AsistenteEntidad::on_botonAgregarAtributo_click() {
	//creo el nuevo atributo
	double xi, yi, xf, yf;
	VistaAtributo *atrib = ComponentsBuilder::getInstance()->crearAtributoEnEntidad(
			this->diagramaActual, this->ventidad, NULL);
	if (this->ventidad != NULL) {
		this->ventidad->getposini(xi, yi);
		this->ventidad->getposfin(xf, yf);
		atrib->mover(xf + 15, yi);
	}
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
	Glib::RefPtr<Gtk::TreeSelection> refTreeSelection = this->treeView.get_selection();
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
	Glib::RefPtr<Gtk::TreeSelection> refTreeSelection = this->treeView.get_selection();
	Gtk::TreeModel::iterator iter = refTreeSelection->get_selected();
	if (iter) //If anything is selected
	{
		Gtk::TreeModel::Row row = *iter;
		VistaAtributo *atrib = row[this->m_Columnas.m_col_Atrib_Pointer];
		//TODO Borro el atributo Mediante El builder
		this->diagramaActual->quitarComponente(atrib);
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

	this->comboTipo.append_text(TIPO_ENTIDAD_COSA);
	this->comboTipo.append_text(TIPO_ENTIDAD_DOMINIO);
	this->comboTipo.append_text(TIPO_ENTIDAD_HISTORICA);
	this->comboTipo.append_text(TIPO_ENTIDAD_PROGRAMADA);
	if (this->ventidad->getEntidadNueva()->getTipo() == TIPO_ENTIDAD_COSA) {
		this->comboTipo.set_active(0);
	}
	if (this->ventidad->getEntidadNueva()->getTipo() == TIPO_ENTIDAD_DOMINIO) {
		this->comboTipo.set_active(1);
	}
	if (this->ventidad->getEntidadNueva()->getTipo() == TIPO_ENTIDAD_HISTORICA) {
		this->comboTipo.set_active(2);
	}
	if (this->ventidad->getEntidadNueva()->getTipo() == TIPO_ENTIDAD_PROGRAMADA) {
		this->comboTipo.set_active(3);
	}

}

void AsistenteEntidad::limpiarLista() {
	this->refTreeModel->clear();
}

void AsistenteEntidad::on_about_hide() {
	this->ventidad->resetearLanzarProp();
}

