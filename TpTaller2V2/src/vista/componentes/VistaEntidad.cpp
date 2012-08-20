#include "VistaEntidad.h"

VistaEntidad::VistaEntidad() {
}

VistaEntidad::~VistaEntidad() {
}


bool VistaEntidad::obtenerInterseccionConLinea(double pos_ini_x, double pos_ini_y,
		double pos_fin_x, double pos_fin_y, double & x, double & y) {
	double xInterseccion, yInterseccion;

	if (Geometria::hayInterseccionDeLineas(pos_ini_x, pos_ini_y, pos_fin_x, pos_fin_y,
			this->pos_ini_x, this->pos_ini_y, this->pos_fin_x, this->pos_ini_y, xInterseccion,
			yInterseccion)) {
		x = xInterseccion;
		y = yInterseccion;
		return true;
	} else if (Geometria::hayInterseccionDeLineas(pos_ini_x, pos_ini_y, pos_fin_x, pos_fin_y,
			this->pos_ini_x, this->pos_ini_y, this->pos_ini_x, this->pos_fin_y, xInterseccion,
			yInterseccion)) {
		x = xInterseccion;
		y = yInterseccion;
		return true;
	} else if (Geometria::hayInterseccionDeLineas(pos_ini_x, pos_ini_y, pos_fin_x, pos_fin_y,
			this->pos_fin_x, this->pos_ini_y, this->pos_fin_x, this->pos_fin_y, xInterseccion,
			yInterseccion)) {
		x = xInterseccion;
		y = yInterseccion;
		return true;
	} else if (Geometria::hayInterseccionDeLineas(pos_ini_x, pos_ini_y, pos_fin_x, pos_fin_y,
			this->pos_ini_x, this->pos_fin_y, this->pos_fin_x, this->pos_fin_y, xInterseccion,
			yInterseccion)) {
		x = xInterseccion;
		y = yInterseccion;
		return true;
	}

	return false;
}
