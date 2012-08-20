#ifndef VISTAENTIDADGLOBAL_H_
#define VISTAENTIDADGLOBAL_H_

#include "VistaEntidad.h"
#include "../../modelo/componentes/EntidadGlobal.h"

class VistaEntidadGlobal: public VistaEntidad {
private:
	EntidadGlobal * entidad;
public:
	VistaEntidadGlobal(EntidadGlobal *);
	virtual ~VistaEntidadGlobal();

	virtual bool contieneEsteComponente(Componente *);

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

	virtual void calcularDimensionesAPartirDeTexto(Cairo::TextExtents * textExtents);

	// Verifica si el punto cae dentro de un punto para redimensionar el elemento
	virtual bool esPuntoDeRedimension(double x, double y);

	virtual void setMouseArriba(double x, double y);

	virtual void redimensionar(double x, double y);

	void setNombre(const std::string & nombre);
	virtual std::string getNombre() const;

};

#endif /* VISTAENTIDADGLOBAL_H_ */
