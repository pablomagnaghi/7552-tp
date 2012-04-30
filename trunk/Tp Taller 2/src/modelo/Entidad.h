/* Entidad.h
 *  Created on: 30/04/2012
 *      Author: Gonzalo Ferrero 89657
 */
#ifndef ENTIDAD_H_
#define ENTIDAD_H_

#include <vector>
#include <string>
#include "Entidad.h"
#include "Relacion.h"
#include "Jerarquia.h"
#include "Atributo.h"
#include "Identificador.h"
#include "Componente.h"

class Jerarquia;
class Relacion;

class Entidad : public Componente{
private:
	std::vector<Relacion*> relaciones;
	std::vector<Jerarquia*> jerarquias;
//	std::string nombre;
	std::vector<Atributo*> atributos;
	std::vector<Identificador*> identificadores;
public:
	Entidad();
	virtual ~Entidad();
};

#endif /* ENTIDAD_H_ */
