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

	virtual bool contieneEsteComponente(Componente *);

	virtual std::string getNombre() const;

	virtual bool obtenerInterseccionColLinea(double pos_ini_x,
					double pos_ini_y, double pos_fin_x, double pos_fin_y, double & x,
					double & y);
};

#endif /* VISTAENTIDADGLOBAL_H_ */
