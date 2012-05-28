/*
 * Atributo.h
 *
 *  Created on: 02/04/2012
 *      Author: Guagnini Enzo 88325
 */

#ifndef ATRIBUTO_H_
#define ATRIBUTO_H_

#include <vector>
#include <algorithm>
#include "Componente.h"
#include "persistencia/Persistencia.h"


class Atributo : public Componente {

private:

	/* PERSISTENCIA DER
	// void obtenerComponentesXmlDER (XmlNodo*);
	 */
	std::string tipo;
	std::string expresion;
	std::string cardinalidadMinima;
	std::string cardinalidadMaxima;
	std::vector<Atributo*> atributosDerivables;

	void borrarAtributosDerivables();

protected:
	/* PERSISTENCIA DER
	// si hay que agregar más propiedades, se redefinen
	// virtual void agregarPropiedadesXmlDER (XmlNodo* nodo);
	// virtual void obtenerPropiedadesXmlDER (XmlNodo* nodo);
	 */

public:

	Atributo();
	virtual ~Atributo();

	std::string getTipo() const;
	void setTipo(const std::string&);

	std::string getExpresion() const;
	void setExpresion(const std::string&);

	std::string getCardinalidadMinima() const;
	void setCardinalidadMinima(const std::string&);

	std::string getCardinalidadMaxima() const;
	void setCardinalidadMaxima(const std::string&);

	void agregarAtributoDerivable(Atributo*);
	void quitarAtributoDerivable(Atributo*);

	std::vector<Atributo*>::iterator atributosDerivablesBegin();
	std::vector<Atributo*>::iterator atributosDerivablesEnd();

	/* PERSISTENCIA DER
	// Atributo(XmlNodo*);
	// virtual XmlNodo guardarXmlDER();
	 */

};

#endif /* ATRIBUTO_H_ */
