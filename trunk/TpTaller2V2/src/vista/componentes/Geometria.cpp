#include <cmath>
#include "Geometria.h"

#include <iostream>
using namespace std;

#define MAX(X,Y) ((X) > (Y) ? (X):(Y))
#define MIN(X,Y) ((X) < (Y) ? (X):(Y))

Geometria::Geometria() {
}

Geometria::~Geometria() {
}

void Geometria::acotarX(double xi, double xf, double yi, double yf, double & m,
		punto_t & posInicial, punto_t & posFinal, const punto_t & cotaInicial,
		const punto_t & cotaFinal) {
	double delta;
	delta = 0.00001;

	// ACOTO en X y busco los Y
	if (xi <= (xf - delta) || xi >= (xf + delta)) {
		m = (yf - yi) / (xf - xi);
		posInicial.x = cotaInicial.x;
		posInicial.y = yi + m * (posInicial.x - xi);
		posFinal.x = cotaFinal.x;
		posFinal.y = yi + m * (posFinal.x - xi);
	} else {
		posInicial.x = xi;
		posInicial.y = cotaInicial.y;
		posFinal.x = xi;
		posFinal.y = cotaFinal.y;
	}
}

void Geometria::normalizarCoordenadas(double & x0, double & y0, double & x1, double & y1) {
	double aux;
	if (x1 < x0) {
		aux = x1, x1 = x0, x0 = aux;
		aux = y1, y1 = y0, y0 = aux;
	}
}

bool Geometria::estaContenidoEnRectangulo(double x, double y, double x_inicial, double y_inicial,
		double x_final, double y_final) {
	if (x >= x_inicial && x <= x_final) {
		if (y >= y_inicial && y <= y_final) {
			return true;
		}
	}
	return false;
}

bool Geometria::hayInterseccionDeLineas(double x0, double y0, double x1, double y1, double x2,
		double y2, double x3, double y3, double & x, double & y) {

	double m0 = NAN, m1 = NAN; // MACRO DE MATH NOT A NUMBER
	punto_t posInicialLinea1, posFinalLinea1;
	punto_t posInicialLinea2, posFinalLinea2;

	normalizarCoordenadas(x0, y0, x1, y1);
	normalizarCoordenadas(x2, y2, x3, y3);

	punto_t cotaInicialInterseccion;
	punto_t cotaFinalInterseccion;
	cotaInicialInterseccion.x = MAX(x0, x2);
	cotaFinalInterseccion.x = MIN(x1, x3);
	if (cotaFinalInterseccion.x < cotaInicialInterseccion.x) {
		return false;
	}
	cotaInicialInterseccion.y = MAX(MIN(y0, y1), MIN(y2, y3));
	cotaFinalInterseccion.y = MIN(MAX(y0, y1), MAX(y2, y3));

	cout << "Cota: (" << cotaInicialInterseccion.x << ";" << cotaInicialInterseccion.y << ") ("
			<< cotaFinalInterseccion.x << ";" << cotaFinalInterseccion.y << ")" << std::endl;

	// ACOTO en X y busco los Y
	acotarX(x0, x1, y0, y1, m0, posInicialLinea1, posFinalLinea1, cotaInicialInterseccion,
			cotaFinalInterseccion);
	acotarX(x2, x3, y2, y3, m1, posInicialLinea2, posFinalLinea2, cotaInicialInterseccion,
			cotaFinalInterseccion);

	// Verifico si no hay interseccion
	if (posInicialLinea1.y < cotaInicialInterseccion.y && posFinalLinea1.y
			< cotaInicialInterseccion.y) {
		return false;
	} else if (posInicialLinea2.y < cotaInicialInterseccion.y && posFinalLinea2.y
			< cotaInicialInterseccion.y) {
		return false;
	} else if (posInicialLinea1.y > cotaFinalInterseccion.y && posFinalLinea1.y
			> cotaFinalInterseccion.y) {
		return false;
	} else if (posInicialLinea2.y > cotaFinalInterseccion.y && posFinalLinea2.y
			> cotaFinalInterseccion.y) {
		return false;
	}

	// CHEQUEO SI HAY COLISION
	if (posInicialLinea1.y <= posInicialLinea2.y && posFinalLinea1.y >= posFinalLinea2.y) {
		if (isnan(m0)) {
			x = x0;
		} else if (isnan(m1)) {
			x = x2;
		} else {
			x = (y2 - y0 + m0 * x0 - m1 * x2) / (m0 - m1);
			y = y0 + m0 * (x - x0);
		}
		if (!isnan(m0)) {
			y = y0 + m0 * (x - x0);
		} else if (!isnan(m1)) {
			y = y2 + m1 * (x - x2);
		}

		cout << "Linea1: (" << x0 << ";" << y0 << ") (" << x1 << ";" << y1 << ")" << std::endl;
		cout << "Linea2: (" << x2 << ";" << y2 << ") (" << x3 << ";" << y3 << ")" << std::endl;
		std::cout << "m0 = " << m0 << std::endl;
		std::cout << "m1 = " << m1 << std::endl;
		return true;
	} else if (posInicialLinea1.y >= posInicialLinea2.y && posFinalLinea1.y <= posFinalLinea2.y) {
		if (isnan(m0)) {
			x = x0;
		} else if (isnan(m1)) {
			x = x2;
		} else {
			x = (y2 - y0 + m0 * x0 - m1 * x2) / (m0 - m1);
			y = y0 + m0 * (x - x0);
		}

		if (!isnan(m0)) {
			y = y0 + m0 * (x - x0);
		} else if (!isnan(m1)) {
			y = y2 + m1 * (x - x2);
		}
		cout << "Linea1: (" << x0 << ";" << y0 << ") (" << x1 << ";" << y1 << ")" << std::endl;
		cout << "Linea2: (" << x2 << ";" << y2 << ") (" << x3 << ";" << y3 << ")" << std::endl;
		std::cout << "m0 = " << m0 << std::endl;
		std::cout << "m1 = " << m1 << std::endl;
		return true;
	}

	// Verifico si las lineas están dentro de la cota
	/*if (posInicialLinea1.y >= cotaInicialInterseccion.y && posFinalLinea1.y
	 <= cotaFinalInterseccion.y && posInicialLinea2.y
	 >= cotaInicialInterseccion.y && posFinalLinea2.y
	 <= cotaFinalInterseccion.y) {
	 // Estoy en rango

	 }*/

	// Acoto en Y y busco los X
	//if (posInicialLinea1.y < cotaInicialInterseccion.y) {

	//}
	return false;
}
