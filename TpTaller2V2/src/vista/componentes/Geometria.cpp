#include <cmath>
#include "Geometria.h"

#include <iostream>
using namespace std;

#define MAX(X,Y) ((X) > (Y) ? (X):(Y))
#define MIN(X,Y) ((X) < (Y) ? (X):(Y))

#define DEBUG_GEOMETRIA 0

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
#if DEBUG_GEOMETRIA==1
	cout << "Cota: (" << cotaInicialInterseccion.x << ";" << cotaInicialInterseccion.y << ") ("
	<< cotaFinalInterseccion.x << ";" << cotaFinalInterseccion.y << ")" << std::endl;
#endif
	// ACOTO en X y busco los Y
	acotarX(x0, x1, y0, y1, m0, posInicialLinea1, posFinalLinea1, cotaInicialInterseccion,
			cotaFinalInterseccion);
	acotarX(x2, x3, y2, y3, m1, posInicialLinea2, posFinalLinea2, cotaInicialInterseccion,
			cotaFinalInterseccion);

	// Verifico si no hay interseccion
	if (posInicialLinea1.y < cotaInicialInterseccion.y
			&& posFinalLinea1.y < cotaInicialInterseccion.y) {
		return false;
	} else if (posInicialLinea2.y < cotaInicialInterseccion.y
			&& posFinalLinea2.y < cotaInicialInterseccion.y) {
		return false;
	} else if (posInicialLinea1.y > cotaFinalInterseccion.y
			&& posFinalLinea1.y > cotaFinalInterseccion.y) {
		return false;
	} else if (posInicialLinea2.y > cotaFinalInterseccion.y
			&& posFinalLinea2.y > cotaFinalInterseccion.y) {
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
#if DEBUG_GEOMETRIA==1
		cout << "Linea1: (" << x0 << ";" << y0 << ") (" << x1 << ";" << y1 << ")" << std::endl;
		cout << "Linea2: (" << x2 << ";" << y2 << ") (" << x3 << ";" << y3 << ")" << std::endl;
		std::cout << "m0 = " << m0 << std::endl;
		std::cout << "m1 = " << m1 << std::endl;
#endif
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
#if DEBUG_GEOMETRIA==1
		cout << "Linea1: (" << x0 << ";" << y0 << ") (" << x1 << ";" << y1 << ")" << std::endl;
		cout << "Linea2: (" << x2 << ";" << y2 << ") (" << x3 << ";" << y3 << ")" << std::endl;
		std::cout << "m0 = " << m0 << std::endl;
		std::cout << "m1 = " << m1 << std::endl;
#endif
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
#if DEBUG_GEOMETRIA==1
	cout << "Linea1: (" << x0 << ";" << y0 << ") (" << x1 << ";" << y1 << ")" << std::endl;
	cout << "Circulo: (" << xc << ";" << yc << ")  radio= " << r << endl;
#endif
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
#if DEBUG_GEOMETRIA==1
			cout << "y1 - yc = " << y1 - yc << endl;
#endif
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
#if DEBUG_GEOMETRIA==1
			cout << "y0 - yc = " << y0 - yc << endl;
#endif
		}

	} else {
		return false;
	}
#if DEBUG_GEOMETRIA==1
	cout << "m= " << m << endl;
#endif
	return true;
}

