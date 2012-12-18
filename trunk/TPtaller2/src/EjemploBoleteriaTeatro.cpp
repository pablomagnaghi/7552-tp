/*
 * EjemploBoleteriaTeatro.cpp
 *
 *  Created on: 26/05/2012
 */

#include "modelo/HeadersModelo.h"
#include "modelo/validacion/ValidacionVisitor.h"
#include "modelo/validacion/MetricasVisitor.h"
#include <iostream>

EntidadNueva* crearSeccionSala(){
	EntidadNueva* seccionSala = new EntidadNueva();
	seccionSala->setNombre("SeccionSala");
	seccionSala->setCodigo(GeneradorCodigo::siguienteCodigo());
	seccionSala->setTipo(TIPO_ENTIDAD_COSA);

	Atributo* nroSecc = new Atributo();

	nroSecc->setNombre("nroSecc");
	nroSecc->setCodigo(GeneradorCodigo::siguienteCodigo());
	nroSecc->setTipo(TIPO_ATRIBUTO_CARACTERIZACION);
	seccionSala->agregarAtributo(nroSecc);

	Atributo* nomSecc = new Atributo();
	nomSecc->setNombre("nomSecc");
	nomSecc->setCodigo(GeneradorCodigo::siguienteCodigo());
	nomSecc->setTipo(TIPO_ATRIBUTO_CARACTERIZACION);
	seccionSala->agregarAtributo(nomSecc);

	Identificador* idNroSecc = new Identificador();
	idNroSecc->agregarCodigoAtributo(nroSecc->getCodigo());
	seccionSala->agregarIdentificador(idNroSecc);

	Identificador* idNomSecc = new Identificador();
	idNomSecc->agregarCodigoAtributo(nomSecc->getCodigo());
	seccionSala->agregarIdentificador(idNomSecc);

	return seccionSala;
}

EntidadNueva* crearLocalidad(){
	EntidadNueva* localidad = new EntidadNueva();
	localidad->setNombre("Localidad");
	localidad->setCodigo(GeneradorCodigo::siguienteCodigo());
	localidad->setTipo(TIPO_ENTIDAD_COSA);

	Atributo* fila = new Atributo();
	fila->setNombre("fila");
	fila->setCodigo(GeneradorCodigo::siguienteCodigo());
	fila->setTipo(TIPO_ATRIBUTO_CARACTERIZACION);
	localidad->agregarAtributo(fila);

	Atributo* nroButaca = new Atributo();
	nroButaca->setNombre("nroButaca");
	nroButaca->setCodigo(GeneradorCodigo::siguienteCodigo());
	nroButaca->setTipo(TIPO_ATRIBUTO_CARACTERIZACION);
	localidad->agregarAtributo(nroButaca);

	return localidad;
}

