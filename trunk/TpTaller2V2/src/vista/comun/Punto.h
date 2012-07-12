#ifndef PUNTO_H_
#define PUNTO_H_

class Punto {
private:
	double x;
	double y;
public:
	Punto();
	Punto(double x0, double y0);
	virtual ~Punto();

    double getX() const;
    void setX(double x);

    double getY() const;
    void setY(double y);
};

#endif /* PUNTO_H_ */
