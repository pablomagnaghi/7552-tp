#include "Diagrama.h"

#include <algorithm>

Diagrama::Diagrama() :
		estado(DIAGRAMA_SIN_VALIDAR), diagramaAncestro(NULL), diagramaValidoCOMP(false) {

}

Diagrama::Diagrama(const std::string nombre) :
		nombre(nombre), estado(DIAGRAMA_SIN_VALIDAR), diagramaAncestro(NULL), diagramaValidoCOMP(
				false) {

}

Diagrama::~Diagrama() {
	this->borrarDiagramasHijos();
	this->borrarEntidadesNuevas();
	this->borrarEntidadesGlobales();
	this->borrarRelaciones();
	this->borrarJerarquias();
}

void Diagrama::setNombre(const std::string nombre) {
	this->nombre = nombre;
}

std::string Diagrama::getNombre() const {
	return this->nombre;
}

void Diagrama::setEstado(const std::string estado) {
	this->estado = estado;
}

std::string Diagrama::getEstado() const {
	return this->estado;
}

void Diagrama::setDiagramaAncestro(Diagrama* diagramaAncestro) {
	this->diagramaAncestro = diagramaAncestro;
}

Diagrama* Diagrama::getDiagramaAncestro() const {
	return this->diagramaAncestro;
}

void Diagrama::setNombreDiagramaAncestro(const std::string& nombre) {
	this->nombreDiagramaAncestro = nombre;
}
std::string Diagrama::getNombreDiagramaAncestro() const {
	return this->nombreDiagramaAncestro;
}

void Diagrama::agregarDiagramaHijo(Diagrama* diagramaHijo) {
	this->diagramasHijos.push_back(diagramaHijo);
}

void Diagrama::quitarDiagramaHijo(Diagrama* diagramaHijo) {
	std::vector<Diagrama*>::iterator e;
	e = find(this->diagramasHijos.begin(), this->diagramasHijos.end(), diagramaHijo);
	if (*e == diagramaHijo) {
		this->diagramasHijos.erase(e);
	}
}

void Diagrama::agregarComponente(Componente* componente) {
	this->componentes.push_back(componente);
}


void Diagrama::agregarEntidad(Entidad* entidad) {
	this->entidades.push_back(entidad);
}

void Diagrama::quitarEntidad(Entidad* entidad) {
	std::vector<Entidad*>::iterator e;
	e = find(this->entidades.begin(), this->entidades.end(), entidad);
	if (*e == entidad) {
		this->entidades.erase(e);
	}
}

void Diagrama::agregarEntidadNueva(EntidadNueva* entidadNueva) {
	this->entidadesNuevas.push_back(entidadNueva);
	this->agregarComponente(entidadNueva);
	this->agregarEntidad(entidadNueva);
}

void Diagrama::quitarEntidadNueva(EntidadNueva* entidadNueva) {
	std::vector<EntidadNueva*>::iterator e;
	e = find(this->entidadesNuevas.begin(), this->entidadesNuevas.end(), entidadNueva);
	if (*e == entidadNueva) {
		this->entidadesNuevas.erase(e);
	}
	this->quitarComponente(entidadNueva);
	this->quitarEntidad(entidadNueva);
}

void Diagrama::agregarEntidadGlobal(EntidadGlobal* entidadGlobal) {
	this->entidadesGlobales.push_back(entidadGlobal);
	this->agregarComponente(entidadGlobal);
	this->agregarEntidad(entidadGlobal);
}

void Diagrama::quitarEntidadGlobal(EntidadGlobal* entidadGlobal) {
	std::vector<EntidadGlobal*>::iterator e;
	e = find(this->entidadesGlobales.begin(), this->entidadesGlobales.end(), entidadGlobal);
	if (*e == entidadGlobal) {
		this->entidadesGlobales.erase(e);
	}
	this->quitarComponente(entidadGlobal);
	this->quitarEntidad(entidadGlobal);
}

