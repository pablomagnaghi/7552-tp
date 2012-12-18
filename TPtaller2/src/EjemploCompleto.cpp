/*
 * EjemploCompleto.cpp
 *
 *  Created on: 20/06/2012
 */

#include "modelo/HeadersModelo.h"
#include <iostream>

EntidadNueva* crearEntidadNuevaPapa(){
	EntidadNueva* entidadNuevaPapa = new EntidadNueva();
	entidadNuevaPapa->setNombre("EntidadNuevaPapa");
	entidadNuevaPapa->setCodigo(GeneradorCodigo::siguienteCodigo());
	entidadNuevaPapa->setTipo(TIPO_ENTIDAD_COSA);

	Atributo* idPapa = new Atributo();
	idPapa->setNombre("idPapa");
	idPapa->setCodigo(GeneradorCodigo::siguienteCodigo());
	idPapa->setTipo(TIPO_ATRIBUTO_CARACTERIZACION);
	entidadNuevaPapa->agregarAtributo(idPapa);

	Identificador* id = new Identificador();
	id->agregarCodigoAtributo(idPapa->getCodigo());
	entidadNuevaPapa->agregarIdentificador(id);

	return entidadNuevaPapa;
}

EntidadNueva* crearEntidadNuevaA(){
	EntidadNueva* entidadNuevaA = new EntidadNueva();
	entidadNuevaA->setNombre("EntidadNuevaA");
	entidadNuevaA->setCodigo(GeneradorCodigo::siguienteCodigo());
	entidadNuevaA->setTipo(TIPO_ENTIDAD_COSA);

	Atributo* idA = new Atributo();
	idA->setNombre("idA");
	idA->setCodigo(GeneradorCodigo::siguienteCodigo());
	idA->setTipo(TIPO_ATRIBUTO_CARACTERIZACION);
	entidadNuevaA->agregarAtributo(idA);

	Identificador* id = new Identificador();
	id->agregarCodigoAtributo(idA->getCodigo());
	entidadNuevaA->agregarIdentificador(id);

	return entidadNuevaA;
}

EntidadNueva* crearEntidadNuevaB(){
	EntidadNueva* entidadNuevaB = new EntidadNueva();
	entidadNuevaB->setNombre("entidadNuevaB");
	entidadNuevaB->setCodigo(GeneradorCodigo::siguienteCodigo());
	entidadNuevaB->setTipo(TIPO_ENTIDAD_COSA);

	Atributo* idB = new Atributo();
	idB->setNombre("idB");
	idB->setCodigo(GeneradorCodigo::siguienteCodigo());
	idB->setTipo(TIPO_ATRIBUTO_CARACTERIZACION);
	entidadNuevaB->agregarAtributo(idB);

	Identificador* id = new Identificador();
	id->agregarCodigoAtributo(idB->getCodigo());
	entidadNuevaB->agregarIdentificador(id);

	return entidadNuevaB;
}

Jerarquia* crearJerarquia(EntidadNueva* entidadNuevaPapa, EntidadNueva* entidadNuevaA, EntidadNueva* entidadNuevaB){
	Jerarquia* jerarquia = new Jerarquia();
	jerarquia->setCodigo(GeneradorCodigo::siguienteCodigo());
	jerarquia->setEntidadGeneral(entidadNuevaPapa);
	jerarquia->agregarEntidadEspecializada(entidadNuevaA);
	jerarquia->agregarEntidadEspecializada(entidadNuevaB);
	jerarquia->setCobertura(TIPO_COBERTURA_TOTAL);
	jerarquia->setInterseccion(TIPO_INTERSECCION_EXCLUSIVA);

	entidadNuevaPapa->setJerarquiaHija(jerarquia);
	entidadNuevaA->agregarJerarquiaPadre(jerarquia);
	entidadNuevaB->agregarJerarquiaPadre(jerarquia);

	return jerarquia;
}

EntidadGlobal* crearEntidadGlobalA(EntidadNueva* entidadNuevaA){
	EntidadGlobal* entidadGlobalA = new EntidadGlobal();
	entidadGlobalA->setNombre("entidadGlobalA");
	entidadGlobalA->setCodigo(GeneradorCodigo::siguienteCodigo());
	entidadGlobalA->setDiagramaAncestro("Principal");
	entidadGlobalA->setEntidadNueva(entidadNuevaA);

	return entidadGlobalA;
}

