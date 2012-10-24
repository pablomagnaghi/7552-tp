#include "VistaIdentificador.h"

#include <iostream>
using namespace std;

VistaIdentificador::VistaIdentificador(Identificador * id) {
	// TODO Auto-generated constructor stub
	//this->atributo = atributoModelo;
	this->identificador = id;
	this->prop_lanzada = false;
}

VistaIdentificador::~VistaIdentificador() {
	// TODO Auto-generated destructor stub
}

bool VistaIdentificador::lanzarProp() {
	/*if (!this->prop_lanzada) {
	 AsistenteAtributo* nuevaProp;
	 Glib::RefPtr<Gtk::Builder> nHbuilder = Gtk::Builder::create_from_file(ARCH_GLADE_ATRIB);
	 nHbuilder->get_widget_derived("PropAtributo", nuevaProp);
	 nuevaProp->setAtributo(this);
	 this->prop_lanzada = true;
	 nuevaProp->show();
	 return true;
	 }*/
	return false;
}

void VistaIdentificador::dibujar(Cairo::RefPtr<Cairo::Context> cr) {
	std::vector<VistaAtributo *>::iterator i;
	std::vector<VistaUnionEntidadRelacion *>::iterator j;
	cr->set_line_width(1);
	if (!this->seleccionado) {
		cr->set_source_rgb(colorNegro.get_red_p(), colorNegro.get_green_p(),
				colorNegro.get_blue_p());
	} else {
		cr->set_source_rgb(colorDeSeleccion.get_red_p(), colorDeSeleccion.get_green_p(),
				colorDeSeleccion.get_blue_p());
	}

	double x0, x1, y0, y1;

	if (this->vistasAtributo.size() == 1) {
		if (this->vistasEntidadesFuertes.empty()) {
			this->vistasAtributo[0]->setEsIdentificador(true);
			this->vistasAtributo[0]->dibujar(cr);
		} else {
			this->vistasAtributo[0]->getPuntoMedioLinea(x0, y0);
			cr->arc(x0, y0, RADIO_CIRCULOS_REDIMENSION, 0, 2 * M_PI);
			cr->fill();
			cr->move_to(x0, y0);
			for (j = this->vistasEntidadesFuertes.begin(); j != this->vistasEntidadesFuertes.end(); j++) {
				(*j)->getPuntoMedioLinea(x1, y1);
				cr->line_to(x1, y1);
				cr->stroke();
				cr->arc(x1, y1, RADIO_CIRCULOS_REDIMENSION, 0, 2 * M_PI);
				cr->fill();
				cr->move_to(x0, y0);
			}
			cr->stroke();
		}
	} else {
		this->vistasAtributo[0]->getPuntoMedioLinea(x0, y0);
		cr->arc(x0, y0, RADIO_CIRCULOS_REDIMENSION, 0, 2 * M_PI);
		cr->fill();
		cr->move_to(x0, y0);

		for (i = (this->vistasAtributo.begin() + 1); i != this->vistasAtributo.end(); i++) {
			(*i)->getPuntoMedioLinea(x1, y1);
			cr->line_to(x1, y1);
			cr->stroke();
			cr->arc(x1, y1, RADIO_CIRCULOS_REDIMENSION, 0, 2 * M_PI);
			cr->fill();
			cr->move_to(x1, y1);
		}
		cr->stroke();
		if (!this->vistasEntidadesFuertes.empty()) {
			cr->move_to(x0, y0);
			for (j = this->vistasEntidadesFuertes.begin(); j != this->vistasEntidadesFuertes.end(); j++) {
				(*j)->getPuntoMedioLinea(x1, y1);
				cr->line_to(x1, y1);
				cout << "X1=" << x1 << " Y1=" << y1 << endl;
				cr->stroke();
				cr->arc(x1, y1, RADIO_CIRCULOS_REDIMENSION, 0, 2 * M_PI);
				cr->fill();
				cr->move_to(x0, y0);
			}
			cr->stroke();
		}
	}

	/*if (this->vistaAtributos.empty()) {
	 double radio;
	 radio = 3;
	 centro_x = this->pos_ini_x + radio;
	 centro_y = this->pos_ini_y + radio;

	 this->pos_fin_x = centro_x + radio;
	 this->pos_fin_y = centro_y + radio;

	 //cr->move_to(centro_x, this->pos_ini_y);
	 cr->arc(centro_x, centro_y, radio, 0, 2 * M_PI);
	 // TODO if es parte de una clave candidata FILL
	 //cr->fill();
	 cr->stroke();
	 } else {
	 double delta_x, delta_y;
	 if (this->pos_fin_x < this->pos_ini_x || this->pos_fin_y < this->pos_ini_y) {
	 cr->get_text_extents(this->atributo->getNombre(), textExtents);
	 this->calcularDimensionesAPartirDeTexto(&textExtents);
	 }
	 // Dibujo una elipse
	 centro_x = (this->pos_ini_x + this->pos_fin_x) / 2;
	 centro_y = (this->pos_ini_y + this->pos_fin_y) / 2;
	 delta_x = centro_x - this->pos_ini_x;
	 delta_y = centro_y - this->pos_ini_y;

	 this->dibujarNombreCentrado(cr, this->atributo->getNombre());

	 cr->save();
	 cr->set_line_width(2 / MAX(delta_x, delta_y));// make (centro_x, centro_y) == (0, 0)
	 cr->translate(centro_x, centro_y);
	 cr->scale(delta_x, delta_y);
	 cr->arc(0.0, 0.0, 1.0, 0.0, 2 * M_PI);
	 cr->stroke();
	 cr->restore(); // back to opaque black
	 if (this->seleccionado) {
	 dibujarCirculosDeRedimension(cr);
	 }
	 }*/
}

