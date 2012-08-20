#ifndef GEOMETRIA_H_
#define GEOMETRIA_H_

#define DEBUG

class Geometria {
private:

	typedef struct {
		double x;
		double y;
	} punto_t;

	Geometria();
	virtual ~Geometria();
	static void normalizarCoordenadas(double & x0, double & y0, double & x1, double & y1);
	static void acotarX(double xi, double xf, double yi, double yf, double & m,
			punto_t & posInicial, punto_t & posFinal, const punto_t & cotaInicial,
			const punto_t & cotaFinal);
public:
	static bool estaContenidoEnRectangulo(double x, double y, double x_inicial, double y_inicial,
			double x_final, double y_final);
	static bool hayInterseccionDeLineas(double x0, double y0, double x1, double y1, double x2,
			double y2, double x3, double y3, double & x, double & y);
	static bool
	hayInterseccionDeLineaConCirculo(double x0, double y0, double x1, double y1, double xc,
			double yc, double r, double & x, double & y);
	static void obtenerPuntosDeTriangulo(double x0, double y0, double x1, double y1, double altura,
			double base, double & x2, double & y2, double & x3, double & y3);
	static void obtenerLineasParalelas(double x0, double y0, double x1, double y1,
			double distancia, double & x2, double & y2, double & x3, double & y3, double & x4,
			double & y4, double & x5, double & y5);
	static bool
	hayInterseccionDeLineaConElipse(double x0, double y0, double x1, double y1, double xc,
			double yc, double rx, double ry, double & x, double & y);
	static bool
	obtenerPuntoDeDibujoDeTextoCentradoEnLinea(double x0, double y0, double x1, double y1,
			double w, double h, double & x, double & y);
	static bool
	obtenerPuntoDeDibujoDeTextoOpuestoALinea(double x0, double y0, double x1, double y1,
			double w, double h, double & x, double & y);
};

#endif /* GEOMETRIA_H_ */
