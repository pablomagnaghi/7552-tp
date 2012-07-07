/* VistaUnionEntidadRelacion.h
 *  Created on: 07/07/2012
 *      Author: Gonzalo Ferrero 89657
 */

#ifndef VISTAUNIONENTIDADRELACION_H_
#define VISTAUNIONENTIDADRELACION_H_

#include "VistaComponente.h"
#include "../../modelo/UnionEntidadRelacion.h"

class VistaUnionEntidadRelacion : public VistaComponente {
private:
	UnionEntidadRelacion * unionModelo;
public:
	VistaUnionEntidadRelacion();
	virtual ~VistaUnionEntidadRelacion();
};

#endif /* VISTAUNIONENTIDADRELACION_H_ */
