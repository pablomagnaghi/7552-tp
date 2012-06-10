/* Entidad.h
 *  Created on: 30/04/2012
 *      Author: Gonzalo Ferrero 89657
 */
#ifndef ENTIDAD_H_
#define ENTIDAD_H_

#include <vector>
#include <algorithm>
#include "Componente.h"
#include "Atributo.h"

class Relacion;

class Entidad : public Componente {

protected:
	bool esDebil;
	std::vector<Relacion*> relaciones;
	std::vector<Atributo *> atributos;

	/* PERSISTENCIA DER
	// void guardarRelacionesXmlDER(XmlNodo*);
	 */

public:

	virtual ~Entidad();

	void agregarRelacion(Relacion*);
	void quitarRelacion(Relacion*);

	std::vector<Relacion*>::iterator relacionesBegin();
	std::vector<Relacion*>::iterator relacionesEnd();

	Relacion* getRelacionByCodigo(int);

	void setEsDebil(bool esDebil);

	void agregarAtributo(Atributo * );
	void quitarAtributo(Atributo *);

};

#endif /* ENTIDAD_H_ */
