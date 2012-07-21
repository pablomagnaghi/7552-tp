#include "ArgumentoInvalido.h"

ArgumentoInvalido::ArgumentoInvalido(const std::string & explicacion) {
	this->explicacion = explicacion;
}

ArgumentoInvalido::~ArgumentoInvalido()throw() {
}

const char * ArgumentoInvalido::what()const throw(){
	std::string error("Argumento Inválido: ");
	error.append(this->explicacion);
	return error.c_str();
}
