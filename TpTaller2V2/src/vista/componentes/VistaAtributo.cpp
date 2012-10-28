#include "VistaAtributo.h"

#include <iostream>
using namespace std;

VistaAtributo::VistaAtributo(Atributo * atributoModelo) {
	// TODO Auto-generated constructor stub
	this->atributo = atributoModelo;
	this->prop_lanzada = false;
	this->esIdentificador = false;
	this->dibujar_cardinalidad = true;
	// Persistencia REP
	this->codigoREP = atributoModelo->getCodigo();
}

VistaAtributo::~VistaAtributo() {
	// TODO Auto-generated destructor stub
}

bool VistaAtributo::lanzarProp() {
	if (!this->prop_lanzada) {
		AsistenteAtributo* nuevaProp;
		Glib::RefPtr<Gtk::Builder> nHbuilder = Gtk::Builder::create_from_file(ARCH_GLADE_ATRIB);
		nHbuilder->get_widget_derived("PropAtributo", nuevaProp);
		nuevaProp->setAtributo(this);
		this->prop_lanzada = true;
		nuevaProp->show();
		return true;
	}
	return false;
}

void VistaAtributo::actualizar_coordenadas() {
	double radio;
	double centro_x, centro_y;
	if (this->vistaAtributos.empty()) {
		radio = 3;
		centro_x = this->pos_ini_x + radio;
		centro_y = this->pos_ini_y + radio;

		this->pos_fin_x = centro_x + radio;
		this->pos_fin_y = centro_y + radio;
	}
}

void VistaAtributo::setposini(double x, double y) {
	this->pos_ini_x = x;
	this->pos_ini_y=y;
	this->actualizar_coordenadas();
}

void VistaAtributo::dibujar(Cairo::RefPtr<Cairo::Context> cr) {
	cr->set_line_width(1);
	Cairo::TextExtents textExtents;
	std::string texto(this->atributo->getNombre());
	if (this->dibujar_cardinalidad) {
		texto.append("(");
		texto.append(this->atributo->getCardinalidadMinima());
		texto.append(";");
		texto.append(this->atributo->getCardinalidadMaxima());
		texto.append(")");
	}
	cr->get_text_extents(texto, textExtents);

	if (!this->seleccionado) {
		cr->set_source_rgb(colorNegro.get_red_p(), colorNegro.get_green_p(),
				colorNegro.get_blue_p());
	} else {
		cr->set_source_rgb(colorDeSeleccion.get_red_p(), colorDeSeleccion.get_green_p(),
				colorDeSeleccion.get_blue_p());
	}

	double centro_x, centro_y;
	this->actualizar_coordenadas();

	if (this->vistaAtributos.empty()) {
		double radio;
		double x_texto, y_texto;
		radio = 3;
		centro_x = this->pos_ini_x + radio;
		centro_y = this->pos_ini_y + radio;



		cr->arc(centro_x, centro_y, radio, 0, 2 * M_PI);
		if (this->esIdentificador) {
			cr->fill();
		} else {
			cr->stroke();
		}

		//Dibujo el nombre
		double x0, y0, x1, y1;
		this->lineaConEntidad->actualizar_coordenadas();
		this->lineaConEntidad->getposini(x0, y0);
		this->lineaConEntidad->getposfin(x1, y1);
		cout << "X0=" << x0 << " Y0=" << y0 << " X1=" << x1 << " Y1=" << y1 << endl;
		if (x0 < this->pos_ini_x || x0 > this->pos_fin_x || y0 < this->pos_ini_y || y0
				> this->pos_fin_y) {
			Geometria::obtenerPuntoDeDibujoDeTextoOpuestoALinea(x1, y1, x0, y0, textExtents.width,
					textExtents.height, x_texto, y_texto);
		} else {
			Geometria::obtenerPuntoDeDibujoDeTextoOpuestoALinea(x0, y0, x1, y1, textExtents.width,
					textExtents.height, x_texto, y_texto);
		}
		cr->move_to(x_texto, y_texto);
		cr->show_text(texto);
		cr->stroke();

	} else {
		double delta_x, delta_y;
		if (this->pos_fin_x < this->pos_ini_x || this->pos_fin_y < this->pos_ini_y) {
			this->calcularDimensionesAPartirDeTexto(&textExtents);
		}
		// Dibujo una elipse
		centro_x = (this->pos_ini_x + this->pos_fin_x) / 2;
		centro_y = (this->pos_ini_y + this->pos_fin_y) / 2;
		delta_x = centro_x - this->pos_ini_x;
		delta_y = centro_y - this->pos_ini_y;

		cr->save();
		cr->set_line_width(2 / MAX(delta_x, delta_y));// make (centro_x, centro_y) == (0, 0)
		cr->translate(centro_x, centro_y);
		cr->scale(delta_x, delta_y);
		cr->arc(0.0, 0.0, 1.0, 0.0, 2 * M_PI);
		if (this->esIdentificador) {
			cr->fill();
		} else {
			cr->stroke();
		}
		cr->restore(); // back to opaque black

		if (this->seleccionado) {
			dibujarCirculosDeRedimension(cr);
		}
		if (this->esIdentificador) {
			cr->set_source_rgb(colorBlanco.get_red_p(), colorBlanco.get_green_p(),
					colorBlanco.get_blue_p());
		}

		this->dibujarNombreCentrado(cr, texto);

	}
}

