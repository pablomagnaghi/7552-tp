/* Identificador.h
 *  Created on: 30/04/2012
 *      Author: Gonzalo Ferrero 89657
 */
#ifndef IDENTIFICADOR_H_
#define IDENTIFICADOR_H_

#include <vector>
#include <string>
#include "Atributo.h"

class Relacion;

class Identificador {

private:

	std::vector<Atributo*> atributos;
	std::vector<Relacion*> relaciones; // Para el caso de entidades debiles. El identificador podría guardar las entidades fuertes, en vez de las relaciones.

public:

	Identificador();
	virtual ~Identificador();

	void agregarAtributo(Atributo*);
	void quitarAtributo(Atributo*);

	void agregarRelacion(Relacion*);
	void quitarRelacion(Relacion*);

	std::vector<Atributo*>::iterator atributosBegin();
	std::vector<Atributo*>::iterator atributosEnd();

	std::vector<Relacion*>::iterator relacionesBegin();
	std::vector<Relacion*>::iterator relacionesEnd();

};

#endif /* IDENTIFICADOR_H_ */
