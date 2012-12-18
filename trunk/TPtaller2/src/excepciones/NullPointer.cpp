#include "NullPointer.h"

NullPointer::NullPointer(const std::string & explicacion) {
	this->explicacion = explicacion;
}

NullPointer::~NullPointer() throw () {
}

const char * NullPointer::what()const throw() {
	std::string error("Null Pointer: ");
	error.append(this->explicacion);
	return error.c_str();
}
