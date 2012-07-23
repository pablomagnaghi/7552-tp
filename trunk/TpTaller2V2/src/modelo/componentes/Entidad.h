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
	std::vector<UnionEntidadRelacion *> unionesARelacion;
	Jerarquia * jerarquiaHija;

	// PERSISTENCIA COMP
	/*
	 void guardarRelacionesXmlCOMP(XmlNodo*);
	 */

public:
	Entidad();
	virtual ~Entidad();

	void agregarUnionARelacion(UnionEntidadRelacion *) throw (NullPointer);
	void removerUnionARelacion(UnionEntidadRelacion *) throw (NullPointer);

	std::vector<UnionEntidadRelacion *>::iterator unionesARelacionBegin();
	std::vector<UnionEntidadRelacion *>::iterator unionesARelacionEnd();

	// Nueva y Global pueden saber si es debil,
	// en caso de Global pregunta a la EntidadNueva que hace referencia
	virtual bool getEsDebil()= 0;

	// Todas las entidades pueden ser padres
	void setJerarquiaHija(Jerarquia *) throw (NullPointer);
	Jerarquia * getJerarquiaHija()const;

};

#endif /* ENTIDAD_H_ */
