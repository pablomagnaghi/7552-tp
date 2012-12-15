#include "VistaRelacion.h"


#include <iostream>
using namespace std;

VistaRelacion::VistaRelacion(Relacion * relacionModelo) {
	this->relacion = relacionModelo;

	// Persistencia REP
	this->codigoREP = relacionModelo->getCodigo();
	this->prop_lanzada = false;
}

VistaRelacion::~VistaRelacion() {
	// TODO Auto-generated destructor stub
	if(this->eliminarModelo){
		delete this->relacion;
	}
}

bool VistaRelacion::lanzarProp() {
	if (!this->prop_lanzada) {
		AsistenteRelacion* nuevaProp;
		Glib::RefPtr<Gtk::Builder> nHbuilder = Gtk::Builder::create_from_file(ARCH_GLADE_RELAC);
		nHbuilder->get_widget_derived("PropRelacion", nuevaProp);
		nuevaProp->setRelacion(this);
		this->prop_lanzada = true;
		nuevaProp->show();
		return true;
	}
	return false;
}

void VistaRelacion::dibujar(Cairo::RefPtr<Cairo::Context> cr) {
	if (!this->seleccionado) {
		cr->set_source_rgb(colorNegro.get_red_p(), colorNegro.get_green_p(),
				colorNegro.get_blue_p());
	} else {
		cr->set_source_rgb(colorDeSeleccion.get_red_p(), colorDeSeleccion.get_green_p(),
				colorDeSeleccion.get_blue_p());
	}
	this->dibujarFiguraDeRelacion(cr);

	if (this->seleccionado) {
		dibujarCirculosDeRedimension(cr);
	}
}

void VistaRelacion::dibujarFiguraDeRelacion(Cairo::RefPtr<Cairo::Context> cr) {
	double mitad_x, mitad_y;
	Cairo::TextExtents textExtents;

	cr->set_line_width(2); // Ancho de linea arbitrario

	if (this->ajustarTamanioPorTexto) {
		cout << "Calculando Tamaño" << endl;
		cr->get_text_extents(this->relacion->getNombre(), textExtents);
		this->calcularDimensionesAPartirDeTexto(&textExtents);
		this->ajustarTamanioPorTexto = false;
	}

	mitad_x = (this->pos_fin_x + this->pos_ini_x) / 2;
	mitad_y = (this->pos_fin_y + this->pos_ini_y) / 2;

	this->dibujarNombreCentrado(cr, this->relacion->getNombre());

	cr->move_to(mitad_x, this->pos_ini_y);
	cr->line_to(this->pos_fin_x, mitad_y);
	cr->line_to(mitad_x, this->pos_fin_y);
	cr->line_to(this->pos_ini_x, mitad_y);
	cr->line_to(mitad_x, this->pos_ini_y);

	//cr->rectangle(this->pos_ini_x, this->pos_ini_y, this->pos_fin_x
	//	- this->pos_ini_x, this->pos_fin_y - this->pos_ini_y);
	cr->stroke();
}

