/*
 * Atributo.h
 *
 *  Created on: 02/04/2012
 *      Author: Guagnini Enzo 88325
 */

#ifndef VISTAATRIBUTO_H_
#define VISTAATRIBUTO_H_
#include "VistaComponente.h"
#include "../../modelo/Atributo.h"
#include <list>

class VistaAtributo: public VistaComponente, public Atributo {
private:
	list<VistaAtributo*> l_atrib_deri;
public:
	VistaAtributo();
	virtual ~VistaAtributo();



	//Dibuja el objeto en el contexto cairo pasado como parametro.
	virtual void dibujar(Cairo::RefPtr<Cairo::Context> cr);

	//Indica q sucede cuando el objeto es seleccionado
	virtual bool esSeleccionado(double x, double y);

	//indica q sucede con el objeto cuando deja de ser seleccionado
	virtual void finSeleccionado(double x, double y);

	//Lanza el asistente de prpiedades del objeto en cuestion.
	virtual void lanzarProp(GdkEventButton* event);

	// Verifica si el punto cae dentro de este componente
	virtual bool contieneAEstePunto(double x, double y);

	virtual void calcularDimensionesAPartirDeTexto(Cairo::TextExtents * textExtents);
};

#endif /* VISTAATRIBUTO_H_ */