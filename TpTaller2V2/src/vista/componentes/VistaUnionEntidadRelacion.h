#ifndef VISTAUNIONENTIDADRELACION_H_
#define VISTAUNIONENTIDADRELACION_H_

#include "VistaComponente.h"
#include "VistaEntidadNueva.h"
#include "VistaRelacion.h"
#include "../../modelo/componentes/UnionEntidadRelacion.h"

class VistaEntidadNueva;

class VistaUnionEntidadRelacion: public VistaComponente {
private:
	UnionEntidadRelacion * unionModelo;
	VistaEntidadNueva * entidad;
	VistaRelacion * relacion;
	bool dibujar_cardinalidad;

	void actualizar_coordenadas();
public:
	VistaUnionEntidadRelacion(UnionEntidadRelacion * unionModelo, VistaEntidadNueva * vEntidad, VistaRelacion * vRelacion);
	virtual ~VistaUnionEntidadRelacion();

	//Dibuja el objeto en el contexto cairo pasado como parametro.
	virtual void dibujar(Cairo::RefPtr<Cairo::Context> cr);

	//Indica q sucede cuando el objeto es seleccionado
	virtual bool esSeleccionado(double x, double y);

	//indica q sucede con el objeto cuando deja de ser seleccionado
	virtual void finSeleccionado(double x, double y);

	//Lanza el asistente de prpiedades del objeto en cuestion.
	virtual bool lanzarProp();

	// Verifica si el punto cae dentro de este componente
	virtual bool contieneAEstePunto(double x, double y);

	virtual void calcularDimensionesAPartirDeTexto(
			Cairo::TextExtents * textExtents);

	// Verifica si el punto cae dentro de un punto para redimensionar el elemento
	virtual bool esPuntoDeRedimension(double x, double y);

	virtual void setMouseArriba(double x, double y);

	virtual bool contieneEsteComponente(Componente *);

	virtual bool obtenerInterseccionConLinea(double pos_ini_x,
					double pos_ini_y, double pos_fin_x, double pos_fin_y, double & x,
					double & y);

	virtual void redimensionar(double x, double y);
	virtual std::string getNombre() const;

	void getPuntoMedioLinea(double&,double &);
};

#endif /* VISTAUNIONENTIDADRELACION_H_ */
