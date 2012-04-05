/*
 * Diagrama.h
 *
 *  Created on: 02/04/2012
 *      Author: Guagnini Enzo 88325
 */

#ifndef DIAGRAMA_H_
#define DIAGRAMA_H_
#include "./componentes/Componente.h"
#include "./componentes/Entidad.h"
#include <list>
#include "../Constantes.h"


using namespace std;

class Diagrama: public Gtk::DrawingArea {
private:
	string nombre;
	list<Diagrama*> l_sub_diagramas;
	list<Componente*> l_componentes;

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
	friend class Proyecto;
public:
	Diagrama(string nom);
	virtual ~Diagrama();

	inline string getNombre() {
		return this->nombre;
	}
	inline void setNombre(string nom) {
		this->nombre = nom;
	}

	bool crearSubdiagrama(string nombre);
};

#endif /* DIAGRAMA_H_ */