void VistaIdentificador::agregarAtributo(VistaAtributo * vAtributo) {
	this->vistasAtributo.push_back(vAtributo);
}

std::vector<VistaAtributo*>::iterator VistaIdentificador::atributosBegin() {
	return this->vistasAtributo.begin();
}

std::vector<VistaAtributo*>::iterator VistaIdentificador::atributosEnd() {
	return this->vistasAtributo.end();
}

void VistaIdentificador::agregarEntidadFuerte(VistaUnionEntidadRelacion * vUnionEntidad) {
	this->vistasEntidadesFuertes.push_back(vUnionEntidad);
}

std::vector<VistaUnionEntidadRelacion*>::iterator VistaIdentificador::entidadesFuertesBegin() {
	return this->vistasEntidadesFuertes.begin();
}

std::vector<VistaUnionEntidadRelacion*>::iterator VistaIdentificador::entidadesFuertesEnd() {
	return this->vistasEntidadesFuertes.end();
}

bool VistaIdentificador::esSeleccionado(double x, double y) {
	return false;
}

void VistaIdentificador::finSeleccionado(double x, double y) {

}

bool VistaIdentificador::contieneAEstePunto(double x, double y) {
	/*double limiteX1, limiteX4;
	 double limiteY1, limiteY4;
	 if (this->seleccionado) {
	 limiteX1 = this->pos_ini_x - RADIO_CIRCULOS_REDIMENSION - LONGITUD_LINEAS_REDIMENSION;
	 limiteX4 = this->pos_fin_x + RADIO_CIRCULOS_REDIMENSION + LONGITUD_LINEAS_REDIMENSION;
	 limiteY1 = this->pos_ini_y - RADIO_CIRCULOS_REDIMENSION - LONGITUD_LINEAS_REDIMENSION;
	 limiteY4 = this->pos_fin_y + RADIO_CIRCULOS_REDIMENSION + LONGITUD_LINEAS_REDIMENSION;
	 return Geometria::estaContenidoEnRectangulo(x, y, limiteX1, limiteY1, limiteX4, limiteY4);
	 }
	 return Geometria::estaContenidoEnRectangulo(x, y, this->pos_ini_x, this->pos_ini_y,
	 this->pos_fin_x, this->pos_fin_y);*/
	return false;
}

