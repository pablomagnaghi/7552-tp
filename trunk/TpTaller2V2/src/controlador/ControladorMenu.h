#ifndef CONTROLADORMENU_H_
#define CONTROLADORMENU_H_

#include "../vista/Ide.h"
#include "gtkmm.h"

class ControladorMenu {
private:
	Ide * editor;
	Gtk::MenuItem * botonArchivoNuevo;
	Gtk::MenuItem * botonArchivoAbrir;
	Gtk::MenuItem * botonArchivoGuardar;
	Gtk::MenuItem * botonArchivoGuardarComo;
	Gtk::MenuItem * botonArchivoImprimir;
	Gtk::MenuItem * botonArchivoExportar;
	Gtk::MenuItem * botonArchivoSalir;

	Gtk::MenuItem * botonEditarCopiar;
	Gtk::MenuItem * botonEditarCortar;
	Gtk::MenuItem * botonEditarPegar;

	Gtk::MenuItem * botonVerZoomMas;
	Gtk::MenuItem * botonVerZoomMenos;

	Gtk::MenuItem * botonAyudaAcercaDe;

	void on_menu_Archivo_Nuevo_click();
	void on_menu_Archivo_Abrir_click();
	void on_menu_Archivo_Guardar_click();
	void on_menu_Archivo_GuardarComo_click();
	void on_menu_Archivo_Imprimir_click();
	void on_menu_Archivo_Exportar_click();
	void on_menu_Archivo_Cerrar_click();
	void on_menu_Archivo_Salir_click();

	void on_menu_Editar_Copiar_click();
	void on_menu_Editar_Cortar_click();
	void on_menu_Editar_Pegar_click();

	void on_menu_Ver_Zoom_Mas_click();
	void on_menu_Ver_Zoom_Menos_click();

	void on_menu_Ayuda_AcercaDe_click();

	void enlazar_botones_de_menu(const Glib::RefPtr<Gtk::Builder>& builder);
public:
	ControladorMenu(const Glib::RefPtr<Gtk::Builder>& builder);
	virtual ~ControladorMenu();

	void setIde(Ide * editor);
};

#endif /* CONTROLADORMENU_H_ */
