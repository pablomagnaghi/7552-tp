#include "Ide.h"
Ide * Ide::instancia = NULL;
//VistaDiagrama * Ide::diagactual = NULL;

Ide::Ide(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder) :
		Gtk::Window(cobject), m_builder(builder), treePanel(builder, this), controladorPanelHerramientas(
				builder, static_cast<Gtk::Window *>(this)) {

	this->set_size_request(800, 600);

	// INICIALIZACION
	this->vproyecto = NULL;
	this->instancia = this;

	this->m_builder->get_widget("contenedor_diag", this->contenedorDiag);

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

bool Ide::abrir_proyecto() {
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
		break;
	}
	}

	// TODO verificar que exista una subcarpeta "DATOS" y que tenga un diagrama principal

	// Cerrar el proyecto Actual (si hay)

	// Levantar los archivos guardados

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
			break;
		}
		}
	}

	nombreProyecto = Utils::getBasename(this->carpetaProyecto);

	this->set_title(nombreProyecto);

	this->vproyecto->setNombre(nombreProyecto);

	this->debugInformarValorVariable("Nombre Proyecto", nombreProyecto);

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
		this->contenedorDiag->remove(*(diagramaActual));
	}

#ifdef DEBUG
	cout << "ANCHO:" << diagrama->getAncho();
	cout << "ALTO:" << diagrama->getAlto() << endl;
#endif

	this->contenedorDiag->set_size_request(diagrama->getAncho(), diagrama->getAlto());
	this->contenedorDiag->put(*diagrama, 0, 0);
	diagramaActual = diagrama;

	//diagrama->show();
	this->contenedorDiag->show_all();
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
	}

	return true;
}

void Ide::debugInformarValorVariable(const std::string & nombreVariable,
		const std::string & valor) {
	Gtk::MessageDialog mensaje(*this, nombreVariable, false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK);

	mensaje.set_secondary_text(valor);
	mensaje.run();
}
