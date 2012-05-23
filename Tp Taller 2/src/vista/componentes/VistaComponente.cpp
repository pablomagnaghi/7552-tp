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
