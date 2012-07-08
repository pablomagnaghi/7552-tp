#include "AtributoCompuesto.h"

AtributoCompuesto::AtributoCompuesto() {
	// TODO Auto-generated constructor stub

}

AtributoCompuesto::~AtributoCompuesto() {
	this->borrarAtributosDerivables();
}

void AtributoCompuesto::agregarAtributoDerivable(Atributo* atributo) {
	this->atributosDerivables.push_back(atributo);
}

void AtributoCompuesto::quitarAtributoDerivable(Atributo* atributo) {
	std::vector<Atributo*>::iterator e;
	e = find(this->atributosDerivables.begin(),
			this->atributosDerivables.end(), atributo);
	if (*e == atributo) {
		this->atributosDerivables.erase(e);
	}
}

std::vector<Atributo*>::iterator AtributoCompuesto::atributosDerivablesBegin() {
	return this->atributosDerivables.begin();
}

std::vector<Atributo*>::iterator AtributoCompuesto::atributosDerivablesEnd() {
	return this->atributosDerivables.end();
}


void AtributoCompuesto::borrarAtributosDerivables() {
	std::vector<Atributo*>::iterator it = this->atributosDerivables.begin();
	while ( it != this->atributosDerivables.end() ) {
		delete (*it);
		it++;
	}
	this->atributosDerivables.clear();
}
