#ifndef VISTAIDENTIFICADOR_H_
#define VISTAIDENTIFICADOR_H_

#include "VistaComponente.h"
#include "../../modelo/componentes/Identificador.h"
#include "VistaLinea.h"
#include "VistaAtributo.h"
#include <vector>
#include "../VistaConstantes.h"
#include "VistaUnionEntidadRelacion.h"

class VistaAtributo;
class VistaUnionEntidadRelacion;

class VistaIdentificador: public VistaComponente {
private:
	std::vector<VistaAtributo *> vistasAtributo;
	std::vector<VistaUnionEntidadRelacion *> vistasEntidadesFuertes;
	Identificador * identificador;
	bool prop_lanzada;

	void dibujarCirculosDeRedimension(Cairo::RefPtr<Cairo::Context> cr);

public:
	VistaIdentificador(Identificador * identificador);
	virtual ~VistaIdentificador();

	void agregarAtributo(VistaAtributo *);
	std::vector<VistaAtributo*>::iterator atributosBegin();
	std::vector<VistaAtributo*>::iterator atributosEnd();

	void agregarEntidadFuerte(VistaUnionEntidadRelacion *);
	std::vector<VistaUnionEntidadRelacion*>::iterator entidadesFuertesBegin();
	std::vector<VistaUnionEntidadRelacion*>::iterator entidadesFuertesEnd();

	void resetearLanzarProp();

	//Dibuja el objeto en el contexto cairo pasado como parametro.
	virtual void dibujar(Cairo::RefPtr<Cairo::Context> cr);


	//Lanza el asistente de prpiedades del objeto en cuestion.
	virtual bool lanzarProp();

	// Verifica si el punto cae dentro de este componente
	virtual bool contieneAEstePunto(double x, double y);

	virtual void calcularDimensionesAPartirDeTexto(Cairo::TextExtents * textExtents);

	// Verifica si el punto cae dentro de un punto para redimensionar el elemento
	virtual bool esPuntoDeRedimension(double x, double y);

	virtual void setMouseArriba(double x, double y);

	virtual void redimensionar(double x, double y);

	virtual bool contieneEsteComponente(Componente *);

	virtual bool obtenerInterseccionConLinea(double pos_ini_x, double pos_ini_y, double pos_fin_x,
			double pos_fin_y, double & x, double & y);

	virtual std::string getNombre() const;
	virtual void setNombre(const std::string &);

	Identificador * getIdentificador();

	void eliminarComponentesAdyacentes(std::vector<VistaComponente *> & componentes);
};

#endif /* VISTAIDENTIFICADOR_H_ */
