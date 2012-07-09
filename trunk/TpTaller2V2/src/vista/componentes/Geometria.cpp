/* Geometria.cpp
 *  Created on: 30/05/2012
 *      Author: Gonzalo Ferrero 89657
 */

#include "Geometria.h"

#define MAX(X,Y) ((X) > (Y) ? (X):(Y))
#define MIN(X,Y) ((X) < (Y) ? (X):(Y))

typedef struct {
	double x;
	double y;
} punto_t;

Geometria::Geometria() {
	// TODO Auto-generated constructor stub

}

Geometria::~Geometria() {
	// TODO Auto-generated destructor stub
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
	double aux;
	if (x1 < x0) {
		aux = x1, x1 = x0, x0 = aux;
		aux = y1, y1 = y0, y0 = aux;
	}
	if (x3 < x2) {
		aux = x3, x3 = x2, x2 = aux;
		aux = y3, y3 = y2, y2 = aux;
	}

	punto_t cotaInicialInterseccion;
	punto_t cotaFinalInterseccion;
	cotaInicialInterseccion.x = MAX(x0,x2);
	cotaFinalInterseccion.x = MIN(x1,x3);
	cotaInicialInterseccion.y = MAX(MIN(y0,y1),MIN(y2,y3));
	cotaFinalInterseccion.y = MIN(MAX(y0,y1),MAX(y2,y3));

	punto_t posInicialLinea1, posFinalLinea1;
	punto_t posInicialLinea2, posFinalLinea2;

	double m0, m1;

	// ACOTO en X y busco los Y
	if (x0 != x1) {
		m0 = (y1 - y0) / (x1 - x0);
		posInicialLinea1.x = cotaInicialInterseccion.x;
		posFinalLinea1.x = cotaFinalInterseccion.x;
		posInicialLinea1.y = y0 + m0 * (posInicialLinea1.x - x0);
		posFinalLinea1.y = y0 + m0 * (posFinalLinea1.x - x0);
	} else {
		posInicialLinea1.x = x0;
		posFinalLinea1.x = x0;
		posInicialLinea1.y = cotaInicialInterseccion.y;
		posFinalLinea1.y = cotaFinalInterseccion.y;
	}
	if (x2 != x3) {
		m1 = (y3 - y2) / (x3 - x2);
		posInicialLinea2.x = cotaInicialInterseccion.x;
		posFinalLinea2.x = cotaFinalInterseccion.x;
		posInicialLinea2.y = y2 + m1 * (posInicialLinea2.x - x2);
		posFinalLinea2.y = y2 + m1 * (posFinalLinea2.x - x2);
	} else {
		posInicialLinea2.x = x2;
		posFinalLinea2.x = x2;
		posInicialLinea2.y = cotaInicialInterseccion.y;
		posFinalLinea2.y = cotaFinalInterseccion.y;
	}

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
		x = (y2 - y0 + m0 * x0 - m1 * x2) / (m0 - m1);
		y = y0 + m0 * (x - x0);
		return true;
	} else if (posInicialLinea1.y >= posInicialLinea2.y && posFinalLinea1.y <= posFinalLinea2.y) {
		x = (y2 - y0 + m0 * x0 - m1 * x2) / (m0 - m1);
		y = y0 + m0 * (x - x0);
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