void Diagrama::agregarRelacion(Relacion* relacion) {
	this->relaciones.push_back(relacion);
	this->agregarComponente(relacion);
}

void Diagrama::quitarRelacion(Relacion* relacion) {
	std::vector<Relacion*>::iterator e;
	e = find(this->relaciones.begin(), this->relaciones.end(), relacion);
	if (*e == relacion) {
		this->relaciones.erase(e);
	}
	this->quitarComponente(relacion);
}

void Diagrama::agregarJerarquia(Jerarquia* jerarquia) {
	this->jerarquias.push_back(jerarquia);
	this->agregarComponente(jerarquia);
}

void Diagrama::quitarJerarquia(Jerarquia* jerarquia) {
	std::vector<Jerarquia*>::iterator e;
	e = find(this->jerarquias.begin(), this->jerarquias.end(), jerarquia);
	if (*e == jerarquia) {
		this->jerarquias.erase(e);
	}
	this->quitarComponente(jerarquia);
}

void Diagrama::quitarComponente(Componente * componente) {
	if (componente != NULL) {
		remove(this->componentes.begin(), this->componentes.end(), componente);
		remove(this->entidades.begin(), this->entidades.end(), static_cast<Entidad *>(componente));
		remove(this->entidadesNuevas.begin(), this->entidadesNuevas.end(),
				static_cast<EntidadNueva *>(componente));
		remove(this->entidadesGlobales.begin(), this->entidadesGlobales.end(),
				static_cast<EntidadGlobal *>(componente));
		remove(this->relaciones.begin(), this->relaciones.end(),
				static_cast<Relacion *>(componente));
		remove(this->jerarquias.begin(), this->jerarquias.end(),
				static_cast<Jerarquia *>(componente));
	}
}

std::vector<Diagrama*>::iterator Diagrama::diagramasHijosBegin() {
	return this->diagramasHijos.begin();
}

std::vector<Diagrama*>::iterator Diagrama::diagramasHijosEnd() {
	return this->diagramasHijos.end();
}

std::vector<EntidadNueva*>::iterator Diagrama::entidadesNuevasBegin() {
	return this->entidadesNuevas.begin();
}

std::vector<EntidadNueva*>::iterator Diagrama::entidadesNuevasEnd() {
	return this->entidadesNuevas.end();
}

std::vector<EntidadGlobal*>::iterator Diagrama::entidadesGlobalesBegin() {
	return this->entidadesGlobales.begin();
}

std::vector<EntidadGlobal*>::iterator Diagrama::entidadesGlobalesEnd() {
	return this->entidadesGlobales.end();
}

std::vector<Relacion*>::iterator Diagrama::relacionesBegin() {
	return this->relaciones.begin();
}

std::vector<Relacion*>::iterator Diagrama::relacionesEnd() {
	return this->relaciones.end();
}

std::vector<Jerarquia*>::iterator Diagrama::jerarquiasBegin() {
	return this->jerarquias.begin();
}

std::vector<Jerarquia*>::iterator Diagrama::jerarquiasEnd() {
	return this->jerarquias.end();
}

std::vector<Componente*>::iterator Diagrama::componentesBegin() {
	return this->componentes.begin();
}

std::vector<Componente*>::iterator Diagrama::componentesEnd() {
	return this->componentes.end();
}

std::vector<Entidad*>::iterator Diagrama::entidadesBegin() {
	return this->entidades.begin();
}

std::vector<Entidad*>::iterator Diagrama::entiadadesEnd() {
	return this->entidades.end();
}

std::vector<std::string>::iterator Diagrama::nombresDiagramasHijosBegin() {
	return this->nombreDiagramasHijos.begin();
}

std::vector<std::string>::iterator Diagrama::nombresDiagramasHijosEnd() {
	return this->nombreDiagramasHijos.end();
}

