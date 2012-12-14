#ifndef VISTARELACION_H_
#define VISTARELACION_H_
#include "../../modelo/componentes/Relacion.h"
#include "../../controlador/AsistenteRelacion.h"
#include "VistaComponente.h"
#include "VistaAtributo.h"
#include "InterfazRemoverAtributo.h"
#include "VistaUnionEntidadRelacion.h"

class VistaAtributo;

class VistaRelacion: public VistaComponente , public InterfazRemoverAtributo{
private:

	Relacion * relacion;
	std::vector<VistaAtributo * >vistaAtributos;
	std::vector<VistaUnionEntidadRelacion * >vistaUniones;
	bool prop_lanzada;

	void dibujarFiguraDeRelacion(Cairo::RefPtr<Cairo::Context> cr);
	void dibujarCirculosDeRedimension(Cairo::RefPtr<Cairo::Context> cr);

public:
	VistaRelacion(Relacion * relacionModelo);
	virtual ~VistaRelacion();
	void resetearLanzarProp();

	virtual void dibujar(Cairo::RefPtr<Cairo::Context> cr);
	virtual bool lanzarProp();
	virtual bool contieneAEstePunto(double x, double y);
	virtual void calcularDimensionesAPartirDeTexto(Cairo::TextExtents * textExtents);
	virtual bool esPuntoDeRedimension(double x, double y);
	virtual void setMouseArriba(double x, double y);
	virtual void redimensionar(double x, double y);
	virtual std::string getNombre() const;
	virtual void setNombre(const std::string &);
	virtual bool contieneEsteComponente(VistaComponente *);
	virtual bool obtenerInterseccionConLinea(double pos_ini_x, double pos_ini_y, double pos_fin_x,
			double pos_fin_y, double & x, double & y);

	Relacion * getRelacion();
	std::vector<UnionEntidadRelacion *> getUniones();

	bool agregarAtributo(VistaAtributo* atrib);
	bool agregarUnion(VistaUnionEntidadRelacion* vuer);
	virtual bool quitarAtributo(VistaAtributo* atrib);
	std::vector<VistaAtributo*>::iterator atributosBegin();
	std::vector<VistaAtributo*>::iterator atributosEnd();

	std::vector<VistaUnionEntidadRelacion*>::iterator unionesBegin();
	std::vector<VistaUnionEntidadRelacion*>::iterator unionesEnd();
	VistaUnionEntidadRelacion* unidaConEntidad(VistaEntidad *ve);

	void eliminarComponentesAdyacentes(Diagrama * diagrama,std::vector<VistaComponente *> & componentes, VistaComponente * componenteEliminado);

	virtual bool hayQueEliminarlo();
};

#endif /* VISTARELACION_H_ */
