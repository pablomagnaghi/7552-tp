/*
 * Componente.cpp
 *
 *  Created on: 02/04/2012
 *      Author: Guagnini Enzo 88325
 */

#include "VistaComponente.h"

VistaComponente::VistaComponente() {
	this->setposfin(0, 0);
	this->setposini(0, 0);
	this->pos_selec_x = 0;
	this->pos_selec_y = 0;
	this->m_pMenuPopup = 0;

	this->colorNegro.set_rgb_p(0, 0, 0);
	//this->colorDeSeleccion.set_rgb(135,225,255);
	this->colorDeSeleccion.set_rgb_p(0.25, 0.69, 1);
	this->seleccionado = false;
}

VistaComponente::~VistaComponente() {
	// TODO Auto-generated destructor stub
}

void VistaComponente::getposini(double&x, double&y) const {
	x = this->pos_ini_x;
	y = this->pos_ini_y;
}

void VistaComponente::setposini(double x, double y) {
	this->pos_ini_x = x;
	this->pos_ini_y = y;

}

void VistaComponente::getposfin(double&x, double&y) const {
	x = this->pos_fin_x;
	y = this->pos_fin_y;
}

void VistaComponente::setposfin(double x, double y) {
	this->pos_fin_x = x;
	this->pos_fin_y = y;
}

void VistaComponente::setDibujable(bool d) {
	this->dibujable = d;
}

bool VistaComponente::getDibujable() {
	return this->dibujable;
}

void VistaComponente::mover(double x, double y) {
	double ancho, alto;
	ancho = this->pos_fin_x - this->pos_ini_x;
	alto = this->pos_fin_y - this->pos_ini_y;
	this->pos_ini_x = x - this->pos_selec_x;
	this->pos_fin_x = this->pos_ini_x + ancho;
	this->pos_ini_y = y - this->pos_selec_y;
	this->pos_fin_y = this->pos_ini_y + alto;
}

void VistaComponente::seleccionar(double x, double y) {
	this->seleccionado = true;
	this->pos_selec_x = x - this->pos_ini_x;
	this->pos_selec_y = y - this->pos_ini_y;
}

void VistaComponente::deseleccionar() {
	this->seleccionado = false;
	this->pos_selec_x = 0;
	this->pos_selec_y = 0;
}

void VistaComponente::dibujarNombreCentrado(Cairo::RefPtr<Cairo::Context> cr,
		const std::string nombre) {
	double centro_x, centro_y;
	double textoCentrado_x, textoCentrado_y;
	Cairo::TextExtents textExtents;

	centro_x = (this->pos_ini_x + this->pos_fin_x) / 2;
	centro_y = (this->pos_ini_y + this->pos_fin_y) / 2;

	/* NO BORRAR, COSTO MUCHO CONSEGUIRLO
	 *
	 * La posicion del texto cuando se dibuja es el .           .TEXTO
	 *
	 * The cairo_text_extents_t structure stores the extents of a single glyph or a
	 * string of glyphs in user-space coordinates. Because text extents are in user-space
	 * coordinates, they are mostly, but not entirely, independent of the current
	 * transformation matrix. If you call cairo_scale(cr, 2.0, 2.0), text will be drawn
	 * twice as big, but the reported text extents will not be doubled. They will change
	 *  slightly due to hinting (so you can't assume that metrics are independent of the
	 *  transformation matrix), but otherwise will remain unchanged.

	 double x_bearing;
	 the horizontal distance from the origin to the leftmost part of the glyphs as drawn.
	 Positive if the glyphs lie entirely to the right of the origin.

	 double y_bearing;
	 the vertical distance from the origin to the topmost part of the glyphs as drawn.
	 Positive only if the glyphs lie completely below the origin; will usually be negative.

	 double width;
	 width of the glyphs as drawn

	 double height;
	 height of the glyphs as drawn

	 double x_advance;
	 distance to advance in the X direction after drawing these glyphs

	 double y_advance;
	 distance to advance in the Y direction after drawing these glyphs. Will typically be
	 zero except for vertical text layout as found in East-Asian languages.*/

	// Obtengo dimensiones del texto
	cr->get_text_extents(nombre, textExtents);
	textoCentrado_x = centro_x - (textExtents.width / 2);
	textoCentrado_y = centro_y + (textExtents.height / 2);

	/*cout << "bearing " << textExtents.x_bearing << " " << textExtents.y_bearing << " ";
	 cout << "dimentions "<< textExtents.width << " " << textExtents.height << " ";
	 cout << "advance "<< textExtents.x_advance << " " << textExtents.y_advance << endl;*/
	cr->move_to(textoCentrado_x, textoCentrado_y);
	cr->show_text(nombre);
	cr->stroke();
}

/* PERSISTENCIA REP

void VistaComponente::obtenerPropiedadesRep(XmlNodo* nodo) {
	this->codigo = nodo->getPropiedadInt("codigo");
}

void VistaComponente::obtenerComponentesREP (XmlNodo* nodo) {
	while (nodo->esValido()) {
		if (nodo->getNombre() == "posicion_incial") {
	  		this->pos_ini_x = nodo->getPropiedadInt("x");
	  		this->pos_ini_y = nodo->getPropiedadInt("y");
		}
		if (nodo->getNombre() == "posicion_final") {
	  		this->pos_fin_x = nodo->getPropiedadInt("x");
	  		this->pos_fin_y = nodo->getPropiedadInt("y");
		}
		if (nodo->getNombre() == "color") {
	  		this->colorR = nodo->getPropiedadInt("r");
	  		this->colorG = nodo->getPropiedadInt("g");
	  		this->colorB = nodo->getPropiedadInt("b");
		}
		*nodo = nodo->getHermano();
	}
}


void VistaComponente::agregarPropiedadesRep(XmlNodo* nodo) {
	nodo->setPropiedad("codigo",this->codigo);

}
void Atributo::agregarPropiedadesXmlDER(XmlNodo* nodo) {
	nodo->setPropiedad("tipo",this->tipo);
}

XmlNodo Entidad::guardarXmlDER() {
	XmlNodo nodo("componente");

	this->agregarPropiedadesXmlDER(&nodo);

	XmlNodo nodoPosicionInicial("posicion_incial");
	nodo->setPropiedad("x",this->pos_ini_x);
	nodo->setPropiedad("y",this->pos_ini_y);
	nodo->agregarHijo(nodoPosicionInicial);

	XmlNodo nodoPosicionFinal("posicion_final");
	nodo->setPropiedad("x",this->pos_fin_x);
	nodo->setPropiedad("y",this->pos_fin_y);
	nodo->agregarHijo(nodoPosicionFinal);

	XmlNodo nodoColor("color");
	nodo->setPropiedad("r",this->colorR);
	nodo->setPropiedad("g",this->colorG);
	nodo->setPropiedad("b",this->colorB);
	nodo->agregarHijo(nodoColor);

	return nodo;
}
*/

