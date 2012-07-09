#ifndef ENTIDAD_H_
#define ENTIDAD_H_

#include <vector>
#include <algorithm>
#include "Componente.h"
#include "Atributo.h"
#include "UnionEntidadRelacion.h"

class UnionEntidadRelacion;

class Entidad : public Componente {

protected:
	bool esDebil;
	std::vector<UnionEntidadRelacion *> unionesARelaciones;

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

	void agregarUnion(UnionEntidadRelacion *);
	void removerUnion(UnionEntidadRelacion *);

	std::vector<UnionEntidadRelacion *> getUniones();
};

#endif /* ENTIDAD_H_ */
