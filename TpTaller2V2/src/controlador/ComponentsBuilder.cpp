/*
 * ComponentsBuilder.cpp
 *
 *  Created on: 21/07/2012
 *      Author: Guagnini Enzo 88325
 */
#include "../vista/Ide.h"
#include "ComponentsBuilder.h"

ComponentsBuilder * ComponentsBuilder::instancia = NULL;

ComponentsBuilder::ComponentsBuilder() {
	// TODO Auto-generated constructor stub

}

ComponentsBuilder::~ComponentsBuilder() {
	// TODO Auto-generated destructor stub
}

ComponentsBuilder * ComponentsBuilder::getInstance() {
	if (ComponentsBuilder::instancia != NULL) {
		return ComponentsBuilder::instancia;
	} else {
		ComponentsBuilder::instancia = new ComponentsBuilder();
		return ComponentsBuilder::instancia;
	}
}

VistaEntidadNueva * ComponentsBuilder::crearEntidadNuevaEnDiagrama(VistaDiagrama *diagramaActual =
		NULL, EntidadNueva *entidadNueva = NULL) {
	if (diagramaActual == NULL) {
		diagramaActual = Ide::getInstance()->getDiagActual();
	}
	if (entidadNueva == NULL) {
		// Crea la entidad y la agrega al diagrama del modelo
		entidadNueva = new EntidadNueva();
		diagramaActual->getDiagrama()->agregarEntidadNueva(entidadNueva);
	}
	VistaEntidadNueva * vEntidadNueva = new VistaEntidadNueva(entidadNueva);
	// AGREGAR COMPONENTE LO VOY A SACAR
	//diagramaActual->agregarComponente(vEntidadNueva);
	diagramaActual->agregarVistaEntidadNueva(vEntidadNueva);
	return vEntidadNueva;
}

VistaAtributo * ComponentsBuilder::crearAtributoEnEntidad(VistaEntidadNueva *ventidad,
		VistaDiagrama *diagramaActual = NULL, Atributo *atrib = NULL) {
	if (ventidad != NULL) {
		if (diagramaActual == NULL) {
			diagramaActual = Ide::getInstance()->getDiagActual();
		}
		if (atrib == NULL) {
			// Crea el atributo y lo agrega a la entidad del modelo
			atrib = new Atributo();
			ventidad->getEntidad()->agregarAtributo(atrib);
		}

		//enlazar con la entidad crear union, poner en diagrama actual,etc.
		VistaAtributo *vatrib = new VistaAtributo(atrib);
		ventidad->agregarAtributo(vatrib);
		VistaLinea * lineaEntidadAtributo = new VistaLinea();
		lineaEntidadAtributo->setComponenteDesde(ventidad);
		lineaEntidadAtributo->setComponenteHasta(vatrib);

		//Agrego vatributo y vlinea a el diag
		diagramaActual->agregarComponente(vatrib);
		diagramaActual->agregarComponente(lineaEntidadAtributo);
		return vatrib;
	} else
		return NULL;
}

VistaAtributo * ComponentsBuilder::crearAtributoEnAtributo(VistaAtributo *vatribPadre,
		VistaDiagrama *diagramaActual = NULL, Atributo *atrib = NULL) {
	if (vatribPadre != NULL) {
		//enlazar con el atributo crear union, poner en diagrama actual,etc.
		if (diagramaActual == NULL) {
			diagramaActual = Ide::getInstance()->getDiagActual();
		}

		if (atrib == NULL) {
			// crea el atributo y lo agrega al atributo compuesto del modelo
			atrib = new Atributo();
			vatribPadre->getAtributo()->agregarAtributo(atrib);
		}

		VistaAtributo *vatrib = new VistaAtributo(atrib);
		vatribPadre->agregarAtributo(vatrib);
		VistaLinea * lineaAtributoAtributo = new VistaLinea();
		lineaAtributoAtributo->setComponenteDesde(vatribPadre);
		lineaAtributoAtributo->setComponenteHasta(vatrib);

		//Agrego vatributo y vlinea a el diag
		diagramaActual->agregarComponente(vatrib);
		diagramaActual->agregarComponente(lineaAtributoAtributo);
		return vatrib;
	} else
		return NULL;
}

VistaJerarquia* ComponentsBuilder::crearJerarquiaEnDiagrama(VistaDiagrama *diagramaActual,
		Jerarquia *j = NULL) {
	if (diagramaActual == NULL) {
		diagramaActual = Ide::getInstance()->getDiagActual();
	}
	if (j == NULL) {
		Jerarquia * j = new Jerarquia();
		Ide::getInstance()->getDiagActual()->getDiagrama()->agregarJerarquia(j);
	}
	VistaJerarquia * vJerarquia = new VistaJerarquia(j);

	diagramaActual->agregarComponente(vJerarquia);
	cout << "JERAQUIA CREADA EN PANEL" << endl;
	return vJerarquia;
}

/*
 VistaDiagrama* ComponentsBuilder::getDiagramaActual(){
 return this->ide->getDiagActual();
 }*/

VistaEntidadGlobal * ComponentsBuilder::crearEntidadGlobalEnDiagrama(VistaDiagrama * diagramaActual,
		const std::string & nombreEntidadNueva, EntidadGlobal * entidadGlobal) {

	// Variables Locales
	VistaDiagrama * diagramaRaiz;
	VistaEntidadGlobal * vistaEntidadGlobal;
	VistaEntidadNueva * vistaEntidadNueva;
	std::string nombreAncestro;

	//BuscarDiagramaAncestroYEntidadNueva
	//vistaEntidadGlobal = diagramaRaiz->
	vistaEntidadNueva = diagramaActual->buscarEntidadNuevaEnAncestro(nombreEntidadNueva,
			nombreAncestro);

	if (vistaEntidadNueva == NULL) {
		throw NullPointer("NUllPointer: no se encontró la Entidad Nueva");
	}

	if (!entidadGlobal) {
		// Crea la entidad y la agrega al diagrama del modelo
		entidadGlobal = new EntidadGlobal();
		entidadGlobal->setCodigo(GeneradorCodigo::getInstance()->siguienteCodigo());
	}

	entidadGlobal->setDiagramaAncestro(nombreAncestro);
	entidadGlobal->setEntidadNueva(vistaEntidadNueva->getEntidad());

	diagramaActual->getDiagrama()->agregarEntidadGlobal(entidadGlobal);
	vistaEntidadGlobal = new VistaEntidadGlobal(entidadGlobal);

	diagramaActual->agregarComponente(vistaEntidadGlobal);
	return vistaEntidadGlobal;
}

VistaRelacion * ComponentsBuilder::crearRelacionEnDiagrama(VistaDiagrama *diagramaActual,
		Relacion *) {

}

VistaAtributo * ComponentsBuilder::crearAtributoEnRelacion(VistaDiagrama *diagramaActual,
		VistaRelacion * relacion, Atributo * atributo) {

}

VistaIdentificador * ComponentsBuilder::crearIdentificadorEnEntidad(VistaDiagrama *diagramaActual,
		VistaEntidadNueva *, Identificador*) {

}

