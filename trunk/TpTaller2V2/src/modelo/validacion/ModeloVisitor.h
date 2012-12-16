/*
 * ModeloVisitor.h
 *
 *  Created on: 04/11/2012
 */

#ifndef MODELOVISITOR_H_
#define MODELOVISITOR_H_

#include <fstream>
#include "../../utils/Utils.h"
#include "../HeadersModelo.h"

class ModeloVisitor {

protected:

	Proyecto* proyecto;
	Diagrama* diagrama;
	std::fstream archivo;
	bool validacionTotal;

	void imprimirMensaje(std::string);

public:

	ModeloVisitor();
	virtual ~ModeloVisitor();

	virtual void visit(Proyecto*) = 0;
	virtual void visit(Diagrama*) = 0;
	virtual void visit(EntidadNueva*) = 0;
	virtual void visit(EntidadGlobal*) = 0;
	virtual void visit(Atributo*) = 0;
	virtual void visit(Identificador*) = 0;
	virtual void visit(Relacion*) = 0;
	virtual void visit(Jerarquia*) = 0;
	virtual void visit(UnionEntidadRelacion*) = 0;

	virtual void postVisit(Proyecto*) = 0;
	virtual void postVisit(Diagrama*) = 0;

	bool validarTotalmente();
};

#endif /* MODELOVISITOR_H_ */
