#include "ControladorPanelHerramientas.h"

#ifdef DEBUG
#include <iostream>
using namespace std;
#endif
#include "../vista/Ide.h"

ControladorPanelHerramientas::ControladorPanelHerramientas(
		const Glib::RefPtr<Gtk::Builder> & builder, Gtk::Window * ventana) :
		m_builder(builder) {

#ifdef DEBUG
	cout << "Creando ControladorPanelHerramientas" << endl;
#endif

	//AsistenteEntidad::getInstance(builder);

	//AsistenteAtributo::getInstance(builder);

	this->ventanaPrincipal = ventana;

	this->enlazar_botones_de_menu(builder);

	this->desactivarBotones();

}

ControladorPanelHerramientas::~ControladorPanelHerramientas() {
	// TODO Auto-generated destructor stub
}

void ControladorPanelHerramientas::on_boton_Agregar_Diagrama_click() {
	int resultado;
	std::string nombre;
	Gtk::Dialog * dialogo_agregar_diagrama;
	Gtk::Entry * entrada_de_texto;
	Gtk::Label * etiqueta_nombre_diagrama_padre;
	Gtk::Button * boton_ok;
	Gtk::Button * boton_cancel;
	m_builder->get_widget("dialogoAgregarDiagrama", dialogo_agregar_diagrama);
	m_builder->get_widget("entradaTextoAgregarDiagrama", entrada_de_texto);
	m_builder->get_widget("etiquetaNombrePadre", etiqueta_nombre_diagrama_padre);
	m_builder->get_widget("botonAgregarDiagramaOK", boton_ok);
	m_builder->get_widget("botonAgregarDiagramaCancel", boton_cancel);
	boton_ok->signal_clicked().connect(
			sigc::bind<Gtk::Dialog *>(
					sigc::mem_fun(*this,
							&ControladorPanelHerramientas::on_boton_Agregar_Diagrama_ok),
					dialogo_agregar_diagrama));
	boton_cancel->signal_clicked().connect(
			sigc::bind<Gtk::Dialog *>(
					sigc::mem_fun(*this,
							&ControladorPanelHerramientas::on_boton_Agregar_Diagrama_Cancel),
					dialogo_agregar_diagrama));
	dialogo_agregar_diagrama->set_default_response(Gtk::RESPONSE_CANCEL);

	etiqueta_nombre_diagrama_padre->set_text(Ide::getInstance()->getDiagActual()->getNombre());

	resultado = dialogo_agregar_diagrama->run();

	nombre = entrada_de_texto->get_text();

	entrada_de_texto->set_text("");

	if (resultado == Gtk::RESPONSE_OK) {
		if (nombre.empty()) {
			Gtk::MessageDialog dialog(*Ide::getInstance(), "Error", false /* use_markup */,
					Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK);
			dialog.set_secondary_text("El campo del nombre está vacio");
			dialog.run();
			return;
		}
		if (Ide::getInstance()->getProyecto()->getDiagramaPrincipal()->existeEsteDiagrama(nombre)) {
			Gtk::MessageDialog dialog(*Ide::getInstance(), "Error", false /* use_markup */,
					Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK);
			std::string texto = "Ya existe un diagrama con el nombre ";
			texto.append(nombre);
			dialog.set_secondary_text(texto);
			dialog.run();
			return;
		}
		VistaDiagrama * nuevo_diagrama = new VistaDiagrama(new Diagrama());
		nuevo_diagrama->getDiagrama()->setNombre(nombre);
		Ide::getInstance()->getDiagActual()->agregarDiagramaHijo(nuevo_diagrama);
		Ide::getInstance()->regenerarTreePanel();
	}
}

void ControladorPanelHerramientas::on_boton_Eliminar_Diagrama_click() {
#ifdef DEBUG
	cout << "Eliminar Diagrama" << endl;
#endif
	if (Ide::getInstance()->getDiagActual() != NULL
			&& Ide::getInstance()->getDiagActual()->getNombre() != "Principal") {
		cout << "Eliminar Diagrama 2" << endl;
		Diagrama * modelo;
		VistaDiagrama * vista;
		VistaDiagrama * padre;
		vista = Ide::getInstance()->getDiagActual();
		modelo = vista->getDiagrama();
		padre = vista->getDiagramaAncestro();
		padre->quitarDiagramaHijo(vista);
		Ide::getInstance()->cargarDiagrama(padre);
		Ide::getInstance()->regenerarTreePanel();
		delete vista;
		delete modelo;
	}
}

void ControladorPanelHerramientas::on_boton_Agregar_Diagrama_ok(Gtk::Dialog * d) {
	d->response(Gtk::RESPONSE_OK);
	d->hide();
}

void ControladorPanelHerramientas::on_boton_Agregar_Diagrama_Cancel(Gtk::Dialog * d) {
	d->response(Gtk::RESPONSE_CANCEL);
	d->hide();
}

void ControladorPanelHerramientas::on_boton_Agregar_Entidad_click() {
#ifdef DEBUG
	cout << "Agregar Entidad" << endl;
#endif
	VistaEntidadNueva *nuevaEntidad = ComponentsBuilder::getInstance()->crearEntidadNuevaEnDiagrama(
			NULL, NULL);
#ifdef DEBUG
	cout << "Vuelve" << endl;
#endif
	if (nuevaEntidad->lanzarProp()) {

	} else {
		delete nuevaEntidad;
	}
	Ide::getInstance()->regenerarTreePanel();
}

