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
	remove(this->unionesARelacion.begin(), this->unionesARelacion.end(), u);
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

