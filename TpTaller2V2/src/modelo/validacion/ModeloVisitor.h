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

	Diagrama* diagrama;
	std::fstream archivo;

public:

	ModeloVisitor();
	virtual ~ModeloVisitor();

	virtual void visit(Diagrama*) = 0;
	virtual void visit(EntidadNueva*) = 0;
	virtual void visit(EntidadGlobal*) = 0;
	virtual void visit(Atributo*) = 0;
	virtual void visit(Identificador*) = 0;
	virtual void visit(Relacion*) = 0;
	virtual void visit(Jerarquia*) = 0;
	virtual void visit(UnionEntidadRelacion*) = 0;

};

#endif /* MODELOVISITOR_H_ */
