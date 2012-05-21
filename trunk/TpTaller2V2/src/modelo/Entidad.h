/* Entidad.h
 *  Created on: 30/04/2012
 *      Author: Gonzalo Ferrero 89657
 */
#ifndef ENTIDAD_H_
#define ENTIDAD_H_

#include <vector>
#include <string>
#include <algorithm>
#include "Entidad.h"
#include "Atributo.h"
#include "Identificador.h"
#include "Componente.h"

class Jerarquia;
class Relacion;

class Entidad: public Componente {
private:
	/* PERSITENCIA DER
	void obtenerComponentesDER(XmlNodo*);

	void guardarComponentesXmlDER(XmlNodo*);
	void guardarIdentificadoresXmlDER(XmlNodo*);
	*/

protected:
	std::vector<Componente*> componentes;
	std::vector<Identificador*> identificadores;
	Entidad();
	std::string tipo;
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
	std::string getTipo() const;
	void setTipo(const std::string& tipo);

	// Entidad ( XmlNodo* nodo);

	// atributos
	void agregarComponente(Componente*);
	void quitarComponente(Componente*);

	std::vector<Componente*>::iterator componenteBegin();
	std::vector<Componente*>::iterator componenteEnd();

	void borrarComponentes();

	// identificadores
	void agregarIdentificador(Identificador*);
	void quitarIdentificador(Identificador*);

	std::vector<Identificador*>::iterator identificadorBegin();
	std::vector<Identificador*>::iterator identificadorEnd();

	void borrarIdentificadores();

	virtual ~Entidad();

	// XmlNodo guardarXmlDER();
};

#endif /* ENTIDAD_H_ */