void Diagrama::borrarDiagramasHijos() {
	std::vector<Diagrama*>::iterator it = this->diagramasHijos.begin();
	while (it != this->diagramasHijos.end()) {
		delete (*it);
		it++;
	}
	this->diagramasHijos.clear();
}

void Diagrama::borrarEntidadesNuevas() {
	std::vector<EntidadNueva*>::iterator it = this->entidadesNuevas.begin();
	while (it != this->entidadesNuevas.end()) {
		delete (*it);
		it++;
	}
	this->entidadesNuevas.clear();
}

void Diagrama::borrarEntidadesGlobales() {
	std::vector<EntidadGlobal*>::iterator it = this->entidadesGlobales.begin();
	while (it != this->entidadesGlobales.end()) {
		delete (*it);
		it++;
	}
	this->entidadesGlobales.clear();
}

void Diagrama::borrarRelaciones() {
	std::vector<Relacion*>::iterator it = this->relaciones.begin();
	while (it != this->relaciones.end()) {
		delete (*it);
		it++;
	}
	this->relaciones.clear();
}

void Diagrama::borrarJerarquias() {
	std::vector<Jerarquia*>::iterator it = this->jerarquias.begin();
	while (it != this->jerarquias.end()) {
		delete (*it);
		it++;
	}
	this->jerarquias.clear();
}

Entidad* Diagrama::getEntidadByCodigo(int codigo) {
	Entidad* entidad = this->getEntidadNuevaByCodigo(codigo);
	if (entidad == NULL) {
		entidad = this->getEntidadGlobalByCodigo(codigo);
	}
	return entidad;
}

EntidadNueva* Diagrama::getEntidadNuevaByCodigo(int codigo) {
	EntidadNueva* entidadNueva = NULL;
	std::vector<EntidadNueva*>::iterator it = this->entidadesNuevas.begin();
	while (it != this->entidadesNuevas.end()) {
		if ((*it)->getCodigo() == codigo) {
			entidadNueva = *it;
		}
		it++;
	}
	return entidadNueva;
}

EntidadGlobal* Diagrama::getEntidadGlobalByCodigo(int codigo) {
	EntidadGlobal* entidadGlobal = NULL;
	std::vector<EntidadGlobal*>::iterator it = this->entidadesGlobales.begin();
	while (it != this->entidadesGlobales.end()) {
		if ((*it)->getCodigo() == codigo) {
			entidadGlobal = *it;
		}
		it++;
	}
	return entidadGlobal;
}

Relacion* Diagrama::getRelacionByCodigo(int codigo) {
	Relacion* relacion = NULL;
	std::vector<Relacion*>::iterator it = this->relaciones.begin();
	while (it != this->relaciones.end()) {
		if ((*it)->getCodigo() == codigo) {
			relacion = *it;
		}
		it++;
	}
	return relacion;
}

Jerarquia* Diagrama::getJerarquiaByCodigo(int codigo) {
	Jerarquia* jerarquia = NULL;
	std::vector<Jerarquia*>::iterator it = this->jerarquias.begin();
	while (it != this->jerarquias.end()) {
		if ((*it)->getCodigo() == codigo) {
			jerarquia = *it;
		}
		it++;
	}
	return jerarquia;
}

Componente* Diagrama::getComponenteByCodigo(int codigo) {
	Componente* componente = NULL;
	std::vector<Componente*>::iterator it = this->componentes.begin();
	while (it != this->componentes.end()) {
		if ((*it)->getCodigo() == codigo) {
			componente = *it;
		}
		it++;
	}
	return componente;
}

bool Diagrama::existeDiagrama(const std::string& nombre) {
	std::string nombreMin = Utils::toLowerCase(nombre);
	std::vector<Diagrama*>::iterator it = this->diagramasHijos.begin();
	while (it != this->diagramasHijos.end()) {
		if ((Utils::toLowerCase((*it)->getNombre())).compare(nombreMin) == 0) {
			return true;
		} else if ((*it)->existeDiagrama(nombre)) {
			return true;
		}
		it++;
	}
	return false;
}

