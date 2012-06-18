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

	// PERSITENCIA DER
	void obtenerComponentesXmlDER(XmlNodo*);

	void guardarAtributosXmlDER(XmlNodo*);
	void guardarIdentificadoresXmlDER(XmlNodo*);
	void guardarJerarquiasXmlDER(XmlNodo*);

protected:
	// PERSISTENCIA DER
	// si hay que agregar más propiedades, se redefinen
	virtual void agregarPropiedadesXmlDER (XmlNodo*);
	virtual void obtenerPropiedadesXmlDER (XmlNodo*);

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

	Atributo* getAtributoByCodigo(int);

	// PERSISTENCIA DER
	EntidadNueva ( XmlNodo* nodo);
	XmlNodo guardarXmlDER();
};

#endif /* ENTIDADNUEVA_H_ */
