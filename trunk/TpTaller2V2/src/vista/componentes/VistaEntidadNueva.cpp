#include "VistaEntidadNueva.h"

#include <iostream>
using namespace std;

VistaEntidadNueva::VistaEntidadNueva(Entidad * entidadDelModelo) {
	// TODO Auto-generated constructor stub

	this->entidad = entidadDelModelo;

	this->mouseArribaDePuntoDeRedimension = 0;
	this->pos_ini_x = 0;
	this->pos_fin_x = 0;
	this->pos_ini_y = 0;
	this->pos_fin_y = 0;
}

VistaEntidadNueva::~VistaEntidadNueva() {
	// TODO Auto-generated destructor stub
}

bool VistaEntidadNueva::lanzarProp() {
	AsistenteEntidad* nuevaProp;
	int result;

	nuevaProp = AsistenteEntidad::getInstance();
	nuevaProp->setEntidad(this);
	nuevaProp->show();
	nuevaProp->set_modal(true);

	// El N° de respuesta se define el glade, en el mismo boton
	result = nuevaProp->run();

#ifdef DEBUG
	cout << "Resultado Dialogo: " << result << endl;
#endif

	return result == 1;
}

void VistaEntidadNueva::dibujar(Cairo::RefPtr<Cairo::Context> cr) {
	if (!this->seleccionado) {
		cr->set_source_rgb(colorNegro.get_red_p(), colorNegro.get_green_p(),
				colorNegro.get_blue_p());
	} else {
		cr->set_source_rgb(colorDeSeleccion.get_red_p(), colorDeSeleccion.get_green_p(),
				colorDeSeleccion.get_blue_p());
	}

	this->dibujarFiguraDeEntidad(cr);

	if (this->seleccionado) {
		dibujarCirculosDeRedimension(cr);
	}
}

void VistaEntidadNueva::dibujarFiguraDeEntidad(Cairo::RefPtr<Cairo::Context> cr) {
	cr->set_line_width(2);
	Cairo::TextExtents textExtents;

	if (!this->seleccionado) {
		cr->set_source_rgb(colorNegro.get_red_p(), colorNegro.get_green_p(),
				colorNegro.get_blue_p());
	} else {
		cr->set_source_rgb(colorDeSeleccion.get_red_p(), colorDeSeleccion.get_green_p(),
				colorDeSeleccion.get_blue_p());
	}

	if (this->ajustarTamanioPorTexto) {
		cr->get_text_extents(this->entidad->getNombre(), textExtents);
		this->calcularDimensionesAPartirDeTexto(&textExtents);
		this->ajustarTamanioPorTexto = false;
	}

	this->dibujarNombreCentrado(cr, this->entidad->getNombre());

	cr->rectangle(this->pos_ini_x, this->pos_ini_y, this->pos_fin_x - this->pos_ini_x,
			this->pos_fin_y - this->pos_ini_y);

	if (this->entidad->getEsDebil()) {
		cr->set_line_width(1);
		cr->rectangle(this->pos_ini_x + 4, this->pos_ini_y + 4, this->pos_fin_x - this->pos_ini_x
				- 8, this->pos_fin_y - this->pos_ini_y - 8);
	}
	cr->stroke();
}

