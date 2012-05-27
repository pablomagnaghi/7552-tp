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
	Cairo::TextExtents textExtents;

	if (!this->seleccionado) {
		cr->set_source_rgb(colorNegro.get_red_p(), colorNegro.get_green_p(),
				colorNegro.get_blue_p());
	} else {
		cr->set_source_rgb(colorDeSeleccion.get_red_p(),
				colorDeSeleccion.get_green_p(), colorDeSeleccion.get_blue_p());
	}

	cr->get_text_extents(this->nombre, textExtents);

	this->calcularDimensionesAPartirDeTexto(&textExtents);

	this->dibujarNombreCentrado(cr, this->nombre);

	//cr->set_source_rgba(0, 0, 0, 1); // negro

	//cr->move_to(this->pos_ini_x, this->pos_ini_y);
	//cr->line_to(this->pos_fin_x, this->pos_ini_y);
	//cr->line_to(this->pos_fin_x, this->pos_fin_y);
	//cr->line_to(this->pos_ini_x, this->pos_fin_y);
	//cr->line_to(this->pos_ini_x, this->pos_ini_y);

	cr->rectangle(this->pos_ini_x, this->pos_ini_y, this->pos_fin_x
			- this->pos_ini_x, this->pos_fin_y - this->pos_ini_y);

	if (this->esDebil) {
		cr->set_line_width(1.1);
		cr->rectangle(this->pos_ini_x + 2.5, this->pos_ini_y + 2.5, this->pos_fin_x
				- this->pos_ini_x - 5, this->pos_fin_y - this->pos_ini_y - 5);
	}

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

void VistaEntidad::calcularDimensionesAPartirDeTexto(
		Cairo::TextExtents * textExtents) {

	double alto, ancho;
	ancho = textExtents->width;
	alto = textExtents->height;

	if (!this->esDebil) {
		this->pos_fin_x = this->pos_ini_x + ancho + 2
				* ESPACIO_ENTRE_TEXTO_Y_BORDE;
		this->pos_fin_y = this->pos_ini_y + alto + 2
				* ESPACIO_ENTRE_TEXTO_Y_BORDE;
	} else {
		this->pos_fin_x = this->pos_ini_x + ancho + 4
				* ESPACIO_ENTRE_TEXTO_Y_BORDE;
		this->pos_fin_y = this->pos_ini_y + alto + 3
				* ESPACIO_ENTRE_TEXTO_Y_BORDE;
	}

}

