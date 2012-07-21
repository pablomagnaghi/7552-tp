#ifndef VISTAENTIDADNUEVA_H_
#define VISTAENTIDADNUEVA_H_
#include "VistaEntidad.h"
#include "../../controlador/AsistenteEntidad.h"
#include "../../modelo/componentes/EntidadNueva.h"
#include <list>

class VistaEntidadNueva: public VistaEntidad{
private:
	friend class AsistenteEntidad;

	EntidadNueva * entidad;

	void calcular_ancho_a_partir_del_nombre();
	void dibujarFiguraDeEntidad(Cairo::RefPtr<Cairo::Context> cr);
	void dibujarCirculosDeRedimension(Cairo::RefPtr<Cairo::Context> cr);
public:
	VistaEntidadNueva(EntidadNueva *);
	virtual ~VistaEntidadNueva();

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
	virtual  std::string getNombre() const;

	virtual bool contieneEsteComponente(Componente *);

	virtual bool obtenerInterseccionColLinea(double pos_ini_x,
				double pos_ini_y, double pos_fin_x, double pos_fin_y, double & x,
				double & y);

	void setEsDebil(bool);

	bool esDebil();
};

#endif /* VISTAENTIDADNUEVA_H_ */
