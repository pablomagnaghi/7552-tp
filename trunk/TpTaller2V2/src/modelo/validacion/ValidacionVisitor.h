/*
 * ValidacionVisitor.h
 *
 *  Created on: 05/11/2012
 */

#ifndef VALIDACIONVISITOR_H_
#define VALIDACIONVISITOR_H_

#include "ModeloVisitor.h"

class ValidacionVisitor : public ModeloVisitor {

private:

	void inicializar(Diagrama*);
	void imprimirMensaje(std::string);
	void invalidarDiagrama();

public:

	ValidacionVisitor();
	virtual ~ValidacionVisitor();

	virtual void visit(Diagrama*);
	virtual void visit(EntidadNueva*);
	virtual void visit(EntidadGlobal*);
	virtual void visit(Atributo*);
	virtual void visit(Identificador*);
	virtual void visit(Relacion*);
	virtual void visit(Jerarquia*);
	virtual void visit(UnionEntidadRelacion*);

};

#endif /* VALIDACIONVISITOR_H_ */
