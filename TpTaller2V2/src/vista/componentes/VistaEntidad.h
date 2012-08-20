#ifndef VISTAENTIDAD_H_
#define VISTAENTIDAD_H_

#include "VistaComponente.h"

class VistaEntidad: public VistaComponente {

public:
	VistaEntidad();
	virtual ~VistaEntidad();

	virtual bool obtenerInterseccionConLinea(double pos_ini_x, double pos_ini_y, double pos_fin_x,
			double pos_fin_y, double & x, double & y);
};

#endif /* VISTAENTIDAD_H_ */
