#include "Ide.h"
Ide * Ide::instancia = NULL;
//VistaDiagrama * Ide::diagactual = NULL;

#ifdef DEBUG
#include <iostream>
using namespace std;
#endif

#define DEBUG_IDE 0

Ide::Ide(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder) :
		Gtk::Window(cobject), m_builder(builder), treePanel(builder, this), controladorPanelHerramientas(
				builder, static_cast<Gtk::Window *>(this)) {

	this->set_size_request(800, 600);

	// INICIALIZACION
	this->vproyecto = NULL;
	this->diagramaActual = NULL;
	this->instancia = this;
	this->expandido = true;
	this->posicion_anterior = 0;

	this->m_builder->get_widget("contenedor_diag", this->contenedorDiag);
	this->m_builder->get_widget("hpaned1", panelHorizontal);
	this->m_builder->get_widget("fixed1", fijacionTreePanel);
	this->m_builder->get_widget("togglebutton1", botonEsconderPanel);
	this->m_builder->get_widget("image3", this->flecha_izquierda);
	this->m_builder->get_widget("image4", this->flecha_derecha);
	this->m_builder->get_widget("scroll_treePanel", this->scrolledTreePanel);

	this->botonEsconderPanel->signal_toggled().connect(
			sigc::mem_fun(*this, &Ide::on_boton_esconder_panel_toggle));
	this->panelHorizontal->signal_size_request().connect(
			sigc::mem_fun(*this, &Ide::on_panel_horizontal_size_request));
	this->show();

	//TODO TEST
	//this->nuevoProyecto();
}

Ide::~Ide() {
	this->cerrarProyecto();
	// TODO Auto-generated destructor stub
}

bool Ide::hayProyecto() {
	if (this->vproyecto == NULL) {
		/*Gtk::MessageDialog mensaje(*this, "Error.", false, Gtk::MESSAGE_ERROR,
		 Gtk::BUTTONS_OK);
		 mensaje.set_secondary_text(
		 "No Hay proyecto cargado, operacion Imposible.");
		 mensaje.run();*/
		return false;
	}
	return true;
}

std::vector<std::string> Ide::obtener_nombres_diagramas_en_carpeta(const std::string & carpeta) {
	std::vector<std::string> nombres;
	std::vector<std::string> archivos;
	std::vector<std::string>::iterator it_archivos;
	std::string nombre;
	size_t pos2;
	archivos = Utils::getFiles(carpeta);

	for (it_archivos = archivos.begin(); it_archivos != archivos.end(); ++it_archivos) {
		pos2 = (*it_archivos).rfind("-COMP.xml");
		if (pos2 != std::string::npos) {
			nombre = (*it_archivos).substr(0, pos2);
			//if (nombre != "Principal") {
			nombres.push_back(nombre);
			//}
		}
	}
	return nombres;
}

