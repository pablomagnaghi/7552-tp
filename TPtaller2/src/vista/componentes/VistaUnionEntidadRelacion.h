#ifndef VISTAUNIONENTIDADRELACION_H_
#define VISTAUNIONENTIDADRELACION_H_

#include "VistaComponente.h"
#include "VistaEntidad.h"
#include "VistaRelacion.h"
#include "../../modelo/componentes/UnionEntidadRelacion.h"

class VistaEntidad;
class VistaRelacion;

class VistaUnionEntidadRelacion: public VistaComponente {
private:
	UnionEntidadRelacion * unionModelo;
	VistaEntidad * entidad;
	VistaRelacion * relacion;
	bool dibujar_cardinalidad;

	void actualizar_coordenadas();
public:
	VistaUnionEntidadRelacion(UnionEntidadRelacion * unionModelo, VistaEntidad * vEntidad,
			VistaRelacion * vRelacion);
	virtual ~VistaUnionEntidadRelacion();

	//Dibuja el objeto en el contexto cairo pasado como parametro.
	virtual void dibujar(Cairo::RefPtr<Cairo::Context> cr);

	//Lanza el asistente de prpiedades del objeto en cuestion.
	virtual bool lanzarProp(bool esNuevo=false);

	// Verifica si el punto cae dentro de este componente
	virtual bool contieneAEstePunto(double x, double y);

	virtual void calcularDimensionesAPartirDeTexto(Cairo::TextExtents * textExtents);

	// Verifica si el punto cae dentro de un punto para redimensionar el elemento
	virtual bool esPuntoDeRedimension(double x, double y);

	virtual void setMouseArriba(double x, double y);

	virtual bool esContenidoPorEsteComponente(VistaComponente *);

	virtual bool obtenerInterseccionConLinea(double pos_ini_x, double pos_ini_y, double pos_fin_x,
			double pos_fin_y, double & x, double & y);

	virtual void redimensionar(double x, double y);
	virtual std::string getNombre() const;
	virtual void setNombre(const std::string &);

	void getPuntoMedioLinea(double&, double &);

	UnionEntidadRelacion * getUnion();

	void eliminarComponentesAdyacentes(Diagrama * diagrama,
			std::vector<VistaComponente *> & componentes, VistaComponente * componenteEliminado);

	const std::string getCardinalidadMinima() const;
	void setCardinalidadMinima(const std::string &);

	const std::string getCardinalidadMaxima() const;
	void setCardinalidadMaxima(const std::string &);

	VistaEntidad * getEntidad();

	VistaRelacion * getRelacion();

	virtual bool hayQueEliminarlo();

	string to_s();

	virtual bool hayInterseccion(VistaComponente *);
	virtual bool probarInterseccionConRectangulo(double x0, double y0, double x1, double y1);

};
#endif /* VISTAUNIONENTIDADRELACION_H_ */
