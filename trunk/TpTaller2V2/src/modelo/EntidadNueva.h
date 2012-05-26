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

class Jerarquia;

class EntidadNueva : public Entidad {

private:

	std::string tipo;
	std::vector<Atributo*> atributos;
	std::vector<Jerarquia*> jerarquias;
	std::vector<Identificador*> identificadores;

	void borrarAtributos();
	void borrarIdentificadores();

	/* PERSITENCIA DER
	void obtenerComponentesDER(XmlNodo*);

	void guardarComponentesXmlDER(XmlNodo*);
	void guardarIdentificadoresXmlDER(XmlNodo*);
	*/

	/*
	// si hay que agregar más propiedades, se redefinen
	// virtual void agregarPropiedadesDER (XmlNodo*);
	// virtual void obtenerPropiedadesDER (XmlNodo*);

	// si hay que agregar más atributos, se redefinen
	// Estos dos metodos estarian de mas por ahora
	// virtual void agregarAtributosDER (XmlNodo*);
	// virtual void obtenerAtributosDER (XmlNodo*);
	*/

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

	// Entidad ( XmlNodo* nodo);
	// XmlNodo guardarXmlDER();

};

#endif /* ENTIDADNUEVA_H_ */
