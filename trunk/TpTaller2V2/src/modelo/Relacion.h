/* Relacion.h
 *  Created on: 30/04/2012
 *      Author: Gonzalo Ferrero 89657
 */
#ifndef RELACION_H_
#define RELACION_H_

#include <vector>
#include <string>
#include "EntidadRelacion.h"
#include "Atributo.h"
#include "Componente.h"

class Entidad;

class Relacion : public Componente {

private:

	std::string tipo;
	std::vector<EntidadRelacion*> entidadesRelacion;
	std::vector<Atributo*> atributos;

	void borrarAtributos();
	void borrarEntidadesRelacion();

	/* PERSISTENCIA DER
	// void obtenerComponentesXmlDER (XmlNodo*);
	// void guardarEntidadesRelacionesXmlDER(XmlNodo *nodo);
	// void guardarAtritbutosXmlDER(XmlNodo *nodo);
	*/

protected:
	/* PERSISTENCIA DER
	// si hay que agregar más propiedades, se redefinen
	// virtual void agregarPropiedadesXmlDER (XmlNodo* nodo);
	// virtual void obtenerPropiedadesXmlDER (XmlNodo* nodo);
	 */

public:

	Relacion();
	virtual ~Relacion();

	std::string getTipo() const;
	void setTipo(const std::string tipo);

	void agregarEntidadRelacion(EntidadRelacion*);
	void quitarEntidadRelacion(EntidadRelacion*);

	void agregarAtributo(Atributo*);
	void quitarAtributo(Atributo*);

	std::vector<EntidadRelacion*>::iterator entidadesRelacionBegin();
	std::vector<EntidadRelacion*>::iterator entidadesRelacionEnd();

	std::vector<Atributo*>::iterator atributosBegin();
	std::vector<Atributo*>::iterator atributosEnd();


	/* PERSISTENCIA DER
	// Relacion(XmlNodo*);
	// virtual XmlNodo guardarXmlDER();
	 */
};

#endif /* RELACION_H_ */