void VistaIdentificador::calcularDimensionesAPartirDeTexto(Cairo::TextExtents * textExtents) {
	/*double alto, ancho;
	 ancho = textExtents->width;
	 alto = textExtents->height;

	 this->pos_fin_x = this->pos_ini_x + ancho + 3 * ESPACIO_ENTRE_TEXTO_Y_BORDE;
	 this->pos_fin_y = this->pos_ini_y + alto + 3 * ESPACIO_ENTRE_TEXTO_Y_BORDE;
	 */
}

bool VistaIdentificador::esPuntoDeRedimension(double x, double y) {
	// Considero los circulos de las puntas como cuadrados para que sea mas facil la comparacion
	/*double limiteX1, limiteX2, limiteX3, limiteX4;
	 double limiteY1, limiteY2, limiteY3, limiteY4;
	 limiteX1 = this->pos_ini_x - RADIO_CIRCULOS_REDIMENSION - LONGITUD_LINEAS_REDIMENSION;
	 limiteX2 = this->pos_ini_x + RADIO_CIRCULOS_REDIMENSION + LONGITUD_LINEAS_REDIMENSION;
	 limiteX3 = this->pos_fin_x - RADIO_CIRCULOS_REDIMENSION - LONGITUD_LINEAS_REDIMENSION;
	 limiteX4 = this->pos_fin_x + RADIO_CIRCULOS_REDIMENSION + LONGITUD_LINEAS_REDIMENSION;
	 limiteY1 = this->pos_ini_y - RADIO_CIRCULOS_REDIMENSION - LONGITUD_LINEAS_REDIMENSION;
	 limiteY2 = this->pos_ini_y + RADIO_CIRCULOS_REDIMENSION + LONGITUD_LINEAS_REDIMENSION;
	 limiteY3 = this->pos_fin_y - RADIO_CIRCULOS_REDIMENSION - LONGITUD_LINEAS_REDIMENSION;
	 limiteY4 = this->pos_fin_y + RADIO_CIRCULOS_REDIMENSION + LONGITUD_LINEAS_REDIMENSION;

	 if (Geometria::estaContenidoEnRectangulo(x, y, limiteX1, limiteY1, limiteX2, limiteY2)) { // Circulo arriba a la izquierda
	 //cout << "arriba a la izquierda" << endl;
	 return true;
	 } else if (Geometria::estaContenidoEnRectangulo(x, y, limiteX1, limiteY3, limiteX2, limiteY4)) { // Circulo abajo a la izquierda
	 //cout << "abajo a la izquierda" << endl;
	 return true;
	 } else if (Geometria::estaContenidoEnRectangulo(x, y, limiteX3, limiteY1, limiteX4, limiteY2)) {// Circulo arriba a la derecha
	 //cout << "arriba a la derecha" << endl;
	 return true;
	 } else if (Geometria::estaContenidoEnRectangulo(x, y, limiteX3, limiteY3, limiteX4, limiteY4)) { // Circulo arriba a la derecha
	 //cout << "abajo a la derecha" << endl;
	 return true;
	 }
	 */
	return false;
}

