#ifndef CONTROLADORPANELHERRAMIENTAS_H_
#define CONTROLADORPANELHERRAMIENTAS_H_

#include <gtkmm.h>
#include "../vista/VistaDiagrama.h"
#include "../vista/VistaProyecto.h"
#include "ComponentsBuilder.h"
#include "AsistenteEntGlobal.h"

class ControladorPanelHerramientas {
private:
	Gtk::Window * ventanaPrincipal;
	Glib::RefPtr<Gtk::Builder> m_builder;

	Gtk::ToolButton * botonAgregarDiagrama;
	Gtk::ToolButton * botonEliminarDiagrama;

	Gtk::ToolButton * botonAgregarEntidad;
	Gtk::ToolButton * botonAgregarRelacion;
	Gtk::ToolButton * botonAgregarJerarquia;
	Gtk::ToolButton * botonAgregarEntidadGlobal;

	Gtk::ToolButton * botonAumentarZoom;
	Gtk::ToolButton * botonReducirZoom;
	Gtk::ToolButton * botonRestablecerZoom;

	void on_boton_Agregar_Diagrama_click();
	void on_boton_Eliminar_Diagrama_click();
	void on_boton_Agregar_Diagrama_ok(Gtk::Dialog *);
	void on_boton_Agregar_Diagrama_Cancel(Gtk::Dialog *);

	void on_boton_Agregar_Entidad_click();
	void on_boton_Agregar_Relacion_click();
	void on_boton_Agregar_Jerarquia_click();
	void on_boton_Agregar_Union_click();
	void on_boton_Agregar_EntidadGlobal_click();
	void on_boton_Agregar_Comentario_click();

	void on_boton_Aumentar_Zoom_click();
	void on_boton_Reducir_Zoom_click();
	void on_boton_Restablecer_Zoom_click();



	void enlazar_botones_de_menu(const Glib::RefPtr<Gtk::Builder>& builder);
public:
	ControladorPanelHerramientas(const Glib::RefPtr<Gtk::Builder>& builder, Gtk::Window * ventana);
	virtual ~ControladorPanelHerramientas();
	void activarBotones();
	void desactivarBotones();
};

#endif /* CONTROLADORPANELHERRAMIENTAS_H_ */
