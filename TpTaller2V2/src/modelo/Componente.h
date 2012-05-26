/* Componente.h
 *  Created on: 30/04/2012
 *      Author: gonzalo
 */
#ifndef COMPONENTE_H_
#define COMPONENTE_H_

#include <string>

class Componente {

private:

	int codigo;
	std::string nombre;

	/* PERSITENCIA
	// si hay que agregar más propiedades, se redefinen
	// virtual void agregarPropiedadesDER (XmlNodo* nodo);
	// virtual void obtenerPropiedadesDER (XmlNodo* nodo);

	// si hay que agregar más atributos, se redefinen
	// Estos dos metodos estarian de mas por ahora
	// virtual void agregarAtributosDER ( XmlNodo* );
	// virtual void obtenerAtributosDER ( XmlNodo* );
	 */

public:

	virtual ~Componente();

	int getCodigo() const;
	void setCodigo(int);

	std::string getNombre() const;
	void setNombre(const std::string&);

	// virtual XmlNodo guardarXmlDER() = 0;

};

#endif /* COMPONENTE_H_ */