void VistaIdentificador::setMouseArriba(double x, double y) {
	/*double limiteX1, limiteX2, limiteX3, limiteX4;
	 double limiteY1, limiteY2, limiteY3, limiteY4;
	 limiteX1 = this->pos_ini_x - RADIO_CIRCULOS_REDIMENSION - LONGITUD_LINEAS_REDIMENSION;
	 limiteX2 = this->pos_ini_x + RADIO_CIRCULOS_REDIMENSION + LONGITUD_LINEAS_REDIMENSION;
	 limiteX3 = this->pos_fin_x - RADIO_CIRCULOS_REDIMENSION - LONGITUD_LINEAS_REDIMENSION;
	 limiteX4 = this->pos_fin_x + RADIO_CIRCULOS_REDIMENSION + LONGITUD_LINEAS_REDIMENSION;
	 limiteY1 = this->pos_ini_y - RADIO_CIRCULOS_REDIMENSION - LONGITUD_LINEAS_REDIMENSION;
	 limiteY2 = this->pos_ini_y + RADIO_CIRCULOS_REDIMENSION + LONGITUD_LINEAS_REDIMENSION;
	 limiteY3 = this->pos_fin_y - RADIO_CIRCULOS_REDIMENSION - LONGITUD_LINEAS_REDIMENSION;
	 limiteY4 = this->pos_fin_y + RADIO_CIRCULOS_REDIMENSION + LONGITUD_LINEAS_REDIMENSION;

	 if (Geometria::estaContenidoEnRectangulo(x, y, limiteX1, limiteY1, limiteX2, limiteY2)) { // Circulo arriba a la izquierda
	 this->mouseArribaDePuntoDeRedimension = 1;
	 } else if (Geometria::estaContenidoEnRectangulo(x, y, limiteX1, limiteY3, limiteX2, limiteY4)) { // Circulo abajo a la izquierda
	 this->mouseArribaDePuntoDeRedimension = 2;
	 } else if (Geometria::estaContenidoEnRectangulo(x, y, limiteX3, limiteY1, limiteX4, limiteY2)) {// Circulo arriba a la derecha
	 this->mouseArribaDePuntoDeRedimension = 3;
	 } else if (Geometria::estaContenidoEnRectangulo(x, y, limiteX3, limiteY3, limiteX4, limiteY4)) { // Circulo arriba a la derecha
	 this->mouseArribaDePuntoDeRedimension = 4;
	 } else {
	 this->mouseArribaDePuntoDeRedimension = 0;
	 }*/
}

void VistaIdentificador::redimensionar(double x, double y) {
	/*if (this->seleccionado) {
	 cout << "Elemento Redimensionado " << this->mouseArribaDePuntoDeRedimension << endl;
	 switch (this->mouseArribaDePuntoDeRedimension) {
	 case 1:
	 if (x < this->pos_fin_x && y < this->pos_fin_y) {
	 this->pos_ini_x = x;
	 this->pos_ini_y = y;
	 }
	 break;
	 case 2:
	 if (x < this->pos_fin_x && y > this->pos_ini_y) {
	 this->pos_ini_x = x;
	 this->pos_fin_y = y;
	 }
	 break;
	 case 3:
	 if (x > this->pos_ini_x && y < this->pos_fin_y) {
	 this->pos_fin_x = x;
	 this->pos_ini_y = y;
	 }
	 break;
	 case 4:
	 if (x > this->pos_ini_x && y > this->pos_ini_y) {
	 this->pos_fin_x = x;
	 this->pos_fin_y = y;
	 }
	 break;
	 }
	 }*/
}

std::string VistaIdentificador::getNombre() const {
	std::string nombre("Identificador");

	return nombre;
}

bool VistaIdentificador::contieneEsteComponente(Componente * c) {
	return (void *) this->identificador == (void *) c;
}

bool VistaIdentificador::obtenerInterseccionConLinea(double pos_ini_x, double pos_ini_y,
		double pos_fin_x, double pos_fin_y, double & x, double & y) {
	//double xInterseccion, yInterseccion;
	//double radio;
	double centro_x, centro_y;

	centro_x = (this->pos_fin_x + this->pos_ini_x) / 2;
	centro_y = (this->pos_fin_y + this->pos_ini_y) / 2;

	/*if (this->vistaAtributos.empty()) {

	 radio = this->pos_fin_x - centro_x;

	 if (Geometria::hayInterseccionDeLineaConCirculo(pos_ini_x, pos_ini_y, pos_fin_x, pos_fin_y,
	 centro_x, centro_y, radio, xInterseccion, yInterseccion)) {
	 x = xInterseccion;
	 y = yInterseccion;
	 return true;
	 }
	 } else {
	 double delta_x, delta_y;
	 // Dibujo una elipse
	 delta_x = centro_x - this->pos_ini_x;
	 delta_y = centro_y - this->pos_ini_y;

	 if (Geometria::hayInterseccionDeLineaConElipse(pos_ini_x, pos_ini_y, pos_fin_x, pos_fin_y,
	 centro_x, centro_y, delta_x, delta_y, xInterseccion, yInterseccion)) {
	 x = xInterseccion;
	 y = yInterseccion;
	 return true;
	 }

	 }*/

	return false;
}

