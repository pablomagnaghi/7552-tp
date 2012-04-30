/*
 * TreePanel.cpp
 *
 *  Created on: 02/04/2012
 *      Author: Guagnini Enzo 88325
 */

#include "TreePanel.h"


TreePanel::TreePanel(VistaProyecto* proy){
	add_events(Gdk::ALL_EVENTS_MASK);
	this->proyecto = proy;
	this->enlazarWidgets();
}

void TreePanel::regenerar(){
	VistaDiagrama *principal = &(this->proyecto->d_principal);
	Gtk::TreeModel::Row row = *(this->refTreeModel->append());
	row[this->m_Columnas.m_col_Nombre] = principal->nombre;
	row[this->m_Columnas.m_col_Diag_Pointer] = principal;
	row[this->m_Columnas.m_col_esDiag] = true;
	this->regenerarRecur(principal, &row);
}

void TreePanel::regenerarRecur(VistaDiagrama* diag, Gtk::TreeModel::Row *row) {
	//primero cargo los componentes de ese diag y luego los diag hijos
	if (diag->l_componentes.size() > 0) {
		list<VistaComponente*>::iterator it1 = diag->l_componentes.begin();
		list<VistaComponente*>::iterator it2 = diag->l_componentes.end();
		while (it1 != it2) {
			Gtk::TreeModel::Row rowSec = *(this->refTreeModel->append(
					row->children()));
			rowSec[this->m_Columnas.m_col_Nombre] = (*it1)->getNombre();
			rowSec[this->m_Columnas.m_col_Comp_Pointer] = *it1;
			rowSec[this->m_Columnas.m_col_esDiag] = false;
			it1++;
		}
	}
	if (diag->l_sub_diagramas.size() > 0) {
		//cargo el sub diagrama y lurgo regenerar recur sobre ese
		list<VistaDiagrama*>::iterator it1 = diag->l_sub_diagramas.begin();
		list<VistaDiagrama*>::iterator it2 = diag->l_sub_diagramas.end();
		while (it1 != it2) {
			Gtk::TreeModel::Row rowSec = *(this->refTreeModel->append(
					row->children()));
			rowSec[this->m_Columnas.m_col_Nombre] = (*it1)->nombre;
			rowSec[this->m_Columnas.m_col_Diag_Pointer] = (*it1);
			rowSec[this->m_Columnas.m_col_esDiag] = true;
			this->regenerarRecur(*it1, &rowSec);
			it1++;
		}
	}

}

TreePanel::~TreePanel() {
	// TODO Auto-generated destructor stub
}


void TreePanel::enlazarWidgets(){
	Gtk::ScrolledWindow* sTpanel;
	this->proyecto->Ide_builder->get_widget("scroll_treePanel",
				sTpanel);
	this->refTreeModel = Gtk::TreeStore::create(this->m_Columnas);
	this->set_model(this->refTreeModel);
	this->append_column("Componentes", this->m_Columnas.m_col_Nombre);
	sTpanel->add(*this);
	this->show();
	this->regenerar();
}

bool TreePanel::on_button_press_event(GdkEventButton* event) {
	Gtk::TreeView::on_button_press_event(event);
	//Doble click izquierdo
	if (event->type == GDK_2BUTTON_PRESS) {
		Glib::RefPtr<Gtk::TreeSelection> refTreeSelection =
				this->get_selection();
		Gtk::TreeModel::iterator iter = refTreeSelection->get_selected();
		if (iter) //If anything is selected
		{
			//Hay que distinguir entre diagramas y componentes
			bool esDiagrama = (*iter)[this->m_Columnas.m_col_esDiag];
			if (esDiagrama) {
				VistaDiagrama *diagPointer =
						(*iter)[this->m_Columnas.m_col_Diag_Pointer];
				this->proyecto->cargarDiagrama(diagPointer);
			} else {
				Gtk::TreeModel::iterator parentIter;
				parentIter = (*iter)->parent();
				//Se supone que tiene que ser un diagrama
				if (((*parentIter)[this->m_Columnas.m_col_esDiag]) == true) {
					VistaDiagrama *diagPointer =
							(*parentIter)[this->m_Columnas.m_col_Diag_Pointer];
					this->proyecto->cargarDiagrama(diagPointer);
				}
			}
			//string s = (*iter)[this->m_Columnas.m_col_Nombre];
			//cout<<s<<(*iter)[this->m_Columnas.m_col_Diag_Pointer] <<"    "<<(*iter)[this->m_Columnas.m_col_esDiag]<<endl;
			//Gtk::TreeModel::Row row = *iter;
			//this->refTreeModel->erase(iter);
		}
	}
	return true;
}

