/* Relacion.h
 *  Created on: 30/04/2012
 *      Author: Gonzalo Ferrero 89657
 */
#ifndef RELACION_H_
#define RELACION_H_

#include <vector>
#include <string>
#include "Entidad.h"
#include "Atributo.h"
#include "Componente.h"

class Entidad;

class Relacion : public Componente{
private:
	std::vector<Atributo *> atributos;
	std::vector<Entidad *> entidades;
//	std::string nombre;
public:
	Relacion();
	virtual ~Relacion();
};

#endif /* RELACION_H_ */
