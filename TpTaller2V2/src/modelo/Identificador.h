/* Identificador.h
 *  Created on: 30/04/2012
 *      Author: Gonzalo Ferrero 89657
 */
#ifndef IDENTIFICADOR_H_
#define IDENTIFICADOR_H_

#include <vector>
#include <string>
#include "Atributo.h"

class Relacion;

class Identificador {

private:

	/* PERSITENCIA DER
	// void obtenerComponentesXmlDER(XmlNodo*);

	// void guardarAtributosXmlDER(XmlNodo*);
	// void guardarRelacionesXmlDER(XmlNodo*);
	 */

	std::vector<Atributo*> atributos;
	std::vector<Relacion*> relaciones;

public:

	Identificador();
	virtual ~Identificador();

	void agregarAtributo(Atributo*);
	void quitarAtributo(Atributo*);

	void agregarRelacion(Relacion*);
	void quitarRelacion(Relacion*);

	std::vector<Atributo*>::iterator atributosBegin();
	std::vector<Atributo*>::iterator atributosEnd();

	std::vector<Relacion*>::iterator relacionesBegin();
	std::vector<Relacion*>::iterator relacionesEnd();

	/* PERSISTENCIA DER
	// EntidadNueva ( XmlNodo* nodo);
	// XmlNodo guardarXmlDER();
	 */

};

#endif /* IDENTIFICADOR_H_ */
