/* Jerarquia.h
 *  Created on: 30/04/2012
 *      Author: Gonzalo Ferrero 89657
 */
#ifndef JERARQUIA_H_
#define JERARQUIA_H_

#include <vector>
#include <string>
#include "EntidadNueva.h"
#include "Componente.h"

// Persistencia
#include "persistencia/Persistencia.h"

class EntidadNueva;

class Jerarquia : public Componente {

private:
	int codigoEntidadGeneral;
	std::vector<int> codigosEntidadesEspecializadas;
	std::string cobertura;
	std::string interseccion;

	void borrarEntidadesEspecializadas();

	// PERSISTENCIA COMP
	/*
	void obtenerComponentesXmlCOMP(XmlNodo*);
	void agregarCodigoEntidadGeneralXmlCOMP(XmlNodo*);
	void agregarCodigosEntidadEspecializadasXmlCOMP(XmlNodo*);
	*/

protected:
	// PERSITENCIA COMP
	// si hay que agregar más propiedades, se redefinen
	/*
	virtual void agregarPropiedadesXmlCOMP(XmlNodo*);
	virtual void obtenerPropiedadesXmlCOMP(XmlNodo*);
	*/

public:
	Jerarquia();
	virtual ~Jerarquia();

	int getCodigoEntidadGeneral() const;
	void setCodigoEntidadGeneral(int);

	void agregarCodigoEntidadEspecializada(int);
	void quitarCodigoEntidadEspecializada(int);

	std::string getCobertura() const;
	void setCobertura(const std::string&);

	std::string getInterseccion() const;
	void setInterseccion(const std::string&);

	std::vector<int>::iterator codigosEntidadesEspecializadasBegin();
	std::vector<int>::iterator codigosEntidadesEspecializadasEnd();

	// PERSISTENCIA COMP
	/*
	Jerarquia(XmlNodo*);
	virtual XmlNodo guardarXmlCOMP();
	*/
};

#endif /* JERARQUIA_H_ */
