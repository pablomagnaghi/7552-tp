/*
 * EntidadNueva.h
 *
 *  Created on: 25/05/2012
 */

#ifndef ENTIDADNUEVA_H_
#define ENTIDADNUEVA_H_

#include <string>
#include "Entidad.h"
#include "Atributo.h"
#include "Identificador.h"
#include "Jerarquia.h"

// Persistencia
#include "persistencia/Persistencia.h"

class Jerarquia;

class EntidadNueva : public Entidad {

private:

	std::string tipo;
	std::vector<Atributo*> atributos;
	std::vector<Jerarquia*> jerarquias;
	std::vector<Identificador*> identificadores;

	void borrarAtributos();
	void borrarIdentificadores();
	void borrarJerarquias();
	void borrarRelaciones();

	// PERSITENCIA COMP
	void obtenerComponentesXmlCOMP(XmlNodo*);

	void guardarAtributosXmlCOMP(XmlNodo*);
	void guardarIdentificadoresXmlCOMP(XmlNodo*);
	void guardarJerarquiasXmlCOMP(XmlNodo*);

	// Agrega los atributos y relaciones a los vectores de
	// atributos y relaciones del identificador
	void obtenerComponentesIdentificadorXmlCOMP(Identificador*, XmlNodo*);
	Atributo* obtenerAtributo(int codigo);

	std::vector<int> codigoIdentificador;



protected:
	// PERSISTENCIA COMP
	// si hay que agregar más propiedades, se redefinen
	virtual void agregarPropiedadesXmlCOMP(XmlNodo*);
	virtual void obtenerPropiedadesXmlCOMP(XmlNodo*);

public:

	EntidadNueva();
	virtual ~EntidadNueva();

	std::string getTipo() const;
	void setTipo(const std::string& tipo);

	void agregarAtributo(Atributo*);
	void quitarAtributo(Atributo*);

	void agregarJerarquia(Jerarquia*);
	void quitarJerarquia(Jerarquia*);

	void agregarIdentificador(Identificador*);
	void quitarIdentificador(Identificador*);

	std::vector<Atributo*>::iterator atributosBegin();
	std::vector<Atributo*>::iterator atributosEnd();

	std::vector<Jerarquia*>::iterator jerarquiasBegin();
	std::vector<Jerarquia*>::iterator jerarquiasEnd();

	std::vector<Identificador*>::iterator identificadoresBegin();
	std::vector<Identificador*>::iterator identificadoresEnd();

	std::vector<int>::iterator codigoIdentificadorBegin();	// Persistencia
	std::vector<int>::iterator codigoIdentificadorEnd();	// Persistencia

	Atributo* getAtributoByCodigo(int);

	// PERSISTENCIA COMP
	EntidadNueva(XmlNodo* nodo);
	XmlNodo guardarXmlCOMP();
};

#endif /* ENTIDADNUEVA_H_ */
