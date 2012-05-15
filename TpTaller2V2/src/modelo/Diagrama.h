/* Diagrama.h
 *  Created on: 30/04/2012
 *      Author: Gonzalo Ferrero 89657
 */

#ifndef DIAGRAMA_H_
#define DIAGRAMA_H_

#include <iostream>
#include <vector>
#include <string>
#include "Entidad.h"
#include "EntidadGlobal.h"
#include "Relacion.h"
#include "Jerarquia.h"
#include "Componente.h"

class Diagrama {

protected:

	std::string nombre;
	Diagrama* diagramaAncestro;
	std::vector<Diagrama*> diagramasHijos;
	std::vector<Entidad*> entidades;
	std::vector<EntidadGlobal*> entidadesGlobales;
	std::vector<Relacion*> relaciones;
	std::vector<Jerarquia*> jerarquias;
	std::vector<Componente*> componentes;

	void agregarComponente(Componente*);
	void quitarComponente(Componente*);

public:

	Diagrama(std::string nombre);
	virtual ~Diagrama();

	void setNombre(std::string);
	std::string getNombre();

	void setDiagramaAncestro(Diagrama*);
	Diagrama* getDiagramaAncestro();

	void agregarDiagramaHijo(Diagrama*);
	void quitarDiagramaHijo(Diagrama*);

	void agregarEntidad(Entidad*);
	void quitarEntidad(Entidad*);

	void agregarEntidadGlobal(EntidadGlobal*);
	void quitarEntidadGlobal(EntidadGlobal*);

	void agregarRelacion(Relacion*);
	void quitarRelacion(Relacion*);

	void agregarJerarquia(Jerarquia*);
	void quitarJerarquia(Jerarquia*);

	std::vector<Componente*>::iterator componentesBegin();
	std::vector<Componente*>::iterator componentesEnd();

	std::vector<Diagrama*>::iterator diagramasHijosBegin();
	std::vector<Diagrama*>::iterator diagramasHijosEnd();

	Diagrama* crearDiagramaHijo(std::string);

};

#endif /* DIAGRAMA_H_ */
