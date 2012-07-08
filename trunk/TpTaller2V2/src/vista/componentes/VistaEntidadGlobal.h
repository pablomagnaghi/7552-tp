#ifndef VISTAENTIDADGLOBAL_H_
#define VISTAENTIDADGLOBAL_H_

#include "VistaComponente.h"
#include "../../modelo/EntidadGlobal.h"

class VistaEntidadGlobal : public VistaComponente{
private:
	EntidadGlobal * entidad;
public:
	VistaEntidadGlobal();
	virtual ~VistaEntidadGlobal();

	virtual std::string getNombre() const;
};

#endif /* VISTAENTIDADGLOBAL_H_ */
