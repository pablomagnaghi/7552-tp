#include "VistaJerarquia.h"

#include <algorithm>

VistaJerarquia::VistaJerarquia(Jerarquia * jerarquiaModelo) {
	this->jerarquia = jerarquiaModelo;
}

VistaJerarquia::~VistaJerarquia() {
}

//Dibuja el objeto en el contexto cairo pasado como parametro.
void VistaJerarquia::dibujar(Cairo::RefPtr<Cairo::Context> cr) {
	double x0, x1, x2, x3, y0, y1, y2, y3;
	double xmin, xmax, ymin, ymax;
	cr->set_line_width(1);
	cr->set_source_rgb(colorNegro.get_red_p(), colorNegro.get_green_p(), colorNegro.get_blue_p());

	this->padre->getposini(x0, y0);
	this->padre->getposfin(x1, y1);
	this->pos_fin_x = (x0 + x1) / 2;
	this->pos_fin_y = (y0 + y1) / 2;

	if (this->hijos.size() == 1) {
		this->hijos[0]->getposini(x0, y0);
		this->hijos[0]->getposfin(x1, y1);
		this->pos_ini_x = (x0 + x1) / 2;
		this->pos_ini_y = (y0 + y1) / 2;

		this->hijos[0]->obtenerInterseccionColLinea(this->pos_ini_x, this->pos_ini_y,
				this->pos_fin_x, this->pos_fin_y, this->pos_ini_x, this->pos_ini_y);
		this->padre->obtenerInterseccionColLinea(this->pos_ini_x, this->pos_ini_y, this->pos_fin_x,
				this->pos_fin_y, this->pos_fin_x, this->pos_fin_y);

		Geometria::obtenerPuntosDeTriangulo(this->pos_ini_x, this->pos_ini_y, this->pos_fin_x,
				this->pos_fin_y, 16, 8, x2, y2, x3, y3);

		cr->move_to(this->pos_ini_x, this->pos_ini_y);
		cr->line_to(this->pos_fin_x, this->pos_fin_y);
		cr->stroke();
		cr->line_to(x2, y2);
		cr->line_to(x3, y3);
		cr->line_to(this->pos_fin_x, this->pos_fin_y);
		cr->fill();

	} else {
		std::vector<VistaEntidadNueva *>::iterator i;
		this->padre->getposcentro(xmax, y0);
		xmin = xmax;
		ymin = 999999;
		ymax = -1;
		for (i = this->hijos.begin(); i != this->hijos.end(); i++) {
			(*i)->getposcentro(x2, y2);
			if (x2 < xmin) {
				xmin = x2;
			}
			if (y2 < ymin) {
				ymin = y2;
			}
			if (x2 > xmax) {
				xmax = x2;
			}
			if (y2 > ymax) {
				ymax = y2;
			}
		}
		this->pos_ini_x = xmin;
		this->pos_fin_x = xmax;

		if (y1 < ymin) {
			this->pos_ini_y = (y1 + ymin) / 2;
		} else if (y0 > ymax) {
			this->pos_ini_y = (y0 + ymax) / 2;
		}
		cr->move_to(this->pos_ini_x, this->pos_ini_y);
		cr->line_to(this->pos_fin_x, this->pos_ini_y);
		cr->stroke();
		this->padre->getposcentro(x0, y0);
		this->padre->obtenerInterseccionColLinea(x0, this->pos_ini_y, x0, y0, x1, y1);
		cr->move_to(x0, this->pos_ini_y);
		cr->line_to(x1, y1);
		cr->stroke();
		Geometria::obtenerPuntosDeTriangulo(x0, this->pos_ini_y, x1, y1, 13, 5, x2, y2, x3, y3);
		cr->line_to(x2, y2);
		cr->line_to(x3, y3);
		cr->line_to(x1, y1);
		cr->fill();
		for (i = this->hijos.begin(); i != this->hijos.end(); i++) {
			(*i)->getposcentro(x0, y0);
			(*i)->obtenerInterseccionColLinea(x0, this->pos_ini_y, x0, y0, x1, y1);
			cr->move_to(x0, this->pos_ini_y);
			cr->line_to(x1, y1);
			cr->stroke();
		}
	}

}

//Indica q sucede cuando el objeto es seleccionado
bool VistaJerarquia::esSeleccionado(double x, double y) {
	return false;
}

//indica q sucede con el objeto cuando deja de ser seleccionado
void VistaJerarquia::finSeleccionado(double x, double y) {

}

//Lanza el asistente de prpiedades del objeto en cuestion.
bool VistaJerarquia::lanzarProp() {
	return false;
}

// Verifica si el punto cae dentro de este componente
bool VistaJerarquia::contieneAEstePunto(double x, double y) {
	return false;
}

void VistaJerarquia::calcularDimensionesAPartirDeTexto(Cairo::TextExtents * textExtents) {

}

// Verifica si el punto cae dentro de un punto para redimensionar el elemento
bool VistaJerarquia::esPuntoDeRedimension(double x, double y) {
	return false;
}

void VistaJerarquia::setMouseArriba(double x, double y) {

}

void VistaJerarquia::redimensionar(double x, double y) {

}

void setNombre(const std::string & nombre) {

}

std::string VistaJerarquia::getNombre() const {
	return "";
}

bool VistaJerarquia::contieneEsteComponente(Componente * comp) {
	return false;
}

bool VistaJerarquia::obtenerInterseccionColLinea(double pos_ini_x, double pos_ini_y,
		double pos_fin_x, double pos_fin_y, double & x, double & y) {
	return false;
}

// TODO Implementar las modificaciones en el modelo
void VistaJerarquia::agregarEntidadEspecializada(VistaEntidadNueva * hijoNuevo) {
	//if ! esta en el vector
	this->hijos.push_back(hijoNuevo);
}

void VistaJerarquia::removerEntidadEspecializada(VistaEntidadNueva * entidadEliminada) {

	remove(this->hijos.begin(), this->hijos.end(), entidadEliminada);
}

std::vector<VistaEntidadNueva *>::iterator VistaJerarquia::entidadesEspecializadasBegin() {
	return this->hijos.begin();
}

std::vector<VistaEntidadNueva *>::iterator VistaJerarquia::entidadesEspecializadasEnd() {
	return this->hijos.end();
}

void VistaJerarquia::setEntidadPadre(VistaEntidad * vistaEntidad) {
	this->padre = vistaEntidad;
}

VistaEntidad * VistaJerarquia::getEntidadPadre() {
	return this->padre;
}
