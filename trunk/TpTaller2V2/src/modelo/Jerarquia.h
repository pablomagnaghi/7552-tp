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
	// Modelo
	EntidadNueva * padre;
	std::vector<EntidadNueva *> hijos;

	// ?????
	std::string cobertura;
	std::string interseccion;

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

	// Hay que ver si van los gets y sets o se pone en el constructor
	void setEntidadGeneral(EntidadNueva *);
	EntidadNueva * getEntidadGeneral() const;

	void agregarEspecializada(EntidadNueva *);
	std::vector<EntidadNueva *>::iterator obtenerEntidadesEspecializadas();
	void quitarEspecializada(EntidadNueva *);

	std::string getCobertura() const;
	void setCobertura(const std::string&);

	std::string getInterseccion() const;
	void setInterseccion(const std::string&);

	// PERSISTENCIA COMP
	/*
	Jerarquia(XmlNodo*);
	virtual XmlNodo guardarXmlCOMP();
	*/
};

#endif /* JERARQUIA_H_ */
