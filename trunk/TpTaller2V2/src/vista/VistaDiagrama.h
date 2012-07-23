#ifndef VISTADIAGRAMA_H_
#define VISTADIAGRAMA_H_

//#define DEBUG 1

#include "../modelo/Diagrama.h"
#include <list>
#include <vector>
#include "VistaConstantes.h"
#include "./componentes/VistasDeComponentes.h"


using namespace std;

class VistaDiagrama: public Gtk::DrawingArea {
private:
	double zoom;
	int ancho;
	int alto;

	Diagrama * diagrama;

	std::vector<VistaComponente *> componentes;
	std::vector<VistaComponente *> componentes_seleccionados;

	// Para controlar el drag and drop
	bool mouse_apretado;
	gdouble x_button_press;
	gdouble y_button_press;
	bool estaRedimensionandoElemento; // Para que no se haga el drag
	bool estaAgregandoElemento;

	// Para controlar el menu de pop up
	bool menu_popup_activo;
	VistaComponente * componenteMenuActivo;

	// Redefinicion del metodo de Gtk::DrawingArea q se llama cada vez q debe dibujarse la hoja.
	bool on_expose_event(GdkEventExpose* e);

	// Se lanza cada vez que el mouse interactua con la hoja presionando alguno de sus botones
	bool on_button_press_event(GdkEventButton* event);

	// Se lanza cada vez que el mouse interactua con la hoja soltando alguno de sus botones
	bool on_button_release_event(GdkEventButton* event);

	bool on_mouse_motion_event(GdkEventMotion * event);

	//friend class TreePanel;
	//friend class VistaProyecto;

	VistaComponente * obtenerComponenteEnPos(gdouble x, gdouble y);

	void
	obtenerVistaAPartirDeRelacion(VistaRelacion *, std::vector<
			VistaEntidadNueva *>&, std::vector<UnionEntidadRelacion *>&);

	void configurar_drag_and_drop();

	// Señales para Drag and Drop
	// Origen
	// Cuando comienza a arrastrar un objeto
	void drag_begin(const Glib::RefPtr<Gdk::DragContext>&);
	// Cuando realiza el movimiento de arrastre de objeto
	bool drag_motion(const Glib::RefPtr<Gdk::DragContext>& context, gint x,
			int y, guint time);
	// Cuando se obtienen los datos del origen
	void drag_data_get(const Glib::RefPtr<Gdk::DragContext>&,
			Gtk::SelectionData& selection_data, guint, guint);
	// Cuando ya se soltó el objeto y se pasaron los datos al destino
	bool drag_drop(const Glib::RefPtr<Gdk::DragContext>& context, gint x,
			gint y, guint time);
	// Cuando finaliza el arrastre
	void drag_end(const Glib::RefPtr<Gdk::DragContext>&);
	// Cuando se debe eliminar los datos al MOVER
	void drag_data_delete(const Glib::RefPtr<Gdk::DragContext>&);
	// Cuando el objeto arrastrado se suelta en un objeto que no es destino
	bool drag_failed(const Glib::RefPtr<Gdk::DragContext>&, Gtk::DragResult);
	// Cuando el arrastre sale del objeto donde comenzo
	void drag_leave(const Glib::RefPtr<Gdk::DragContext>&, guint);

	// Destino
	// Cuando el destino recibe los datos del objeto arrastrado
	void drag_data_received(const Glib::RefPtr<Gdk::DragContext>& context,
			gint, int, const Gtk::SelectionData& selection_data, guint,
			guint time);

	void seleccionar_componente_clickeado(gdouble x, gdouble y);

	// Persistencia
	bool diagramaValidoREP;

	void obtenerPropiedadesXmlREP(XmlNodo* nodo);
	void obtenerComponentesXmlREP(XmlNodo* nodo);
	void agregarPropiedadesXmlREP(XmlNodo* nodo);
	void guardarComponentesXmlREP(XmlNodo *nodo);

	XmlNodo guardarXmlREP();

public:

	VistaDiagrama(Diagrama * diagramaModelo);
	virtual ~VistaDiagrama();

	void setZoom(double z);

	virtual VistaDiagrama* crearDiagramaHijo(string nombre);
	int getAlto();
	int getAncho();

	void agregarComponente(VistaComponente * componente);

	std::string getNombre() const;

	std::vector<VistaComponente*>::iterator componentesBegin();
	std::vector<VistaComponente*>::iterator componentesEnd();

	Diagrama * getDiagrama();
	void test_cargar_componentes_visuales();
	// Persistencia REP
	void abrirREP(const std::string& path);
	bool isOpenREP() const;
	void guardarDiagramaREP(const std::string& path);
};

#endif /* VISTADIAGRAMA_H_ */