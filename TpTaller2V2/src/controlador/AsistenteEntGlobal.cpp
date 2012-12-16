/*
 * AsistenteEntGlobal.cpp
 *
 *  Created on: 24/07/2012
 *      Author: Guagnini Enzo 88325
 */

#include "AsistenteEntGlobal.h"
#include "../vista/Ide.h"

AsistenteEntGlobal * AsistenteEntGlobal::instancia = NULL;

AsistenteEntGlobal::AsistenteEntGlobal(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder) :
		Gtk::Window(cobject), m_builder(builder) {
	//this->hide();
	this->enlazarWidgets();
	this->setDiagrama(Ide::getInstance()->getDiagActual());
}

AsistenteEntGlobal::~AsistenteEntGlobal() {

}

void AsistenteEntGlobal::setDiagrama(VistaDiagrama * diag) {
	this->vdiagrama = diag;
	this->llenarListaDiagramas();
}
void AsistenteEntGlobal::enlazarWidgets() {
	Gtk::Button* bAceptar = 0;
	Gtk::Button* bCancelar = 0;
	Gtk::Button* bSelecDiag = 0;

	Gtk::ScrolledWindow* scrollLista = 0;

	this->m_builder->get_widget("bAceptar", bAceptar);
	this->m_builder->get_widget("bCancelar", bCancelar);
	this->m_builder->get_widget("bSelecDiag", bSelecDiag);

	bAceptar->signal_clicked().connect(sigc::mem_fun(*this, &AsistenteEntGlobal::on_botonAceptar_click));
	bCancelar->signal_clicked().connect(sigc::mem_fun(*this, &AsistenteEntGlobal::on_botonCancelar_click));
	bSelecDiag->signal_clicked().connect(sigc::mem_fun(*this, &AsistenteEntGlobal::on_bSelecDiag_click));

	this->signal_hide().connect(sigc::mem_fun(*this, &AsistenteEntGlobal::on_about_hide));

	//Lista
	this->m_builder->get_widget("scrollDiagramas", scrollLista);
	scrollLista->add(this->treeViewDiagramas);
	this->refTreeModelDiagramas = Gtk::ListStore::create(this->m_ColumnasDiagramas);

	//Agrego modelo a treeview
	this->treeViewDiagramas.set_model(this->refTreeModelDiagramas);
	this->treeViewDiagramas.append_column("Nombre", this->m_ColumnasDiagramas.m_col_Nombre);

	//ListaEntidades
	this->m_builder->get_widget("scrollEntidades", scrollLista);
	scrollLista->add(this->treeViewEntidades);
	this->refTreeModelEntidades = Gtk::ListStore::create(this->m_ColumnasEntidades);

	//Agrego modelo a treeviewEntidades
	this->treeViewEntidades.set_model(this->refTreeModelEntidades);
	this->treeViewEntidades.append_column("Nombre", this->m_ColumnasEntidades.m_col_Nombre);

	this->treeViewEntidades.show();
	this->treeViewDiagramas.show();
}

void AsistenteEntGlobal::llenarListaEntidades(VistaDiagrama* diag) {
	this->limpiarListaEntidades();
	std::vector<VistaEntidadNueva *>::iterator it1 = diag->vEntidadesBegin();
	std::vector<VistaEntidadNueva *>::iterator it2 = diag->vEntidadesEnd();
	while (it1 != it2) {
		Gtk::TreeModel::Row row = *(this->refTreeModelEntidades->append());
		row[this->m_ColumnasEntidades.m_col_Nombre] = (*it1)->getNombre();
		row[this->m_ColumnasEntidades.m_col_vEnt_Pointer] = *it1;
		it1++;
	}
}

void AsistenteEntGlobal::llenarListaDiagramas() {
	//Asi llena con todos los diagramas del proyecto
	/*std::list<VistaDiagrama*> lista;
	 Ide::getInstance()->getProyecto()->get_diagramas(lista);
	 std::list<VistaDiagrama*>::iterator it = lista.begin();
	 std::list<VistaDiagrama*>::iterator it1 = lista.end();
	 while(it != it1){
	 cout<<"Diagrama:"<<(*it)->getNombre()<<endl;
	 //Agrego en la lista de diagramas
	 if ((*it) != this->vdiagrama){
	 Gtk::TreeModel::Row row = *(this->refTreeModelDiagramas->append());
	 row[this->m_ColumnasDiagramas.m_col_Nombre] = (*it)->getNombre();
	 row[this->m_ColumnasDiagramas.m_col_vDiag_Pointer] = *it;
	 }
	 it++;
	 }*/

	VistaDiagrama *ancestro = this->vdiagrama->getDiagramaAncestro();
	while (ancestro != NULL) {
		Gtk::TreeModel::Row row = *(this->refTreeModelDiagramas->append());
		row[this->m_ColumnasDiagramas.m_col_Nombre] = ancestro->getNombre();
		row[this->m_ColumnasDiagramas.m_col_vDiag_Pointer] = ancestro;
		ancestro = ancestro->getDiagramaAncestro();
	}
}

void AsistenteEntGlobal::on_botonAceptar_click() {
	bool musthide = false;
	Glib::RefPtr<Gtk::TreeSelection> refTreeSelection = this->treeViewEntidades.get_selection();
	Gtk::TreeModel::iterator iter = refTreeSelection->get_selected();
	if (iter) //If anything is selected
	{
		Gtk::TreeModel::Row row = *iter;
		VistaEntidad *entidad = row[this->m_ColumnasEntidades.m_col_vEnt_Pointer];
		// todo
		//VistaEntidadGlobal *v = ComponentsBuilder::getInstance()->crearEntidadGlobalEnDiagrama(
		//		this->vdiagrama, entidad->getNombre(), NULL);
		VistaEntidadGlobal *v = ComponentsBuilder::getInstance()->crearEntidadGlobalEnDiagrama(
				this->vdiagrama, entidad->getCodigoREP(), NULL);
		v->setposini(50, 50);
		v->setposfin(100, 100);
		musthide = true;
	} else {
		Gtk::MessageDialog err_dialog(*this, "Debe seleccionar una entidad.", false, Gtk::MESSAGE_ERROR,
				Gtk::BUTTONS_OK, true);
		err_dialog.run();
	}
	if (musthide == true) {
		this->hide();
	}
}

void AsistenteEntGlobal::on_botonCancelar_click() {
	this->hide();
}

void AsistenteEntGlobal::on_bSelecDiag_click() {
	Glib::RefPtr<Gtk::TreeSelection> refTreeSelection = this->treeViewDiagramas.get_selection();
	Gtk::TreeModel::iterator iter = refTreeSelection->get_selected();
	if (iter) //If anything is selected
	{
		Gtk::TreeModel::Row row = *iter;
		VistaDiagrama *diag = row[this->m_ColumnasDiagramas.m_col_vDiag_Pointer];
		this->llenarListaEntidades(diag);
	}
}

void AsistenteEntGlobal::inicializarAsistente() {

}

void AsistenteEntGlobal::on_about_hide() {

}

void AsistenteEntGlobal::limpiarListaEntidades() {
	this->refTreeModelEntidades->clear();
}