bool VistaAtributo::contieneAEstePunto(double x, double y) {
	double limiteX1, limiteX4;
	double limiteY1, limiteY4;
	if (this->seleccionado) {
		limiteX1 = this->pos_ini_x - RADIO_CIRCULOS_REDIMENSION - LONGITUD_LINEAS_REDIMENSION;
		limiteX4 = this->pos_fin_x + RADIO_CIRCULOS_REDIMENSION + LONGITUD_LINEAS_REDIMENSION;
		limiteY1 = this->pos_ini_y - RADIO_CIRCULOS_REDIMENSION - LONGITUD_LINEAS_REDIMENSION;
		limiteY4 = this->pos_fin_y + RADIO_CIRCULOS_REDIMENSION + LONGITUD_LINEAS_REDIMENSION;
		return Geometria::estaContenidoEnRectangulo(x, y, limiteX1, limiteY1, limiteX4, limiteY4);
	}
	return Geometria::estaContenidoEnRectangulo(x, y, this->pos_ini_x, this->pos_ini_y,
			this->pos_fin_x, this->pos_fin_y);
}

void VistaAtributo::calcularDimensionesAPartirDeTexto(Cairo::TextExtents * textExtents) {
	double alto, ancho;
	ancho = textExtents->width;
	alto = textExtents->height;

	this->pos_fin_x = this->pos_ini_x + ancho + 3 * ESPACIO_ENTRE_TEXTO_Y_BORDE;
	this->pos_fin_y = this->pos_ini_y + alto + 3 * ESPACIO_ENTRE_TEXTO_Y_BORDE;

}

bool VistaAtributo::esPuntoDeRedimension(double x, double y) {

	if (this->vistaAtributos.empty()) {
		return false;
	}
	// Considero los circulos de las puntas como cuadrados para que sea mas facil la comparacion
	double limiteX1, limiteX2, limiteX3, limiteX4;
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

	return false;
}

void VistaAtributo::setMouseArriba(double x, double y) {
	double limiteX1, limiteX2, limiteX3, limiteX4;
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
	}
}

void VistaAtributo::redimensionar(double x, double y) {
	if (this->seleccionado) {
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
	}
}

std::string VistaAtributo::getNombre() const {
	return this->atributo->getNombre();
}

bool VistaAtributo::contieneEsteComponente(Componente * c) {
	return this->atributo == c;
}

bool VistaAtributo::obtenerInterseccionConLinea(double pos_ini_x, double pos_ini_y,
		double pos_fin_x, double pos_fin_y, double & x, double & y) {
	double xInterseccion, yInterseccion;
	double centro_x, centro_y, radio;

	centro_x = (this->pos_fin_x + this->pos_ini_x) / 2;
	centro_y = (this->pos_fin_y + this->pos_ini_y) / 2;

	if (this->vistaAtributos.empty()) {

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

	}

	return false;
}

bool VistaAtributo::agregarAtributo(VistaAtributo* atributo) {
	if (atributo == NULL) {
		return false;
	}
	// Para que se recalcule el tamaño
	if(this->vistaAtributos.empty()){
		this->pos_fin_y = 0;
		this->pos_fin_x = 0;
	}
	this->vistaAtributos.push_back(atributo);
	return true;
}

bool VistaAtributo::quitarAtributo(VistaAtributo* atributo) {
	if (atributo == NULL) {
		return false;
	}
	remove(this->vistaAtributos.begin(), this->vistaAtributos.end(), atributo);
	return true;
}

std::vector<VistaAtributo*>::iterator VistaAtributo::atributosBegin() {
	return this->vistaAtributos.begin();
}

std::vector<VistaAtributo*>::iterator VistaAtributo::atributosEnd() {
	return this->vistaAtributos.end();
}

Atributo* VistaAtributo::getAtributo() {
	return this->atributo;
}

void VistaAtributo::resetearLanzarProp() {
	this->prop_lanzada = false;
}

void VistaAtributo::dibujarCirculosDeRedimension(Cairo::RefPtr<Cairo::Context> cr) {
	cr->set_line_width(2);
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
	}
}

void VistaAtributo::setEsIdentificador(bool id) {
	this->esIdentificador = id;
}

void VistaAtributo::setLinea(VistaLinea * linea) {
	this->lineaConEntidad = linea;
}

void VistaAtributo::getPuntoMedioLinea(double &x, double &y) {
	double x0, y0, x1, y1;
	this->lineaConEntidad->getposini(x0, y0);
	this->lineaConEntidad->getposfin(x1, y1);
	x = (x0 + x1) / 2;
	y = (y0 + y1) / 2;
}

void VistaAtributo::setNombre(const std::string & nombre) {
	this->atributo->setNombre(nombre);
}