bool Diagrama::existeEntidadNueva(const std::string& nombre) {
	std::string nombreMin = Utils::toLowerCase(nombre);
	std::vector<EntidadNueva*>::iterator itE = this->entidadesNuevas.begin();
	while (itE != this->entidadesNuevas.end()) {
		if (Utils::toLowerCase((*itE)->getNombre()).compare(nombreMin) == 0) {
			return true;
		}
		itE++;
	}
	std::vector<Diagrama*>::iterator it = this->diagramasHijos.begin();
	while (it != this->diagramasHijos.end()) {
		if ((*it)->existeEntidadNueva(nombre)) {
			return true;
		}
		it++;
	}
	return false;
}

bool Diagrama::existeEntidadGlobal(const std::string& nombre) {
	std::string nombreMin = Utils::toLowerCase(nombre);
	std::vector<EntidadGlobal*>::iterator itE = this->entidadesGlobales.begin();
	while (itE != this->entidadesGlobales.end()) {
		if (Utils::toLowerCase((*itE)->getNombre()).compare(nombreMin) == 0) {
			return true;
		}
		itE++;
	}
	std::vector<Diagrama*>::iterator it = this->diagramasHijos.begin();
	while (it != this->diagramasHijos.end()) {
		if ((*it)->existeEntidadGlobal(nombre)) {
			return true;
		}
		it++;
	}
	return false;
}

// PERSISTENCIA COMP

// Devuelve true si se logró abrir y cargar el documento.
bool Diagrama::isOpenXmlCOMP() const {
	return this->diagramaValidoCOMP;
}

// CARGAR

// Abre un archivo xml, y carga un diagrama con la informacion que contenga.
void Diagrama::abrirXmlCOMP(const std::string& path) {
	try {
		// Abro el archivo
		Xml docXml(path);
		this->diagramaValidoCOMP = true;

		XmlNodo* nodoRaiz = docXml.getNodoRaiz();
		XmlNodo::verificarNombre(NOMBRE_DIAGRAMA, *nodoRaiz);
		this->cargarXmlCOMP(nodoRaiz);
	} catch (XmlArchivoInexistenteExc* ex) {
		delete ex;
		throw new DiagramaArchivoInexistenteExc(path);
	} catch (XmlArchivoInvalidoExc* ex) {
		delete ex;
		throw new DiagramaInvalidoExc(path);
	}
}

void Diagrama::cargarXmlCOMP(XmlNodo* nodoRaiz) {
	// archivo listo para cargar los componentes del diagrama
	this->obtenerPropiedadesXmlCOMP(nodoRaiz);

	XmlNodo nodo = nodoRaiz->getHijo();
	this->obtenerComponentesXmlCOMP(&nodo);

	this->cargarComponentes();

	this->cargarDiagramasHijos();
}

void Diagrama::obtenerPropiedadesXmlCOMP(XmlNodo* nodo) {
	this->nombre = nodo->getPropiedad("nombre");
}

void Diagrama::obtenerComponentesXmlCOMP(XmlNodo* nodo) {
	while (nodo->esValido()) {
		if (nodo->getNombre() == "diagrama_hijo") {
			std::string nombreDiagramaHijo = nodo->getContenido();
			this->nombreDiagramasHijos.push_back(nombreDiagramaHijo);
		}
		if (nodo->getNombre() == "entidad_nueva") {
			EntidadNueva *entidadNueva = new EntidadNueva(nodo);
			this->agregarEntidadNueva(entidadNueva);
			this->agregarComponente(entidadNueva);
			this->agregarEntidad(entidadNueva);
		}
		if (nodo->getNombre() == "entidad_global") {
			EntidadGlobal *entidadGlobal = new EntidadGlobal(nodo);
			this->agregarEntidadGlobal(entidadGlobal);
			this->agregarComponente(entidadGlobal);
			this->agregarEntidad(entidadGlobal);
		}
		if (nodo->getNombre() == "relacion") {
			Relacion *relacion = new Relacion(nodo);
			this->agregarRelacion(relacion);
			this->agregarComponente(relacion);
		}
		if (nodo->getNombre() == "jerarquia") {
			Jerarquia *jerarquia = new Jerarquia(nodo);
			this->agregarJerarquia(jerarquia);
			this->agregarComponente(jerarquia);
		}
		*nodo = nodo->getHermano();
	}
}

