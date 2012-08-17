/* Jerarquia.h
 *  Created on: 30/04/2012
 *      Author: Gonzalo Ferrero 89657
 */
#ifndef JERARQUIA_H_
#define JERARQUIA_H_

#include <vector>
#include <string>
#include "Entidad.h"
#include "EntidadNueva.h"
#include "Componente.h"
#include "../../excepciones/NullPointer.h"

// Persistencia
#include "../persistencia/Persistencia.h"

class EntidadNueva;

class Jerarquia : public Componente {

private:
	// Modelo
	Entidad * entidadGeneral;
	std::vector<EntidadNueva *> entidadesEspecializadas;
	std::string cobertura; // Esta en el enunciado: total, parcial.
	std::string interseccion; // Esta en el enunciado: exclusiva, superpuesta.

	int codigoEntidadGeneral;
	std::vector<int> codigosEntidadesEspecializadas;

	// PERSISTENCIA COMP
	// CARGAR
	void obtenerComponentesXmlCOMP(XmlNodo*);

	// GUARDAR
	void agregarCodigoEntidadGeneralXmlCOMP(XmlNodo*);
	void agregarCodigosEntidadEspecializadasXmlCOMP(XmlNodo*);

protected:
	// PERSITENCIA COMP
	// si hay que agregar más propiedades, se redefinen

	// CARGAR
	virtual void obtenerPropiedadesXmlCOMP(XmlNodo*);

	// GUARDAR
	virtual void agregarPropiedadesXmlCOMP(XmlNodo*);

public:
	Jerarquia();
	virtual ~Jerarquia();

	// Hay que ver si van los gets y sets o se pone en el constructor
	void setEntidadGeneral(Entidad *) throw (NullPointer);
	Entidad * getEntidadGeneral() const;

	void agregarEntidadEspecializada(EntidadNueva *) throw (NullPointer);
	void quitarEntidadEspecializada(EntidadNueva *) throw (NullPointer);
	std::vector<EntidadNueva *>::iterator entidadesEspecializadasBegin();
	std::vector<EntidadNueva *>::iterator entidadesEspecializadasEnd();

	std::vector<int>::iterator codigosEntidadesEspecializadasBegin();
	std::vector<int>::iterator codigosEntidadesEspecializadasEnd();

	std::string getCobertura() const;
	void setCobertura(const std::string&);

	std::string getInterseccion() const;
	void setInterseccion(const std::string&);

	int getCodigoEntidadGeneral();

	// PERSISTENCIA COMP
	// CARGAR
	Jerarquia(XmlNodo*);

	// GUARDAR
	virtual XmlNodo guardarXmlCOMP();
};

#endif /* JERARQUIA_H_ */