void VistaEntidadNueva::dibujarCirculosDeRedimension(Cairo::RefPtr<Cairo::Context> cr) {
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

bool VistaEntidadNueva::esSeleccionado(double x, double y) {
	return false;
}

void VistaEntidadNueva::finSeleccionado(double x, double y) {

}

bool VistaEntidadNueva::contieneAEstePunto(double x, double y) {
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

void VistaEntidadNueva::calcularDimensionesAPartirDeTexto(Cairo::TextExtents * textExtents) {

	double alto, ancho;
	ancho = textExtents->width;
	alto = textExtents->height;

	if (!this->entidad->getEsDebil()) {
		this->pos_fin_x = this->pos_ini_x + ancho + 3 * ESPACIO_ENTRE_TEXTO_Y_BORDE;
		this->pos_fin_y = this->pos_ini_y + alto + 3 * ESPACIO_ENTRE_TEXTO_Y_BORDE;
	} else {
		this->pos_fin_x = this->pos_ini_x + ancho + 5 * ESPACIO_ENTRE_TEXTO_Y_BORDE;
		this->pos_fin_y = this->pos_ini_y + alto + 4 * ESPACIO_ENTRE_TEXTO_Y_BORDE;
	}

}

bool VistaEntidadNueva::esPuntoDeRedimension(double x, double y) {
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

#ifdef DEBUG
	if (Geometria::estaContenidoEnRectangulo(x, y, limiteX1, limiteY1, limiteX2, limiteY2)) { // Circulo arriba a la izquierda
		cout << "arriba a la izquierda" << endl;
		return true;
	} else if (Geometria::estaContenidoEnRectangulo(x, y, limiteX1, limiteY3, limiteX2, limiteY4)) { // Circulo abajo a la izquierda
		cout << "abajo a la izquierda" << endl;
		return true;
	} else if (Geometria::estaContenidoEnRectangulo(x, y, limiteX3, limiteY1, limiteX4, limiteY2)) {// Circulo arriba a la derecha
		cout << "arriba a la derecha" << endl;
		return true;
	} else if (Geometria::estaContenidoEnRectangulo(x, y, limiteX3, limiteY3, limiteX4, limiteY4)) { // Circulo arriba a la derecha
		cout << "abajo a la derecha" << endl;
		return true;
	}

#endif

	return false;
}

void VistaEntidadNueva::setMouseArriba(double x, double y) {
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

#ifdef DEBUG
	cout << "Punto Seleccionado " << this->mouseArribaDePuntoDeRedimension << endl;

	if (this->seleccionado) {
		cout << "Dimensiones: (" << this->pos_fin_x - this->pos_ini_x << ";" << this->pos_fin_y
				- this->pos_ini_y << ")" << endl;
		cout << "Posicion: inicial=(" << this->pos_ini_x << ";" << this->pos_ini_y << ")  final=("
				<< this->pos_fin_x << ";" << this->pos_fin_y << ")" << endl;
		cout << "Circulo arriba izq: (" << limiteX1 << ";" << limiteY1 << ") (" << limiteX2 << ";"
				<< limiteY2 << ")" << endl;
		cout << "Circulo abajo izq: (" << limiteX1 << ";" << limiteY3 << ") (" << limiteX2 << ";"
				<< limiteY4 << ")" << endl;
		cout << "Circulo arriba der: (" << limiteX3 << ";" << limiteY1 << ") (" << limiteX4 << ";"
				<< limiteY2 << ")" << endl;
		cout << "Circulo abajo der: (" << limiteX3 << ";" << limiteY3 << ") (" << limiteX4 << ";"
				<< limiteY4 << ")" << endl;
	}
#endif
}

void VistaEntidadNueva::redimensionar(double x, double y) {
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

void VistaEntidadNueva::setNombre(const std::string & nombre) {
	this->entidad->setNombre(nombre);
}

void VistaEntidadNueva::setEsDebil(bool debil) {
	this->entidad->setEsDebil(debil);
}

std::string VistaEntidadNueva::getNombre() const {
	return this->entidad->getNombre();
}

bool VistaEntidadNueva::contieneEsteComponente(Componente * c) {
	return this->entidad == c;
}

bool VistaEntidadNueva::obtenerInterseccionColLinea(double pos_ini_x, double pos_ini_y,
		double pos_fin_x, double pos_fin_y, double & x, double & y) {
	double xInterseccion, yInterseccion;

	if (Geometria::hayInterseccionDeLineas(pos_ini_x, pos_ini_y, pos_fin_x, pos_fin_y,
			this->pos_ini_x, this->pos_ini_y, this->pos_fin_x, this->pos_ini_y, xInterseccion,
			yInterseccion)) {
		x = xInterseccion;
		y = yInterseccion;
		return true;
	} else if (Geometria::hayInterseccionDeLineas(pos_ini_x, pos_ini_y, pos_fin_x, pos_fin_y,
			this->pos_ini_x, this->pos_ini_y, this->pos_ini_x, this->pos_fin_y, xInterseccion,
			yInterseccion)) {
		x = xInterseccion;
		y = yInterseccion;
		return true;
	} else if (Geometria::hayInterseccionDeLineas(pos_ini_x, pos_ini_y, pos_fin_x, pos_fin_y,
			this->pos_fin_x, this->pos_ini_y, this->pos_fin_x, this->pos_fin_y, xInterseccion,
			yInterseccion)) {
		x = xInterseccion;
		y = yInterseccion;
		return true;
	} else if (Geometria::hayInterseccionDeLineas(pos_ini_x, pos_ini_y, pos_fin_x, pos_fin_y,
			this->pos_ini_x, this->pos_fin_y, this->pos_fin_x, this->pos_fin_y, xInterseccion,
			yInterseccion)) {
		x = xInterseccion;
		y = yInterseccion;
		return true;
	}

	return false;
}