bool Ide::abrir_proyecto() {
	std::string diagrama_principal;
	std::vector<std::string>::iterator it_nombres_diagramas;
	std::vector<std::string> nombres_diagramas;
	VistaDiagrama * nuevo_diagrama;

	// Pedir Carpeta donde se guarda el proyecto
	Gtk::FileChooserDialog selector("Seleccione la carpeta del proyecto",
			Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER);
	selector.set_transient_for(*this);
	selector.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	selector.add_button("Seleccionar", Gtk::RESPONSE_OK);

	selector.set_current_folder(Utils::getCurrentDirectory());

	switch (selector.run()) {
	case (Gtk::RESPONSE_OK): {
		/*std::cout << "Select clicked." << std::endl;
		 std::cout << "Folder selected: " << selector.get_filename()
		 << std::endl;*/
		this->carpetaProyecto = selector.get_filename();

		break;
	}
	case (Gtk::RESPONSE_CANCEL): {
		//std::cout << "Cancel clicked." << std::endl;
		return false;
		break;
	}
	default: {
		std::cout << "Unexpected button clicked." << std::endl;
		return false;
		break;
	}
	}

	// TODO verificar que exista una subcarpeta "DATOS" y que tenga un diagrama principal

	// Cerrar el proyecto Actual (si hay)
	this->cerrarProyecto();

	// Levantar los archivos guardados
	//this->carpetaProyecto.append("/Principal");
	diagrama_principal = this->carpetaProyecto + "/Principal";

	if (!Utils::file_exists(diagrama_principal + "-COMP.xml")
			|| !Utils::file_exists(diagrama_principal + "-REP.xml")) {
		Gtk::MessageDialog dialog(*Ide::getInstance(), "Error", false, Gtk::MESSAGE_ERROR,
				Gtk::BUTTONS_OK);
		dialog.set_secondary_text("No existe el diagrama principal");
		dialog.run();

		return false;
	}

	this->vproyecto = new VistaProyecto(new Proyecto(new Diagrama("Principal")));

	this->diagramaActual = this->vproyecto->getDiagramaPrincipal();

	// todo (Gonzalo)

	//nombres_diagramas = obtener_nombres_diagramas_en_carpeta(this->carpetaProyecto);

	//this->diagramaActual->abrirXmlDiagramas(this->carpetaProyecto, nombres_diagramas);
	this->diagramaActual->abrirXml(diagrama_principal, this->carpetaProyecto);

	// todo (Pablo)

	/*
	 nombres_diagramas = obtener_nombres_diagramas_en_carpeta(this->carpetaProyecto);

	 for (it_nombres_diagramas = nombres_diagramas.begin();
	 it_nombres_diagramas != nombres_diagramas.end(); ++it_nombres_diagramas) {
	 nuevo_diagrama = new VistaDiagrama(new Diagrama(*it_nombres_diagramas));
	 nuevo_diagrama->abrirXml(this->carpetaProyecto + "/" + (*it_nombres_diagramas));
	 }*/

	this->cargarDiagrama(this->vproyecto->getDiagramaPrincipal());

	this->controladorPanelHerramientas.activarBotones();
	this->treePanel.regenerar();

	return true;
}

bool Ide::guardar_proyecto(bool guardarComo) {
	std::string nombreProyecto;

	if (guardarComo) {
		// Pedir Carpeta donde se guarda el proyecto
		Gtk::FileChooserDialog selector("Seleccione la carpeta del proyecto",
				Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER);
		selector.set_transient_for(*this);
		selector.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
		selector.add_button("Seleccionar", Gtk::RESPONSE_OK);

		selector.set_current_folder(Utils::getCurrentDirectory());

		switch (selector.run()) {
		case (Gtk::RESPONSE_OK): {
			//std::cout << "Select clicked." << std::endl;
			//std::cout << "Folder selected: " << selector.get_filename()
			//<< std::endl;
			this->carpetaProyecto = selector.get_filename();

			nombreProyecto = Utils::getBasename(this->carpetaProyecto);

			this->set_title(nombreProyecto);

			this->vproyecto->setNombre(nombreProyecto);
			break;
		}
		case (Gtk::RESPONSE_CANCEL): {
			//std::cout << "Cancel clicked." << std::endl;
			return false;
			break;
		}
		default: {
			std::cout << "Unexpected button clicked." << std::endl;
			break;
			return false;
		}
		}
	}

	// ES PARA PROBAR, GUARDAR SIN QUE TE PIDA LA CARPETA A CADA RATO
	//this->carpetaProyecto = "/home/gonzalo/workspaces/Distribuidos/TPtaller2/proyectos/proyecto1";

	//this->debugInformarValorVariable("Nombre Proyecto", nombreProyecto);

	this->vproyecto->getDiagramaPrincipal()->guardarDiagramaXml(this->carpetaProyecto);

	return true;
}

void Ide::regenerarTreePanel() {
	this->treePanel.regenerar();
}