void VistaIdentificador::resetearLanzarProp() {
	this->prop_lanzada = false;
}

void VistaIdentificador::dibujarCirculosDeRedimension(Cairo::RefPtr<Cairo::Context> cr) {
	/*cr->set_line_width(2);
	 //  Dibujo los circulos en las puntas
	 cr->set_source_rgb(colorBlanco.get_red_p(), colorBlanco.get_green_p(), colorBlanco.get_blue_p());
	 cr->set_line_width(1);
	 cr->arc(this->pos_ini_x, this->pos_ini_y, RADIO_CIRCULOS_REDIMENSION, 0, 2 * M_PI);
	 cr->move_to(this->pos_ini_x + RADIO_CIRCULOS_REDIMENSION, this->pos_fin_y);
	 cr->arc(this->pos_ini_x, this->pos_fin_y, RADIO_CIRCULOS_REDIMENSION, 0, 2 * M_PI);
	 cr->move_to(this->pos_fin_x + RADIO_CIRCULOS_REDIMENSION, this->pos_ini_y);
	 cr->arc(this->pos_fin_x, this->pos_ini_y, RADIO_CIRCULOS_REDIMENSION, 0, 2 * M_PI);
	 cr->move_to(this->pos_fin_x + RADIO_CIRCULOS_REDIMENSION, this->pos_fin_y);
	 cr->arc(this->pos_fin_x, this->pos_fin_y, RADIO_CIRCULOS_REDIMENSION, 0, 2 * M_PI);
	 cr->fill();
	 cr->set_source_rgb(colorDeSeleccion.get_red_p(), colorDeSeleccion.get_green_p(),
	 colorDeSeleccion.get_blue_p());
	 cr->arc(this->pos_ini_x, this->pos_ini_y, RADIO_CIRCULOS_REDIMENSION, 0, 2 * M_PI);
	 cr->move_to(this->pos_ini_x + RADIO_CIRCULOS_REDIMENSION, this->pos_fin_y);
	 cr->arc(this->pos_ini_x, this->pos_fin_y, RADIO_CIRCULOS_REDIMENSION, 0, 2 * M_PI);
	 cr->move_to(this->pos_fin_x + RADIO_CIRCULOS_REDIMENSION, this->pos_ini_y);
	 cr->arc(this->pos_fin_x, this->pos_ini_y, RADIO_CIRCULOS_REDIMENSION, 0, 2 * M_PI);
	 cr->move_to(this->pos_fin_x + RADIO_CIRCULOS_REDIMENSION, this->pos_fin_y);
	 cr->arc(this->pos_fin_x, this->pos_fin_y, RADIO_CIRCULOS_REDIMENSION, 0, 2 * M_PI);
	 cr->stroke();
	 switch (this->mouseArribaDePuntoDeRedimension) {
	 case 1:
	 cr->arc(this->pos_ini_x, this->pos_ini_y, RADIO_CIRCULOS_REDIMENSION, 0, 2 * M_PI);
	 cr->fill();
	 break;
	 case 2:
	 cr->arc(this->pos_ini_x, this->pos_fin_y, RADIO_CIRCULOS_REDIMENSION, 0, 2 * M_PI);
	 cr->fill();
	 break;
	 case 3:
	 cr->arc(this->pos_fin_x, this->pos_ini_y, RADIO_CIRCULOS_REDIMENSION, 0, 2 * M_PI);
	 cr->fill();
	 break;
	 case 4:
	 cr->arc(this->pos_fin_x, this->pos_fin_y, RADIO_CIRCULOS_REDIMENSION, 0, 2 * M_PI);
	 cr->fill();
	 break;
	 }*/
}
