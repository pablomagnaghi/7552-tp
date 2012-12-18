/*
 * MetricasVisitor.cpp
 *
 *  Created on: 10/12/2012
 */

#include "MetricasVisitor.h"

MetricasVisitor::MetricasVisitor() {

}

MetricasVisitor::~MetricasVisitor() {

}

void MetricasVisitor::inicializar(Proyecto* proyecto){
	this->archivo.close();

	std::string nombreArchivo = proyecto->getNombre() + "-" + Utils::getDate() + "-Metricas";
	this->archivo.open(nombreArchivo.c_str(), std::fstream::out);

	this->proyecto = proyecto;
	this->validacionTotal = true;
	this->cantidadDiagramas = 0;
}

void MetricasVisitor::inicializar(Diagrama* diagrama){
	this->diagrama = diagrama;
	this->cantidadComponentes[diagrama->getNombre()] = 0;
	this->cantidadEntidadesNuevas[diagrama->getNombre()] = 0;
	this->cantidadEntidadesGlobales[diagrama->getNombre()] = 0;
	this->cantidadRelaciones[diagrama->getNombre()] = 0;
	this->cantidadJerarquias[diagrama->getNombre()] = 0;
	this->cantidadIdentificadores[diagrama->getNombre()] = 0;
	this->cantidadAtributosEntidadesNuevas[diagrama->getNombre()] = 0;
	this->cantidadIdentificadoresEntidadesNuevas[diagrama->getNombre()] = 0;
	this->cantidadAtributosRelaciones[diagrama->getNombre()] = 0;
	this->cantidadAtributosIdentificadores[diagrama->getNombre()] = 0;
	this->cantidadEntidadesSinRelacion[diagrama->getNombre()] = 0;
}

void MetricasVisitor::imprimirMetricasProyecto(){
	this->imprimirMensaje(" ");
	this->imprimirMensaje("Métricas generales del proyecto " + this->proyecto->getNombre() + ":");
	this->imprimirMensaje(" Cantidad de diagramas del proyecto: " + Utils::intToString(this->cantidadDiagramas));
	this->imprimirMensaje(" Cantidad promedio de componentes por diagrama: " + Utils::floatToString(this->calcularComponentesPromedio()));
	this->imprimirMensaje(" Cantidad promedio de entidades nuevas por diagrama: " + Utils::floatToString(this->calcularEntidadesNuevasPromedio()));
	this->imprimirMensaje(" Cantidad promedio de entidades globales por diagrama: " + Utils::floatToString(this->calcularEntidadesGlobalesPromedio()));
	if (this->cantidadDiagramas != 0){
		this->imprimirMensaje(" Cantidad promedio de relaciones por diagrama: " + Utils::floatToString(this->calcularRelacionesPromedio()));
		this->imprimirMensaje(" Cantidad promedio de jerarquias por diagrama: " + Utils::floatToString(this->calcularJerarquiasPromedio()));
	}
	if (this->getCantidadEntidadesNuevasTotal() != 0){
		this->imprimirMensaje(" Cantidad promedio de atributos por entidad nueva: "+ Utils::floatToString(this->calcularAtributosEntidadesNuevasPromedio()));
	}
	if (this->getCantidadEntidadesNuevasTotal() != 0){
		this->imprimirMensaje(" Cantidad promedio de identificadores por entidad nueva: " + Utils::floatToString(this->calcularIdentificadoresEntidadesNuevasPromedio()));
	}
	if (this->getCantidadRelacionesTotal() != 0){
		this->imprimirMensaje(" Cantidad promedio de atributos por relación: " + Utils::floatToString(this->calcularAtributosRelacionesPromedio()));
	}
	if (this->getCantidadIdentificadoresTotal() != 0){
		this->imprimirMensaje(" Cantidad promedio de atributos por identificador: " + Utils::floatToString(this->calcularAtributosIdentificadoresPromedio()));
	}
}

