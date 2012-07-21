#ifndef ATRIBUTO_H_
#define ATRIBUTO_H_

#include <vector>
#include <algorithm>
#include "Componente.h"
#include "ConstantesModelo.h"

class Atributo : public Componente {

private:
	// Modelo
	std::string tipo;
	std::string nombre;
	std::string cardinalidadMinima;
	std::string cardinalidadMaxima;

	std::vector<Atributo*> atributosDerivables;



	// PERSISTENCIA COMP
	/*
	void obtenerComponentesXmlCOMP(XmlNodo*);
	void guardarAtributosDerivablesXmlCOMP(XmlNodo*);
	*/

protected:
	// PERSISTENCIA COMP
	// si hay que agregar más propiedades, se redefinen
	/*
	virtual void agregarPropiedadesXmlCOMP(XmlNodo*);
	virtual void obtenerPropiedadesXmlCOMP(XmlNodo*);
	*/
public:
	Atributo();
	virtual ~Atributo();

	std::string getTipo() const;
	void setTipo(const std::string&);

	std::string getNombre() const;
	void setNombre(const std::string&);

	std::string getCardinalidadMinima() const;
	void setCardinalidadMinima(const std::string&);

	std::string getCardinalidadMaxima() const;
	void setCardinalidadMaxima(const std::string&);

	// PERSISTENCIA COMP
	/*
	Atributo(XmlNodo*);
	virtual XmlNodo guardarXmlCOMP();
	*/
};

#endif /* ATRIBUTO_H_ */
