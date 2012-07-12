#ifndef ELEMENTOVISUAL_H_
#define ELEMENTOVISUAL_H_

#include <gtkmm.h>
#include <cairomm/cairomm.h>
#include "../comun/Punto.h"

class ElementoVisual {
protected:
	Punto posicionInicial;
	Punto posicionFinal;
public:
	ElementoVisual();
	virtual ~ElementoVisual();

	virtual void dibujar(Cairo::RefPtr<Cairo::Context> cr) = 0;
};

#endif /* ELEMENTOVISUAL_H_ */
