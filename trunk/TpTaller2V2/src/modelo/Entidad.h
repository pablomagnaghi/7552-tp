/* Entidad.h
 *  Created on: 30/04/2012
 *      Author: Gonzalo Ferrero 89657
 */
#ifndef ENTIDAD_H_
#define ENTIDAD_H_

#include <vector>
#include <algorithm>
#include "Componente.h"
#include "Atributo.h"
#include "Relacion.h"

// Persistencia
#include "persistencia/Persistencia.h"

class Relacion;

class Entidad : public Componente {

protected:
	bool esDebil;
	std::vector<Relacion*> relaciones;

	// PERSISTENCIA COMP
	void guardarRelacionesXmlCOMP(XmlNodo*);
	Relacion* obtenerRelacion(int);

public:
	Entidad();
	virtual ~Entidad();

	void agregarRelacion(Relacion*);
	void quitarRelacion(Relacion*);

	std::vector<Relacion*>::iterator relacionesBegin();
	std::vector<Relacion*>::iterator relacionesEnd();

	Relacion* getRelacionByCodigo(int);

	void setEsDebil(bool);

	void agregarAtributo(Atributo*);
	void quitarAtributo(Atributo*);
};

#endif /* ENTIDAD_H_ */
