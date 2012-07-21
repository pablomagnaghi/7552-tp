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

bool Geometria::hayInterseccionDeLineaConCirculo(double x0, double y0, double x1, double y1,
		double xc, double yc, double r, double & x, double & y) {
	double m = NAN; // MACRO DE MATH NOT A NUMBER
	double angulo;
	double delta_x, delta_y;

	double delta;
	delta = 0.00001;

	// ACOTO en X y busco los Y
	if (x0 <= (x1 - delta) || x0 >= (x1 + delta)) {
		m = (y1 - y0) / (x1 - x0);
	}
	cout << "Linea1: (" << x0 << ";" << y0 << ") (" << x1 << ";" << y1 << ")" << std::endl;
	cout << "Circulo: (" << xc << ";" << yc << ")  radio= " << r << endl;
	if (x0 < xc + r && x0 > xc - r && y0 < yc + r && y0 > yc - r) {
		if (isnan(m)) {
			x = xc;
			if (y1 <= yc) {
				y = yc - r;
			} else {
				y = yc + r;
			}
		} else {
			angulo = atan2(y1 - yc, x1 - xc);
			delta_x = cos(angulo);
			delta_y = sin(angulo);
			x = xc + delta_x * r;
			y = yc + delta_y * r;
			cout << "y1 - yc = " << y1 - yc << endl;
		}
	} else if (x1 < xc + r && x1 > xc - r && y1 < yc + r && y1 > yc - r) {
		if (isnan(m)) {
			x = xc;
			if (y0 <= yc) {
				y = yc - r;
			} else {
				y = yc + r;
			}
		} else {
			angulo = atan2(y0 - yc, x0 - xc);
			delta_x = cos(angulo);
			delta_y = sin(angulo);
			x = xc + delta_x * r;
			y = yc + delta_y * r;
			cout << "y0 - yc = " << y0 - yc << endl;
		}

	} else {
		return false;
	}

	cout << "m= " << m << endl;

	return true;
}

void Geometria::obtenerPuntosDeTriangulo(double x0, double y0, double x1, double y1, double altura,
		double base, double & x2, double & y2, double & x3, double & y3) {
	double m = NAN; // MACRO DE MATH NOT A NUMBER
	double angulo;
	double angulo2;
	double delta_x, delta_y;
	double xc, yc;
	double mitad_base;
	double delta;

	delta = 0.00001;
	mitad_base = base / 2;

	angulo2 = atan2(mitad_base, altura);

	if (x0 <= (x1 - delta) || x0 >= (x1 + delta)) {
		angulo = atan2(y1 - y0, x1 - x0);
		delta_x = cos(angulo) * altura;
		delta_y = sin(angulo) * altura;
		/*xc = x1 - delta_x;
		 yc = y1 - delta_y;*/

		// QUEDO COMO SI FUERA UN CIRCULO, PERO ES IMPORTANTE
		y2 = y1 - sin(angulo + angulo2) * altura;
		y3 = y1 - sin(angulo - angulo2) * altura;
		x2 = x1 - cos(angulo + angulo2) * altura;
		x3 = x1 - cos(angulo - angulo2) * altura;

	} else {
		xc = x1;
		if (y1 > y0) {
			yc = y1 - altura;
		} else {
			yc = y1 + altura;
		}
		y2 = yc;
		y3 = yc;
		x2 = xc - mitad_base;
		x3 = xc + mitad_base;
	}

}
