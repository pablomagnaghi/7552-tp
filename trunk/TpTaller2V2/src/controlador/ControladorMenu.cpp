#include "ControladorMenu.h"

#ifdef DEBUG
#include <iostream>
using namespace std;
#endif
#include <gtkmm.h>
#include <memory>

#define GLIBMM_EXCEPTIONS_ENABLED

ControladorMenu::ControladorMenu(const Glib::RefPtr<Gtk::Builder> & builder) {
	this->editor = NULL;
	this->enlazar_botones_de_menu(builder);

	// Deshabilito los botones guardar, exportar, imprimir (Todavia no hay proyecto)
	this->botonArchivoGuardar->set_sensitive(false);
	this->botonArchivoGuardarComo->set_sensitive(false);
	this->botonArchivoImprimir->set_sensitive(false);
	this->botonArchivoExportar->set_sensitive(false);

	m_refPageSetup = Gtk::PageSetup::create();
	m_refSettings = Gtk::PrintSettings::create();
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
	builder->get_widget("MAConfigurarPagina", botonArchivoConfigurarPagina);
	botonArchivoConfigurarPagina->signal_activate().connect(
			sigc::mem_fun(*this, &ControladorMenu::on_menu_Archivo_Configurar_Pagina_click));
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

void ControladorMenu::on_menu_Archivo_Configurar_Pagina_click() {
	//Show the page setup dialog, asking it to start with the existing settings:
	Glib::RefPtr<Gtk::PageSetup> new_page_setup = Gtk::run_page_setup_dialog(*Ide::getInstance(),
			m_refPageSetup, m_refSettings);

	//Save the chosen page setup dialog for use when printing, previewing, or
	//showing the page setup dialog again:
	m_refPageSetup = new_page_setup;
}

void ControladorMenu::on_menu_Archivo_Imprimir_click() {
#ifdef DEBUG
	cout << "Menu Archivo Imprimir" << endl;
#endif
	Gtk::PrintOperationAction print_action;
	Glib::RefPtr<ImpresionDiagrama> print = ImpresionDiagrama::create();
	print->set_diagrama(*Ide::getInstance()->getDiagActual());
	print->set_track_print_status();
	print->set_default_page_setup(m_refPageSetup);
	print->set_print_settings(m_refSettings);

	print->signal_done().connect(
			sigc::bind(sigc::mem_fun(*this, &ControladorMenu::on_finalizacion_impresion), print));

	//print->run(Gtk::PRINT_OPERATION_ACTION_PREVIEW, *Ide::getInstance());

	print_action = Gtk::PRINT_OPERATION_ACTION_PREVIEW;

#ifdef GLIBMM_EXCEPTIONS_ENABLED
	try {
		Gtk::PrintOperationResult result = print->run(print_action /* print or preview */,
				*Ide::getInstance());
		if(result == Gtk::PRINT_OPERATION_RESULT_APPLY){
			std::cout << "Apply" << std::endl;
		} else if(result == Gtk::PRINT_OPERATION_RESULT_ERROR){
			std::cout << "Error" << std::endl;
		}
	} catch (const Gtk::PrintError& ex) {
		//See documentation for exact Gtk::PrintError error codes.
		std::cerr << "An error occurred while trying to run a print operation:" << ex.what()
				<< std::endl;
	}
#else
	std::auto_ptr<Glib::Error> ex;
	print->run(print_action /* print or preview */, Ide::getInstance(), ex);

	if (ex.get()) {
		std::cerr << "An error occurred while trying to run a print operation:" << ex->what()
		<< std::endl;
	}
#endif /* !GLIBMM_EXCEPTIONS_ENABLED */

}

void ControladorMenu::on_finalizacion_impresion(Gtk::PrintOperationResult result,
		const Glib::RefPtr<ImpresionDiagrama>& operation) {
	if (result == Gtk::PRINT_OPERATION_RESULT_ERROR) {
		Gtk::MessageDialog err_dialog(*Ide::getInstance(), "Error printing form", false,
				Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK, true);
		err_dialog.run();
	} else if (result == Gtk::PRINT_OPERATION_RESULT_APPLY) {
		//Update PrintSettings with the ones used in this PrintOperation:
		m_refSettings = operation->get_print_settings();
	}

	/*if (!operation->is_finished()) {
	 //We will connect to the status-changed signal to track status
	 //and update a status bar. In addition, you can, for example,
	 //keep a list of active print operations, or provide a progress dialog.
	 operation->signal_status_changed().connect(
	 sigc::bind(
	 sigc::mem_fun(*Ide::getInstance(), &PrintExampleWindow::on_printoperation_status_changed),
	 operation));
	 }*/
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
