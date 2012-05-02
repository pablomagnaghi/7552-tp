/*
 * Diagrama.h
 *
 *  Created on: 02/04/2012
 *      Author: Guagnini Enzo 88325
 */

#ifndef VISTADIAGRAMA_H_
#define VISTADIAGRAMA_H_
#include "./componentes/VistaComponente.h"
#include "./componentes/VistaAtributo.h"
#include "../modelo/Diagrama.h"
#include <list>
#include "VistaConstantes.h"

using namespace std;

class VistaDiagrama : public Gtk::DrawingArea, public Diagrama {
private:
	double zoom;
	int ancho;
	int alto;

	/*
	 * Redefinicion del metodo de Gtk::DrawingArea q se llama cada vez q debe dibujarse la hoja.
	 */
	bool on_expose_event(GdkEventExpose* e);

	/*
	 * Se lanza cada vez que el mouse interactua con la hoja preionando alguno de sus botones
	 */
	bool on_button_press_event(GdkEventButton* event);

	/*
	 * Se lanza cada vez que el mouse interactua con la hoja soltando alguno de sus botones
	 */
	bool on_button_release_event(GdkEventButton* event);

	friend class TreePanel;
	friend class VistaProyecto;
public:

	VistaDiagrama(string nom);
	virtual ~VistaDiagrama();

	void setZoom(double z);

	virtual VistaDiagrama* crearSubdiagrama(string nombre);
	int getAlto();
	int getAncho();
};

#endif /* VISTADIAGRAMA_H_ */
