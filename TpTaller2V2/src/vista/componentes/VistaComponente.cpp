/*
 * Componente.cpp
 *
 *  Created on: 02/04/2012
 *      Author: Guagnini Enzo 88325
 */

#include "VistaComponente.h"

VistaComponente::VistaComponente() {
	this->setposfin(0,0);
	this->setposini(0,0);
	this->pos_selec_x = 0;
	this->pos_selec_y = 0;
	this->m_pMenuPopup = 0;
}

VistaComponente::~VistaComponente() {
	// TODO Auto-generated destructor stub
}

void VistaComponente::getposini(double&x, double&y)const{
	x = this->pos_ini_x;
	y = this->pos_ini_y;
}

void VistaComponente::setposini(double x,double y){
	this->pos_ini_x = x;
	this->pos_ini_y = y;
}

void VistaComponente::getposfin(double&x, double&y)const{
	x = this->pos_fin_x;
	y = this->pos_fin_y;
}

void VistaComponente::setposfin(double x,double y){
	this->pos_fin_x = x;
	this->pos_fin_y = y;
}

void VistaComponente::setDibujable(bool d){
	this->dibujable = d;
}

bool VistaComponente::getDibujable(){
	return this->dibujable;
}

string VistaComponente::getNombre()const{
	return this->nombre;
}
/* PERSISTENCIA REPRESENTACION
void VistaComponente::agregarPropiedadesRep(XmlNodo* nodo) {
	nodo->setPropiedad("codigo",this->codigo);
}

void VistaComponente::obtenerPropiedadesRep(XmlNodo* nodo) {
	this->codigo = nodo->getPropiedadInt("codigo");
}

VER nombre de los atributos, que tomamos por "x" e "y" y por
"ancho" y "alto". Podria ser

	x = this->pos_ini_x;
	y = this->pos_ini_y;

	ancho = this->pos_fin_x - this->pos_ini_x;
	alto = this->pos_fin_y - his->pos_ini_y;

Falta definir color

void VistaComponente:agregarAtributosRep ( XmlNodo* nodo ) {
	XmlNodo nodoPosicion("posicion");
	nodoPosicion.setPropiedad("x", verPosicionX);
	nodoPosicion.setPropiedad("y", verPosicionY);
	nodo->agregarHijo(nodoPosicion);

	XmlNodo nodoTamanio("tamanio");
	nodoTamanio.setPropiedad("ancho", verAncho);
	nodoTamanio.setPropiedad("alto", verAlto);
	nodo->agregarHijo(nodoTamanio);

	XmlNodo nodoColor("color");
	nodoColor.setContenido(this->color verColor);
	nodo->agregarHijo(nodoColor);
}

void VistaComponente:obtenerAtributosRep ( XmlNodo* nodo ) {
	VER this->PosX = nodo->getPropiedadInt("x");
	VER this->PosY = nodo->getPropiedadInt("yo");
	*nodo = nodo->getHermano();

	VER this->ancho = nodo->getPropiedadInt("ancho");
	VER this->alto = nodo->getPropiedadInt("alto");
	*nodo = nodo->getHermano();

	VER this->color = nodo->getContenidoInt();
	*nodo = nodo->getHermano();
}

XmlNodo VistaComponente:guardarXmlREP() {
	XmlNodo nodo("componente");

	this->agregarPropiedades(&nodo);

	this->agregarAtributos(&nodo);

	return nodo;
}
 */
