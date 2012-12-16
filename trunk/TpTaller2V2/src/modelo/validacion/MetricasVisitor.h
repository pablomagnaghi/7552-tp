/*
 * MetricasVisitor.h
 *
 *  Created on: 10/12/2012
 */

#ifndef METRICASVISITOR_H_
#define METRICASVISITOR_H_

#include <map>
#include "ModeloVisitor.h"

class MetricasVisitor: public ModeloVisitor {

private:

	int cantidadDiagramas;
	std::map<std::string, int> cantidadComponentes;
	std::map<std::string, int> cantidadEntidadesNuevas;
	std::map<std::string, int> cantidadEntidadesGlobales;
	std::map<std::string, int> cantidadRelaciones;
	std::map<std::string, int> cantidadJerarquias;

	void inicializar(Proyecto*);
	void inicializar(Diagrama*);
	void imprimirMetricasProyecto();
	void imprimirMetricasDiagrama(Diagrama*);

	float calcularComponentesPromedio();
	float calcularEntidadesNuevasPromedio();
	float calcularEntidadesGlobalesPromedio();
	float calcularRelacionesPromedio();
	float calcularJerarquiasPromedio();

public:

	MetricasVisitor();
	virtual ~MetricasVisitor();

	virtual void visit(Proyecto*);
	virtual void visit(Diagrama*);
	virtual void visit(EntidadNueva*);
	virtual void visit(EntidadGlobal*);
	virtual void visit(Atributo*);
	virtual void visit(Identificador*);
	virtual void visit(Relacion*);
	virtual void visit(Jerarquia*);
	virtual void visit(UnionEntidadRelacion*);

	virtual void postVisit(Proyecto*);
	virtual void postVisit(Diagrama*);
};

#endif /* METRICASVISITOR_H_ */

