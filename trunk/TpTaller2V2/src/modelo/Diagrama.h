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
#include <iostream>
#include <list>
using namespace std;

class Diagrama {
protected:
//	std::vector<Entidad*> entidades;
//	std::vector<Relacion*> relaciones;
//	std::vector<Jerarquia*> jerarquias;
	//std::vector<Componente *> componentes;
	std::string nombre;
	Diagrama * padre;
	//std::vector<Diagrama *> hijos;

	list<Diagrama*> l_sub_diagramas;
	list<Componente*> l_componentes;
	friend class TreePanel;
	friend class VistaDiagrama;
	Diagrama(string nombre);
public:

	virtual ~Diagrama();

	inline string getNombre() {
		return this->nombre;
	}
	inline void setNombre(string nom) {
		this->nombre = nom;
	}

	virtual Diagrama* crearSubdiagrama(string nombre);
};

#endif /* DIAGRAMA_H_ */
