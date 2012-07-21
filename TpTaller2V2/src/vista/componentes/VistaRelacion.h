#ifndef VISTARELACION_H_
#define VISTARELACION_H_
#include "../../modelo/componentes/Relacion.h"
#include "VistaComponente.h"

class VistaRelacion: public VistaComponente {
private:

	Relacion * relacion;

	void dibujarFiguraDeRelacion(Cairo::RefPtr<Cairo::Context> cr);
	void dibujarCirculosDeRedimension(Cairo::RefPtr<Cairo::Context> cr);

public:
	VistaRelacion(Relacion * relacionModelo);
	virtual ~VistaRelacion();

	virtual void dibujar(Cairo::RefPtr<Cairo::Context> cr);
	virtual bool esSeleccionado(double x, double y);
	virtual void finSeleccionado(double x, double y);
	virtual bool lanzarProp();
	virtual bool contieneAEstePunto(double x, double y);
	virtual void calcularDimensionesAPartirDeTexto(Cairo::TextExtents * textExtents);
	virtual bool esPuntoDeRedimension(double x, double y);
	virtual void setMouseArriba(double x, double y);
	virtual void redimensionar(double x, double y);
	void setNombre(const std::string & nombre);
	virtual std::string getNombre() const;
	virtual bool contieneEsteComponente(Componente *);
	virtual bool obtenerInterseccionConLinea(double pos_ini_x, double pos_ini_y, double pos_fin_x,
			double pos_fin_y, double & x, double & y);

	std::vector<UnionEntidadRelacion *> getUniones();

};

#endif /* VISTARELACION_H_ */
