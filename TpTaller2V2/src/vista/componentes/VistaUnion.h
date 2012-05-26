/* VistaUnion.h
 *  Created on: 24/05/2012
 *      Author: Gonzalo Ferrero 89657
 */

#ifndef VISTAUNION_H_
#define VISTAUNION_H_
#include "VistaComponente.h"

class VistaUnion: public VistaComponente {
public:
	VistaUnion();
	virtual ~VistaUnion();

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

};

#endif /* VISTAUNION_H_ */
