/*
 * Proyecto.h
 *
 *  Created on: 02/04/2012
 *      Author: Guagnini Enzo 88325
 */

#ifndef VISTAPROYECTO_H_
#define VISTAPROYECTO_H_

#include "VistaDiagrama.h"
#include <list>
#include <string>
#include "VistaConstantes.h"
#include "../modelo/Proyecto.h"
using namespace std;

class VistaDiagrama;

class VistaProyecto {
private:

	VistaDiagrama * diagramaPrincipal;
	Proyecto * proyecto;

	void diagramas_recur(VistaDiagrama* diag, list<VistaDiagrama*> & lista);

public:
	VistaProyecto(Proyecto * proyectoModelo);
	virtual ~VistaProyecto();
	void testCargarDiagramas();
	VistaDiagrama* getDiagramaPrincipal();

	void get_diagramas(list<VistaDiagrama*> & lista);

	void eliminarModelo();

	void setNombre(const std::string & nombre);
	std::string getNombre();

	void validarModelo();

	void obtenerEstadoDiagramas(std::vector<std::string> & nombres,
			std::vector<std::string>& estado_modelo, std::vector<bool> & estado_vista);


	void obtenerMetricas();
};

#endif /* VISTAPROYECTO_H_ */
