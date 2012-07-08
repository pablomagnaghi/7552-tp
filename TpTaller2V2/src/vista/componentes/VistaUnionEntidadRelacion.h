#ifndef VISTAUNIONENTIDADRELACION_H_
#define VISTAUNIONENTIDADRELACION_H_

#include "VistaComponente.h"
#include "../../modelo/UnionEntidadRelacion.h"

class VistaUnionEntidadRelacion : public VistaComponente {
private:
	UnionEntidadRelacion * unionModelo;
public:
	VistaUnionEntidadRelacion(UnionEntidadRelacion * unionModelo);
	virtual ~VistaUnionEntidadRelacion();

	virtual std::string getNombre() const;
};

#endif /* VISTAUNIONENTIDADRELACION_H_ */
