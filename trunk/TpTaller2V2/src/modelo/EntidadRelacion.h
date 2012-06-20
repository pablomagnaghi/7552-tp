/*
 * EntidadRelacion.h
 *
 *  Created on: 20/05/2012
 */

#ifndef ENTIDADRELACION_H_
#define ENTIDADRELACION_H_

#include "Entidad.h"
#include "ConstantesModelo.h"

// Persistencia
#include "persistencia/Persistencia.h"

// Clase usada dentro de una Relacion para vincular
// una Entidad a su cardinalidad y a su rol.
// En el xsd aparece como "tipo_entidad_cardinalidad"

class Entidad;

class EntidadRelacion {

private:
	Entidad *entidad;
	std::string cardinalidadMinima;
	std::string cardinalidadMaxima;
	std::string rol;
	bool entidadGuardada;

public:

	EntidadRelacion();
	virtual ~EntidadRelacion();

	Entidad* getEntidad() const;
	void setEntidad(Entidad* entidad);

	std::string getCardinalidadMinima() const;
	void setCardinalidadMinima(const std::string cardinalidadMinima);

	std::string getCardinalidadMaxima() const;
	void setCardinalidadMaxima(const std::string cardinalidadMaxima);

	std::string getRol() const;
	void setRol(const std::string rol);

	// PERSISTENCIA COMP
	EntidadRelacion(XmlNodo*);
	virtual XmlNodo guardarXmlCOMP();
};

#endif /* ENTIDADRELACION_H_ */
