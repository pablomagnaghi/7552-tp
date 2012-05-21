/*
 * EntidadRelacion.h
 *
 *  Created on: 20/05/2012
 */

#ifndef ENTIDADRELACION_H_
#define ENTIDADRELACION_H_

#include "Entidad.h"

/**
 * Clase usada dentro de una Relacion para vincular
 * una Entidad a su cardinalidad y a su rol.
 *
 * En el xsd aparece como "tipo_entidad_cardinalidad"
 */
class EntidadRelacion {

private:

	Entidad* entidad;
	// TODO esto tambien tiene que soportar entidades globales.
	// Sugerencia: hacer una clase EntidadNueva para la actual clase Entidad.
	// y que las clases EntidadNueva y EntidadGlobal hereden de Entidad.
	std::string cardinalidadMinima;
	std::string cardinalidadMaxima;
	std::string rol;

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

};

#endif /* ENTIDADRELACION_H_ */
