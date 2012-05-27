#include "VistaEntidad.h"

#include <iostream>
using namespace std;

VistaEntidad::VistaEntidad() {
	// TODO Auto-generated constructor stub

}

VistaEntidad::~VistaEntidad() {
	// TODO Auto-generated destructor stub
}

void VistaEntidad::lanzarProp(GdkEventButton* event) {
	AsistenteEntidad* nuevaProp;
	Glib::RefPtr<Gtk::Builder> nHbuilder = Gtk::Builder::create_from_file(
			ARCH_GLADE_APENTIDAD);
	nHbuilder->get_widget_derived("PropEntidad", nuevaProp);
	nuevaProp->setEntidad(this);
}

void VistaEntidad::dibujar(Cairo::RefPtr<Cairo::Context> cr) {
	// Dibujo el cuadrado en el contexto
	// Ancho de linea arbitrario
	cr->set_line_width(2);
	double centro_x, centro_y;

	if (!this->seleccionado) {
		cr->set_source_rgb(colorNegro.get_red_p(), colorNegro.get_green_p(),
				colorNegro.get_blue_p());
	} else {
		cr->set_source_rgb(colorDeSeleccion.get_red_p(),
				colorDeSeleccion.get_green_p(), colorDeSeleccion.get_blue_p());
	}

	this->dibujarNombreCentrado(cr);

	//cr->set_source_rgba(0, 0, 0, 1); // negro

	//cr->move_to(this->pos_ini_x, this->pos_ini_y);
	//cr->line_to(this->pos_fin_x, this->pos_ini_y);
	//cr->line_to(this->pos_fin_x, this->pos_fin_y);
	//cr->line_to(this->pos_ini_x, this->pos_fin_y);
	//cr->line_to(this->pos_ini_x, this->pos_ini_y);

	cr->rectangle(this->pos_ini_x, this->pos_ini_y, this->pos_fin_x
			- this->pos_ini_x, this->pos_fin_y - this->pos_ini_y);

	cr->stroke();
}

bool VistaEntidad::esSeleccionado(double x, double y) {
	return false;
}

void VistaEntidad::finSeleccionado(double x, double y) {

}

bool VistaEntidad::contieneAEstePunto(double x, double y) {
	if (x > this->pos_ini_x && x < this->pos_fin_x) {
		if (y > this->pos_ini_y && y < this->pos_fin_y) {
			return true;
		}
	}
	return false;
}

