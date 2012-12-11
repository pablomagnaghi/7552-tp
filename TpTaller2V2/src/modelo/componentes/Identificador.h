/* Identificador.h
 *  Created on: 30/04/2012
 *      Author: Gonzalo Ferrero 89657
 */
#ifndef IDENTIFICADOR_H_
#define IDENTIFICADOR_H_

#include <vector>
#include <string>
#include "Relacion.h"
#include "Atributo.h"

class Identificador {

private:
	std::vector<int> codigoAtributos;
	std::vector<int> codigoRelaciones;

public:
	Identificador();
	virtual ~Identificador();

	void agregarCodigoAtributo(int);
	void quitarCodigoAtributo(int);

	void agregarCodigoRelacion(int);
	void quitarCodigoRelacion(int);

	std::vector<int>::iterator codigoAtributosBegin();
	std::vector<int>::iterator codigoAtributosEnd();

	std::vector<int>::iterator codigoRelacionesBegin();
	std::vector<int>::iterator codigoRelacionesEnd();

	void accept(ModeloVisitor*);
};

#endif /* IDENTIFICADOR_H_ */
