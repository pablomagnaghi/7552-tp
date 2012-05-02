/* Componente.h
 *  Created on: 30/04/2012
 *      Author: gonzalo
 */
#ifndef COMPONENTE_H_
#define COMPONENTE_H_

#include <string>
using namespace std;

class Componente {
protected:
	int codigo;
	std::string nombre;
	Componente();
public:

	virtual ~Componente();
	inline string getNombre() {
		return this->nombre;
	}
	inline void setNombre(string nom) {
		this->nombre = nom;
	}
};

#endif /* COMPONENTE_H_ */
