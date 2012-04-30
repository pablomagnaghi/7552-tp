/* Componente.h
 *  Created on: 30/04/2012
 *      Author: gonzalo
 */
#ifndef COMPONENTE_H_
#define COMPONENTE_H_

#include <string>

class Componente {
protected:
	int codigo;
	std::string nombre;
public:
	Componente();
	virtual ~Componente();
};

#endif /* COMPONENTE_H_ */
