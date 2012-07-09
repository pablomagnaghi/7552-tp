#ifndef GEOMETRIA_H_
#define GEOMETRIA_H_

#define DEBUG

class Geometria {
	Geometria();
	virtual ~Geometria();
public:
	static bool estaContenidoEnRectangulo(double x, double y, double x_inicial,
			double y_inicial, double x_final, double y_final);
	static bool hayInterseccionDeLineas(double x0, double y0, double x1,
			double y1, double x2, double y2, double x3, double y3, double & x,
			double & y);
};

#endif /* GEOMETRIA_H_ */
