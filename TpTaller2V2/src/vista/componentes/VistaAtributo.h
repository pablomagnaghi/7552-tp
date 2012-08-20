#ifndef VISTAATRIBUTO_H_
#define VISTAATRIBUTO_H_
#include "VistaComponente.h"
#include "../../modelo/componentes/Atributo.h"
#include "../../controlador/AsistenteAtributo.h"
#include <list>
#include "../VistaConstantes.h"
#include "VistaLinea.h"

class VistaAtributo: public VistaComponente {
private:
	std::vector<VistaAtributo*> vistaAtributos;
	Atributo * atributo;
	bool prop_lanzada;
	bool esIdentificador;
	VistaLinea * lineaConEntidad;
	bool dibujar_cardinalidad;

	void dibujarCirculosDeRedimension(Cairo::RefPtr<Cairo::Context> cr);

	void actualizar_coordenadas();

public:
	VistaAtributo(Atributo * atributoModelo);
	virtual ~VistaAtributo();

	std::vector<VistaAtributo*>::iterator atributosBegin();
	std::vector<VistaAtributo*>::iterator atributosEnd();

	void resetearLanzarProp();

	Atributo* getAtributo();

	virtual void setposini(double x, double y);

	// Solo se puede agregar y sacar atributos a la entidad nueva
	bool agregarAtributo(VistaAtributo* atrib);
	bool quitarAtributo(VistaAtributo* atrib);

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

	virtual bool contieneEsteComponente(Componente *);

	virtual bool obtenerInterseccionConLinea(double pos_ini_x, double pos_ini_y, double pos_fin_x,
			double pos_fin_y, double & x, double & y);

	virtual std::string getNombre() const;

	void setEsIdentificador(bool);

	void setLinea(VistaLinea *);

	void getPuntoMedioLinea(double &x, double &y);
};

#endif /* VISTAATRIBUTO_H_ */