void VistaRelacion::dibujarCirculosDeRedimension(Cairo::RefPtr<Cairo::Context> cr) {
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

bool VistaRelacion::contieneAEstePunto(double x, double y) {
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

void VistaRelacion::calcularDimensionesAPartirDeTexto(Cairo::TextExtents * textExtents) {
	double alto, ancho;
	ancho = textExtents->width;
	alto = textExtents->height;

	this->pos_fin_x = this->pos_ini_x + ancho + 7 * ESPACIO_ENTRE_TEXTO_Y_BORDE;
	this->pos_fin_y = this->pos_ini_y + alto + 7 * ESPACIO_ENTRE_TEXTO_Y_BORDE;

}

bool VistaRelacion::esPuntoDeRedimension(double x, double y) {
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

void VistaRelacion::setMouseArriba(double x, double y) {
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

void VistaRelacion::redimensionar(double x, double y) {
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

std::string VistaRelacion::getNombre() const {
	return this->relacion->getNombre();
}

void VistaRelacion::setNombre(const std::string & nombre) {
	this->relacion->setNombre(nombre);
}

std::vector<UnionEntidadRelacion *> VistaRelacion::getUniones() {
	std::vector<UnionEntidadRelacion *> uniones;
	std::vector<UnionEntidadRelacion *>::iterator i;

	for (i = this->relacion->unionesAEntidadBegin(); i != this->relacion->unionesAEntidadEnd();
			i++) {
		uniones.push_back(*i);
	}
	return uniones;
}

bool VistaRelacion::contieneEsteComponente(VistaComponente * c) {
	return false;
}

bool VistaRelacion::obtenerInterseccionConLinea(double pos_ini_x, double pos_ini_y,
		double pos_fin_x, double pos_fin_y, double & x, double & y) {
	double mitad_x, mitad_y;
	double xInterseccion, yInterseccion;

	mitad_x = (this->pos_fin_x + this->pos_ini_x) / 2;
	mitad_y = (this->pos_fin_y + this->pos_ini_y) / 2;

	if (Geometria::hayInterseccionDeLineas(pos_ini_x, pos_ini_y, pos_fin_x, pos_fin_y,
			this->pos_ini_x, mitad_y, mitad_x, this->pos_ini_y, xInterseccion, yInterseccion)) {
		x = xInterseccion;
		y = yInterseccion;
		return true;
	} else if (Geometria::hayInterseccionDeLineas(pos_ini_x, pos_ini_y, pos_fin_x, pos_fin_y,
			mitad_x, this->pos_ini_y, this->pos_fin_x, mitad_y, xInterseccion, yInterseccion)) {
		x = xInterseccion;
		y = yInterseccion;
		return true;
	} else if (Geometria::hayInterseccionDeLineas(pos_ini_x, pos_ini_y, pos_fin_x, pos_fin_y,
			this->pos_ini_x, mitad_y, mitad_x, this->pos_fin_y, xInterseccion, yInterseccion)) {
		x = xInterseccion;
		y = yInterseccion;
		return true;
	} else if (Geometria::hayInterseccionDeLineas(pos_ini_x, pos_ini_y, pos_fin_x, pos_fin_y,
			mitad_x, this->pos_fin_y, this->pos_fin_x, mitad_y, xInterseccion, yInterseccion)) {
		x = xInterseccion;
		y = yInterseccion;
		return true;
	}
	return false;
}

Relacion * VistaRelacion::getRelacion() {
	return this->relacion;
}

bool VistaRelacion::agregarAtributo(VistaAtributo* atributo) {
	if (atributo == NULL) {
		return false;
	}
	this->vistaAtributos.push_back(atributo);
	return true;
}

bool VistaRelacion::agregarUnion(VistaUnionEntidadRelacion* vuer){
	if (vuer == NULL){
		return false;
	}
	this->vistaUniones.push_back(vuer);
	return true;
}

bool VistaRelacion::quitarAtributo(VistaAtributo* atributo) {
	if (atributo == NULL || this->eliminando) {
		return false;
	}
	std::vector<VistaAtributo *>::iterator it_atributos;
	it_atributos = find(this->vistaAtributos.begin(), this->vistaAtributos.end(), atributo);
	if (it_atributos != vistaAtributos.end()) {
		this->vistaAtributos.erase(it_atributos);
	}
	return true;
}

std::vector<VistaAtributo*>::iterator VistaRelacion::atributosBegin() {
	return this->vistaAtributos.begin();
}

std::vector<VistaAtributo*>::iterator VistaRelacion::atributosEnd() {
	return this->vistaAtributos.end();
}

std::vector<VistaUnionEntidadRelacion*>::iterator VistaRelacion::unionesBegin() {
	return this->vistaUniones.begin();
}

std::vector<VistaUnionEntidadRelacion*>::iterator VistaRelacion::unionesEnd() {
	return this->vistaUniones.end();
}

void VistaRelacion::eliminarComponentesAdyacentes(Diagrama * diagrama,
		std::vector<VistaComponente *> & componentes, VistaComponente * componenteEliminado) {
	std::vector<VistaAtributo *>::iterator it_atributo;
	this->eliminando = true;
	for (it_atributo = vistaAtributos.begin(); it_atributo != vistaAtributos.end(); ++it_atributo) {
		(*it_atributo)->eliminarComponentesAdyacentes(diagrama, componentes,componenteEliminado);
		componentes.push_back((*it_atributo));
		this->relacion->quitarAtributo((*it_atributo)->getAtributo());
		delete (*it_atributo);
	}
	diagrama->quitarComponente(this->relacion);
	this->eliminarModelo = true;
}

bool VistaRelacion::hayQueEliminarlo(){
	return this->eliminando;
}

void VistaRelacion::resetearLanzarProp() {
	this->prop_lanzada = false;
}

VistaUnionEntidadRelacion* VistaRelacion::unidaConEntidad(VistaEntidad *ve){
	//Verifico en cada union si alguna tiene esa entidad
	std::vector<VistaUnionEntidadRelacion*>::iterator it1 = this->unionesBegin();
	std::vector<VistaUnionEntidadRelacion*>::iterator it2 = this->unionesEnd();
	VistaUnionEntidadRelacion * v = NULL;
	while(it1 != it2){
		v = *it1;
		if (v->getEntidad() == ve){
			return v;
		}
		it1++;
	}
	return NULL;
}

