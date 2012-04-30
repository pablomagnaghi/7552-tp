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
	std::vector <Atributo *> atributos;
public:
	Identificador();
	virtual ~Identificador();
};

#endif /* IDENTIFICADOR_H_ */
