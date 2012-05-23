/*
 * main.cpp
 *
 *  Created on: 22/10/2010
 *      Author: metal
 */

#include "vista/Ide.h"
#include "vista/VistaConstantes.h"
#include <iostream>

int main(int argc, char *argv[]) {
	Gtk::Main kit(argc, argv);
	Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create();
	try {
		builder->add_from_file(ARCH_GLADE_IDE);
	} catch (const Glib::FileError& ex) {
		std::cerr << "FileError: " << ex.what() << std::endl;
		return 1;
	} catch (const Gtk::BuilderError& ex) {
		std::cerr << "BuilderError: " << ex.what() << std::endl;
		return 1;
	}
	Ide* ide = 0;

	builder->get_widget_derived("IDE", ide);

	if (ide) {
		// Comienza el bucle de eventos
		Gtk::Main::run(*ide);
	}

	delete ide;

	return 0;
}
