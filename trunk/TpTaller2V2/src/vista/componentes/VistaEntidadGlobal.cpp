#include "VistaEntidadGlobal.h"

VistaEntidadGlobal::VistaEntidadGlobal(EntidadGlobal * eg) {
	this->entidad = eg;

	// Persistencia REP
	this->codigoREP = eg->getCodigo();
}

VistaEntidadGlobal::~VistaEntidadGlobal() {

}

std::string VistaEntidadGlobal::getNombre() const {
	return this->entidad->getNombre();
}

void VistaEntidadGlobal::setNombre(const std::string & nombre) {
	this->entidad->setNombre(nombre);
}

bool VistaEntidadGlobal::contieneEsteComponente(VistaComponente * c) {
	return false;
}

bool VistaEntidadGlobal::lanzarProp() {
	return false;
}

void VistaEntidadGlobal::dibujar(Cairo::RefPtr<Cairo::Context> cr) {
	if (!this->seleccionado) {
		cr->set_source_rgb(colorVerde.get_red_p(), colorVerde.get_green_p(),
				colorVerde.get_blue_p());
	} else {
		cr->set_source_rgb(colorDeSeleccion.get_red_p(), colorDeSeleccion.get_green_p(),
				colorDeSeleccion.get_blue_p());
	}

	this->dibujarFiguraDeEntidad(cr);

	if (this->seleccionado) {
		dibujarCirculosDeRedimension(cr);
	}
}

void VistaEntidadGlobal::dibujarFiguraDeEntidad(Cairo::RefPtr<Cairo::Context> cr) {
	cr->set_line_width(2);
	Cairo::TextExtents textExtents;

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
		cr->rectangle(this->pos_ini_x + 4, this->pos_ini_y + 4,
				this->pos_fin_x - this->pos_ini_x - 8, this->pos_fin_y - this->pos_ini_y - 8);
	}
	cr->stroke();
}

void VistaEntidadGlobal::dibujarCirculosDeRedimension(Cairo::RefPtr<Cairo::Context> cr) {
	cr->set_line_width(2);
	//  Dibujo los circulos en las puntas
	cr->set_source_rgb(colorBlanco.get_red_p(), colorBlanco.get_green_p(),
			colorBlanco.get_blue_p());
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

bool VistaEntidadGlobal::contieneAEstePunto(double x, double y) {
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

void VistaEntidadGlobal::calcularDimensionesAPartirDeTexto(Cairo::TextExtents * textExtents) {
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

bool VistaEntidadGlobal::esPuntoDeRedimension(double x, double y) {
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
	} else if (Geometria::estaContenidoEnRectangulo(x, y, limiteX3, limiteY1, limiteX4, limiteY2)) { // Circulo arriba a la derecha
		//cout << "arriba a la derecha" << endl;
		return true;
	} else if (Geometria::estaContenidoEnRectangulo(x, y, limiteX3, limiteY3, limiteX4, limiteY4)) { // Circulo arriba a la derecha
		//cout << "abajo a la derecha" << endl;
		return true;
	}

	return false;
}

void VistaEntidadGlobal::setMouseArriba(double x, double y) {
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
	} else if (Geometria::estaContenidoEnRectangulo(x, y, limiteX3, limiteY1, limiteX4, limiteY2)) { // Circulo arriba a la derecha
		this->mouseArribaDePuntoDeRedimension = 3;
	} else if (Geometria::estaContenidoEnRectangulo(x, y, limiteX3, limiteY3, limiteX4, limiteY4)) { // Circulo arriba a la derecha
		this->mouseArribaDePuntoDeRedimension = 4;
	} else {
		this->mouseArribaDePuntoDeRedimension = 0;
	}

#if DEBUG_SELECCION==1
	cout << "Punto Seleccionado " << this->mouseArribaDePuntoDeRedimension << endl;

	if (this->seleccionado) {
		cout << "Dimensiones: (" << this->pos_fin_x - this->pos_ini_x << ";"
				<< this->pos_fin_y - this->pos_ini_y << ")" << endl;
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

void VistaEntidadGlobal::redimensionar(double x, double y) {
	if (this->seleccionado) {
#if DEBUG_REDIMENSION==1
		cout << "Elemento Redimensionado " << this->mouseArribaDePuntoDeRedimension << endl;
#endif
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

Entidad * VistaEntidadGlobal::getEntidad(){
	return this->entidad;
}

void VistaEntidadGlobal::eliminarComponentesAdyacentes(Diagrama * diagrama,std::vector<VistaComponente *> & componentes){

}
