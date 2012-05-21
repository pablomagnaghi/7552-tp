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

class Relacion : public Componente{

private:

	std::string tipo;
	std::vector<EntidadRelacion*> entidadesRelacion;
	std::vector<Atributo*> atributos;

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

};

#endif /* RELACION_H_ */
