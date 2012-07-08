#ifndef ENTIDAD_H_
#define ENTIDAD_H_

#include <vector>
#include <algorithm>
#include "Componente.h"
#include "Atributo.h"

class Entidad : public Componente {

protected:
	bool esDebil;

	// PERSISTENCIA COMP
	/*
	void guardarRelacionesXmlCOMP(XmlNodo*);
	*/

public:
	Entidad();
	virtual ~Entidad();

	void setEsDebil(bool);
	bool getEsDebil();

	void agregarAtributo(Atributo*);
	void quitarAtributo(Atributo*);
};

#endif /* ENTIDAD_H_ */
