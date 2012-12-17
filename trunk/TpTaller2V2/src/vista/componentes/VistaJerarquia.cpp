#include "VistaJerarquia.h"
#include "../Ide.h"

#include <algorithm>

#define DEBUG_VISTA_JERARQUIA 0
#define GAP_ESPACIO_LINEA 5

VistaJerarquia::VistaJerarquia(Jerarquia * jerarquiaModelo) {
	this->jerarquia = jerarquiaModelo;
	this->prop_lanzada = false;
	this->padre = NULL;

	// Persistencia REP
	this->codigoREP = jerarquiaModelo->getCodigo();
}

VistaJerarquia::~VistaJerarquia() {
	if (eliminarModelo) {
		delete this->jerarquia;
	}
}
void VistaJerarquia::calcularMinMax(double & xmin, double & xmax, double & ymin, double & ymax) {
	double x0, x2, y0, y2, y3;
	std::vector<VistaEntidadNueva *>::iterator i;

	this->padre->getposcentro(xmax, y0);
	xmin = xmax;
	ymin = 999999;
	ymax = -1;
	for (i = this->hijos.begin(); i != this->hijos.end(); i++) {
		(*i)->getposcentro(x2, y2);
		(*i)->getposini(x0, y2);
		(*i)->getposfin(x0, y3);
		if (x2 < xmin) {
			xmin = x2;
		}
		if (y2 < ymin) {
			ymin = y2;
		}
		if (x2 > xmax) {
			xmax = x2;
		}
		if (y3 > ymax) {
			ymax = y3;
		}
	}
	this->pos_ini_x = xmin;
	this->pos_fin_x = xmax;
}

void VistaJerarquia::calcularLineaMedia(double ymin, double ymax) {
	double x0, y0, x1, y1;

	this->padre->getposini(x0, y0);
	this->padre->getposfin(x1, y1);

	if (y1 < ymin) {
		this->pos_ini_y = (y1 + ymin) / 2;
		if (this->pos_ini_y < y1 + 18) {
			this->pos_ini_y = y0 - 18;
		}
	} else if (y0 > ymax) {
		this->pos_ini_y = (y0 + ymax) / 2;
		if (this->pos_ini_y > y0 - 18) {
			this->pos_ini_y = y1 + 18;
		}
	} else if (ymin < y1 && y0 < ymax) {
		this->pos_ini_y = MIN(ymin, y0) - 18;
	} else if (ymin < y0 && y1 < ymax) {
		this->pos_ini_y = MIN(ymin, y0) - 18;
	}
}

void VistaJerarquia::dibujarLineaMedia(Cairo::RefPtr<Cairo::Context> cr, double ymin, double ymax) {
	double x0, y0, x1, y1, x2, y2, x3, y3;

	this->padre->getposini(x0, y0);
	this->padre->getposfin(x1, y1);

	this->calcularLineaMedia(ymin, ymax);

	cr->move_to(this->pos_ini_x, this->pos_ini_y);
	cr->line_to(this->pos_fin_x, this->pos_ini_y);
	cr->stroke();

	this->padre->getposcentro(x0, y0);
	this->padre->obtenerInterseccionConLinea(x0, this->pos_ini_y, x0, y0, x1, y1);
	cr->move_to(x0, this->pos_ini_y);
	cr->line_to(x1, y1);
	cr->stroke();

	Geometria::obtenerPuntosDeTriangulo(x0, this->pos_ini_y, x1, y1, 13, 5, x2, y2, x3, y3);
	cr->line_to(x2, y2);
	cr->line_to(x3, y3);
	cr->line_to(x1, y1);
	cr->fill();

#if DEBUG_VISTA_JERARQUIA==1
	cout << "ymin=" << ymin << endl;
	cout << "ymax=" << ymax << endl;
	cout << "y0=" << y0 << endl;
	cout << "y1=" << y1 << endl;
	cout << "Pos Linea Media=" << this->pos_ini_y << endl;
#endif
}

