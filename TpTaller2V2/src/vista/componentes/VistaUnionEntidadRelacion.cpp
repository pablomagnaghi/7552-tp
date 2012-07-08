#include "VistaUnionEntidadRelacion.h"

VistaUnionEntidadRelacion::VistaUnionEntidadRelacion(UnionEntidadRelacion * unionModelo) {
	// TODO Auto-generated constructor stub

}

VistaUnionEntidadRelacion::~VistaUnionEntidadRelacion() {
	// TODO Auto-generated destructor stub
}

std::string VistaUnionEntidadRelacion::getNombre() const{
	return this->unionModelo->getNombre();
}
