#ifndef VISTAENTIDAD_H_
#define VISTAENTIDAD_H_
#include "VistaComponente.h"
#include "../../controlador/AsistenteEntidad.h"
#include "../../modelo/Entidad.h"
#include <list>

class VistaEntidad: public VistaComponente, public Entidad {
private:
	friend class AsistenteEntidad;
	void calcular_ancho_a_partir_del_nombre();
public:
	VistaEntidad();
	virtual ~VistaEntidad();

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

#endif /* VISTAENTIDAD_H_ */
