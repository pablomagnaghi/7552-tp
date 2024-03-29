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
#include "../../modelo/Diagrama.h"

using namespace std;

#define ESPACIO_ENTRE_TEXTO_Y_BORDE 5
#define LONGITUD_LINEAS_REDIMENSION 2
#define RADIO_CIRCULOS_REDIMENSION 3

#define DEBUG_QUITAR 1
#define DEBUG_DIBUJAR 0
#define DEBUG_SELECCION 0
#define DEBUG_REDIMENSION 0

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

	bool eliminando;
	bool eliminarModelo;

	void dibujarNombreCentrado(Cairo::RefPtr<Cairo::Context> cr, const std::string nombre);

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
	void getposseleccion(double &x, double &y) const;

	void setDibujable(bool d);
	bool getDibujable();

	// Dibuja el objeto en el contexto cairo pasado como parametro.
	virtual void dibujar(Cairo::RefPtr<Cairo::Context> cr) = 0;

	// Lanza el asistente de prpiedades del objeto en cuestion.
	virtual bool lanzarProp(bool esNuevo=false) = 0;

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
	virtual void calcularDimensionesAPartirDeTexto(Cairo::TextExtents * textExtents)=0;

	// Verifica si el punto cae dentro de un punto para redimensionar el elemento
	virtual bool esPuntoDeRedimension(double x, double y) = 0;

	void ajustarTamanioAlTexto();

	virtual std::string getNombre() const = 0;
	virtual void setNombre(const std::string &) = 0;

	// Menu Pop Up
	virtual void crear_menu(Glib::RefPtr<Gtk::UIManager> & userInterfaceManager);
	void on_popup_boton_propiedades();

	virtual void on_popup_boton_Identificadores();

	virtual bool esContenidoPorEsteComponente(VistaComponente *)=0;

	virtual bool obtenerInterseccionConLinea(double pos_ini_x, double pos_ini_y, double pos_fin_x,
			double pos_fin_y, double & x, double & y)=0;

	virtual bool hayInterseccion(VistaComponente *);

	virtual bool probarInterseccionConRectangulo(double x0, double y0, double x1, double y1);

	bool estaSeleccionado();

	virtual void eliminarComponentesAdyacentes(Diagrama * diagrama,
			std::vector<VistaComponente *> & componentes_a_eliminar,
			VistaComponente * componenteEliminado) = 0;
	virtual void removerComponenteAEliminar(VistaComponente * componente);
	virtual bool hayQueEliminarlo()=0;

	// PERSISTENCIA REP
	int getCodigoREP();
	void setCodigoREP(int codigoREP);
	// CARGAR
	void cargarDatosXmlRep(XmlNodo*);
	// GUARDAR
	XmlNodo guardarXmlREP();

	virtual bool identificador_en_popup();
};

#endif /* VISTACOMPONENTE_H_ */
