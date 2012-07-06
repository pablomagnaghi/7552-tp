/*
 * EntidadRelacion.h
 *
 *  Created on: 20/05/2012
 */

#ifndef ENTIDADRELACION_H_
#define ENTIDADRELACION_H_

#include "Entidad.h"

// Clase usada dentro de una Relacion para vincular
// una Entidad a su cardinalidad y a su rol.
// En el xsd aparece como "tipo_entidad_cardinalidad"

class EntidadRelacion {

private:
	int codigoEntidad;
	std::string cardinalidadMinima;
	std::string cardinalidadMaxima;
	std::string rol;
	bool entidadGuardada;

public:
	EntidadRelacion();
	virtual ~EntidadRelacion();

	int getCodigoEntidad() const;
	void setCodigoEntidad(int);

	std::string getCardinalidadMinima() const;
	void setCardinalidadMinima(const std::string&);

	std::string getCardinalidadMaxima() const;
	void setCardinalidadMaxima(const std::string&);

	std::string getRol() const;
	void setRol(const std::string&);

	// PERSISTENCIA COMP
	/*
	EntidadRelacion(XmlNodo*);
	virtual XmlNodo guardarXmlCOMP();
	*/
};

#endif /* ENTIDADRELACION_H_ */
