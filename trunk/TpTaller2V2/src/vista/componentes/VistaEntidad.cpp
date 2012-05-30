#include "VistaEntidad.h"

#include <iostream>
using namespace std;

VistaEntidad::VistaEntidad() {
	// TODO Auto-generated constructor stub
	this->esDebil = false;
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

	cr->rectangle(this->pos_ini_x + 2, this->pos_ini_y + 2, this->pos_fin_x
			- this->pos_ini_x - 4, this->pos_fin_y - this->pos_ini_y - 4);

	if (this->esDebil) {
		cr->set_line_width(1);
		cr->rectangle(this->pos_ini_x + 6, this->pos_ini_y + 6, this->pos_fin_x
				- this->pos_ini_x - 12, this->pos_fin_y - this->pos_ini_y - 12);
	}
	cr->stroke();

	if (this->seleccionado) {
		//  Dibujo los circulos en las puntas
		cr->set_source_rgb(colorBlanco.get_red_p(), colorBlanco.get_green_p(),
				colorBlanco.get_blue_p());
		cr->set_line_width(1);
		cr->arc(this->pos_ini_x + 2, this->pos_ini_y + 2, 3, 0, 2 * M_PI);
		cr->move_to(this->pos_ini_x + 4, this->pos_fin_y - 2);
		cr->arc(this->pos_ini_x + 2, this->pos_fin_y - 2, 3, 0, 2 * M_PI);
		cr->move_to(this->pos_fin_x, this->pos_ini_y + 2);
		cr->arc(this->pos_fin_x - 2, this->pos_ini_y + 2, 3, 0, 2 * M_PI);
		cr->move_to(this->pos_fin_x, this->pos_fin_y - 2);
		cr->arc(this->pos_fin_x - 2, this->pos_fin_y - 2, 3, 0, 2 * M_PI);
		cr->fill();
		cr->set_source_rgb(colorDeSeleccion.get_red_p(),
				colorDeSeleccion.get_green_p(), colorDeSeleccion.get_blue_p());
		cr->arc(this->pos_ini_x + 2, this->pos_ini_y + 2, 3, 0, 2 * M_PI);
		cr->move_to(this->pos_ini_x + 4, this->pos_fin_y - 2);
		cr->arc(this->pos_ini_x + 2, this->pos_fin_y - 2, 3, 0, 2 * M_PI);
		cr->move_to(this->pos_fin_x, this->pos_ini_y + 2);
		cr->arc(this->pos_fin_x - 2, this->pos_ini_y + 2, 3, 0, 2 * M_PI);
		cr->move_to(this->pos_fin_x, this->pos_fin_y - 2);
		cr->arc(this->pos_fin_x - 2, this->pos_fin_y - 2, 3, 0, 2 * M_PI);
		cr->stroke();
	}

}

bool VistaEntidad::esSeleccionado(double x, double y) {
	return false;
}

void VistaEntidad::finSeleccionado(double x, double y) {

}

bool VistaEntidad::contieneAEstePunto(double x, double y) {
	return Geometria::estaContenidoEnRectangulo(x, y, this->pos_ini_x,
			this->pos_ini_y, this->pos_fin_x, this->pos_fin_y);
}

void VistaEntidad::calcularDimensionesAPartirDeTexto(
		Cairo::TextExtents * textExtents) {

	double alto, ancho;
	ancho = textExtents->width;
	alto = textExtents->height;

	if (!this->esDebil) {
		this->pos_fin_x = this->pos_ini_x + ancho + 3
				* ESPACIO_ENTRE_TEXTO_Y_BORDE;
		this->pos_fin_y = this->pos_ini_y + alto + 3
				* ESPACIO_ENTRE_TEXTO_Y_BORDE;
	} else {
		this->pos_fin_x = this->pos_ini_x + ancho + 5
				* ESPACIO_ENTRE_TEXTO_Y_BORDE;
		this->pos_fin_y = this->pos_ini_y + alto + 4
				* ESPACIO_ENTRE_TEXTO_Y_BORDE;
	}

}

bool VistaEntidad::esPuntoDeRedimension(double x, double y) {
	// Considero los circulos de las puntas como cuadrados para que sea mas facil la comparacion

	if (Geometria::estaContenidoEnRectangulo(x, y, this->pos_ini_x,
			this->pos_ini_y, this->pos_ini_x + 4, this->pos_ini_y + 4)) {
		// Circulo arriba a la izquierda
		cout << "arriba a la izquierda" << endl;
		return true;
	} else if (Geometria::estaContenidoEnRectangulo(x, y, this->pos_ini_x,
			this->pos_fin_y - 4, this->pos_ini_x + 4, this->pos_fin_y)) {
		// Circulo abajo a la izquierda
		cout << "abajo a la izquierda" << endl;
		return true;
	} else if (Geometria::estaContenidoEnRectangulo(x, y, this->pos_fin_x - 4,
			this->pos_ini_y, this->pos_fin_x, this->pos_ini_y + 4)) {
		// Circulo arriba a la derecha
		cout << "arriba a la derecha" << endl;
		return true;
	} else if (Geometria::estaContenidoEnRectangulo(x, y, this->pos_fin_x - 4,
			this->pos_fin_y - 4, this->pos_fin_x, this->pos_fin_y)) {
		// Circulo arriba a la derecha
		cout << "abajo a la derecha" << endl;
		return true;
	}

	return false;
}

void VistaEntidad::setMouseArriba(double x, double y) {

}
