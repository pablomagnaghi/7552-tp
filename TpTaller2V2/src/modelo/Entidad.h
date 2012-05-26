/* Entidad.h
 *  Created on: 30/04/2012
 *      Author: Gonzalo Ferrero 89657
 */
#ifndef ENTIDAD_H_
#define ENTIDAD_H_

#include <vector>
#include <algorithm>
#include "Componente.h"

class Relacion;

class Entidad : public Componente {

private:

	std::vector<Relacion*> relaciones;

public:

	virtual ~Entidad();

	void agregarRelacion(Relacion*);
	void quitarRelacion(Relacion*);

};

#endif /* ENTIDAD_H_ */
