/*
 * Componente.h
 *
 *  Created on: 02/04/2012
 *      Author: Guagnini Enzo 88325
 */

#ifndef VISTACOMPONENTE_H_
#define VISTACOMPONENTE_H_
#include <gtkmm.h>
#include <cairomm/cairomm.h>
#include <string>
#include "../VistaConstantes.h"
#include <gtkmm/targetentry.h>
#include "../../modelo/Componente.h"

using namespace std;

#define ESPACIO_ENTRE_TEXTO_Y_BORDE 5

class VistaComponente /*: public Componente*/ {
protected:
	double pos_ini_x;
	double pos_ini_y;
	double pos_fin_x;
	double pos_fin_y;
	double pos_selec_x;
	double pos_selec_y;
	bool dibujable;
	Gtk::Menu* m_pMenuPopup;

	bool seleccionado;
	Gdk::Color colorNegro;
	Gdk::Color colorDeSeleccion;

	void dibujarNombreCentrado(Cairo::RefPtr<Cairo::Context> cr, const std::string nombre);

	/*PERSISTENCIA REP
	// void Componente::agregarPropiedadesRep(XmlNodo* nodo);
	// void Componente::obtenerPropiedadesRep(XmlNodo* nodo);

	// void VistaComponente:agregarAtributosRep ( XmlNodo* nodo );
	// void VistaComponente:obtenerAtributosRep ( XmlNodo* nodo );
	*/

public:
	VistaComponente();
	virtual ~VistaComponente();

	void getposini(double &x, double&y) const;
	void setposini(double x, double y);
	void getposfin(double&x, double&y) const;
	virtual void setposfin(double x, double y);
	void setDibujable(bool d);
	bool getDibujable();

	// Dibuja el objeto en el contexto cairo pasado como parametro.
	virtual void dibujar(Cairo::RefPtr<Cairo::Context> cr) = 0;

	// Indica q sucede cuando el objeto es seleccionado
	virtual bool esSeleccionado(double x, double y) = 0;

	// indica q sucede con el objeto cuando deja de ser seleccionado
	virtual void finSeleccionado(double x, double y) = 0;

	// Lanza el asistente de prpiedades del objeto en cuestion.
	virtual void lanzarProp(GdkEventButton* event) = 0;

	// Verifica si el punto cae dentro de este componente
	virtual bool contieneAEstePunto(double x, double y) = 0;

	// Para seleccionar a este componente
	void seleccionar(double x, double y);
	void deseleccionar();

	// para mover el componente
	void mover(double x, double y);

	// Calcula las dimensiones del componente a partir de las dimensiones del nombre
	virtual void calcularDimensionesAPartirDeTexto(Cairo::TextExtents * textExtents)=0;



	/*PERSISTENCIA REP
	// XmlNodo guardarXmlREP();
	 */

};

#endif /* VISTACOMPONENTE_H_ */