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

	/* PERSITENCIA DER
	// si hay que agregar más propiedades, se redefinen
	// virtual void agregarPropiedadesDER (XmlNodo* nodo);
	// virtual void obtenerPropiedadesDER (XmlNodo* nodo);
	 */

public:

	virtual ~Componente();

	int getCodigo() const;
	void setCodigo(int);

	std::string getNombre() const;
	void setNombre(const std::string&);

	/* PERSISTENCIA DER
	// virtual XmlNodo guardarXmlDER() = 0;
	 */

};

#endif /* COMPONENTE_H_ */
