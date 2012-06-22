/* Identificador.h
 *  Created on: 30/04/2012
 *      Author: Gonzalo Ferrero 89657
 */
#ifndef IDENTIFICADOR_H_
#define IDENTIFICADOR_H_

#include <vector>
#include <string>
#include "Atributo.h"

class Identificador {

private:
	std::vector<Atributo*> atributos;
	std::vector<int> codigoRelaciones;

	void borrarAtributos();

	// PERSITENCIA COMP
	void guardarAtributosXmlCOMP(XmlNodo*);
	void guardarRelacionesXmlCOMP(XmlNodo*);

public:

	Identificador();
	virtual ~Identificador();

	void agregarAtributo(Atributo*);
	void quitarAtributo(Atributo*);

	void agregarCodigoRelacion(int);
	void quitarCodigoRelacion(int);

	std::vector<Atributo*>::iterator atributosBegin();
	std::vector<Atributo*>::iterator atributosEnd();

	std::vector<int>::iterator codigoRelacionesBegin();
	std::vector<int>::iterator codigoRelacionesEnd();

	// PERSISTENCIA DER
	XmlNodo guardarXmlCOMP();
};

#endif /* IDENTIFICADOR_H_ */
