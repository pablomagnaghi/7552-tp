#ifndef VISTAENTIDADGLOBAL_H_
#define VISTAENTIDADGLOBAL_H_

#include "VistaEntidad.h"
#include "../../modelo/componentes/EntidadGlobal.h"

class VistaEntidadGlobal : public VistaEntidad{
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
