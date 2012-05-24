/*
 * PanelAcciones.cpp
 *
 *  Created on: 06/11/2010
 *      Author: metal
 */

#include "PanelAcciones.h"
#include "Ide.h"

PanelAcciones::PanelAcciones(const Glib::RefPtr<Gtk::Builder> Ide_b,Ide *i): Ide_builder(Ide_b)
,ide(i){
	this->enlazarWidgets();
}

PanelAcciones::~PanelAcciones() {
}

void PanelAcciones::enlazarWidgets(){
	Gtk::ToolButton *ptool = 0;
	//Botones de creacion de componentes
	this->Ide_builder->get_widget("tbAgregarEntidad", ptool);
	ptool->signal_clicked().connect(sigc::mem_fun(*this,
			&PanelAcciones::on_click_nuevaEntidad));
}


bool PanelAcciones::hayDiagrama() {
	if (this->ide->getDiagActual() == NULL) {

		Gtk::MessageDialog mensaje(*(this->ide), "Error.", false, Gtk::MESSAGE_ERROR,
						Gtk::BUTTONS_OK);
		mensaje.set_secondary_text(
				"No Hay Diagrama seleccionado, operacion Imposible.");
		mensaje.run();
		return false;
	}
	return true;
}

void PanelAcciones::on_click_nuevaEntidad(){
	//if (this->hayDiagrama()){
		VistaEntidad *nEntidad = new VistaEntidad();
		nEntidad->lanzarProp(NULL);
	//}
}
