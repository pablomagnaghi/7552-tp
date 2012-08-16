#include "Componente.h"

Componente::Componente(int codigo, const std::string &nombre) {
	this->codigo = codigo;
	this->nombre = nombre;
}

Componente::~Componente() {
}

int Componente::getCodigo() const {
	return codigo;
}

void Componente::setCodigo(int codigo) {
	if(codigo < 0){
		throw ArgumentoInvalido("El codigo del componente no puede ser negativo");
	}
	this->codigo = codigo;
}

std::string Componente::getNombre() const {
	return nombre;
}

void Componente::setNombre(const std::string& nombre) {
	this->nombre = nombre;
}

// PERSISTENCIA COMP

// CARGAR

void Componente::obtenerPropiedadesXmlCOMP(XmlNodo* nodo) {
	this->codigo = nodo->getPropiedadInt("codigo");
	this->nombre = nodo->getPropiedad("nombre");
}

// GUARDAR
void Componente::agregarPropiedadesXmlCOMP(XmlNodo* nodo) {
	nodo->setPropiedad("codigo",this->codigo);
	if (this->nombre.size())
		nodo->setPropiedad("nombre",this->nombre);
}