bool Ide::crearNuevoProyecto() {
	if (this->vproyecto == NULL) {
		this->vproyecto = new VistaProyecto(new Proyecto(new Diagrama("Principal")));
		this->cargarDiagrama(this->vproyecto->getDiagramaPrincipal());
		this->controladorPanelHerramientas.activarBotones();
		this->treePanel.regenerar();
		this->set_title("*Nuevo Proyecto");
		this->vproyecto->setNombre("*Nuevo Proyecto");
	} else {
		Gtk::MessageDialog mensaje(*this, "Error", false, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK);
		mensaje.set_secondary_text("Ya existe un proyecto");
		mensaje.run();
		return false;
	}
	return true;
}

void Ide::cargarDiagrama(VistaDiagrama* diagrama) {

	//Primero tengo que sacar el diag actual
	if (diagramaActual != NULL) {
		this->contenedorDiag->remove(*diagramaActual);
	}

#if DEBUG_IDE==1
	cout << "ANCHO:" << diagrama->getAncho();
	cout << "ALTO:" << diagrama->getAlto() << endl;
#endif

	this->contenedorDiag->set_size_request(diagrama->getAncho(), diagrama->getAlto());
	this->contenedorDiag->put(*diagrama, 0, 0);
	diagramaActual = diagrama;
	//diagrama->set_parent(*this->contenedorDiag);

	//diagrama->show();
	this->contenedorDiag->show_all();
	diagramaActual->setPanel(&this->treePanel);
	this->set_title(this->vproyecto->getNombre() + " : " + diagramaActual->getNombre());
}

VistaDiagrama* Ide::getDiagActual() {
	VistaDiagrama *d = diagramaActual;
	return d;
}

Ide * Ide::getInstance() {
	if (Ide::instancia != NULL) {
		return Ide::instancia;
	} else {
		return Ide::instancia;
	}
}

bool Ide::cerrarProyecto() {

	// PEDIR CONFIRMACION

	//Primero tengo que sacar el diagrama actual
	if (this->vproyecto != NULL) {
		this->contenedorDiag->remove(*(diagramaActual));

		delete this->vproyecto;

		this->vproyecto = NULL;
		this->diagramaActual = NULL;

		this->treePanel.regenerar();

		this->controladorPanelHerramientas.desactivarBotones();
	}

	return true;
}

void Ide::exportar_diagrama() {
	std::string filename;
	double offset_x, offset_y, ancho_imagen, alto_imagen;
	double margen_x = 20, margen_y = 20;
	double ajuste_zoom;
	std::string type;
	// Pedir Carpeta donde se guarda el proyecto
	Gtk::FileChooserDialog selector("Seleccione la carpeta del proyecto",
			Gtk::FILE_CHOOSER_ACTION_SAVE);
	selector.set_transient_for(*this);
	selector.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	selector.add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);

	selector.set_current_folder(Utils::getCurrentDirectory());

	Gtk::FileFilter filter_png;
	filter_png.set_name("Png files");
	filter_png.add_pattern("*.png");
	selector.add_filter(filter_png);
	Gtk::FileFilter filter_jpg;
	filter_jpg.set_name("Jpg files");
	filter_jpg.add_pattern("*.jpg");
	selector.add_filter(filter_jpg);

	switch (selector.run()) {
	case (Gtk::RESPONSE_OK): {

		filename = selector.get_filename();
		if (selector.get_filter() == &filter_jpg) {
			type = "jpeg";
			if (filename.find(".jpg", filename.length() - 4, 4) == string::npos) {
				filename.append(".jpg");
			}
			//this->debugInformarValorVariable("FILTER JPG", filename);
		}
		if (selector.get_filter() == &filter_png) {
			type = "png";
			if (filename.find(".png", filename.length() - 4, 4) == string::npos) {
				filename.append(".png");
			}
			//this->debugInformarValorVariable("FILTER PNG", filename);
		}
		break;
	}
	case (Gtk::RESPONSE_CANCEL): {
		//std::cout << "Cancel clicked." << std::endl;
		return;
		break;
	}
	default: {
		std::cout << "Unexpected button clicked." << std::endl;
		return;
		break;
	}

	}

	this->diagramaActual->getDimensionesDelDiagrama(offset_x, offset_y, ancho_imagen, alto_imagen);

	ajuste_zoom = 5;

	Cairo::RefPtr<Cairo::ImageSurface> surface = Cairo::ImageSurface::create(Cairo::FORMAT_ARGB32,
			ancho_imagen * ajuste_zoom + margen_x, alto_imagen * ajuste_zoom + margen_y);

	Cairo::RefPtr<Cairo::Context> cr = Cairo::Context::create(surface);
	cr->set_source_rgba(1, 1, 1, 1); // white
	cr->paint();
	cr->translate(margen_x / 2 - offset_x * ajuste_zoom, margen_y / 2 - offset_y * ajuste_zoom);
	cr->scale(ajuste_zoom, ajuste_zoom);

	this->diagramaActual->dibujarComponentes(cr, false);

	Glib::RefPtr<Gdk::Pixbuf> pixbuf = Gdk::Pixbuf::create_from_data(surface->get_data(),
			Gdk::COLORSPACE_RGB, true, 8, ancho_imagen * ajuste_zoom + margen_x,
			alto_imagen * ajuste_zoom + margen_y, surface->get_stride());

	pixbuf->save(filename, type);

}

