#include "Proyecto.h"

Proyecto::Proyecto(Diagrama * diagrama) :
	diagramaPrincipal (diagrama) {

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

bool Proyecto::existeDiagrama(const std::string& nombre){
	std::string nombreMin = toLowerCase(nombre);
	if (this->diagramaPrincipal != NULL){
		return (toLowerCase(diagramaPrincipal->getNombre()).compare(nombreMin) == 0
				|| this->diagramaPrincipal->existeDiagrama(nombre));
	} else {
		return false;
	}
}

bool Proyecto::existeEntidadNueva(const std::string& nombre){
	if (this->diagramaPrincipal != NULL){
		return this->diagramaPrincipal->existeEntidadNueva(nombre);
	} else {
		return false;
	}
}

bool Proyecto::existeEntidadGlobal(const std::string& nombre){
	if (this->diagramaPrincipal != NULL) {
		return this->diagramaPrincipal->existeEntidadGlobal(nombre);
	} else {
		return false;
	}
}
