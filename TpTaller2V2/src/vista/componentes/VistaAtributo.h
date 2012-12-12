#ifndef VISTAATRIBUTO_H_
#define VISTAATRIBUTO_H_
#include "VistaComponente.h"
#include "../../modelo/componentes/Atributo.h"
#include "../../controlador/AsistenteAtributo.h"
#include <list>
#include "../VistaConstantes.h"
#include "VistaLinea.h"
#include "InterfazRemoverAtributo.h"

class VistaAtributo: public VistaComponente, public InterfazRemoverAtributo {
private:
	std::vector<VistaAtributo*> atributosHijos;
	Atributo * atributo;
	bool prop_lanzada;
	bool esIdentificador;
	VistaLinea * linea;
	bool dibujar_cardinalidad;
	InterfazRemoverAtributo * padre;

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
	virtual bool quitarAtributo(VistaAtributo* atrib);

	//Dibuja el objeto en el contexto cairo pasado como parametro.
	virtual void dibujar(Cairo::RefPtr<Cairo::Context> cr);

	void setPadre(InterfazRemoverAtributo * padre);

	//Lanza el asistente de prpiedades del objeto en cuestion.
	virtual bool lanzarProp();

	// Verifica si el punto cae dentro de este componente
	virtual bool contieneAEstePunto(double x, double y);

	virtual void calcularDimensionesAPartirDeTexto(Cairo::TextExtents * textExtents);

	// Verifica si el punto cae dentro de un punto para redimensionar el elemento
	virtual bool esPuntoDeRedimension(double x, double y);

	virtual void setMouseArriba(double x, double y);

	virtual void redimensionar(double x, double y);

	virtual bool contieneEsteComponente(VistaComponente *);

	virtual bool obtenerInterseccionConLinea(double pos_ini_x, double pos_ini_y, double pos_fin_x,
			double pos_fin_y, double & x, double & y);

	virtual std::string getNombre() const;
	virtual void setNombre(const std::string &);

	void setEsIdentificador(bool);

	void setLinea(VistaLinea *);

	void getPuntoMedioLinea(double &x, double &y);

	void eliminarComponentesAdyacentes(Diagrama * diagrama,std::vector<VistaComponente *> & componentes);
};

#endif /* VISTAATRIBUTO_H_ */
