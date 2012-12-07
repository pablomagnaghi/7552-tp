#ifndef VISTACOMPONENTE_H_
#define VISTACOMPONENTE_H_
#include <gtkmm.h>
#include <cairomm/cairomm.h>
#include <string>
#include "../VistaConstantes.h"
#include <gtkmm/targetentry.h>
#include "../../modelo/componentes/Componente.h"
#include "Geometria.h"

// Persistencia
#include "../../modelo/persistencia/Persistencia.h"

using namespace std;

#define ESPACIO_ENTRE_TEXTO_Y_BORDE 5
#define LONGITUD_LINEAS_REDIMENSION 2
#define RADIO_CIRCULOS_REDIMENSION 3

class VistaComponente {
protected:
	double pos_ini_x;
	double pos_ini_y;
	double pos_fin_x;
	double pos_fin_y;
	double pos_selec_x;
	double pos_selec_y;
	double colorR;
	double colorG;
	double colorB;
	bool dibujable;

	bool seleccionado;
	//bool estaMouseArriba;
	static Gdk::Color colorNegro;
	static Gdk::Color colorDeSeleccion;
	static Gdk::Color colorDeRedimension;
	static Gdk::Color colorBlanco;
	static Gdk::Color colorVerde;
	int mouseArribaDePuntoDeRedimension;
	bool ajustarTamanioPorTexto;
	bool prop_lanzada;

	void dibujarNombreCentrado(Cairo::RefPtr<Cairo::Context> cr,
			const std::string nombre);

	void on_popup_boton_propiedades();

	// PERSISTENCIA REP
	int codigoREP;
	// GUARDAR
	void agregarPropiedadesXmlREP(XmlNodo* nodo);

	// CARGAR
	void obtenerPropiedadesXmlREP(XmlNodo* nodo);
	void obtenerComponentesXmlREP(XmlNodo* nodo);

public:
	VistaComponente();
	virtual ~VistaComponente();

	void getposini(double &x, double&y) const;
	virtual void setposini(double x, double y);
	void getposfin(double&x, double&y) const;
	virtual void setposfin(double x, double y);
	void getposcentro(double &x, double&y) const;
	void getposseleccion(double &x, double &y)const;

	void setDibujable(bool d);
	bool getDibujable();

	// Dibuja el objeto en el contexto cairo pasado como parametro.
	virtual void dibujar(Cairo::RefPtr<Cairo::Context> cr) = 0;

	// Lanza el asistente de prpiedades del objeto en cuestion.
	virtual bool lanzarProp() = 0;

	// lanza el menú al hacer click derecho
	virtual void lanzarMenuPopUp(GdkEventButton* event);

	// Verifica si el punto cae dentro de este componente
	virtual bool contieneAEstePunto(double x, double y) = 0;

	// Para seleccionar a este componente
	void seleccionar(double x, double y);
	void deseleccionar();

	virtual void setMouseArriba(double x, double y) = 0;

	// para mover el componente
	void mover(double x, double y);

	virtual void redimensionar(double x, double y)=0;

	// Calcula las dimensiones del componente a partir de las dimensiones del nombre
	virtual void calcularDimensionesAPartirDeTexto(
			Cairo::TextExtents * textExtents)=0;

	// Verifica si el punto cae dentro de un punto para redimensionar el elemento
	virtual bool esPuntoDeRedimension(double x, double y) = 0;

	void ajustarTamanioAlTexto();

	virtual std::string getNombre() const = 0;
	virtual void setNombre(const std::string &)  = 0;

	// Menu Pop Up
	void crear_menu(Glib::RefPtr<Gtk::UIManager> & userInterfaceManager);

	virtual bool contieneEsteComponente(Componente *)=0;

	virtual bool obtenerInterseccionConLinea(double pos_ini_x,
			double pos_ini_y, double pos_fin_x, double pos_fin_y, double & x,
			double & y)=0;

	bool estaSeleccionado();

	// PERSISTENCIA REP
	int getCodigoREP();
	void setCodigoREP(int codigoREP);
	// CARGAR
	void cargarDatosXmlRep(XmlNodo*);
	// GUARDAR
	XmlNodo guardarXmlREP();
};

#endif /* VISTACOMPONENTE_H_ */
