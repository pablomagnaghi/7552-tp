/*
 * main.cpp
 *
 *  Created on: 22/10/2010
 *      Author: metal
 */

#include "modelo/Ide.h"
#include <iostream>

int main(int argc, char *argv[]){
	Gtk::Main kit(argc, argv);
	Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create();
	  try
	  {
	    builder->add_from_file(ARCH_GLADE_DISENIADOR);
	  }
	  catch(const Glib::FileError& ex)
	  {
	    std::cerr << "FileError: " << ex.what() << std::endl;
	    return 1;
	  }
	  catch(const Gtk::BuilderError& ex)
	  {
	    std::cerr << "BuilderError: " << ex.what() << std::endl;
	    return 1;
	  }
	  Ide* ide = 0;

	  builder->get_widget_derived("IDE", ide);

	  if(ide)
	  {
	    //Start:
		  Gtk::Main::run(*ide);
	  }

	  delete diseniador;

	  return 0;
}
