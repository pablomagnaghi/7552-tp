#ifndef ENTIDADNUEVA_H_
#define ENTIDADNUEVA_H_

#include <string>
#include "Entidad.h"
#include "Atributo.h"
#include "Identificador.h"
#include "UnionEntidadRelacion.h"
#include "Jerarquia.h"

class Jerarquia;

class EntidadNueva : public Entidad {

private:
	// Modelo
	std::string tipo; // ?????
	std::vector<Atributo*> atributos;
	std::vector<Identificador*> identificadores;
	std::vector<Jerarquia *> hijos;
	std::vector<Jerarquia *> padres;

	void borrarAtributos();
	void borrarIdentificadores();

	// PERSITENCIA COMP
	/*
	void obtenerComponentesXmlCOMP(XmlNodo*);

	void guardarAtributosXmlCOMP(XmlNodo*);
	void guardarIdentificadoresXmlCOMP(XmlNodo*);
	void guardarJerarquiasXmlCOMP(XmlNodo*);

	void guardarAtributosIdentificadorXmlCOMP(XmlNodo*, Identificador*);
	void guardarRelacionesIdentificadorXmlCOMP(XmlNodo*, Identificador*);
	XmlNodo guardarIdentificadorXmlCOMP();

	// Agrega los atributos y relaciones a los vectores de
	// atributos y relaciones del identificador
	void obtenerComponentesIdentificadorXmlCOMP(XmlNodo*, Identificador*);
	Atributo* obtenerAtributo(int codigo);
	*/

protected:
	// PERSISTENCIA COMP
	// si hay que agregar más propiedades, se redefinen
	/*
	virtual void agregarPropiedadesXmlCOMP(XmlNodo*);
	virtual void obtenerPropiedadesXmlCOMP(XmlNodo*);
	*/

public:
	EntidadNueva();
	virtual ~EntidadNueva();

	std::string getTipo() const;
	void setTipo(const std::string&);

	void agregarAtributo(Atributo*);
	void quitarAtributo(Atributo*);

	void agregarCodigoJerarquia(int);
	void quitarCodigoJerarquia(int);

	void agregarIdentificador(Identificador*);
	void quitarIdentificador(Identificador*);

	std::vector<Atributo*>::iterator atributosBegin();
	std::vector<Atributo*>::iterator atributosEnd();

	std::vector<Identificador*>::iterator identificadoresBegin();
	std::vector<Identificador*>::iterator identificadoresEnd();

	Atributo* getAtributoByCodigo(int);



	// PERSISTENCIA COMP
	/*
	EntidadNueva(XmlNodo*);
	XmlNodo guardarXmlCOMP();
	*/
};

#endif /* ENTIDADNUEVA_H_ */
