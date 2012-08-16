#ifndef RELACION_H_
#define RELACION_H_

#include <vector>
#include <string>
#include "UnionEntidadRelacion.h"
#include "Atributo.h"
#include "Componente.h"
#include "../../excepciones/NullPointer.h"

// Persistencia
#include "../persistencia/Persistencia.h"

class UnionEntidadRelacion;

class Relacion : public Componente {

private:

	// Modelo
	std::string tipo; // Asociacion, composición.
	std::vector<UnionEntidadRelacion*> unionesAEntidad;
	std::vector<Atributo*> atributos;

	void borrarAtributos();
	void borrarUnionesAEntidad();

	// PERSISTENCIA COMP
	/*
	void obtenerComponentesXmlCOMP(XmlNodo*);
	*/
	// GUARDAR
	void guardarUnionEntidadRelacionXmlCOMP(XmlNodo*);
	void guardarAtributosXmlCOMP(XmlNodo*);

protected:
	// PERSISTENCIA COMP
	// si hay que agregar más propiedades, se redefinen
	/*
	virtual void obtenerPropiedadesXmlCOMP(XmlNodo*);
	*/

	// GUARDAR
	virtual void agregarPropiedadesXmlCOMP(XmlNodo*);

public:

	Relacion();
	virtual ~Relacion();

	std::string getTipo() const;
	void setTipo(const std::string&);

	void agregarUnionAEntidad(UnionEntidadRelacion*)throw (NullPointer);
	void quitarUnionAEntidad(UnionEntidadRelacion*)throw (NullPointer);
	std::vector<UnionEntidadRelacion*>::iterator unionesAEntidadBegin();
	std::vector<UnionEntidadRelacion*>::iterator unionesAEntidadEnd();

	void agregarAtributo(Atributo *)throw (NullPointer);
	void quitarAtributo(Atributo *)throw (NullPointer);
	std::vector<Atributo*>::iterator atributosBegin();
	std::vector<Atributo*>::iterator atributosEnd();

	// PERSISTENCIA COMP
	/*
	Relacion(XmlNodo*);
	*/
	// GUARDAR
	virtual XmlNodo guardarXmlCOMP();
};

#endif /* RELACION_H_ */