void MetricasVisitor::imprimirMetricasDiagrama(Diagrama* diagrama){
	this->imprimirMensaje(" ");
	this->imprimirMensaje("Métricas del diagrama " + diagrama->getNombre() + ":");

	this->imprimirMensaje(" Cantidad de componentes: " + Utils::intToString(this->cantidadComponentes[diagrama->getNombre()]));
	this->imprimirMensaje(" Cantidad de entidades nuevas: " + Utils::intToString(this->cantidadEntidadesNuevas[diagrama->getNombre()]));
	this->imprimirMensaje(" Cantidad de entidades globales: " + Utils::intToString(this->cantidadEntidadesGlobales[diagrama->getNombre()]));
	this->imprimirMensaje(" Cantidad de relaciones: " + Utils::intToString(this->cantidadRelaciones[diagrama->getNombre()]));
	this->imprimirMensaje(" Cantidad de jerarquías: " + Utils::intToString(this->cantidadJerarquias[diagrama->getNombre()]));

	if (this->cantidadEntidadesNuevas[diagrama->getNombre()] != 0){
		this->imprimirMensaje(" Cantidad promedio de atributos por entidad nueva: "
			+ Utils::floatToString( (float) this->cantidadAtributosEntidadesNuevas[diagrama->getNombre()] / this->cantidadEntidadesNuevas[diagrama->getNombre()]));
	}
	if (this->cantidadEntidadesNuevas[diagrama->getNombre()] != 0){
		this->imprimirMensaje(" Cantidad promedio de identificadores por entidad nueva: "
			+ Utils::floatToString( (float) this->cantidadIdentificadoresEntidadesNuevas[diagrama->getNombre()] / this->cantidadEntidadesNuevas[diagrama->getNombre()]));
	}
	if (this->cantidadRelaciones[diagrama->getNombre()] != 0){
		this->imprimirMensaje(" Cantidad promedio de atributos por relación: "
			+ Utils::floatToString( (float) this->cantidadAtributosRelaciones[diagrama->getNombre()] / this->cantidadRelaciones[diagrama->getNombre()]));
	}
	if (this->cantidadIdentificadores[diagrama->getNombre()] != 0){
		this->imprimirMensaje(" Cantidad promedio de atributos por identificador: "
			+ Utils::floatToString( (float) this->cantidadAtributosIdentificadores[diagrama->getNombre()] / this->cantidadIdentificadores[diagrama->getNombre()]));
	}

	if ( (this->cantidadEntidadesGlobales[diagrama->getNombre()] + this->cantidadEntidadesNuevas[diagrama->getNombre()]) != 0){
		this->imprimirMensaje(" Cohesión: " );
		this->imprimirMensaje("  Relación cantidad relaciones / cantidad entidades: "
			+ Utils::floatToString( (float) this->cantidadRelaciones[diagrama->getNombre()] /
			(this->cantidadEntidadesGlobales[diagrama->getNombre()] + this->cantidadEntidadesNuevas[diagrama->getNombre()])));
		this->imprimirMensaje("  Cantidad entidades sin ninguna relación: " + Utils::intToString(this->cantidadEntidadesSinRelacion[diagrama->getNombre()]));
	}

	if (this->cantidadEntidadesNuevas[diagrama->getNombre()] != 0){
		this->imprimirMensaje(" Acoplamiento: ");
		this->imprimirMensaje("  Relación cantidad entidades globales / cantidad entidades nuevas: "
			+ Utils::floatToString( (float) this->cantidadEntidadesGlobales[diagrama->getNombre()] / this->cantidadEntidadesNuevas[diagrama->getNombre()]));
	}
}

void MetricasVisitor::visit(Proyecto* proyecto){
	this->inicializar(proyecto);
}

void MetricasVisitor::visit(Diagrama* diagrama){
	this->inicializar(diagrama);
	this->cantidadDiagramas++;
}

void MetricasVisitor::visit(EntidadNueva* entidadNueva){
	this->cantidadComponentes[this->diagrama->getNombre()]++;
	this->cantidadEntidadesNuevas[this->diagrama->getNombre()]++;

	std::vector<Atributo*>::iterator itAtributos = entidadNueva->atributosBegin();
	while (itAtributos != entidadNueva->atributosEnd()){
		this->cantidadAtributosEntidadesNuevas[this->diagrama->getNombre()]++;
		itAtributos++;
	}

	std::vector<Identificador*>::iterator itIdentificadores = entidadNueva->identificadoresBegin();
	while (itIdentificadores != entidadNueva->identificadoresEnd()){
		this->cantidadIdentificadoresEntidadesNuevas[this->diagrama->getNombre()]++;
		itIdentificadores++;
	}

	if (entidadNueva->unionesARelacionBegin() == entidadNueva->unionesARelacionEnd()){
		this->cantidadEntidadesSinRelacion[this->diagrama->getNombre()]++;
	}
}

void MetricasVisitor::visit(EntidadGlobal* entidadGlobal){
	this->cantidadComponentes[this->diagrama->getNombre()]++;
	this->cantidadEntidadesGlobales[this->diagrama->getNombre()]++;

	if (entidadGlobal->unionesARelacionBegin() == entidadGlobal->unionesARelacionEnd()){
		this->cantidadEntidadesSinRelacion[this->diagrama->getNombre()]++;
	}
}

void MetricasVisitor::visit(Atributo* atributo){

}

void MetricasVisitor::visit(Identificador* identificador){
	this->cantidadIdentificadores[this->diagrama->getNombre()]++;

	std::vector<int>::iterator itAtributos = identificador->codigoAtributosBegin();
	while (itAtributos != identificador->codigoAtributosEnd()){
		this->cantidadAtributosIdentificadores[this->diagrama->getNombre()]++;
		itAtributos++;
	}
}