void Diagrama::cargarComponentes() {
	this->cargarEntidadesGlobales();
	this->cargarUnionesEntidadRelacion();
	this->cargarEntidadesYJerarquias();
}

void Diagrama::cargarEntidadesGlobales() {
	std::vector<EntidadGlobal*>::iterator it = this->entidadesGlobales.begin();
	while (it != this->entidadesGlobales.end()) {
		Diagrama *diagramaAux = this->diagramaAncestro;
		bool salir = false;
		while ((diagramaAux) && (!salir)) {
			// busco el diagrama ancestro por el nombre para obtener la entidadNueva
			if (diagramaAux->getNombre() == (*it)->getDiagramaAncestro()) {
				// Agrego la entidadNueva a la entidadGlobal
				EntidadNueva *entidadNueva = diagramaAux->getEntidadNuevaByCodigo(
						(*it)->getCodigoEntidadNueva());
				(*it)->setEntidadNueva(entidadNueva);
				salir = true;
			}
			diagramaAux = diagramaAux->getDiagramaAncestro();
		}
		it++;
	}
}

void Diagrama::cargarUnionesEntidadRelacion() {
	std::vector<Relacion*>::iterator it = this->relacionesBegin();
	while (it != this->relacionesEnd()) {
		std::vector<UnionEntidadRelacion*>::iterator itUnion = (*it)->unionesAEntidadBegin();
		// Para cada union agrego la entidad a traves de una busqueda por su codigo
		// Ademas agrego la relacion
		while (itUnion != (*it)->unionesAEntidadEnd()) {
			Entidad *entidad = this->getEntidadByCodigo((*itUnion)->getCodigoEntidad());
			(*itUnion)->setEntidad(entidad);
			(*itUnion)->setRelacion((*it));
			// agregar a entidad la union entidad relacion
			entidad->agregarUnionARelacion((*itUnion));
			itUnion++;
		}
		it++;
	}
}

void Diagrama::cargarEntidadesYJerarquias() {
	std::vector<Jerarquia*>::iterator it = this->jerarquiasBegin();
	while (it != this->jerarquiasEnd()) {
		Entidad *entidad = this->getEntidadByCodigo((*it)->getCodigoEntidadGeneral());
		(*it)->setEntidadGeneral(entidad);
		// agrego la jerarquia a la entidad, o sea agrego la jerarquia hija
		entidad->setJerarquiaHija((*it));

		std::vector<int>::iterator itEntidadesNuevas = (*it)->codigosEntidadesEspecializadasBegin();
		// Para cada jerarquia agrego la entidad nueva a traves de una busqueda por su codigo
		while (itEntidadesNuevas != (*it)->codigosEntidadesEspecializadasEnd()) {
			EntidadNueva *entidadNueva = this->getEntidadNuevaByCodigo((*itEntidadesNuevas));
			(*it)->agregarEntidadEspecializada(entidadNueva);

			// agrego la jerarquia a la entidad nueva, o sea agrego la jerarquia padre
			entidadNueva->agregarJerarquiaPadre((*it));
			itEntidadesNuevas++;
		}
		it++;
	}
}

