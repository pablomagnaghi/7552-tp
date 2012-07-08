#ifndef RELACION_H_
#define RELACION_H_

#include <vector>
#include <string>
#include "UnionEntidadRelacion.h"
#include "Atributo.h"
#include "Componente.h"

// Persistencia
#include "persistencia/Persistencia.h"

class UnionEntidadRelacion;

class Relacion : public Componente {

private:

	// Modelo
	std::string tipo; // ?????
	std::vector<UnionEntidadRelacion*> unionAEntidades;
	std::vector<Atributo*> atributos;

	void borrarAtributos();
	void borrarEntidadesRelacion();

	// PERSISTENCIA COMP
	/*
	void obtenerComponentesXmlCOMP(XmlNodo*);
	void guardarEntidadesRelacionesXmlCOMP(XmlNodo*);
	void guardarAtributosXmlCOMP(XmlNodo*);
	*/

protected:
	// PERSISTENCIA COMP
	// si hay que agregar más propiedades, se redefinen
	/*
	virtual void agregarPropiedadesXmlCOMP(XmlNodo*);
	virtual void obtenerPropiedadesXmlCOMP(XmlNodo*);
	*/

public:

	Relacion();
	virtual ~Relacion();

	std::string getTipo() const;
	void setTipo(const std::string&);


	// Modelo
	void agregarUnionAEntidad(UnionEntidadRelacion*);
	void quitarUnionAEntidad(UnionEntidadRelacion*);

	void agregarAtributo(Atributo *);
	void quitarAtributo(Atributo *);



	std::vector<UnionEntidadRelacion*>::iterator entidadesRelacionBegin();
	std::vector<UnionEntidadRelacion*>::iterator entidadesRelacionEnd();

	std::vector<Atributo*>::iterator atributosBegin();
	std::vector<Atributo*>::iterator atributosEnd();

	// PERSISTENCIA COMP
	/*
	Relacion(XmlNodo*);
	virtual XmlNodo guardarXmlCOMP();
	*/
};

#endif /* RELACION_H_ */
