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
	EntidadNueva* entidadGeneral;
	std::vector<EntidadNueva*> entidadesEspecializadas;
	std::string cobertura;
	std::string interseccion;

	void borrarEntidadesEspecializadas();

	// PERSISTENCIA COMP
	void obtenerComponentesXmlCOMP(XmlNodo*);

protected:
	// PERSITENCIA COMP
	// si hay que agregar más propiedades, se redefinen
	virtual void agregarPropiedadesXmlCOMP(XmlNodo* nodo);
	virtual void obtenerPropiedadesXmlCOMP(XmlNodo* nodo);

public:
	Jerarquia();
	virtual ~Jerarquia();

	EntidadNueva* getEntidadGeneral() const;
	void setEntidadGeneral(EntidadNueva*);

	void agregarEntidadEspecializada(EntidadNueva*);
	void quitarEntidadEspecializada(EntidadNueva*);

	std::string getCobertura() const;
	void setCobertura(const std::string);

	std::string getInterseccion() const;
	void setInterseccion(const std::string);

	std::vector<EntidadNueva*>::iterator entidadesEspecializadasBegin();
	std::vector<EntidadNueva*>::iterator entidadesEspecializadasEnd();

	// PERSISTENCIA COMP
	Jerarquia(XmlNodo*);
	virtual XmlNodo guardarXmlCOMP();
};

#endif /* JERARQUIA_H_ */
