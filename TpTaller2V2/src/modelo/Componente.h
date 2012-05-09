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
	/* PERSITENCIA
	// si hay que agregar más propiedades, se redefinen
	// virtual void agregarPropiedadesDER (XmlNodo* nodo);
	// virtual void obtenerPropiedadesDER (XmlNodo* nodo);

	// si hay que agregar más atributos, se redefinen
	// Estos dos metodos estarian de mas por ahora
	// virtual void agregarAtributosDER ( XmlNodo* );
	// virtual void obtenerAtributosDER ( XmlNodo* );
	 */
	int codigo;
	std::string nombre;
	Componente();
public:
	int getCodigo() const;
	void setCodigo(int codigo);

	std::string getNombre() const;
	void setNombre(const std::string& codigo);

	virtual ~Componente();

	// virtual XmlNodo guardarXmlDER() = 0;

};

#endif /* COMPONENTE_H_ */