EntidadNueva* crearObra(){
	EntidadNueva* obra = new EntidadNueva();
	obra->setNombre("Obra");
	obra->setCodigo(GeneradorCodigo::siguienteCodigo());
	obra->setTipo(TIPO_ENTIDAD_COSA);

	Atributo* idObra = new Atributo();
	idObra->setNombre("idObra");
	idObra->setCodigo(GeneradorCodigo::siguienteCodigo());
	idObra->setTipo(TIPO_ATRIBUTO_CARACTERIZACION);
	obra->agregarAtributo(idObra);
	
	Atributo* titulo = new Atributo();
	titulo->setNombre("titulo");
	titulo->setCodigo(GeneradorCodigo::siguienteCodigo());
	titulo->setTipo(TIPO_ATRIBUTO_CARACTERIZACION);
	obra->agregarAtributo(titulo);

	Atributo* autor = new Atributo();
	autor->setNombre("autor");
	autor->setCodigo(GeneradorCodigo::siguienteCodigo());
	autor->setTipo(TIPO_ATRIBUTO_CARACTERIZACION);
	autor->setCardinalidadMaxima("n");
	obra->agregarAtributo(autor);

	Atributo* director = new Atributo();
	director->setNombre("director");
	director->setCodigo(GeneradorCodigo::siguienteCodigo());
	director->setTipo(TIPO_ATRIBUTO_CARACTERIZACION);
	director->setCardinalidadMaxima("n");
	obra->agregarAtributo(director);

	Atributo* genero = new Atributo();
	genero->setNombre("genero");
	genero->setCodigo(GeneradorCodigo::siguienteCodigo());
	genero->setTipo(TIPO_ATRIBUTO_CARACTERIZACION);
	obra->agregarAtributo(genero);

	Atributo* nroProxFunc = new Atributo();
	nroProxFunc->setNombre("nroProxFunc");
	nroProxFunc->setCodigo(GeneradorCodigo::siguienteCodigo());
	nroProxFunc->setTipo(TIPO_ATRIBUTO_CARACTERIZACION);
	obra->agregarAtributo(nroProxFunc);

	Identificador* idIdObra = new Identificador();
	idIdObra->agregarCodigoAtributo(idObra->getCodigo());
	obra->agregarIdentificador(idIdObra);

	Identificador* idTitulo = new Identificador();
	idTitulo->agregarCodigoAtributo(titulo->getCodigo());
	obra->agregarIdentificador(idTitulo);

	return obra;
}

EntidadNueva* crearFuncion(){
	EntidadNueva* funcion = new EntidadNueva();
	funcion->setNombre("Funcion");
	funcion->setCodigo(GeneradorCodigo::siguienteCodigo());
	funcion->setTipo(TIPO_ENTIDAD_COSA);

	Atributo* nroFunc = new Atributo();
	nroFunc->setNombre("nroFunc");
	nroFunc->setCodigo(GeneradorCodigo::siguienteCodigo());
	nroFunc->setTipo(TIPO_ATRIBUTO_CARACTERIZACION);
	funcion->agregarAtributo(nroFunc);

	Atributo* fecha = new Atributo();
	fecha->setNombre("fecha");
	fecha->setCodigo(GeneradorCodigo::siguienteCodigo());
	fecha->setTipo(TIPO_ATRIBUTO_CARACTERIZACION);
	funcion->agregarAtributo(fecha);

	Atributo* hora = new Atributo();
	hora->setNombre("hora");
	hora->setCodigo(GeneradorCodigo::siguienteCodigo());
	hora->setTipo(TIPO_ATRIBUTO_CARACTERIZACION);
	funcion->agregarAtributo(hora);

	// Le falta dos identificadores que se agregan despues cuando se crea FO

	return funcion;
}

Relacion* crearSL(EntidadNueva* seccionSala, EntidadNueva* localidad){
	Relacion* sL = new Relacion();
	sL->setNombre("SL");
	sL->setCodigo(GeneradorCodigo::siguienteCodigo());
	sL->setTipo(TIPO_RELACION_ASOCIACION);

	UnionEntidadRelacion* uerSeccionSala = new UnionEntidadRelacion(seccionSala, sL);
	uerSeccionSala->setCodigo(GeneradorCodigo::siguienteCodigo());
	uerSeccionSala->setCardinalidadMaxima("n");

	UnionEntidadRelacion* uerLocalidad = new UnionEntidadRelacion(localidad, sL);
	uerLocalidad->setCodigo(GeneradorCodigo::siguienteCodigo());

	// Busco el atributo nroButaca de Localidad para crear el identificador que le falta
	Atributo* nroButaca, *fila;
	std::vector<Atributo*>::iterator itAtributos = localidad->atributosBegin();
	while (itAtributos != localidad->atributosEnd()){
		if ((*itAtributos)->getNombre().compare("nroButaca") == 0){
			nroButaca = *itAtributos;
		}
		if ((*itAtributos)->getNombre().compare("fila") == 0){
			fila = *itAtributos;
		}
		itAtributos++;
	}

	Identificador* id = new Identificador();
	id->agregarCodigoAtributo(fila->getCodigo());
	id->agregarCodigoAtributo(nroButaca->getCodigo());
	id->agregarCodigoRelacion(sL->getCodigo());
	localidad->agregarIdentificador(id);

	return sL;
}