void Ide::debugInformarValorVariable(const std::string & nombreVariable,
		const std::string & valor) {
	Gtk::MessageDialog mensaje(*this, nombreVariable, false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK);

	mensaje.set_secondary_text(valor);
	mensaje.run();
}

void Ide::on_boton_esconder_panel_toggle() {
	int w, h;
	//this->fijacionTreePanel->get_size_request(w, h);
	if (this->expandido) {
		this->posicion_anterior = this->panelHorizontal->get_position();
		cout << "off" << endl;
		this->expandido = false;
		this->botonEsconderPanel->set_image(*this->flecha_derecha);
		//this->fijacionTreePanel->set_size_request(24, h);
		this->panelHorizontal->set_position(24);
		this->treePanel.set_visible(false);
	} else {
		cout << "on" << endl;
		this->expandido = true;
		this->botonEsconderPanel->set_image(*this->flecha_izquierda);
		//this->fijacionTreePanel->set_size_request(this->posicion_anterior, h);
		this->panelHorizontal->set_position(this->posicion_anterior);
		this->panelHorizontal->get_size_request(w, h);
		this->treePanel.set_size_request(this->posicion_anterior - 15, h);
		this->treePanel.set_visible(true);
	}
	this->panelHorizontal->check_resize();
	this->panelHorizontal->queue_resize();
}

void Ide::on_panel_horizontal_size_request(Gtk::Requisition* const & requisition) {
	int w, h;
	this->get_size_request(w, h);
	if (this->panelHorizontal->get_position() < 24) {
		this->panelHorizontal->set_position(24);
	}
	if (this->expandido == false) {
		this->panelHorizontal->set_position(24);
	}

	this->treePanel.set_size_request(this->panelHorizontal->get_position(), -1);

	this->panelHorizontal->get_size_request(w, h);
	Gtk::Allocation alloc = this->panelHorizontal->get_allocation();
#if DEBUG_IDE==1
	std::cout << "hpaned1 w: " << w << " h: " << h << endl;
	this->fijacionTreePanel->get_size_request(w, h);
	std::cout << "fixed1 w: " << w << " h: " << h << endl;
#endif
	this->treePanel.get_size_request(w, h);
#if DEBUG_IDE==1
	std::cout << "treePanel w: " << w << " h: " << h << endl;
#endif
	if (alloc.get_height() >= 25) {
		this->scrolledTreePanel->set_size_request(w, alloc.get_height() - 25);
	}
#if DEBUG_IDE==1
	this->scrolledTreePanel->get_size_request(w, h);
	std::cout << "scrolledTreePanel w: " << w << " h: " << h << endl;
	std::cout << "posicion: " << this->panelHorizontal->get_position() << std::endl;
#endif
}

