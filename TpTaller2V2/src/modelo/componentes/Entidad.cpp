#include "Entidad.h"

#include <algorithm>

Entidad::Entidad() {
	this->jerarquiaHija = NULL;
}

Entidad::~Entidad() {
	if (this->jerarquiaHija) {
		delete this->jerarquiaHija;
	}
}
void Entidad::quitarJerarquiaHija() {
	this->jerarquiaHija = NULL;
}

void Entidad::agregarUnionARelacion(UnionEntidadRelacion *u) throw (NullPointer) {
	if (u == NULL) {
		throw NullPointer("Puntero nulo en agregarUnionARelacion de Entidad");
	}
	this->unionesARelacion.push_back(u);
}

void Entidad::removerUnionARelacion(UnionEntidadRelacion *u) throw (NullPointer) {
	if (u == NULL) {
		throw NullPointer("Puntero nulo en removerUnionARelacion de Entidad");
	}
	std::vector<UnionEntidadRelacion *>::iterator it_uniones;
	it_uniones = find(this->unionesARelacion.begin(), this->unionesARelacion.end(), u);
	if (it_uniones != this->unionesARelacion.end()) {
		this->unionesARelacion.erase(it_uniones);
	}
}

std::vector<UnionEntidadRelacion *>::iterator Entidad::unionesARelacionBegin() {
	return this->unionesARelacion.begin();
}

std::vector<UnionEntidadRelacion *>::iterator Entidad::unionesARelacionEnd() {
	return this->unionesARelacion.end();
}

void Entidad::setJerarquiaHija(Jerarquia * jHija) throw (NullPointer) {
	if (jHija == NULL) {
		throw NullPointer("Puntero nulo en setJerarquiaHija de Entidad");
	}
	this->jerarquiaHija = jHija;
}

Jerarquia * Entidad::getJerarquiaHija() const {
	return this->jerarquiaHija;
}

