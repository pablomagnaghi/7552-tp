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
//TODO
}

TreePanel::~TreePanel() {
	// TODO Auto-generated destructor stub
}


void TreePanel::enlazarWidgets(){
	cout<<"PASSA"<<endl;

	Gtk::ScrolledWindow* sTpanel;
	this->proyecto->Ide_builder->get_widget("scroll_treePanel",
				sTpanel);

	this->refTreeModel = Gtk::TreeStore::create(this->m_Columnas);
	this->treeView.set_model(this->refTreeModel);
	this->treeView.append_column("", this->m_Columnas.m_col_Nombre);
	sTpanel->add(this->treeView);
	this->treeView.set_size_request(500,500);
	this->treeView.show();

	this->regenerar();
}