Relacion* crearVtaLoc(EntidadNueva* localidad, EntidadNueva* obra){
	Relacion* vtaLoc = new Relacion();
	vtaLoc->setNombre("VtaLoc");
	vtaLoc->setCodigo(GeneradorCodigo::siguienteCodigo());
	vtaLoc->setTipo(TIPO_RELACION_ASOCIACION);

	UnionEntidadRelacion* uerLocalidad = new UnionEntidadRelacion(localidad, vtaLoc);
	uerLocalidad->setCodigo(GeneradorCodigo::siguienteCodigo());
	uerLocalidad->setCardinalidadMinima("0");
	uerLocalidad->setCardinalidadMaxima("n");

	UnionEntidadRelacion* uerObra = new UnionEntidadRelacion(obra, vtaLoc);
	uerObra->setCodigo(GeneradorCodigo::siguienteCodigo());
	uerObra->setCardinalidadMinima("0");
	uerObra->setCardinalidadMaxima("n");

	Atributo* tarj = new Atributo();
	tarj->setNombre("tarj");
	tarj->setCodigo(GeneradorCodigo::siguienteCodigo());
	tarj->setCardinalidadMinima("0");
	tarj->setTipo(TIPO_ATRIBUTO_CARACTERIZACION);
	vtaLoc->agregarAtributo(tarj);

	Atributo* nomTarj = new Atributo();
	nomTarj->setNombre("nomTarj");
	nomTarj->setCodigo(GeneradorCodigo::siguienteCodigo());
	nomTarj->setTipo(TIPO_ATRIBUTO_CARACTERIZACION);
	tarj->agregarAtributo(nomTarj);

	Atributo* bco = new Atributo();
	bco->setNombre("bco");
	bco->setCodigo(GeneradorCodigo::siguienteCodigo());
	bco->setTipo(TIPO_ATRIBUTO_CARACTERIZACION);
	tarj->agregarAtributo(bco);
	
	Atributo* nroTarj = new Atributo();
	nroTarj->setNombre("nroTarj");
	nroTarj->setCodigo(GeneradorCodigo::siguienteCodigo());
	nroTarj->setTipo(TIPO_ATRIBUTO_CARACTERIZACION);
	tarj->agregarAtributo(nroTarj);

	Atributo* nroAutoriz = new Atributo();
	nroAutoriz->setNombre("nroAutoriz");
	nroAutoriz->setCodigo(GeneradorCodigo::siguienteCodigo());
	nroAutoriz->setTipo(TIPO_ATRIBUTO_CARACTERIZACION);
	tarj->agregarAtributo(nroAutoriz);

	Atributo* cr = new Atributo();
	cr->setNombre("cr");
	cr->setCodigo(GeneradorCodigo::siguienteCodigo());
	cr->setCardinalidadMinima("0");
	cr->setTipo(TIPO_ATRIBUTO_CARACTERIZACION);
	tarj->agregarAtributo(cr);

	Atributo* cuotas = new Atributo();
	cuotas->setNombre("cuotas");
	cuotas->setCodigo(GeneradorCodigo::siguienteCodigo());
	cuotas->setTipo(TIPO_ATRIBUTO_CARACTERIZACION);
	cr->agregarAtributo(cuotas);

	Atributo* atrInt = new Atributo();
	atrInt->setNombre("int");
	atrInt->setCodigo(GeneradorCodigo::siguienteCodigo());
	atrInt->setCardinalidadMinima("0");
	atrInt->setTipo(TIPO_ATRIBUTO_CALCULADO);
	atrInt->setExpresion("cuotas*0.1");
	cr->agregarAtributo(atrInt);

	return vtaLoc;
}