// TODO REFACTORIZAR
void VistaJerarquia::dibujar(Cairo::RefPtr<Cairo::Context> cr) {
	if (this->padre == NULL) {
		return;
	}

	double x0, x1, x2, x3, y0, y1, y2, y3;
	double xmin, xmax, ymin, ymax;

	cr->set_line_width(1);
	if (!this->seleccionado) {
		cr->set_source_rgb(colorNegro.get_red_p(), colorNegro.get_green_p(),
				colorNegro.get_blue_p());
	} else {
		cr->set_source_rgb(colorDeSeleccion.get_red_p(), colorDeSeleccion.get_green_p(),
				colorDeSeleccion.get_blue_p());
	}

	this->padre->getposini(x0, y0);
	this->padre->getposfin(x1, y1);
	this->pos_fin_x = (x0 + x1) / 2;
	this->pos_fin_y = (y0 + y1) / 2;

	if (this->hijos.size() == 1) {
		this->hijos[0]->getposini(x0, y0);
		this->hijos[0]->getposfin(x1, y1);
		this->pos_ini_x = (x0 + x1) / 2;
		this->pos_ini_y = (y0 + y1) / 2;

		this->hijos[0]->obtenerInterseccionConLinea(this->pos_ini_x, this->pos_ini_y,
				this->pos_fin_x, this->pos_fin_y, this->pos_ini_x, this->pos_ini_y);
		this->padre->obtenerInterseccionConLinea(this->pos_ini_x, this->pos_ini_y, this->pos_fin_x,
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
#if DEBUG_VISTA_JERARQUIA==1
		Geometria::obtenerLineasParalelas(this->pos_ini_x, this->pos_ini_y, this->pos_fin_x,
				this->pos_fin_y, GAP_ESPACIO_LINEA, x0, y0, x1, y1, x2, y2, x3, y3);
		cr->set_source_rgb(1, 0, 0);
		cr->move_to(x0, y0);
		cr->line_to(x1, y1);
		cr->stroke();

		cr->move_to(x2, y2);
		cr->line_to(x3, y3);
		cr->stroke();
#endif
	} else {
		std::vector<VistaEntidadNueva *>::iterator i;

		this->calcularMinMax(xmin, xmax, ymin, ymax);

		dibujarLineaMedia(cr, ymin, ymax);

#if DEBUG_VISTA_JERARQUIA==1
		cr->save();
		Geometria::obtenerLineasParalelas(this->pos_ini_x, this->pos_ini_y, this->pos_fin_x,
				this->pos_ini_y, GAP_ESPACIO_LINEA, x0, y0, x1, y1, x2, y2, x3, y3);
		cr->set_source_rgb(1, 0, 0);
		cr->move_to(x0, y0);
		cr->line_to(x1, y1);
		cr->stroke();

		cr->move_to(x2, y2);
		cr->line_to(x3, y3);
		cr->stroke();
		cr->restore();
#endif

		for (i = this->hijos.begin(); i != this->hijos.end(); i++) {
			(*i)->getposcentro(x0, y0);
			(*i)->obtenerInterseccionConLinea(x0, this->pos_ini_y, x0, y0, x1, y1);
			cr->move_to(x0, this->pos_ini_y);
			cr->line_to(x1, y1);
			cr->stroke();

#if DEBUG_VISTA_JERARQUIA==1
			cr->save();
			Geometria::obtenerLineasParalelas(x0, this->pos_ini_y, x1, y1, GAP_ESPACIO_LINEA, x0,
					y0, x1, y1, x2, y2, x3, y3);
			cr->set_source_rgb(1, 0, 0);
			cr->move_to(x0, y0);
			cr->line_to(x1, y1);
			cr->stroke();

			cr->move_to(x2, y2);
			cr->line_to(x3, y3);
			cr->stroke();
			cr->restore();
#endif
		}

	}
}

//Lanza el asistente de prpiedades del objeto en cuestion.
bool VistaJerarquia::lanzarProp() {
	if (!this->prop_lanzada) {
		AsistenteJerarquia* nuevaProp;
		Glib::RefPtr<Gtk::Builder> nHbuilder = Gtk::Builder::create_from_file(ARCH_GLADE_JERAR);
		nHbuilder->get_widget_derived("PropJerarquia", nuevaProp);
		nuevaProp->setJerarquia(this);
		this->prop_lanzada = true;
		nuevaProp->show();
		return true;
	}
	return false;
}

// Verifica si el punto cae dentro de este componente
bool VistaJerarquia::contieneAEstePunto(double x, double y) {
	std::vector<VistaEntidadNueva *>::iterator i;
	double x0, y0, x1, y1, x2, y2, x3, y3;
	double xmin, xmax, ymin, ymax;
	if (this->hijos.size() == 1) {
		Geometria::obtenerLineasParalelas(this->pos_ini_x, this->pos_ini_y, this->pos_fin_x,
				this->pos_fin_y, GAP_ESPACIO_LINEA, x0, y0, x1, y1, x2, y2, x3, y3);
		return Geometria::estaEntreLineasParalelas(x, y, x0, y0, x1, y1, x2, y2, x3, y3);
	} else {
		this->calcularMinMax(xmin, xmax, ymin, ymax);
		this->calcularLineaMedia(ymin, ymax);

		Geometria::obtenerLineasParalelas(this->pos_ini_x, this->pos_ini_y, this->pos_fin_x,
				this->pos_ini_y, GAP_ESPACIO_LINEA, x0, y0, x1, y1, x2, y2, x3, y3);
		if (Geometria::estaEntreLineasParalelas(x, y, x0, y0, x1, y1, x2, y2, x3, y3)) {
			return true;
		}

		this->padre->getposcentro(x0, y0);
		this->padre->obtenerInterseccionConLinea(x0, this->pos_ini_y, x0, y0, x1, y1);
		Geometria::obtenerLineasParalelas(x0, this->pos_ini_y, x1, y1, GAP_ESPACIO_LINEA, x0, y0,
				x1, y1, x2, y2, x3, y3);
		if (Geometria::estaEntreLineasParalelas(x, y, x0, y0, x1, y1, x2, y2, x3, y3)) {
			return true;
		}

		for (i = this->hijos.begin(); i != this->hijos.end(); i++) {
			(*i)->getposcentro(x0, y0);
			(*i)->obtenerInterseccionConLinea(x0, this->pos_ini_y, x0, y0, x1, y1);

			Geometria::obtenerLineasParalelas(x0, this->pos_ini_y, x1, y1, GAP_ESPACIO_LINEA, x0,
					y0, x1, y1, x2, y2, x3, y3);
			if (Geometria::estaEntreLineasParalelas(x, y, x0, y0, x1, y1, x2, y2, x3, y3)) {
				return true;
			}
		}
	}

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

std::string VistaJerarquia::getNombre() const {
	return this->jerarquia->getNombre();
}

bool VistaJerarquia::contieneEsteComponente(VistaComponente * comp) {
	if (static_cast<VistaComponente*>(this->padre) == comp) {
		return true;
	}
	if (find(this->hijos.begin(), this->hijos.end(), static_cast<VistaEntidadNueva*>(comp))
			!= this->hijos.end()) {
		return true;
	}
	return false;
}

bool VistaJerarquia::obtenerInterseccionConLinea(double pos_ini_x, double pos_ini_y,
		double pos_fin_x, double pos_fin_y, double & x, double & y) {
	return false;
}

// todo ACA PONGO EL METODO PROVISORIO
/*
 bool VistaJerarquia::existeEntidadNueva(EntidadNueva *entidad) {
 std::vector<EntidadNueva *>::iterator it;

 it = find(this->jerarquia->entidadesEspecializadasBegin(), this->jerarquia->entidadesEspecializadasEnd(), entidad);
 if (it != this->jerarquia->entidadesEspecializadasEnd()) {
 return true;
 }
 return false;
 }
 */
// TODO Implementar las modificaciones en el modelo
// Aca se da el caso de que guarda de vuelta la entidad con la cual esta cargando el modelo
void VistaJerarquia::agregarEntidadEspecializada(VistaEntidadNueva * hijoNuevo) {
	//if ! esta en el vector
	this->hijos.push_back(hijoNuevo);

	/*
	 //todo PARCHE PROVISORIO A EVALUACION MAÑANA
	 if (!existeEntidadNueva(hijoNuevo->getEntidadNueva())) {
	 this->jerarquia->agregarEntidadEspecializada(hijoNuevo->getEntidadNueva());
	 }
	 */
}

void VistaJerarquia::removerEntidadEspecializada(VistaEntidadNueva * entidadEliminada) {
	std::vector<VistaEntidadNueva *>::iterator it_entidades;
	it_entidades = find(this->hijos.begin(), this->hijos.end(), entidadEliminada);
	if (it_entidades != this->hijos.end()) {
		this->hijos.erase(it_entidades);
	}
}

std::vector<VistaEntidadNueva *>::iterator VistaJerarquia::entidadesEspecializadasBegin() {
	return this->hijos.begin();
}

std::vector<VistaEntidadNueva *>::iterator VistaJerarquia::entidadesEspecializadasEnd() {
	return this->hijos.end();
}

void VistaJerarquia::setEntidadPadre(VistaEntidad * vistaEntidad) {
	this->padre = vistaEntidad;
	this->jerarquia->setEntidadGeneral(vistaEntidad->getEntidad());
}

VistaEntidad * VistaJerarquia::getEntidadPadre() {
	return this->padre;
}

void VistaJerarquia::resetearLanzarProp() {
	this->prop_lanzada = false;
}

void VistaJerarquia::setNombre(const std::string & nombre) {
	this->jerarquia->setNombre(nombre);
}

Jerarquia * VistaJerarquia::getJerarquia() {
	return this->jerarquia;
}

void VistaJerarquia::eliminarComponentesAdyacentes(Diagrama * diagrama,
		std::vector<VistaComponente *> & componentes, VistaComponente * componenteEliminado) {
	std::vector<VistaEntidadNueva *>::iterator it_entidades;
	if (static_cast<VistaComponente*>(this->padre) == componenteEliminado || this == componenteEliminado) {
		this->eliminando = true;
		diagrama->quitarComponente(this->jerarquia);
		for (it_entidades = this->hijos.begin(); it_entidades != this->hijos.end();
				++it_entidades) {
			this->jerarquia->quitarEntidadEspecializada((*it_entidades)->getEntidadNueva());
			(*it_entidades)->getEntidadNueva()->quitarJerarquiaPadre(this->jerarquia);
		}
		this->jerarquia->getEntidadGeneral()->quitarJerarquiaHija();
		this->eliminarModelo = true;
	} else {
		it_entidades = find(this->hijos.begin(), this->hijos.end(),
				static_cast<VistaEntidadNueva*>(componenteEliminado));
		if (it_entidades != this->hijos.end()) {
			this->jerarquia->quitarEntidadEspecializada((*it_entidades)->getEntidadNueva());
			(*it_entidades)->getEntidadNueva()->quitarJerarquiaPadre(this->jerarquia);
			this->hijos.erase(it_entidades);
		}
		if (this->hijos.empty()) {
			this->eliminando = true;
			diagrama->quitarComponente(this->jerarquia);
			this->jerarquia->getEntidadGeneral()->quitarJerarquiaHija();
			this->eliminarModelo = true;
		}
	}

}

bool VistaJerarquia::hayQueEliminarlo() {
	return this->eliminando;
}

bool VistaJerarquia::unidaConEntidad(VistaEntidad * ventidad){
	std::vector<VistaEntidadNueva*>::iterator it = this->entidadesEspecializadasBegin();
	std::vector<VistaEntidadNueva*>::iterator it1 = this->entidadesEspecializadasEnd();
	VistaEntidad * ve = NULL;
	while (it!=it1){
		ve = *it;
		if (ve == ventidad){
			return true;
		}
		it++;
	}
	return false;
}
