/* Componente.h
 *  Created on: 30/04/2012
 *      Author: gonzalo
 */
#ifndef COMPONENTE_H_
#define COMPONENTE_H_

#include <string>

// Persistencia
#include "persistencia/Persistencia.h"

class Componente {

protected:

	int codigo;
	std::string nombre;

	// PERSITENCIA COMP
	// si hay que agregar más propiedades, se redefinen
	virtual void agregarPropiedadesXmlCOMP(XmlNodo* nodo);
	virtual void obtenerPropiedadesXmlCOMP(XmlNodo* nodo);

public:

	virtual ~Componente();

	int getCodigo() const;
	void setCodigo(int);

	std::string getNombre() const;
	void setNombre(const std::string&);
};

#endif /* COMPONENTE_H_ */
