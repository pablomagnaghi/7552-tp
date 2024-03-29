#ifndef VISTAJERARQUIA_H_
#define VISTAJERARQUIA_H_

#include "VistaComponente.h"
#include "VistaEntidadNueva.h"
#include "../../controlador/AsistenteJerarquia.h"

#include "../../modelo/componentes/Jerarquia.h"

// INCLUDE PARA METODO PARCHE
#include "../../modelo/componentes/EntidadNueva.h"

#include <vector>

class VistaEntidadNueva;

class VistaJerarquia: public VistaComponente {
private:

	Jerarquia * jerarquia;
	VistaEntidad * padre;
	std::vector<VistaEntidadNueva *> hijos;

	void calcularLineaMedia(double ymin, double ymax);
	void calcularMinMax(double & xmin, double & xmax, double & ymin, double & ymax);
	void dibujarLineaMedia(Cairo::RefPtr<Cairo::Context> cr, double ymin, double ymax);

	// METODO PARCHE A EVALUAR
	bool existeEntidadNueva(EntidadNueva *entidad);
public:
	VistaJerarquia(Jerarquia * jerarquiaModelo);
	virtual ~VistaJerarquia();

	virtual void dibujar(Cairo::RefPtr<Cairo::Context> cr);
	virtual bool lanzarProp(bool esNuevo=false);
	void resetearLanzarProp();
	virtual bool contieneAEstePunto(double x, double y);
	virtual void calcularDimensionesAPartirDeTexto(Cairo::TextExtents * textExtents);
	virtual bool esPuntoDeRedimension(double x, double y);
	virtual void setMouseArriba(double x, double y);
	virtual void redimensionar(double x, double y);
	virtual std::string getNombre() const;
	virtual void setNombre(const std::string &);
	virtual bool esContenidoPorEsteComponente(VistaComponente *);
	virtual bool obtenerInterseccionConLinea(double pos_ini_x, double pos_ini_y, double pos_fin_x,
			double pos_fin_y, double & x, double & y);

	// Interfaz para modificar la Jerarquia
	void agregarEntidadEspecializada(VistaEntidadNueva *);
	void removerEntidadEspecializada(VistaEntidadNueva *);
	std::vector<VistaEntidadNueva *>::iterator entidadesEspecializadasBegin();
	std::vector<VistaEntidadNueva *>::iterator entidadesEspecializadasEnd();
	void setEntidadPadre(VistaEntidad *);
	VistaEntidad * getEntidadPadre();

	Jerarquia * getJerarquia();

	void eliminarComponentesAdyacentes(Diagrama * diagrama,
			std::vector<VistaComponente *> & componentes, VistaComponente * componenteEliminado);

	virtual bool hayQueEliminarlo();

	virtual bool hayInterseccion(VistaComponente *);

	virtual bool probarInterseccionConRectangulo(double x0, double y0, double x1, double y1);

	virtual bool unidaConEntidad(VistaEntidad * ventidad);

};

#endif /* VISTAJERARQUIA_H_ */
