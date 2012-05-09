/* Jerarquia.h
 *  Created on: 30/04/2012
 *      Author: Gonzalo Ferrero 89657
 */
#ifndef JERARQUIA_H_
#define JERARQUIA_H_

#include <vector>
#include <string>
#include "Entidad.h"
#include "Componente.h"

class Entidad;

class Jerarquia : public Componente{
private:
	Entidad * padre;
	std::vector<Entidad*> hijos;
//	std::string nombre;
public:
	Jerarquia();
	virtual ~Jerarquia();
};

#endif /* JERARQUIA_H_ */
