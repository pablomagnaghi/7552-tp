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
	this->padre = NULL;
}

VistaAtributo::~VistaAtributo() {
	// TODO Auto-generated destructor stub
#if DEBUG_QUITAR==1
	std::cout << "delete Atributo(" << this->atributo->getNombre() << ")" << std::endl;
#endif
	if (this->eliminarModelo) {
		delete this->atributo;
	}
}

bool VistaAtributo::lanzarProp(bool esNuevo) {
	if (!this->prop_lanzada) {
		AsistenteAtributo* nuevaProp;
		Glib::RefPtr<Gtk::Builder> nHbuilder = Gtk::Builder::create_from_file(ARCH_GLADE_ATRIB);
		nHbuilder->get_widget_derived("PropAtributo", nuevaProp);
		nuevaProp->setAtributo(this);
		this->prop_lanzada = true;
		try {
			nuevaProp->show();
		} catch (int e) {
			cout << "ERROR" << endl;
		}
		return true;
	}
	return false;
}

void VistaAtributo::actualizar_coordenadas() {
	double radio;
	double centro_x, centro_y;
	if (this->atributosHijos.empty()) {
		radio = 3;
		centro_x = this->pos_ini_x + radio;
		centro_y = this->pos_ini_y + radio;

		this->pos_fin_x = centro_x + radio;
		this->pos_fin_y = centro_y + radio;
	}
}

