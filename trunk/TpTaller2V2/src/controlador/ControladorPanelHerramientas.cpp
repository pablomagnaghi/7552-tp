
#include "ControladorPanelHerramientas.h"

#ifdef DEBUG
#include <iostream>
using namespace std;
#endif

ControladorPanelHerramientas::ControladorPanelHerramientas(const Glib::RefPtr<
		Gtk::Builder> & builder, Gtk::Window * ventana) :
	m_builder (builder) {

#ifdef DEBUG
	cout << "Creando ControladorPanelHerramientas" << endl;
#endif

	AsistenteEntidad::getInstance(builder);

	this->ventanaPrincipal = ventana;

	this->diagramaActual = NULL;

	this->enlazar_botones_de_menu(builder);

	this->desactivarBotones();

}

ControladorPanelHerramientas::~ControladorPanelHerramientas() {
	// TODO Auto-generated destructor stub
}

void ControladorPanelHerramientas::on_boton_Agregar_Entidad_click() {
#ifdef DEBUG
	cout << "Agregar Entidad" << endl;
#endif

	if (this->diagramaActual != NULL) {
		VistaEntidadNueva * nuevaEntidad = new VistaEntidadNueva(new Entidad());

		if (nuevaEntidad->lanzarProp()) {
			this->diagramaActual->agregarComponente(nuevaEntidad);
		} else {
			delete nuevaEntidad;
		}
	}
}

void ControladorPanelHerramientas::on_boton_Agregar_Relacion_click() {
#ifdef DEBUG
	cout << "Agregar Relacion" << endl;
#endif
}

void ControladorPanelHerramientas::on_boton_Agregar_Jerarquia_click() {
#ifdef DEBUG
	cout << "Agregar Jerarquia" << endl;
#endif
}

void ControladorPanelHerramientas::on_boton_Agregar_Union_click() {
#ifdef DEBUG
	cout << "Agregar Union" << endl;
#endif
}

void ControladorPanelHerramientas::on_boton_Agregar_Comentario_click() {
#ifdef DEBUG
	cout << "Agregar Comentario" << endl;
#endif
}

void ControladorPanelHerramientas::enlazar_botones_de_menu(const Glib::RefPtr<
		Gtk::Builder>& builder) {
	builder->get_widget("TBAgregarEntidad", botonAgregarEntidad);
	botonAgregarEntidad->signal_clicked().connect(sigc::mem_fun(*this,
			&ControladorPanelHerramientas::on_boton_Agregar_Entidad_click));
	builder->get_widget("TBAgregarRelacion", botonAgregarRelacion);
	botonAgregarRelacion->signal_clicked().connect(sigc::mem_fun(*this,
			&ControladorPanelHerramientas::on_boton_Agregar_Relacion_click));
	builder->get_widget("TBAgregarJerarquia", botonAgregarJerarquia);
	botonAgregarJerarquia->signal_clicked().connect(sigc::mem_fun(*this,
			&ControladorPanelHerramientas::on_boton_Agregar_Jerarquia_click));
	builder->get_widget("TBAgregarUnion", botonAgregarUnion);
	botonAgregarUnion->signal_clicked().connect(sigc::mem_fun(*this,
			&ControladorPanelHerramientas::on_boton_Agregar_Union_click));
	builder->get_widget("TBAgregarComentario", botonAgregarComentario);
	botonAgregarComentario->signal_clicked().connect(sigc::mem_fun(*this,
			&ControladorPanelHerramientas::on_boton_Agregar_Comentario_click));
}

void ControladorPanelHerramientas::setDiagrama(VistaDiagrama * diagrama) {
	if (diagrama != NULL) {
		this->diagramaActual = diagrama;
	}
}

void ControladorPanelHerramientas::activarBotones() {
	botonAgregarEntidad->set_sensitive(true);
	botonAgregarRelacion->set_sensitive(true);
	botonAgregarJerarquia->set_sensitive(true);
	botonAgregarUnion->set_sensitive(true);
	botonAgregarComentario->set_sensitive(true);
}

void ControladorPanelHerramientas::desactivarBotones() {
	botonAgregarEntidad->set_sensitive(false);
	botonAgregarRelacion->set_sensitive(false);
	botonAgregarJerarquia->set_sensitive(false);
	botonAgregarUnion->set_sensitive(false);
	botonAgregarComentario->set_sensitive(false);
}
