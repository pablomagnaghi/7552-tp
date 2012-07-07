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

class Entidad : public Componente {

protected:
	bool esDebil;
	std::vector<int> codigoRelaciones;

	// PERSISTENCIA COMP
	/*
	void guardarRelacionesXmlCOMP(XmlNodo*);
	*/

public:
	Entidad();
	virtual ~Entidad();

	void agregarCodigoRelacion(int);
	void quitarCodigoRelacion(int);

	std::vector<int>::iterator codigoRelacionesBegin();
	std::vector<int>::iterator codigoRelacionesEnd();

	void setEsDebil(bool);
	bool getEsDebil();

	void agregarAtributo(Atributo*);
	void quitarAtributo(Atributo*);
};

#endif /* ENTIDAD_H_ */
