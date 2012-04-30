/* Proyecto.h
 *  Created on: 30/04/2012
 *      Author: Gonzalo Ferrero 89657
 */
#ifndef PROYECTO_H_
#define PROYECTO_H_

#include "Diagrama.h"
#include <vector>
#include <string>

class Proyecto {
private:
	std::vector<Diagrama*> diagramas;
	std::string nombre;

public:
	Proyecto();
	virtual ~Proyecto();
};

#endif /* PROYECTO_H_ */