void VistaAtributo::setposini(double x, double y) {
	this->pos_ini_x = x;
	this->pos_ini_y = y;
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

	if (this->atributosHijos.empty()) {
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
		this->linea->actualizar_coordenadas();
		this->linea->getposini(x0, y0);
		this->linea->getposfin(x1, y1);
#if DEBUG_DIBUJAR==1
		cout << "X0=" << x0 << " Y0=" << y0 << " X1=" << x1 << " Y1=" << y1 << endl;
#endif
		if (x0 < this->pos_ini_x || x0 > this->pos_fin_x || y0 < this->pos_ini_y
				|| y0 > this->pos_fin_y) {
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
		cerr << "llego5" << endl;
		cr->set_line_width(2 / MAX(delta_x, delta_y)); // make (centro_x, centro_y) == (0, 0)
		cerr << "llego6" << endl;
		cr->translate(centro_x, centro_y);
		cerr << "llego7" << endl;
		cerr << "delta (" << delta_x << ":" << delta_y << ")" << endl;
		if (delta_x == 0 || delta_y == 0) {
			delta_x = 2;
			delta_y = 1;
		}
		cr->scale(delta_x, delta_y);
		cerr << "llego8" << endl;
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

	if (this->atributosHijos.empty()) {
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
	} else if (Geometria::estaContenidoEnRectangulo(x, y, limiteX3, limiteY1, limiteX4, limiteY2)) { // Circulo arriba a la derecha
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
	} else if (Geometria::estaContenidoEnRectangulo(x, y, limiteX3, limiteY1, limiteX4, limiteY2)) { // Circulo arriba a la derecha
		this->mouseArribaDePuntoDeRedimension = 3;
	} else if (Geometria::estaContenidoEnRectangulo(x, y, limiteX3, limiteY3, limiteX4, limiteY4)) { // Circulo arriba a la derecha
		this->mouseArribaDePuntoDeRedimension = 4;
	} else {
		this->mouseArribaDePuntoDeRedimension = 0;
	}
}

void VistaAtributo::redimensionar(double x, double y) {
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

std::string VistaAtributo::getNombre() const {
	return this->atributo->getNombre();
}

bool VistaAtributo::esContenidoPorEsteComponente(VistaComponente * c) {
	if (static_cast<VistaEntidadNueva *>(this->padre) == static_cast<VistaEntidadNueva *>(c)) {
		return true;
	}
	return false;
}

bool VistaAtributo::obtenerInterseccionConLinea(double pos_ini_x, double pos_ini_y,
		double pos_fin_x, double pos_fin_y, double & x, double & y) {
	double xInterseccion, yInterseccion;
	double centro_x, centro_y, radio;

	centro_x = (this->pos_fin_x + this->pos_ini_x) / 2;
	centro_y = (this->pos_fin_y + this->pos_ini_y) / 2;

	if (this->atributosHijos.empty()) {

		radio = this->pos_fin_x - centro_x;

		if (Geometria::obtenerInterseccionDeLineaConCirculo(pos_ini_x, pos_ini_y, pos_fin_x, pos_fin_y,
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

		if(!Geometria::hayInterseccionDeLineaConElipse(pos_ini_x, pos_ini_y, pos_fin_x, pos_fin_y,
				centro_x, centro_y, delta_x, delta_y)){
			return false;
		}

		if (Geometria::obtenerInterseccionDeLineaConElipse(pos_ini_x, pos_ini_y, pos_fin_x, pos_fin_y,
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
	if (this->atributosHijos.empty()) {
		this->pos_fin_y = 0;
		this->pos_fin_x = 0;
	}
	this->atributosHijos.push_back(atributo);
	return true;
}

bool VistaAtributo::quitarAtributo(VistaAtributo* atributo) {
	if (atributo == NULL || this->eliminando) {
		return false;
	}
	std::vector<VistaAtributo *>::iterator it_atributo;

	it_atributo = find(atributosHijos.begin(), atributosHijos.end(), atributo);
	if (it_atributo != atributosHijos.end()) {
		atributosHijos.erase(it_atributo);
	}
	this->atributo->quitarAtributo(atributo->getAtributo());
	return true;
}

std::vector<VistaAtributo*>::iterator VistaAtributo::atributosBegin() {
	return this->atributosHijos.begin();
}

std::vector<VistaAtributo*>::iterator VistaAtributo::atributosEnd() {
	return this->atributosHijos.end();
}

Atributo* VistaAtributo::getAtributo() {
	return this->atributo;
}

void VistaAtributo::setPadre(InterfazRemoverAtributo * padre) {
	this->padre = padre;
}

void VistaAtributo::resetearLanzarProp() {
	this->prop_lanzada = false;
}

void VistaAtributo::dibujarCirculosDeRedimension(Cairo::RefPtr<Cairo::Context> cr) {
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

void VistaAtributo::setEsIdentificador(bool id) {
	this->esIdentificador = id;
}

void VistaAtributo::setLinea(VistaLinea * linea) {
	this->linea = linea;
}

void VistaAtributo::getPuntoMedioLinea(double &x, double &y) {
	double x0, y0, x1, y1;
	this->linea->getposini(x0, y0);
	this->linea->getposfin(x1, y1);
	x = (x0 + x1) / 2;
	y = (y0 + y1) / 2;
}

void VistaAtributo::setNombre(const std::string & nombre) {
	this->atributo->setNombre(nombre);
}

void VistaAtributo::eliminarComponentesAdyacentes(Diagrama * diagrama,
		std::vector<VistaComponente *> & componentes, VistaComponente * componenteEliminado) {
	std::vector<VistaAtributo*>::iterator i;

	if (this->eliminando) {
		return;
	}

	this->eliminando = true;
	for (i = this->atributosHijos.begin(); i != this->atributosHijos.end(); i++) {
#if DEBUG_QUITAR==1
		std::cout << "Atributo(" << this->atributo->getNombre() << "): Agrego Atributo "
				<< (*i)->getNombre() << " a componentes_a_eliminar" << std::endl;
#endif

		componentes.push_back((*i));
		(*i)->eliminarComponentesAdyacentes(diagrama, componentes, componenteEliminado);
		this->atributo->quitarAtributo((*i)->getAtributo());
		//delete (*i);
	}
	diagrama->quitarComponente(this->atributo);
	this->eliminarModelo = true;

#if DEBUG_QUITAR==1
	std::cout << "Atributo(" << this->atributo->getNombre() << "): Agrego VistaLinea "
			<< " a componentes_a_eliminar" << std::endl;
#endif
	componentes.push_back(this->linea);
	this->padre->quitarAtributo(this);
}

bool VistaAtributo::hayQueEliminarlo() {
	return this->eliminando;
}


