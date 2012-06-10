/*
 * main.cpp
 *
 *  Created on: 22/10/2010
 *      Author: metal
 */

#include "vista/Ide.h"
#include "controlador/ControladorMenu.h"
#include "vista/VistaConstantes.h"
#include <iostream>

#include "modelo/Modelo.h"

int aplicacion_principal(int argc, char *argv[]) {
	Gtk::Main kit(argc, argv);
	Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create();

#ifdef DEBUG
	cout << "Inicio" << endl;
#endif
	try {
		builder->add_from_file(ARCH_GLADE_IDE);
#ifdef DEBUG
	cout << "Archivo Glade Cargado" << endl;
#endif
	} catch (const Glib::FileError& ex) {
		std::cerr << "FileError: " << ex.what() << std::endl;
		return 1;
	} catch (const Gtk::BuilderError& ex) {
		std::cerr << "BuilderError: " << ex.what() << std::endl;
		return 1;
	}
	Ide* ide = 0;
	ControladorMenu * menu;

	builder->get_widget_derived("IDE", ide);

#ifdef DEBUG
	cout << "IDE Construido" << endl;
#endif
	menu = new ControladorMenu(builder);
	menu->setIde(ide);

	if (ide) {
		//Start:
		Gtk::Main::run(*ide);
	}

	delete ide;

	return 0;
}

int main(int argc, char *argv[]) {
	//test_modelo();
	aplicacion_principal(argc, argv);
	return 0;
}
