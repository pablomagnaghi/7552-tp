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
}

void MetricasVisitor::imprimirMetricasProyecto(){
	this->imprimirMensaje(" ");
	this->imprimirMensaje("Proyecto: " + this->proyecto->getNombre());
	this->imprimirMensaje(" Cantidad de diagramas del proyecto: " + Utils::intToString(this->cantidadDiagramas));
	this->imprimirMensaje(" Cantidad de componentes promedio por diagrama: " + Utils::floatToString(this->calcularComponentesPromedio()));
	this->imprimirMensaje(" Cantidad de entidades nuevas promedio por diagrama: " + Utils::floatToString(this->calcularEntidadesNuevasPromedio()));
	this->imprimirMensaje(" Cantidad de entidades globales promedio por diagrama: " + Utils::floatToString(this->calcularEntidadesGlobalesPromedio()));
	this->imprimirMensaje(" Cantidad de relaciones promedio por diagrama: " + Utils::floatToString(this->calcularRelacionesPromedio()));
	this->imprimirMensaje(" Cantidad de jerarquias promedio por diagrama: " + Utils::floatToString(this->calcularJerarquiasPromedio()));
}

void MetricasVisitor::imprimirMetricasDiagrama(Diagrama* diagrama){
	this->imprimirMensaje(" ");
	this->imprimirMensaje("Diagrama: " + diagrama->getNombre());
	this->imprimirMensaje(" Cantidad de componentes: " + Utils::intToString(this->cantidadComponentes[diagrama->getNombre()]));
	this->imprimirMensaje(" Cantidad de entidades nuevas: " + Utils::intToString(this->cantidadEntidadesNuevas[diagrama->getNombre()]));
	this->imprimirMensaje(" Cantidad de entidades globales: " + Utils::intToString(this->cantidadEntidadesGlobales[diagrama->getNombre()]));
	this->imprimirMensaje(" Cantidad de relaciones: " + Utils::intToString(this->cantidadRelaciones[diagrama->getNombre()]));
	this->imprimirMensaje(" Cantidad de jerarquías: " + Utils::intToString(this->cantidadJerarquias[diagrama->getNombre()]));
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
}

void MetricasVisitor::visit(EntidadGlobal* entidadGlobal){
	this->cantidadComponentes[this->diagrama->getNombre()]++;
	this->cantidadEntidadesGlobales[this->diagrama->getNombre()]++;
}

void MetricasVisitor::visit(Atributo* atributo){

}

void MetricasVisitor::visit(Identificador* identificador){

}

void MetricasVisitor::visit(Relacion* relacion){
	this->cantidadComponentes[this->diagrama->getNombre()]++;
	this->cantidadRelaciones[this->diagrama->getNombre()]++;
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

float MetricasVisitor::calcularComponentesPromedio(){
	int total = 0;
	std::map<std::string, int>::iterator it = this->cantidadComponentes.begin();
	while(it != this->cantidadComponentes.end()){
		total += it->second;
		it++;
	}
	return (float) total / this->cantidadDiagramas;
}

float MetricasVisitor::calcularEntidadesNuevasPromedio(){
	int total = 0;
	std::map<std::string, int>::iterator it = this->cantidadEntidadesNuevas.begin();
	while(it != this->cantidadEntidadesNuevas.end()){
		total += it->second;
		it++;
	}
	return (float) total / this->cantidadDiagramas;
}

float MetricasVisitor::calcularEntidadesGlobalesPromedio(){
	int total = 0;
	std::map<std::string, int>::iterator it = this->cantidadEntidadesGlobales.begin();
	while(it != this->cantidadEntidadesGlobales.end()){
		total += it->second;
		it++;
	}
	return (float) total / this->cantidadDiagramas;
}

float MetricasVisitor::calcularRelacionesPromedio(){
	int total = 0;
	std::map<std::string, int>::iterator it = this->cantidadRelaciones.begin();
	while(it != this->cantidadRelaciones.end()){
		total += it->second;
		it++;
	}
	return (float) total / this->cantidadDiagramas;
}

float MetricasVisitor::calcularJerarquiasPromedio(){
	int total = 0;
	std::map<std::string, int>::iterator it = this->cantidadJerarquias.begin();
	while(it != this->cantidadJerarquias.end()){
		total += it->second;
		it++;
	}
	return (float) total / this->cantidadDiagramas;
}

