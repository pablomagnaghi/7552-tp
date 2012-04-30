/* Diagrama.h
 *  Created on: 30/04/2012
 *      Author: Gonzalo Ferrero 89657
 */
#ifndef DIAGRAMA_H_
#define DIAGRAMA_H_

#include <vector>
#include <string>
//#include "Entidad.h"
//#include "Relacion.h"
//#include "Jerarquia.h"
#include "Componente.h"

class Diagrama {
private:
//	std::vector<Entidad*> entidades;
//	std::vector<Relacion*> relaciones;
//	std::vector<Jerarquia*> jerarquias;
	std::vector<Componente *> componentes;
	std::string nombre;
	Diagrama * padre;
	std::vector<Diagrama *> hijos;

public:
	Diagrama();
	virtual ~Diagrama();
};

#endif /* DIAGRAMA_H_ */