Relacion* crearFO(EntidadNueva* obra, EntidadNueva* funcion){
	Relacion* fO = new Relacion();
	fO->setNombre("FO");
	fO->setCodigo(GeneradorCodigo::siguienteCodigo());
	fO->setTipo(TIPO_RELACION_ASOCIACION);

	UnionEntidadRelacion* uerObra = new UnionEntidadRelacion(obra, fO);
	uerObra->setCodigo(GeneradorCodigo::siguienteCodigo());
	uerObra->setCardinalidadMinima("0");
	uerObra->setCardinalidadMaxima("n");

	UnionEntidadRelacion* uerFuncion = new UnionEntidadRelacion(funcion, fO);
	uerFuncion->setCodigo(GeneradorCodigo::siguienteCodigo());

	// Busco los atributos de Funcion para crear los identificadores que le faltan.
	Atributo *nroFunc, *fecha, *hora;
	std::vector<Atributo*>::iterator itAtributos = funcion->atributosBegin();
	while (itAtributos != funcion->atributosEnd()){
		if ((*itAtributos)->getNombre().compare("nroFunc") == 0){
			nroFunc = *itAtributos;
		}
		if ((*itAtributos)->getNombre().compare("fecha") == 0){
			fecha = *itAtributos;
		}
		if ((*itAtributos)->getNombre().compare("hora") == 0){
			hora = *itAtributos;
		}
		itAtributos++;
	}

	Identificador* id1 = new Identificador();
	id1->agregarCodigoAtributo(nroFunc->getCodigo());
	id1->agregarCodigoRelacion(fO->getCodigo());
	funcion->agregarIdentificador(id1);

	Identificador* id2 = new Identificador();
	id2->agregarCodigoAtributo(fecha->getCodigo());
	id2->agregarCodigoAtributo(hora->getCodigo());
	id2->agregarCodigoRelacion(fO->getCodigo());
	funcion->agregarIdentificador(id2);

	return fO;
}

Diagrama* crearDiagramaPrincipal(){
	Diagrama* diagramaPrincipal = new Diagrama("boleteria teatro");

	EntidadNueva* seccionSala = crearSeccionSala();
	diagramaPrincipal->agregarEntidadNueva(seccionSala);

	EntidadNueva* localidad = crearLocalidad();
	diagramaPrincipal->agregarEntidadNueva(localidad);

	EntidadNueva* obra = crearObra();
	diagramaPrincipal->agregarEntidadNueva(obra);

	EntidadNueva* funcion = crearFuncion();
	diagramaPrincipal->agregarEntidadNueva(funcion);

	Relacion* sL = crearSL(seccionSala, localidad);
	diagramaPrincipal->agregarRelacion(sL);

	Relacion* vtaLoc = crearVtaLoc(localidad, obra);
	diagramaPrincipal->agregarRelacion(vtaLoc);

	Relacion* fO = crearFO(obra, funcion);
	diagramaPrincipal->agregarRelacion(fO);

	return diagramaPrincipal;
}

int main348(int argc, char* argv[]){

	Proyecto* proyecto = new Proyecto("BoleteriaTeatro");

	Diagrama* diagramaPrincipal = crearDiagramaPrincipal();
	proyecto->setDiagramaPrincipal(diagramaPrincipal);

	Diagrama* apsdok = new Diagrama("Asd");
	diagramaPrincipal->agregarDiagramaHijo(apsdok);

	// prueba persistencia
//	diagramaPrincipal->guardarDiagramaXmlCOMP("boleteria teatro.xml");
//	std::cout << "Generacion del xml OK" << std::endl;

	// prueba validacion
	ValidacionVisitor* validacionVisitor = new ValidacionVisitor();
	proyecto->accept(validacionVisitor);
	std::cout << "Validación finalizada." << std::endl;

	MetricasVisitor* metricasVisitor = new MetricasVisitor();
	proyecto->accept(metricasVisitor);
	std::cout << "Metricas finalizadas." << std::endl;

	delete proyecto;
	delete validacionVisitor;
	delete metricasVisitor;

	GeneradorCodigo::destruir();

	return 0;
}

