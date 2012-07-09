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

void verificar(bool a, bool b) {
	if (a == b) {
		cout << "OK" << endl;
	} else {
		cout << "ERROR" << endl;
	}
}

int main(int argc, char *argv[]) {
	//test_modelo();
	aplicacion_principal(argc, argv);

	/*double x, y;
	if (Geometria::hayInterseccionDeLineas(0, 0, 100, 100, 0, 100, 10, 0, x, y)) {
		cout << "x= " << x << " y= " << y << endl;
	}
	if (Geometria::hayInterseccionDeLineas(0, 0, 100, 100, 0, 100, 100, 0, x, y)) {
		cout << "x= " << x << " y= " << y << endl;
	}
	if (Geometria::hayInterseccionDeLineas(0, 0, 100, 100, 0, 100, 100, 90, x, y)) {
		cout << "x= " << x << " y= " << y << endl;
	}
	if (Geometria::hayInterseccionDeLineas(0, 0, 100, 100, 0, 100, 45, 45, x, y)) {
		cout << "x= " << x << " y= " << y << endl;
	}
	if (Geometria::hayInterseccionDeLineas(0, 0, 100, 100, 0, 100, 45, 55, x, y)) {
		cout << "x= " << x << " y= " << y << endl;
	}
	if (Geometria::hayInterseccionDeLineas(0, 0, 100, 100, 10, 0, 100, 90, x, y)) {
		cout << "x= " << x << " y= " << y << endl;
	}*/
	return 0;
}

