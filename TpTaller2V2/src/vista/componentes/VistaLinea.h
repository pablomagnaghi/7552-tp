#ifndef VISTALINEA_H_
#define VISTALINEA_H_

#include "VistaComponente.h"
#include <string>

class VistaLinea: public VistaComponente {
private:
	std::string texto;
	VistaComponente * desde;
	VistaComponente * hasta;


public:
	VistaLinea();
	virtual ~VistaLinea();

	// Dibuja el objeto en el contexto cairo pasado como parametro.
	virtual void dibujar(Cairo::RefPtr<Cairo::Context> cr);

	void setComponenteDesde(VistaComponente *);

	void setComponenteHasta(VistaComponente *);

	void actualizar_coordenadas();

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

	virtual bool contieneEsteComponente(Componente *);

	virtual bool obtenerInterseccionConLinea(double pos_ini_x, double pos_ini_y, double pos_fin_x,
			double pos_fin_y, double & x, double & y);

	void setTexto(const std::string &);
	std::string getTexto();

};

#endif /* VISTALINEA_H_ */
