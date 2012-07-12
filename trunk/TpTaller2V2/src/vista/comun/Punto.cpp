#include "Punto.h"

Punto::Punto() {

}

Punto::Punto(double X, double Y) {
	this->x = X;
	this->y = Y;
}

double Punto::getX() const {
	return x;
}

double Punto::getY() const {
	return y;
}

void Punto::setX(double x) {
	this->x = x;
}

void Punto::setY(double y) {
	this->y = y;
}

Punto::~Punto() {
}