void ControladorPanelHerramientas::on_boton_Agregar_Relacion_click() {
#ifdef DEBUG
	cout << "Agregar Relacion" << endl;
#endif
	VistaRelacion * nuevaRelacion = ComponentsBuilder::getInstance()->crearRelacionEnDiagrama(
			Ide::getInstance()->getDiagActual(), NULL);

	if (nuevaRelacion->lanzarProp()) {

	} else {
		delete nuevaRelacion;
	}
	Ide::getInstance()->regenerarTreePanel();
}

void ControladorPanelHerramientas::on_boton_Agregar_Jerarquia_click() {
#ifdef DEBUG
	cout << "Agregar Jerarquia" << endl;
#endif
	VistaJerarquia *nuevaJerarquia = ComponentsBuilder::getInstance()->crearJerarquiaEnDiagrama(
			NULL, NULL);
	Ide::getInstance()->regenerarTreePanel();
	nuevaJerarquia->lanzarProp();
}


void ControladorPanelHerramientas::on_boton_Agregar_EntidadGlobal_click() {
#ifdef DEBUG
	cout << "Agregar EntidadGlobal" << endl;
#endif
	AsistenteEntGlobal* nuevaProp;
	Glib::RefPtr<Gtk::Builder> nHbuilder = Gtk::Builder::create_from_file(ARCH_GLADE_ENTGLOB);
	nHbuilder->get_widget_derived("PropEntGlob", nuevaProp);
	nuevaProp->show();
}

void ControladorPanelHerramientas::on_boton_Aumentar_Zoom_click() {
	Ide::getInstance()->getDiagActual()->aumentarZoom();
}

void ControladorPanelHerramientas::on_boton_Reducir_Zoom_click() {
	Ide::getInstance()->getDiagActual()->disminuirZoom();
}

void ControladorPanelHerramientas::on_boton_Restablecer_Zoom_click() {
	Ide::getInstance()->getDiagActual()->restablecerZoom();
}

void ControladorPanelHerramientas::enlazar_botones_de_menu(
		const Glib::RefPtr<Gtk::Builder>& builder) {
	builder->get_widget("TBAgregarDiagrama", botonAgregarDiagrama);
	botonAgregarDiagrama->signal_clicked().connect(
			sigc::mem_fun(*this, &ControladorPanelHerramientas::on_boton_Agregar_Diagrama_click));
	builder->get_widget("TBEliminarDiagrama", botonEliminarDiagrama);
	botonEliminarDiagrama->signal_clicked().connect(
			sigc::mem_fun(*this, &ControladorPanelHerramientas::on_boton_Eliminar_Diagrama_click));
	builder->get_widget("TBAgregarEntidad", botonAgregarEntidad);
	botonAgregarEntidad->signal_clicked().connect(
			sigc::mem_fun(*this, &ControladorPanelHerramientas::on_boton_Agregar_Entidad_click));
	builder->get_widget("TBAgregarRelacion", botonAgregarRelacion);
	botonAgregarRelacion->signal_clicked().connect(
			sigc::mem_fun(*this, &ControladorPanelHerramientas::on_boton_Agregar_Relacion_click));
	builder->get_widget("TBAgregarJerarquia", botonAgregarJerarquia);
	botonAgregarJerarquia->signal_clicked().connect(
			sigc::mem_fun(*this, &ControladorPanelHerramientas::on_boton_Agregar_Jerarquia_click));
	builder->get_widget("TBAgregarEntidadGlobal", botonAgregarEntidadGlobal);
	botonAgregarEntidadGlobal->signal_clicked().connect(
			sigc::mem_fun(*this,
					&ControladorPanelHerramientas::on_boton_Agregar_EntidadGlobal_click));
	builder->get_widget("TBZoom+", botonAumentarZoom);
	botonAumentarZoom->signal_clicked().connect(
			sigc::mem_fun(*this, &ControladorPanelHerramientas::on_boton_Aumentar_Zoom_click));
	builder->get_widget("TBZoom-", botonReducirZoom);
	botonReducirZoom->signal_clicked().connect(
			sigc::mem_fun(*this, &ControladorPanelHerramientas::on_boton_Reducir_Zoom_click));
	builder->get_widget("TBZoomNormal", botonRestablecerZoom);
	botonRestablecerZoom->signal_clicked().connect(
			sigc::mem_fun(*this, &ControladorPanelHerramientas::on_boton_Restablecer_Zoom_click));
}

void ControladorPanelHerramientas::activarBotones() {
	botonAgregarEntidad->set_sensitive(true);
	botonAgregarRelacion->set_sensitive(true);
	botonAgregarJerarquia->set_sensitive(true);
	botonAgregarEntidadGlobal->set_sensitive(true);
	botonAgregarDiagrama->set_sensitive(true);
	botonEliminarDiagrama->set_sensitive(true);
	botonAumentarZoom->set_sensitive(true);
	botonReducirZoom->set_sensitive(true);
	botonRestablecerZoom->set_sensitive(true);
}

void ControladorPanelHerramientas::desactivarBotones() {
	botonAgregarEntidad->set_sensitive(false);
	botonAgregarRelacion->set_sensitive(false);
	botonAgregarJerarquia->set_sensitive(false);
	botonAgregarEntidadGlobal->set_sensitive(false);
	botonAgregarDiagrama->set_sensitive(false);
	botonEliminarDiagrama->set_sensitive(false);
	botonAumentarZoom->set_sensitive(false);
	botonReducirZoom->set_sensitive(false);
	botonRestablecerZoom->set_sensitive(false);
}
