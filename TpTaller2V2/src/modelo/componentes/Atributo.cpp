#include "Atributo.h"

Atributo::Atributo() :
	cardinalidadMinima ("1"),
	cardinalidadMaxima ("1") {
	this->nombre = "Atributo";
}

Atributo::~Atributo() {
	this->borrarAtributos();
}

std::string Atributo::getTipo() const {
	return this->tipo;
}

void Atributo::setTipo(const std::string& tipo) {
	this->tipo = tipo;
}

std::string Atributo::getExpresion() const {
	return this->expresion;
}

void Atributo::setExpresion(const std::string& expresion) {
	this->expresion = expresion;
}

std::string Atributo::getCardinalidadMinima() const {
	return this->cardinalidadMinima;
}

void Atributo::setCardinalidadMinima(const std::string& cardinalidadMinima) {
	this->cardinalidadMinima = cardinalidadMinima;
}

std::string Atributo::getCardinalidadMaxima() const {
	return this->cardinalidadMaxima;
}

void Atributo::setCardinalidadMaxima(const std::string& cardinalidadMaxima) {
	this->cardinalidadMaxima = cardinalidadMaxima;
}

void Atributo::agregarAtributo(Atributo* atributo) throw (NullPointer) {
	if (atributo == NULL) {
		throw NullPointer("Puntero nulo en agregarAtributo en Atributo");
	}
	this->atributos.push_back(atributo);
}

void Atributo::quitarAtributo(Atributo* atributo) throw (NullPointer) {
	if (atributo == NULL) {
		throw NullPointer("Puntero nulo en quitarAtributo en Atributo");
	}
	remove(this->atributos.begin(), this->atributos.end(), atributo);
}

std::vector<Atributo*>::iterator Atributo::atributosBegin() {
	return this->atributos.begin();
}

std::vector<Atributo*>::iterator Atributo::atributosEnd() {
	return this->atributos.end();
}

void Atributo::borrarAtributos() {
	std::vector<Atributo*>::iterator it = this->atributos.begin();
	while ( it != this->atributos.end() ) {
		delete (*it);
		it++;
	}
	this->atributos.clear();
}

bool Atributo::existeAtributo(const std::string& nombre){
	std::string nombreMin = toLowerCase(nombre);
	std::vector<Atributo*>::iterator it = this->atributos.begin();
	while (it != this->atributos.end()) {
		if (toLowerCase((*it)->getNombre()).compare(nombreMin) == 0) {
			return true;
		}
		it++;
	}
	return false;
}

// PERSISTENCIA COMP
// CARGAR
Atributo::Atributo(XmlNodo* nodo) {
	this->obtenerPropiedadesXmlCOMP(nodo);
	XmlNodo nodoAux = nodo->getHijo();
	this->obtenerComponentesXmlCOMP(&nodoAux);
}

void Atributo::obtenerPropiedadesXmlCOMP(XmlNodo* nodo) {
	Componente::obtenerPropiedadesXmlCOMP(nodo);

	this->tipo = nodo->getPropiedad("tipo");
	this->expresion = nodo->getPropiedad("expresion");
	this->cardinalidadMinima = nodo->getPropiedad("cardinalidad_minima");
	this->cardinalidadMaxima = nodo->getPropiedad("cardinalidad_maxima");
}

void Atributo::obtenerComponentesXmlCOMP(XmlNodo* nodo) {
	while (nodo->esValido()) {
		if (nodo->getNombre() == "atributo") {
	  		Atributo *atributo = new Atributo (nodo);
			this->agregarAtributo(atributo);
		}
		*nodo = nodo->getHermano();
	}
}

// GUARDAR
XmlNodo Atributo::guardarXmlCOMP() {
	XmlNodo nodo("atributo");

	this->agregarPropiedadesXmlCOMP(&nodo);
	this->guardarAtributosDerivablesXmlCOMP(&nodo);

	return nodo;
}

void Atributo::agregarPropiedadesXmlCOMP(XmlNodo* nodo) {
	Componente::agregarPropiedadesXmlCOMP(nodo);
	nodo->setPropiedad("tipo",this->tipo);
	// si son nulos los siguientes atributos, no se ponen
	if (this->expresion.size())
		nodo->setPropiedad("expresion",this->expresion);
	if (this->cardinalidadMinima.size() && this->cardinalidadMaxima.size())
		if (this->cardinalidadMinima != CARDINALIDAD_MINIMA || this->cardinalidadMaxima != CARDINALIDAD_MINIMA) {
			nodo->setPropiedad("cardinalidad_minima",this->cardinalidadMinima);
			nodo->setPropiedad("cardinalidad_maxima",this->cardinalidadMaxima);
		}
}

void Atributo::guardarAtributosDerivablesXmlCOMP(XmlNodo* nodo) {
	std::vector<Atributo*>::iterator i;

	for(i = this->atributosBegin(); i != this->atributosEnd(); ++i)
		nodo->agregarHijo((*i)->guardarXmlCOMP());
}
