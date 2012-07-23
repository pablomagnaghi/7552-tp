#ifndef ENTIDADRELACION_H_
#define ENTIDADRELACION_H_

#include "Entidad.h"
#include "Relacion.h"
#include "Componente.h"
#include <vector>

class Entidad;
class Relacion;

/**
 * Clase usada dentro de una Relacion para vincular una Entidad a su cardinalidad y a su rol.
 */
class UnionEntidadRelacion: public Componente {

private:
	// Modelo
	Entidad * entidad;
	Relacion * relacion;
	std::string cardinalidadMinima;
	std::string cardinalidadMaxima;
	std::string rol;

	// Persistencia
	bool entidadGuardada;

public:
	UnionEntidadRelacion(Entidad *, Relacion *);
	virtual ~UnionEntidadRelacion();

	const std::string  getCardinalidadMinima() const;
	void setCardinalidadMinima(const std::string &);

	const std::string  getCardinalidadMaxima() const;
	void setCardinalidadMaxima(const std::string &);

	const std::string getRol() const;
	void setRol(const std::string &);

	Entidad * getEntidad();
	Relacion * getRelacion();

	// PERSISTENCIA COMP
	/*
	 EntidadRelacion(XmlNodo*);
	 virtual XmlNodo guardarXmlCOMP();
	 */
};

#endif /* ENTIDADRELACION_H_ */
