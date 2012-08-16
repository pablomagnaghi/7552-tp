#ifndef ATRIBUTO_H_
#define ATRIBUTO_H_

#include <vector>
#include <algorithm>
#include "Componente.h"
#include "../../utils/Utils.h"
#include "../ConstantesModelo.h"
#include "../../excepciones/NullPointer.h"

class Atributo : public Componente {

private:
	// Modelo
	std::string tipo;
	std::string expresion;
	std::string cardinalidadMinima;
	std::string cardinalidadMaxima;
	std::vector<Atributo*> atributos;

	void borrarAtributos();

	// PERSISTENCIA COMP
	// void obtenerComponentesXmlCOMP(XmlNodo*);

	// GUARDAR
	void guardarAtributosDerivablesXmlCOMP(XmlNodo*);

protected:
	// PERSISTENCIA COMP
	// si hay que agregar más propiedades, se redefinen
	// virtual void obtenerPropiedadesXmlCOMP(XmlNodo*);

	// GUARDAR
	virtual void agregarPropiedadesXmlCOMP(XmlNodo*);
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

	void agregarAtributo(Atributo*) throw (NullPointer);
	void quitarAtributo(Atributo*) throw (NullPointer);

	std::vector<Atributo*>::iterator atributosBegin();
	std::vector<Atributo*>::iterator atributosEnd();

	// Devuelve true si tiene un atributo componente con ese nombre.
	bool existeAtributo(const std::string&);

	// PERSISTENCIA COMP
	/*
	Atributo(XmlNodo*);*/

	// GUARDAR
	virtual XmlNodo guardarXmlCOMP();
};

#endif /* ATRIBUTO_H_ */
