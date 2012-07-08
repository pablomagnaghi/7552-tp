#include "Proyecto.h"

Proyecto::Proyecto(Diagrama * diagrama) {
	this->diagramaPrincipal = diagrama;
}

Proyecto::Proyecto(const std::string& nombre)
	: nombre (nombre) {

}

Proyecto::~Proyecto() {
	delete this->diagramaPrincipal;
}

std::string Proyecto::getNombre() const{
	return this->nombre;
}

void Proyecto::setNombre(const std::string& nombre){
	this->nombre = nombre;
}

Diagrama* Proyecto::getDiagramaPrincipal(){
	return this->diagramaPrincipal;
}

void Proyecto::setDiagramaPrincipal(Diagrama* diagramaPrincipal){
	this->diagramaPrincipal = diagramaPrincipal;
}
