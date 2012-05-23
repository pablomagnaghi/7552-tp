/*
 * Entidad.h
 *
 *  Created on: 02/04/2012
 *      Author: Guagnini Enzo 88325
 */

#ifndef ENTIDAD_H_
#define ENTIDAD_H_
#include "VistaComponente.h"
#include "VistaAtributo.h"
#include <list>

class VistaEntidad: public VistaComponente {
private:
	list<VistaAtributo*> l_atributos;
	string nombre;
public:
	VistaEntidad();
	virtual ~VistaEntidad();

	inline string getNombre() {
		return this->nombre;
	}
	inline void setNombre(string nom) {
		this->nombre = nom;
	}


	// Metodos heredados de VistaComponente
	/*
	 * Dibuja el objeto en el contexto cairo pasado como parametro.
	 */
	virtual void dibujar(Cairo::RefPtr<Cairo::Context> cr);

	/*
	 * Indica q sucede cuando el objeto es seleccionado
	 */
	virtual bool esSeleccionado(double x, double y);

	/*
	 * indica q sucede con el objeto cuando deja de ser seleccionado
	 */
	virtual void finSeleccionado(double x, double y);

	/*
	 * Lanza el asistente de prpiedades del objeto en cuestion.
	 */
	virtual void lanzarProp(GdkEventButton* event);
};

#endif /* ENTIDAD_H_ */
