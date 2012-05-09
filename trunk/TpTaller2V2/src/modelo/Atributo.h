/*
 * Atributo.h
 *
 *  Created on: 02/04/2012
 *      Author: Guagnini Enzo 88325
 */

#ifndef ATRIBUTO_H_
#define ATRIBUTO_H_
#include "Componente.h"
#include <vector>
#include <algorithm>

class Atributo : public Componente{
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
	std::string tipo;
	std::string expresion;
	std::string cardinalidadMinima;
	std::string cardinalidadMaxima;
	vector<Atributo*> atributosDerivables;
	Atributo();
public:
	std::string getTipo() const;
	void setTipo(const std::string& tipo);

	std::string getExpresion() const;
	void setExpresion(const std::string& expresion);

	std::string getCardinalidadMinima() const;
	void setCardinalidadMinima(const std::string& cardinalidadMinima);

	std::string getCardinalidadMaxima() const;
	void setCardinalidadMaxima(const std::string& cardinalidadMaxima);

	// atributos
	void agregarAtributoDerivable(Atributo*);
	void quitarAtributoDerivable(Atributo*);

	std::vector<Atributo*>::iterator atributoDerivableBegin();
	std::vector<Atributo*>::iterator atributoDerivableEnd();

	void borrarAtributosDerivables();

	virtual ~Atributo();
};

#endif /* ATRIBUTO_H_ */