void MetricasVisitor::visit(Relacion* relacion){
	this->cantidadComponentes[this->diagrama->getNombre()]++;
	this->cantidadRelaciones[this->diagrama->getNombre()]++;

	std::vector<Atributo*>::iterator itAtributos = relacion->atributosBegin();
	while (itAtributos != relacion->atributosEnd()){
		this->cantidadAtributosRelaciones[this->diagrama->getNombre()]++;
		itAtributos++;
	}
}

void MetricasVisitor::visit(Jerarquia* jerarquia){
	this->cantidadComponentes[this->diagrama->getNombre()]++;
	this->cantidadJerarquias[this->diagrama->getNombre()]++;
}

void MetricasVisitor::visit(UnionEntidadRelacion* unionEntidadRelacion){

}

void MetricasVisitor::postVisit(Proyecto* proyecto){
	this->imprimirMetricasProyecto();
}

void MetricasVisitor::postVisit(Diagrama* diagrama){
	this->imprimirMetricasDiagrama(diagrama);
}

int MetricasVisitor::getCantidadComponentesTotal(){
	int total = 0;
	std::map<std::string, int>::iterator it = this->cantidadComponentes.begin();
	while(it != this->cantidadComponentes.end()){
		total += it->second;
		it++;
	}
	return total;
}

int MetricasVisitor::getCantidadEntidadesNuevasTotal(){
	int total = 0;
	std::map<std::string, int>::iterator it = this->cantidadEntidadesNuevas.begin();
	while(it != this->cantidadEntidadesNuevas.end()){
		total += it->second;
		it++;
	}
	return total;
}

int MetricasVisitor::getCantidadEntidadesGlobalesTotal(){
	int total = 0;
	std::map<std::string, int>::iterator it = this->cantidadEntidadesGlobales.begin();
	while(it != this->cantidadEntidadesGlobales.end()){
		total += it->second;
		it++;
	}
	return total;
}

int MetricasVisitor::getCantidadRelacionesTotal(){
	int total = 0;
	std::map<std::string, int>::iterator it = this->cantidadRelaciones.begin();
	while(it != this->cantidadRelaciones.end()){
		total += it->second;
		it++;
	}
	return total;
}

int MetricasVisitor::getCantidadJerarquiasTotal(){
	int total = 0;
	std::map<std::string, int>::iterator it = this->cantidadJerarquias.begin();
	while(it != this->cantidadJerarquias.end()){
		total += it->second;
		it++;
	}
	return total;
}

int MetricasVisitor::getCantidadIdentificadoresTotal(){
	int total = 0;
	std::map<std::string, int>::iterator it = this->cantidadIdentificadores.begin();
	while(it != this->cantidadIdentificadores.end()){
		total += it->second;
		it++;
	}
	return total;
}

float MetricasVisitor::calcularComponentesPromedio(){
	return (float) this->getCantidadComponentesTotal() / this->cantidadDiagramas;
}

float MetricasVisitor::calcularEntidadesNuevasPromedio(){
	return (float) this->getCantidadEntidadesNuevasTotal() / this->cantidadDiagramas;
}

float MetricasVisitor::calcularEntidadesGlobalesPromedio(){
	return (float) this->getCantidadEntidadesGlobalesTotal() / this->cantidadDiagramas;
}

float MetricasVisitor::calcularRelacionesPromedio(){
	return (float) this->getCantidadRelacionesTotal() / this->cantidadDiagramas;
}

float MetricasVisitor::calcularJerarquiasPromedio(){
	return (float) this->getCantidadJerarquiasTotal() / this->cantidadDiagramas;
}

float MetricasVisitor::calcularAtributosEntidadesNuevasPromedio(){
	int total = 0;
	std::map<std::string, int>::iterator it = this->cantidadAtributosEntidadesNuevas.begin();
	while(it != this->cantidadAtributosEntidadesNuevas.end()){
		total += it->second;
		it++;
	}
	return (float) total / this->getCantidadEntidadesNuevasTotal();
}

float MetricasVisitor::calcularIdentificadoresEntidadesNuevasPromedio(){
	return (float) this->getCantidadIdentificadoresTotal() / this->getCantidadEntidadesNuevasTotal();
}

float MetricasVisitor::calcularAtributosRelacionesPromedio(){
	int total = 0;
	std::map<std::string, int>::iterator it = this->cantidadAtributosRelaciones.begin();
	while(it != this->cantidadAtributosRelaciones.end()){
		total += it->second;
		it++;
	}
	return (float) total / this->getCantidadRelacionesTotal();
}

float MetricasVisitor::calcularAtributosIdentificadoresPromedio(){
	int total = 0;
	std::map<std::string, int>::iterator it = this->cantidadAtributosIdentificadores.begin();
	while(it != this->cantidadAtributosIdentificadores.end()){
		total += it->second;
		it++;
	}
	return (float) total / this->getCantidadIdentificadoresTotal();
}


