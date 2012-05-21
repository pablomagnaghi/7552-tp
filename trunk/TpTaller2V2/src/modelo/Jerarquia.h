/* Jerarquia.h
 *  Created on: 30/04/2012
 *      Author: Gonzalo Ferrero 89657
 */
#ifndef JERARQUIA_H_
#define JERARQUIA_H_

#include <vector>
#include <string>
#include "Entidad.h"
#include "Componente.h"

class Entidad;

class Jerarquia : public Componente {

private:

	Entidad* entidadGeneral;
	std::vector<Entidad*> entidadesEspecializadas;
	std::string cobertura;
	std::string interseccion;

public:

	Jerarquia();
	virtual ~Jerarquia();

	Entidad* getEntidadGeneral() const;
	void setEntidadGeneral(Entidad*);

	void agregarEntidadEspecializada(Entidad*);
	void quitarEntidadEspecializada(Entidad*);

	std::string getCobertura() const;
	void setCobertura(const std::string);

	std::string getInterseccion() const;
	void setInterseccion(const std::string);

	std::vector<Entidad*>::iterator entidadesEspecializadasBegin();
	std::vector<Entidad*>::iterator entidadesEspecializadasEnd();

};

#endif /* JERARQUIA_H_ */
