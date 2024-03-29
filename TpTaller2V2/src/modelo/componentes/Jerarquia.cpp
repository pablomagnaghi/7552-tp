#include "Jerarquia.h"
#include "../validacion/ModeloVisitor.h"

Jerarquia::Jerarquia() :
		entidadGeneral(NULL) {
	this->nombre = "JERARQUIA";
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

void Jerarquia::setEntidadGeneral(Entidad * entidadGeneral) throw (NullPointer) {
	if (entidadGeneral == NULL) {
		throw NullPointer("Puntero nulo en setEntidadGeneral en Jerarquia");
	}
	this->entidadGeneral = entidadGeneral;
}

Entidad * Jerarquia::getEntidadGeneral() const {
	return this->entidadGeneral;
}

int Jerarquia::getCodigoEntidadGeneral() {
	return this->codigoEntidadGeneral;
}

void Jerarquia::agregarEntidadEspecializada(EntidadNueva * entidadEspecializada) throw (NullPointer) {
	if (entidadEspecializada == NULL) {
		throw NullPointer("Puntero nulo en agregarEntidadEspecializada en Jerarquia");
	}
	this->entidadesEspecializadas.push_back(entidadEspecializada);
}

std::vector<EntidadNueva *>::iterator Jerarquia::entidadesEspecializadasBegin() {
	return this->entidadesEspecializadas.begin();
}

std::vector<EntidadNueva *>::iterator Jerarquia::entidadesEspecializadasEnd() {
	return this->entidadesEspecializadas.end();
}

std::vector<int>::iterator Jerarquia::codigosEntidadesEspecializadasBegin() {
	return this->codigosEntidadesEspecializadas.begin();
}

std::vector<int>::iterator Jerarquia::codigosEntidadesEspecializadasEnd() {
	return this->codigosEntidadesEspecializadas.end();
}

void Jerarquia::quitarEntidadEspecializada(EntidadNueva * entidadEspecializada) throw (NullPointer) {
	if (entidadEspecializada == NULL) {
		throw NullPointer("Puntero nulo en quitarEntidadEspecializada en Jerarquia");
	}
	std::vector<EntidadNueva *>::iterator it_entidad;
	it_entidad = find(this->entidadesEspecializadas.begin(), this->entidadesEspecializadas.end(),
			entidadEspecializada);
	if (it_entidad != this->entidadesEspecializadas.end()) {
		this->entidadesEspecializadas.erase(it_entidad);
	}
}

// PERSISTENCIA COMP
// CARGAR
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

void Jerarquia::accept(ModeloVisitor* modeloVisitor) {
	modeloVisitor->visit(this);
}

// GUARDAR
XmlNodo Jerarquia::guardarXmlCOMP() {
	XmlNodo nodo("jerarquia");

	this->agregarPropiedadesXmlCOMP(&nodo);
	this->agregarCodigoEntidadGeneralXmlCOMP(&nodo);
	this->agregarCodigosEntidadEspecializadasXmlCOMP(&nodo);

	return nodo;
}

void Jerarquia::agregarPropiedadesXmlCOMP(XmlNodo* nodo) {
	Componente::agregarPropiedadesXmlCOMP(nodo);
	nodo->setPropiedad("cobertura", this->cobertura);
	nodo->setPropiedad("interseccion", this->interseccion);
}

void Jerarquia::agregarCodigoEntidadGeneralXmlCOMP(XmlNodo* nodo) {
	XmlNodo nodoEntidadGeneral("entidad_general");
	nodoEntidadGeneral.setContenido(this->entidadGeneral->getCodigo());
	nodo->agregarHijo(nodoEntidadGeneral);
}

void Jerarquia::agregarCodigosEntidadEspecializadasXmlCOMP(XmlNodo* nodo) {
	std::vector<EntidadNueva *>::iterator i;

	for (i = this->entidadesEspecializadasBegin(); i != this->entidadesEspecializadasEnd(); ++i) {
		XmlNodo nodoEntidadEspecializada("entidad_especializada");
		nodoEntidadEspecializada.setContenido((*i)->getCodigo());
		nodo->agregarHijo(nodoEntidadEspecializada);
	}
}
