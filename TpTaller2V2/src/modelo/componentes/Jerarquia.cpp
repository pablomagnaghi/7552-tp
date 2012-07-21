#include "Jerarquia.h"

Jerarquia::Jerarquia() {
	this->padre = NULL;
}

Jerarquia::~Jerarquia() {

}

std::string Jerarquia::getCobertura() const {
	return this->cobertura;
}

void Jerarquia::setCobertura(const std::string& cobertura) {
	this->cobertura = cobertura;
}

std::string Jerarquia::getInterseccion() const {
	return this->interseccion;
}

void Jerarquia::setInterseccion(const std::string& interseccion) {
	this->interseccion = interseccion;
}

void Jerarquia::setEntidadGeneral(Entidad * entidadPadre) throw (NullPointer) {
	if (entidadPadre == NULL) {
		throw NullPointer("agregarEspecializada en Jerarquia");
	}
	this->padre = entidadPadre;
}

Entidad * Jerarquia::getEntidadGeneral() const {
	return this->padre;
}

void Jerarquia::agregarEspecializada(EntidadNueva * entidadHija) throw (NullPointer) {
	if (entidadHija == NULL) {
		throw NullPointer("agregarEspecializada en Jerarquia");
	}
	this->hijos.push_back(entidadHija);
}

std::vector<EntidadNueva *>::iterator Jerarquia::entidadesEspecializadasBegin() {
	return this->hijos.begin();
}

std::vector<EntidadNueva *>::iterator Jerarquia::entidadesEspecializadasEnd() {
	return this->hijos.end();
}

void Jerarquia::quitarEspecializada(EntidadNueva * entidad) throw (NullPointer) {

	if (entidad == NULL) {
		throw NullPointer("quitarEspecializada en Jerarquia");
	}
	remove(this->hijos.begin(), this->hijos.end(), entidad);

}

// PERSISTENCIA COMP
/*
 Jerarquia::Jerarquia(XmlNodo* nodo) {
 this->obtenerPropiedadesXmlCOMP(nodo);

 XmlNodo nodoAux = nodo->getHijo();

 this->obtenerComponentesXmlCOMP(&nodoAux);
 }

 void Jerarquia::obtenerPropiedadesXmlCOMP(XmlNodo* nodo) {
 Componente::obtenerPropiedadesXmlCOMP(nodo);
 this->cobertura = nodo->getPropiedad("cobertura");
 this->interseccion = nodo->getPropiedad("interseccion");
 }

 void Jerarquia::obtenerComponentesXmlCOMP(XmlNodo* nodo) {
 while (nodo->esValido()) {
 if (nodo->getNombre() == "entidad_general") {
 this->codigoEntidadGeneral = nodo->getContenidoInt();
 }
 if (nodo->getNombre() == "entidad_especializada") {
 this->codigosEntidadesEspecializadas.push_back(nodo->getContenidoInt());
 }
 *nodo = nodo->getHermano();
 }
 }

 void Jerarquia::agregarPropiedadesXmlCOMP(XmlNodo* nodo) {
 Componente::agregarPropiedadesXmlCOMP(nodo);
 nodo->setPropiedad("cobertura",this->cobertura);
 nodo->setPropiedad("interseccion",this->interseccion);
 }

 void Jerarquia::agregarCodigoEntidadGeneralXmlCOMP(XmlNodo* nodo) {
 XmlNodo nodoEntidadGeneral("entidad_general");
 nodoEntidadGeneral.setContenido(this->codigoEntidadGeneral);
 nodo->agregarHijo(nodoEntidadGeneral);
 }

 void Jerarquia::agregarCodigosEntidadEspecializadasXmlCOMP(XmlNodo* nodo) {
 std::vector<int>::iterator i;

 for(i = this->codigosEntidadesEspecializadas.begin(); i != this->codigosEntidadesEspecializadas.end(); ++i) {
 XmlNodo nodoEntidadEspecializada("entidad_especializada");
 nodoEntidadEspecializada.setContenido((*i));
 nodo->agregarHijo(nodoEntidadEspecializada);
 }
 }

 XmlNodo Jerarquia::guardarXmlCOMP() {
 XmlNodo nodo("jerarquia");

 this->agregarPropiedadesXmlCOMP(&nodo);
 this->agregarCodigoEntidadGeneralXmlCOMP(&nodo);
 this->agregarCodigosEntidadEspecializadasXmlCOMP(&nodo);

 return nodo;
 }
 */
