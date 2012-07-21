#ifndef ENTIDAD_H_
#define ENTIDAD_H_

#include <vector>
#include <algorithm>
#include "Componente.h"
#include "Atributo.h"
//#include "UnionEntidadRelacion.h"
//#include "Jerarquia.h"
#include "../../excepciones/NullPointer.h"

class Jerarquia;
class UnionEntidadRelacion;

class Entidad: public Componente {

protected:
	std::vector<UnionEntidadRelacion *> unionesARelaciones;
	Jerarquia * jerarquiaHija;

	// PERSISTENCIA COMP
	/*
	 void guardarRelacionesXmlCOMP(XmlNodo*);
	 */

public:
	Entidad();
	virtual ~Entidad();

	void agregarUnion(UnionEntidadRelacion *) throw (NullPointer);
	void removerUnion(UnionEntidadRelacion *) throw (NullPointer);

	std::vector<UnionEntidadRelacion *>::iterator unionesBegin();
	std::vector<UnionEntidadRelacion *>::iterator unionesEnd();

	// Nueva y Global pueden saber si es debil,
	// en caso de Global pregunta a la EntidadNueva que hace referencia
	virtual bool getEsDebil()= 0;

	// Todas las entidades pueden ser padres
	void setJerarquiaHija(Jerarquia * jHija) throw (NullPointer);
	Jerarquia * getJerarquiaHija()const;

};

#endif /* ENTIDAD_H_ */
