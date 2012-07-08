#ifndef ENTIDADRELACION_H_
#define ENTIDADRELACION_H_

#include "Entidad.h"
#include "Relacion.h"
#include "Componente.h"

#include <vector>

// Clase usada dentro de una Relacion para vincular
// una Entidad a su cardinalidad y a su rol.
// En el xsd aparece como "tipo_entidad_cardinalidad"

class Relacion;
class Entidad;

class UnionEntidadRelacion: public Componente {

private:
	// Modelo
	Entidad * entidades;
	Relacion * relacion;
	std::string cardinalidadMinima;
	std::string  cardinalidadMaxima;


	// Persistencia
	bool entidadGuardada;

public:
	UnionEntidadRelacion();
	virtual ~UnionEntidadRelacion();

	int getCodigoEntidad() const;
	void setCodigoEntidad(int);

	const std::string  getCardinalidadMinima() const;
	void setCardinalidadMinima(const std::string &);

	const std::string  getCardinalidadMaxima() const;
	void setCardinalidadMaxima(const std::string &);


	// PERSISTENCIA COMP
	/*
	 EntidadRelacion(XmlNodo*);
	 virtual XmlNodo guardarXmlCOMP();
	 */
};

#endif /* ENTIDADRELACION_H_ */
