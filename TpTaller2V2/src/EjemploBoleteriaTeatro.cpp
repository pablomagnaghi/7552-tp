/*
 * EjemploBoleteriaTeatro.cpp
 *
 *  Created on: 26/05/2012
 */

#include "modelo/Modelo.h"
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
	idNroSecc->agregarAtributo(nroSecc);
	seccionSala->agregarIdentificador(idNroSecc);

	Identificador* idNomSecc = new Identificador();
	idNomSecc->agregarAtributo(nomSecc);
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

	Identificador* id = new Identificador();
	id->agregarAtributo(fila);
	id->agregarAtributo(nroButaca);
	localidad->agregarIdentificador(id);

	// Le falta un identificador que se agrega despues, cuando se crea la relacion SL.

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
	idIdObra->agregarAtributo(idObra);
	obra->agregarIdentificador(idIdObra);

	Identificador* idTitulo = new Identificador();
	idTitulo->agregarAtributo(titulo);
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

	seccionSala->agregarRelacion(sL);
	localidad->agregarRelacion(sL);

	EntidadRelacion* erSeccionSala = new EntidadRelacion();
	erSeccionSala->setEntidad(seccionSala);
	erSeccionSala->setCardinalidadMaxima("n");
	sL->agregarEntidadRelacion(erSeccionSala);

	EntidadRelacion* erLocalidad = new EntidadRelacion();
	erLocalidad->setEntidad(localidad);
	sL->agregarEntidadRelacion(erLocalidad);

	// Busco el atributo nroButaca de Localidad para crear el identificador que le falta
	Atributo* nroButaca;
	std::vector<Atributo*>::iterator itAtributos = localidad->atributosBegin();
	while (itAtributos != localidad->atributosEnd()){
		if ((*itAtributos)->getNombre().compare("nroButaca") == 0){
			nroButaca = *itAtributos;
		}
		itAtributos++;
	}

	Identificador* id = new Identificador();
	id->agregarAtributo(nroButaca);
	id->agregarRelacion(sL);
	localidad->agregarIdentificador(id);

	return sL;
}

Relacion* crearVtaLoc(EntidadNueva* localidad, EntidadNueva* obra){
	Relacion* vtaLoc = new Relacion();
	vtaLoc->setNombre("VtaLoc");
	vtaLoc->setCodigo(GeneradorCodigo::siguienteCodigo());
	vtaLoc->setTipo(TIPO_RELACION_ASOCIACION);

	localidad->agregarRelacion(vtaLoc);
	obra->agregarRelacion(vtaLoc);

	EntidadRelacion* erLocalidad = new EntidadRelacion();
	erLocalidad->setEntidad(localidad);
	erLocalidad->setCardinalidadMinima("0");
	erLocalidad->setCardinalidadMaxima("n");
	vtaLoc->agregarEntidadRelacion(erLocalidad);

	EntidadRelacion* erObra = new EntidadRelacion();
	erObra->setEntidad(localidad);
	erObra->setCardinalidadMinima("0");
	erObra->setCardinalidadMaxima("n");
	vtaLoc->agregarEntidadRelacion(erObra);

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
	tarj->agregarAtributoDerivable(nomTarj);

	Atributo* bco = new Atributo();
	bco->setNombre("bco");
	bco->setCodigo(GeneradorCodigo::siguienteCodigo());
	bco->setTipo(TIPO_ATRIBUTO_CARACTERIZACION);
	tarj->agregarAtributoDerivable(bco);
	
	Atributo* nroTarj = new Atributo();
	nroTarj->setNombre("nroTarj");
	nroTarj->setCodigo(GeneradorCodigo::siguienteCodigo());
	nroTarj->setTipo(TIPO_ATRIBUTO_CARACTERIZACION);
	tarj->agregarAtributoDerivable(nroTarj);

	Atributo* nroAutoriz = new Atributo();
	nroAutoriz->setNombre("nroAutoriz");
	nroAutoriz->setCodigo(GeneradorCodigo::siguienteCodigo());
	nroAutoriz->setTipo(TIPO_ATRIBUTO_CARACTERIZACION);
	tarj->agregarAtributoDerivable(nroAutoriz);

	Atributo* cr = new Atributo();
	cr->setNombre("cr");
	cr->setCodigo(GeneradorCodigo::siguienteCodigo());
	cr->setCardinalidadMinima("0");
	cr->setTipo(TIPO_ATRIBUTO_CARACTERIZACION);
	tarj->agregarAtributoDerivable(cr);

	Atributo* cuotas = new Atributo();
	cuotas->setNombre("cuotas");
	cuotas->setCodigo(GeneradorCodigo::siguienteCodigo());
	cuotas->setTipo(TIPO_ATRIBUTO_CARACTERIZACION);
	cr->agregarAtributoDerivable(cuotas);

	Atributo* atrInt = new Atributo();
	atrInt->setNombre("int");
	atrInt->setCodigo(GeneradorCodigo::siguienteCodigo());
	atrInt->setCardinalidadMinima("0");
	atrInt->setTipo(TIPO_ATRIBUTO_CALCULADO);
	atrInt->setExpresion("cuotas*0.1");
	cr->agregarAtributoDerivable(atrInt);

	return vtaLoc;
}

Relacion* crearFO(EntidadNueva* obra, EntidadNueva* funcion){
	Relacion* fO = new Relacion();
	fO->setNombre("FO");
	fO->setCodigo(GeneradorCodigo::siguienteCodigo());
	fO->setTipo(TIPO_RELACION_ASOCIACION);

	obra->agregarRelacion(fO);
	funcion->agregarRelacion(fO);

	EntidadRelacion* erObra = new EntidadRelacion();
	erObra->setEntidad(obra);
	erObra->setCardinalidadMinima("0");
	erObra->setCardinalidadMaxima("n");
	fO->agregarEntidadRelacion(erObra);

	EntidadRelacion* erFuncion = new EntidadRelacion();
	erFuncion->setEntidad(funcion);
	fO->agregarEntidadRelacion(erFuncion);

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
	id1->agregarAtributo(nroFunc);
	id1->agregarRelacion(fO);
	funcion->agregarIdentificador(id1);

	Identificador* id2 = new Identificador();
	id2->agregarAtributo(fecha);
	id2->agregarAtributo(hora);
	id2->agregarRelacion(fO);
	funcion->agregarIdentificador(id2);

	return fO;
}

int main(int argc, char* argv[]){

	Proyecto* proyecto = new Proyecto("BoleteriaTeatro");

	Diagrama* diagramaPrincipal = new Diagrama("Principal");
	proyecto->setDiagramaPrincipal(diagramaPrincipal);

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

	delete proyecto;
	GeneradorCodigo::destruir();

	return 0;
}


