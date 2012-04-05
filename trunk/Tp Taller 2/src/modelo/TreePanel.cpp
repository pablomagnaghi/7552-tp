/*
 * TreePanel.cpp
 *
 *  Created on: 02/04/2012
 *      Author: Guagnini Enzo 88325
 */

#include "TreePanel.h"


TreePanel::TreePanel(Proyecto* proy){
	this->proyecto = proy;
	this->enlazarWidgets();
}

void TreePanel::regenerar(){
	Diagrama *principal = &(this->proyecto->d_principal);
	Gtk::TreeModel::Row row = *(this->refTreeModel->append());
	row[this->m_Columnas.m_col_Nombre] = principal->nombre;
	this->regenerarRecur(principal, &row);
}

void TreePanel::regenerarRecur(Diagrama* diag, Gtk::TreeModel::Row *row) {
	//primero cargo los componentes de ese diag y luego los diag hijos
	if (diag->l_componentes.size() > 0) {
		list<Componente*>::iterator it1 = diag->l_componentes.begin();
		list<Componente*>::iterator it2 = diag->l_componentes.end();
		while (it1 != it2) {
			Gtk::TreeModel::Row rowSec = *(this->refTreeModel->append(
					row->children()));
			rowSec[this->m_Columnas.m_col_Nombre] = (*it1)->getNombre();
			it1++;
		}
	}
	if (diag->l_sub_diagramas.size() > 0) {
		//cargo el sub diagrama y lurgo regenerar recur sobre ese
		list<Diagrama*>::iterator it1 = diag->l_sub_diagramas.begin();
		list<Diagrama*>::iterator it2 = diag->l_sub_diagramas.end();
		while (it1 != it2) {
			Gtk::TreeModel::Row rowSec = *(this->refTreeModel->append(
					row->children()));
			rowSec[this->m_Columnas.m_col_Nombre] = (*it1)->nombre;
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
	this->treeView.set_model(this->refTreeModel);
	this->treeView.append_column("Componentes", this->m_Columnas.m_col_Nombre);
	sTpanel->add(this->treeView);
	this->treeView.show();
	this->regenerar();
}
