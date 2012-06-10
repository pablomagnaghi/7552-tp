#ifndef GEOMETRIA_H_
#define GEOMETRIA_H_

#define DEBUG

class Geometria {
	Geometria();
	virtual ~Geometria();
public:
	static bool estaContenidoEnRectangulo(double x, double y, double x_inicial,
			double y_inicial, double x_final, double y_final);
};

#endif /* GEOMETRIA_H_ */
