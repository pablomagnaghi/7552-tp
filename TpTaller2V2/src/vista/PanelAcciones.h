/*
 * PanelAcciones.h
 *
 *  Created on: 06/11/2010
 *      Author: metal
 */

#ifndef PANELACCIONES_H_
#define PANELACCIONES_H_

#include <gtkmm.h>
#include "VistaDiagrama.h"
#include "componentes/VistaEntidad.h"
#include <iostream>

using namespace std;
class Ide;

/*
 * Representa el panel que contiene todas las acciones posibles(panel superior)
 */

class PanelAcciones{
private:
	const Glib::RefPtr<Gtk::Builder>& Ide_builder;

	const VistaDiagrama* vdiagrama;

	Ide* ide;

	void on_click_nuevaEntidad();

	void enlazarWidgets();

	bool hayDiagrama();

public:
	PanelAcciones(const Glib::RefPtr<Gtk::Builder> Ide_b,Ide* i);

	virtual ~PanelAcciones();

	void setDiagrama(const VistaDiagrama* diag);
};

#endif /* PANELACCIONES_H_ */
