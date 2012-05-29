/* VistaRelacion.h
 *  Created on: 24/05/2012
 *      Author: Gonzalo Ferrero 89657
 */

#ifndef VISTARELACION_H_
#define VISTARELACION_H_
#include "../../modelo/Relacion.h"
#include "VistaComponente.h"

class VistaRelacion: public VistaComponente, public Relacion {
public:
	VistaRelacion();
	virtual ~VistaRelacion();

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

#endif /* VISTARELACION_H_ */