/*
 * Diagrama.h
 *
 *  Created on: 02/04/2012
 *      Author: Guagnini Enzo 88325
 */

#ifndef DIAGRAMA_H_
#define DIAGRAMA_H_
#include "./componentes/VistaComponente.h"
#include "./componentes/VistaAtributo.h"
#include <list>
#include "VistaConstantes.h"


using namespace std;

class VistaDiagrama: public Gtk::DrawingArea {
private:
	string nombre;
	double zoom;
	int ancho;
	int alto;
	list<VistaDiagrama*> l_sub_diagramas;
	list<VistaComponente*> l_componentes;

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

	inline string getNombre() {
		return this->nombre;
	}
	inline void setNombre(string nom) {
		this->nombre = nom;
	}

	VistaDiagrama* crearSubdiagrama(string nombre);

	void setZoom(double z);

	int getAlto();
	int getAncho();
};

#endif /* DIAGRAMA_H_ */
