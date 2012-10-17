#include "ControladorMenu.h"

#ifdef DEBUG
#include <iostream>
using namespace std;
#endif

ControladorMenu::ControladorMenu(const Glib::RefPtr<Gtk::Builder> & builder) {
	this->editor = NULL;
	this->enlazar_botones_de_menu(builder);

	// Deshabilito los botones guardar, exportar, imprimir (Todavia no hay proyecto)
	this->botonArchivoGuardar->set_sensitive(false);
	this->botonArchivoGuardarComo->set_sensitive(false);
	this->botonArchivoImprimir->set_sensitive(false);
	this->botonArchivoExportar->set_sensitive(false);
}

ControladorMenu::~ControladorMenu() {

}

void ControladorMenu::enlazar_botones_de_menu(const Glib::RefPtr<Gtk::Builder>& builder) {
	builder->get_widget("MANuevo", botonArchivoNuevo);
	botonArchivoNuevo->signal_activate().connect(
			sigc::mem_fun(*this, &ControladorMenu::on_menu_Archivo_Nuevo_click));
	builder->get_widget("MAAbrir", botonArchivoAbrir);
	botonArchivoAbrir->signal_activate().connect(
			sigc::mem_fun(*this, &ControladorMenu::on_menu_Archivo_Abrir_click));
	builder->get_widget("MAGuardar", botonArchivoGuardar);
	botonArchivoGuardar->signal_activate().connect(
			sigc::mem_fun(*this, &ControladorMenu::on_menu_Archivo_Guardar_click));
	builder->get_widget("MAGuardarComo", botonArchivoGuardarComo);
	botonArchivoGuardarComo->signal_activate().connect(
			sigc::mem_fun(*this, &ControladorMenu::on_menu_Archivo_GuardarComo_click));
	builder->get_widget("MAImprimir", botonArchivoImprimir);
	botonArchivoImprimir->signal_activate().connect(
			sigc::mem_fun(*this, &ControladorMenu::on_menu_Archivo_Imprimir_click));
	builder->get_widget("MAExportar", botonArchivoExportar);
	botonArchivoExportar->signal_activate().connect(
			sigc::mem_fun(*this, &ControladorMenu::on_menu_Archivo_Exportar_click));
	builder->get_widget("MACerrar", botonArchivoSalir);
	botonArchivoSalir->signal_activate().connect(
			sigc::mem_fun(*this, &ControladorMenu::on_menu_Archivo_Cerrar_click));
	builder->get_widget("MASalir", botonArchivoSalir);
	botonArchivoSalir->signal_activate().connect(
			sigc::mem_fun(*this, &ControladorMenu::on_menu_Archivo_Salir_click));

	builder->get_widget("MAyAcercaDe", botonAyudaAcercaDe);
	botonAyudaAcercaDe->signal_activate().connect(
			sigc::mem_fun(*this, &ControladorMenu::on_menu_Ayuda_AcercaDe_click));
}

void ControladorMenu::on_menu_Archivo_Nuevo_click() {

#ifdef DEBUG
	cout << "Menu Archivo Nuevo" << endl;
#endif

	if (this->editor->crearNuevoProyecto()) {

		//this->botonArchivoGuardar->set_sensitive(true);
		this->botonArchivoGuardarComo->set_sensitive(true);
		this->botonArchivoImprimir->set_sensitive(true);
		this->botonArchivoExportar->set_sensitive(true);
	}

}

void ControladorMenu::on_menu_Archivo_Abrir_click() {
#ifdef DEBUG
	cout << "Menu Archivo Abrir" << endl;
#endif

	if (this->editor->abrir_proyecto()) {
		this->botonArchivoGuardarComo->set_sensitive(true);
		this->botonArchivoImprimir->set_sensitive(true);
		this->botonArchivoExportar->set_sensitive(true);
	}
}

void ControladorMenu::on_menu_Archivo_Guardar_click() {
#ifdef DEBUG
	cout << "Menu Archivo Guardar" << endl;
#endif

	if (this->editor->guardar_proyecto(false)) {
		this->botonArchivoGuardar->set_sensitive(true);
	}
}

void ControladorMenu::on_menu_Archivo_GuardarComo_click() {
#ifdef DEBUG
	cout << "Menu Archivo Guardar Como" << endl;
#endif
	if (this->editor->guardar_proyecto(true)) {
		this->botonArchivoGuardar->set_sensitive(false);
	}
}

void ControladorMenu::on_menu_Archivo_Imprimir_click() {
#ifdef DEBUG
	cout << "Menu Archivo Imprimir" << endl;
#endif

}

void ControladorMenu::on_menu_Archivo_Exportar_click() {
#ifdef DEBUG
	cout << "Menu Archivo Exportar" << endl;
#endif

}

void ControladorMenu::on_menu_Archivo_Cerrar_click() {

	if (this->editor->cerrarProyecto()) {
		this->botonArchivoGuardar->set_sensitive(false);
		this->botonArchivoGuardarComo->set_sensitive(false);
		this->botonArchivoImprimir->set_sensitive(false);
		this->botonArchivoExportar->set_sensitive(false);
	}
#ifdef DEBUG
	cout << "Menu Archivo Cerrar" << endl;
#endif
}

void ControladorMenu::on_menu_Archivo_Salir_click() {
#ifdef DEBUG
	cout << "Menu Archivo Salir" << endl;
#endif

	this->editor->hide();

}

void ControladorMenu::on_menu_Editar_Copiar_click() {
#ifdef DEBUG
	cout << "Copiar" << endl;
#endif

}

void ControladorMenu::on_menu_Editar_Cortar_click() {
#ifdef DEBUG
	cout << "Cortar" << endl;
#endif

}

void ControladorMenu::on_menu_Editar_Pegar_click() {
#ifdef DEBUG
	cout << "Pegar" << endl;
#endif

}

void ControladorMenu::on_menu_Ver_Zoom_Mas_click() {
#ifdef DEBUG
	cout << "Zoom+" << endl;
#endif

}

void ControladorMenu::on_menu_Ver_Zoom_Menos_click() {
#ifdef DEBUG
	cout << "Zoom-" << endl;
#endif

}

void ControladorMenu::on_menu_Ayuda_AcercaDe_click() {
#ifdef DEBUG
	cout << "Ayuda" << endl;
#endif

}

void ControladorMenu::setIde(Ide * editor) {
	this->editor = editor;
}