void Diagrama::cargarDiagramasHijos() {
	std::vector<std::string>::iterator it = this->nombresDiagramasHijosBegin();
	while (it != this->nombresDiagramasHijosEnd()) {
		std::string nombre = (*it);
		Diagrama *diagramaHijo = new Diagrama(nombre);
		diagramaHijo->setDiagramaAncestro(this);
		nombre += EXTENSION_COMP;
		diagramaHijo->abrirXmlCOMP(nombre);
		this->agregarDiagramaHijo(diagramaHijo);
		it++;
		nombre.clear();
	}
}

// GUARDAR

// Guarda el Diagrama
void Diagrama::guardarDiagramaXmlCOMP(const std::string& path) {
	Xml docXml;
	docXml.nuevoDoc();
	XmlNodo nodoDoc = this->guardarXmlCOMP();
	docXml.setNodoRaiz(nodoDoc);
	docXml.guardar(path);
}

XmlNodo Diagrama::guardarXmlCOMP() {
	XmlNodo nodo("diagrama");

	this->agregarPropiedadesXmlCOMP(&nodo);

	// puede no tener diagrama ancestro
	if (diagramaAncestro) {
		this->agregarNodoDiagramaAncestroXmlCOMP(&nodo);
	}

	this->guardarDiagramasHijosXmlCOMP(&nodo);
	this->guardarEntidadesNuevasXmlCOMP(&nodo);
	this->guardarEntidadesGlobalesXmlCOMP(&nodo);
	this->guardarRelacionesXmlCOMP(&nodo);
	this->guardarJerarquiasXmlCOMP(&nodo);

	return nodo;
}

void Diagrama::agregarPropiedadesXmlCOMP(XmlNodo* nodo) {
	nodo->setPropiedad(XMLNS, INSTANCE);
	nodo->setPropiedad(XSI, COMPOSICION);
	nodo->setPropiedad("nombre", this->nombre);
}

void Diagrama::agregarNodoDiagramaAncestroXmlCOMP(XmlNodo *nodo) {
	XmlNodo nodoDiagramaAncestro("diagrama_ancestro");
	nodoDiagramaAncestro.setContenido(this->diagramaAncestro->getNombre());
	nodo->agregarHijo(nodoDiagramaAncestro);
}

void Diagrama::guardarDiagramasHijosXmlCOMP(XmlNodo *nodo) {
	std::vector<Diagrama*>::iterator i;

	for (i = this->diagramasHijosBegin(); i != this->diagramasHijosEnd(); ++i) {
		XmlNodo nodoDiagramaHijo("diagrama_hijo");
		nodoDiagramaHijo.setContenido((*i)->getNombre());
		nodo->agregarHijo(nodoDiagramaHijo);
	}
}

void Diagrama::guardarEntidadesNuevasXmlCOMP(XmlNodo *nodo) {
	std::vector<EntidadNueva*>::iterator i;

	for (i = this->entidadesNuevas.begin(); i != this->entidadesNuevas.end(); ++i)
		nodo->agregarHijo((*i)->guardarXmlCOMP());
}

void Diagrama::guardarEntidadesGlobalesXmlCOMP(XmlNodo *nodo) {
	std::vector<EntidadGlobal*>::iterator i;

	for (i = this->entidadesGlobales.begin(); i != this->entidadesGlobales.end(); ++i) {
		nodo->agregarHijo((*i)->guardarXmlCOMP());
	}
}

void Diagrama::guardarRelacionesXmlCOMP(XmlNodo *nodo) {
	std::vector<Relacion*>::iterator i;

	for (i = this->relaciones.begin(); i != this->relaciones.end(); ++i)
		nodo->agregarHijo((*i)->guardarXmlCOMP());
}

void Diagrama::guardarJerarquiasXmlCOMP(XmlNodo *nodo) {
	std::vector<Jerarquia*>::iterator i;

	for (i = this->jerarquias.begin(); i != this->jerarquias.end(); ++i)
		nodo->agregarHijo((*i)->guardarXmlCOMP());
}