void Geometria::obtenerPuntosDeTriangulo(double x0, double y0, double x1, double y1, double altura,
		double base, double & x2, double & y2, double & x3, double & y3) {
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

void Geometria::obtenerLineasParalelas(double x0, double y0, double x1, double y1, double distancia,
		double & x2, double & y2, double & x3, double & y3, double & x4, double & y4, double & x5,
		double & y5) {

	double angulo;
	double delta_x, delta_y;

	double delta;
	delta = 0.00001;

	if (x0 <= (x1 - delta) || x0 >= (x1 + delta)) {
		angulo = atan2(y1 - y0, x1 - x0) + 0.5 * M_PI;
	} else {
		angulo = M_PI;
	}
	delta_x = cos(angulo) * distancia;
	delta_y = sin(angulo) * distancia;

	x2 = x0 + delta_x;
	y2 = y0 + delta_y;
	x3 = x1 + delta_x;
	y3 = y1 + delta_y;

	x4 = x0 - delta_x;
	y4 = y0 - delta_y;
	x5 = x1 - delta_x;
	y5 = y1 - delta_y;

#if DEBUG_GEOMETRIA==1
	cout << "delta x= " << delta_x << endl;
	cout << "delta y= " << delta_y << endl;
	cout << "distancia" << distancia << endl;
#endif
}

bool Geometria::hayInterseccionDeLineaConElipse(double x0, double y0, double x1, double y1,
		double xc, double yc, double rx, double ry, double & x, double & y) {
	double m = NAN; // MACRO DE MATH NOT A NUMBER
	double angulo;
	double delta_x, delta_y;
	double r_elipse;

	double delta;
	delta = 0.00001;

	// ACOTO en X y busco los Y
	if (x0 <= (x1 - delta) || x0 >= (x1 + delta)) {
		m = (y1 - y0) / (x1 - x0);
	}

	if (x0 < xc + rx && x0 > xc - rx && y0 < yc + ry && y0 > yc - ry) {
		if (isnan(m)) {
			x = xc;
			if (y1 <= yc) {
				y = yc - ry;
			} else {
				y = yc + ry;
			}
		} else {
			angulo = atan2(y1 - yc, x1 - xc);
			r_elipse = 1 / sqrt(pow(cos(angulo) / rx, 2) + pow(sin(angulo) / ry, 2));
			delta_x = cos(angulo);
			delta_y = sin(angulo);
			x = xc + delta_x * r_elipse;
			y = yc + delta_y * r_elipse;
		}
	} else if (x1 < xc + rx && x1 > xc - rx && y1 < yc + ry && y1 > yc - ry) {
		if (isnan(m)) {
			x = xc;
			if (y0 <= yc) {
				y = yc - ry;
			} else {
				y = yc + ry;
			}
		} else {
			angulo = atan2(y0 - yc, x0 - xc);
			r_elipse = 1 / sqrt(pow(cos(angulo) / rx, 2) + pow(sin(angulo) / ry, 2));
			delta_x = cos(angulo);
			delta_y = sin(angulo);
			x = xc + delta_x * r_elipse;
			y = yc + delta_y * r_elipse;
		}

	}
	return true;
}

bool Geometria::obtenerPuntoDeDibujoDeTextoCentradoEnLinea(double x0, double y0, double x1,
		double y1, double w, double h, double & x, double & y) {
	double r;
	double m = NAN; // MACRO DE MATH NOT A NUMBER
	double angulo;
	double delta;
	double xc, yc;
	delta = 0.00001;

	if (x0 <= (x1 - delta) || x0 >= (x1 + delta)) {
		m = (y1 - y0) / (x1 - x0);
	}

	xc = (x0 + x1) / 2 - w / 2;
	yc = (y0 + y1) / 2 + h / 2;

	if (isnan(m)) {
		x = xc - w / 2 - 2;
		y = yc;
	} else {
		angulo = atan2(y1 - y0, x1 - x0);
		r = sqrt(pow(h / 2 * cos(angulo), 2) + pow(w / 2 * sin(angulo), 2)) + 4;
		angulo = angulo - M_PI / 2;
		x = xc + r * cos(angulo);
		y = yc + r * sin(angulo);
	}

	return true;
}

bool Geometria::obtenerPuntoDeDibujoDeTextoOpuestoALinea(double x0, double y0, double x1, double y1,
		double w, double h, double & x, double & y) {
	double r;
	double m = NAN; // MACRO DE MATH NOT A NUMBER
	double angulo;
	double delta;
	double xc, yc;
	delta = 0.00001;

	if (x0 <= (x1 - delta) || x0 >= (x1 + delta)) {
		m = (y1 - y0) / (x1 - x0);
	}

	xc = x0 - w / 2;
	yc = y0 + h / 2;

	if (isnan(m)) {
		x = xc;
		if (y0 < y1) {
			y = yc - h - 3;
		} else {
			y = yc + h + 3;
		}
	} else {
		angulo = atan2(y1 - y0, x1 - x0);
		r = 1 / sqrt(pow(cos(angulo) / (w / 2 + 10), 2) + pow(sin(angulo) / (h / 2 + 11), 2));
		//r = sqrt(pow(w * cos(angulo), 2) + pow((h + 8) * sin(angulo), 2))*0.75;
		//cout << "r= " << r << " ang= " << angulo * 180 / M_PI << endl;
		//angulo = angulo - M_PI / 2;
		x = xc - r * cos(angulo);
		y = yc - r * sin(angulo);
	}

	return true;

	return true;
}

void Geometria::calcularAjusteDiagrama(double offset_x, double offset_y, double ancho_diagrama,
		double alto_diagrama, double & rotacion, double & zoom, double & traslacion_x,
		double & traslacion_y, double ancho_contexto, double alto_contexto) {
	double aux;

	if (ancho_contexto > alto_contexto) {
		if (ancho_diagrama > alto_diagrama) {
			rotacion = 0;
		} else {
			rotacion = 90;
		}
	} else {
		if (ancho_diagrama > alto_diagrama) {
			rotacion = 90;
		} else {
			rotacion = 0;
		}
	}

	if (rotacion == 0) {
		zoom = ancho_contexto / ancho_diagrama;
		aux = alto_contexto / alto_diagrama;

	} else {
		zoom = alto_contexto / ancho_diagrama;
		aux = ancho_contexto / alto_diagrama;
	}

#if DEBUG_GEOMETRIA==1
	std::cout << "ZoomH=" << zoom;
	std::cout << " ZoomV= " << aux << std::endl;
#endif

	if (aux < zoom) {
		zoom = aux;
	}

	zoom *= 0.95;

	if (rotacion == 0) {
		traslacion_x = ancho_contexto / 2 + ((-ancho_diagrama) / 2 - offset_x) * zoom;
		traslacion_y = alto_contexto / 2 + ((-alto_diagrama) / 2 - offset_y) * zoom;
	} else {
		traslacion_x = ancho_contexto / 2 + ((alto_diagrama) / 2 + offset_y) * zoom;
		traslacion_y = alto_contexto / 2 + ((-ancho_diagrama) / 2 - offset_x) * zoom;
	}
#if DEBUG_GEOMETRIA==1
	std::cout << "Rotacion=" << rotacion;
	std::cout << " Zoom= " << zoom;
	std::cout << " Traslacion= (" << traslacion_x << ":" << traslacion_y << ")" << std::endl;
#endif
}
