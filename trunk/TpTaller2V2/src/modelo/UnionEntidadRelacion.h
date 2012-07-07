#ifndef ENTIDADRELACION_H_
#define ENTIDADRELACION_H_

#include "Entidad.h"
#include "Relacion.h"

#include <vector>
// Clase usada dentro de una Relacion para vincular
// una Entidad a su cardinalidad y a su rol.
// En el xsd aparece como "tipo_entidad_cardinalidad"

class Relacion;
class Entidad;

class UnionEntidadRelacion {

private:
	std::vector<Entidad *> entidades;
	Relacion * relacion;

	int codigoEntidad;
	std::string cardinalidadMinima;
	std::string cardinalidadMaxima;
	std::string rol;
	bool entidadGuardada;

public:
	UnionEntidadRelacion();
	virtual ~UnionEntidadRelacion();

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
