/*
 * Componente.cpp
 *
 *  Created on: 02/04/2012
 *      Author: Guagnini Enzo 88325
 */

#include "Componente.h"

Componente::Componente() {
	this->setposfin(0,0);
	this->setposini(0,0);
	this->pos_selec_x = 0;
	this->pos_selec_y = 0;
	this->m_pMenuPopup = 0;
}

Componente::~Componente() {
	// TODO Auto-generated destructor stub
}

void Componente::getposini(double&x, double&y)const{
	x = this->pos_ini_x;
	y = this->pos_ini_y;
}

void Componente::setposini(double x,double y){
	this->pos_ini_x = x;
	this->pos_ini_y = y;
}

void Componente::getposfin(double&x, double&y)const{
	x = this->pos_fin_x;
	y = this->pos_fin_y;
}

void Componente::setposfin(double x,double y){
	this->pos_fin_x = x;
	this->pos_fin_y = y;
}

void Componente::setDibujable(bool d){
	this->dibujable = d;
}

bool Componente::getDibujable(){
	return this->dibujable;
}

string Componente::getNombre()const{
	return this->nombre;
}