EntidadNueva* crearEntidadNuevaC(){
	EntidadNueva* entidadNuevaC = new EntidadNueva();
	entidadNuevaC->setNombre("entidadNuevaC");
	entidadNuevaC->setCodigo(GeneradorCodigo::siguienteCodigo());
	entidadNuevaC->setTipo(TIPO_ENTIDAD_COSA);

	Atributo* idC = new Atributo();
	idC->setNombre("idC");
	idC->setCodigo(GeneradorCodigo::siguienteCodigo());
	idC->setTipo(TIPO_ATRIBUTO_CARACTERIZACION);
	entidadNuevaC->agregarAtributo(idC);

	Identificador* id = new Identificador();
	id->agregarCodigoAtributo(idC->getCodigo());
	entidadNuevaC->agregarIdentificador(id);

	return entidadNuevaC;
}

Relacion* crearRelacion1(EntidadGlobal* entidadGlobalA, EntidadNueva* entidadNuevaC){
	Relacion* relacion1 = new Relacion();
	relacion1->setNombre("Relacion1");
	relacion1->setCodigo(GeneradorCodigo::siguienteCodigo());
	relacion1->setTipo(TIPO_RELACION_ASOCIACION);

	UnionEntidadRelacion* uerEntidadGlobalA = new UnionEntidadRelacion(entidadGlobalA, relacion1);
	uerEntidadGlobalA->setCodigo(GeneradorCodigo::siguienteCodigo());

	UnionEntidadRelacion* uerEntidadNuevaC = new UnionEntidadRelacion(entidadNuevaC, relacion1);
	uerEntidadNuevaC->setCodigo(GeneradorCodigo::siguienteCodigo());
	uerEntidadNuevaC->setCardinalidadMaxima("N");

	return relacion1;
}

Relacion* crearRelacion2(EntidadNueva* entidadNuevaC){
	Relacion* relacion2 = new Relacion();
	relacion2->setNombre("Relacion2");
	relacion2->setCodigo(GeneradorCodigo::siguienteCodigo());
	relacion2->setTipo(TIPO_RELACION_COMPOSICION);

	UnionEntidadRelacion* uerEntidadNuevaC1 = new UnionEntidadRelacion(entidadNuevaC, relacion2);
	uerEntidadNuevaC1->setCodigo(GeneradorCodigo::siguienteCodigo());
	uerEntidadNuevaC1->setCardinalidadMinima("0");

	UnionEntidadRelacion* uerEntidadNuevaC2 = new UnionEntidadRelacion(entidadNuevaC, relacion2);
	uerEntidadNuevaC2->setCodigo(GeneradorCodigo::siguienteCodigo());
	uerEntidadNuevaC2->setCardinalidadMinima("0");
	uerEntidadNuevaC2->setCardinalidadMaxima("N");

	return relacion2;
}

int main2(int argc, char* argv[]){

	Proyecto* proyecto = new Proyecto("Proyecto");

	Diagrama* diagramaPrincipal = new Diagrama("Principal");
	proyecto->setDiagramaPrincipal(diagramaPrincipal);
	
	EntidadNueva* entidadNuevaPapa = crearEntidadNuevaPapa();
	diagramaPrincipal->agregarEntidadNueva(entidadNuevaPapa);

	EntidadNueva* entidadNuevaA = crearEntidadNuevaA();
	diagramaPrincipal->agregarEntidadNueva(entidadNuevaA);

	EntidadNueva* entidadNuevaB = crearEntidadNuevaB();
	diagramaPrincipal->agregarEntidadNueva(entidadNuevaB);

	Jerarquia* jerarquia = crearJerarquia(entidadNuevaPapa, entidadNuevaA, entidadNuevaB);
	diagramaPrincipal->agregarJerarquia(jerarquia);

	Diagrama* diagramaHijo = new Diagrama("Hijo");
	diagramaPrincipal->agregarDiagramaHijo(diagramaHijo);
	diagramaHijo->setDiagramaAncestro(diagramaPrincipal);

	EntidadGlobal* entidadGlobalA = crearEntidadGlobalA(entidadNuevaA);
	diagramaHijo->agregarEntidadGlobal(entidadGlobalA);

	EntidadNueva* entidadNuevaC = crearEntidadNuevaC();
	diagramaHijo->agregarEntidadNueva(entidadNuevaC);

	Relacion* relacion1 = crearRelacion1(entidadGlobalA, entidadNuevaC);
	diagramaHijo->agregarRelacion(relacion1);

	Relacion* relacion2 = crearRelacion2(entidadNuevaC);
	diagramaHijo->agregarRelacion(relacion2);

	diagramaPrincipal->guardarDiagramaXmlCOMP("Principal.xml");
	diagramaHijo->guardarDiagramaXmlCOMP("Hijo.xml");

	std::cout << "OK" << std::endl;

	delete proyecto;
	GeneradorCodigo::destruir();

	return 0;
}

