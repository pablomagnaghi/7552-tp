/*
 * EjemploCreacion.cpp
 *
 *  Created on: 20/06/2012
 */

#include "modelo/Modelo.h"
#include <iostream>

EntidadNueva* crearEntidadA(){
	EntidadNueva* entidadA = new EntidadNueva();
	entidadA->setNombre("EntidadA");
	entidadA->setCodigo(GeneradorCodigo::siguienteCodigo());
	entidadA->setTipo(TIPO_ENTIDAD_COSA);

	Atributo* atributoA = new Atributo();
	atributoA->setNombre("atributoA");
	atributoA->setCodigo(GeneradorCodigo::siguienteCodigo());
	atributoA->setTipo(TIPO_ATRIBUTO_CARACTERIZACION);
	entidadA->agregarAtributo(atributoA);

	return entidadA;
}

EntidadNueva* crearEntidadB(){
	EntidadNueva* entidadB = new EntidadNueva();
	entidadB->setNombre("entidadB");
	entidadB->setCodigo(GeneradorCodigo::siguienteCodigo());
	entidadB->setTipo(TIPO_ENTIDAD_COSA);

	Atributo* atributoB = new Atributo();
	atributoB->setNombre("atributoB");
	atributoB->setCodigo(GeneradorCodigo::siguienteCodigo());
	atributoB->setTipo(TIPO_ATRIBUTO_CARACTERIZACION);
	entidadB->agregarAtributo(atributoB);

	return entidadB;
}

Relacion* crearRelacion(){
	Relacion* relacion = new Relacion();
	relacion->setNombre("Relacion");
	relacion->setCodigo(GeneradorCodigo::siguienteCodigo());
	relacion->setTipo(TIPO_RELACION_ASOCIACION);

	return relacion;
}

void cargarIdentificadoresEntidadA(EntidadNueva* entidadA, Diagrama* diagrama){
	// Del xml se van a ir leyendo los códigos de cada componente que conforma el identificador.
	// Por lo tanto los códigos 2 y 5; y si es atributo o relación se saben leyendo el xml.

	Atributo* atributoA = entidadA->getAtributoByCodigo(2);
	Relacion* relacion = diagrama->getRelacionByCodigo(5);

	Identificador* id = new Identificador();
	id->agregarAtributo(atributoA);
	id->agregarRelacion(relacion);
	entidadA->agregarIdentificador(id);
}

void cargarIdentificadoresEntidadB(EntidadNueva* entidadB){
	Atributo* atributoB = entidadB->getAtributoByCodigo(4);

	Identificador* id = new Identificador();
	id->agregarAtributo(atributoB);
	entidadB->agregarIdentificador(id);
}

void agregarRelacionAEntidadA(EntidadNueva* entidadA, Diagrama* diagrama){
	Relacion* relacion = diagrama->getRelacionByCodigo(5);
	entidadA->agregarRelacion(relacion);
}

void agregarRelacionAEntidadB(EntidadNueva* entidadB, Diagrama* diagrama){
	Relacion* relacion = diagrama->getRelacionByCodigo(5);
	entidadB->agregarRelacion(relacion);
}

void agregarEntidadesARelacion(Relacion* relacion, Diagrama* diagrama){
	EntidadRelacion* erEntidadA = new EntidadRelacion();
	erEntidadA->setEntidad(diagrama->getEntidadByCodigo(1)); // Carga la entidadA
	erEntidadA->setCardinalidadMaxima("n");
	relacion->agregarEntidadRelacion(erEntidadA);

	EntidadRelacion* erEntidadB = new EntidadRelacion();
	erEntidadB->setEntidad(diagrama->getEntidadByCodigo(3)); // Carga la entidadB
	relacion->agregarEntidadRelacion(erEntidadB);
}

int main4(int argc, char* argv[]){

	Diagrama* diagrama = new Diagrama("Principal");
	
	// 1ra pasada

		// Primero creo dos entidades, sin identificadores, solo con sus atributos
		EntidadNueva* entidadA = crearEntidadA();
		EntidadNueva* entidadB = crearEntidadB();
		diagrama->agregarEntidadNueva(entidadA);
		diagrama->agregarEntidadNueva(entidadB);

		// Creo la relacion vacia y la agrego al mapa
		Relacion* relacion = crearRelacion();
		diagrama->agregarRelacion(relacion);


	// 2da pasada, se usan los componentes que se cargaron en diagrama

		// Cargo los identificadores en cada entidad
		cargarIdentificadoresEntidadA(entidadA, diagrama);
		cargarIdentificadoresEntidadB(entidadB);

		// Agrego la relacion a las entidades
		agregarRelacionAEntidadA(entidadA, diagrama);
		agregarRelacionAEntidadB(entidadB, diagrama);

		// Agrego las entidades a la relacion
		agregarEntidadesARelacion(relacion, diagrama);

	delete entidadA;
	delete entidadB;
	delete relacion;
	GeneradorCodigo::destruir();

	return 0;
}
