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

VistaEntidadNueva * ComponentsBuilder::crearEntidadNuevaEnDiagrama(VistaDiagrama *diagramaActual,
		EntidadNueva *entidadNueva) {
	if (diagramaActual == NULL) {
		diagramaActual = Ide::getInstance()->getDiagActual();
	}
	if (entidadNueva == NULL) {
		// Crea la entidad y la agrega al diagrama del modelo
		entidadNueva = new EntidadNueva();
		entidadNueva->setCodigo(GeneradorCodigo::getInstance()->getSiguienteCodigo());
		diagramaActual->getDiagrama()->agregarEntidadNueva(entidadNueva);
	}

	VistaEntidadNueva * vEntidadNueva = new VistaEntidadNueva(entidadNueva);
	// AGREGAR COMPONENTE EN ESTE NO SE USA
	diagramaActual->agregarVistaEntidadNueva(vEntidadNueva);
	// Para la carga de la persistencia, necesito guardar todas las vistaEntidadNueva como VistaEntidad
	diagramaActual->agregarVistaEntidad(vEntidadNueva);
	return vEntidadNueva;
}

VistaAtributo * ComponentsBuilder::crearAtributoEnEntidad(VistaDiagrama *diagramaActual,
		VistaEntidadNueva *ventidad, Atributo *atrib) {
	if (ventidad == NULL) {
		throw NullPointer("NullPointer: Vista entidad no puede ser nulo");
	}
	if (atrib == NULL) {
		// Crea el atributo y lo agrega a la entidad del modelo
		atrib = new Atributo();
		atrib->setCodigo(GeneradorCodigo::getInstance()->getSiguienteCodigo());
		ventidad->getEntidadNueva()->agregarAtributo(atrib);
	}

	//enlazar con la entidad crear union, poner en diagrama actual,etc.
	VistaAtributo *vatrib = new VistaAtributo(atrib);
	ventidad->agregarAtributo(vatrib);
	vatrib->setPadre(ventidad);
	VistaLinea * lineaEntidadAtributo = new VistaLinea();
	lineaEntidadAtributo->setComponenteDesde(ventidad);
	lineaEntidadAtributo->setComponenteHasta(vatrib);
	lineaEntidadAtributo->setCodigoREP(GeneradorCodigo::getInstance()->getSiguienteCodigo());
	vatrib->setLinea(lineaEntidadAtributo);

	//Agrego vatributo y vlinea al diag
	diagramaActual->agregarComponente(vatrib);
	diagramaActual->agregarComponente(lineaEntidadAtributo);
	return vatrib;

}

VistaAtributo * ComponentsBuilder::crearAtributoEnAtributo(VistaDiagrama *diagramaActual,
		VistaAtributo *vatribPadre, Atributo *atrib) {

	if (vatribPadre == NULL) {
		throw NullPointer("NullPointer: El atributo padre no puede ser nulo");
	}

	//enlazar con el atributo crear union, poner en diagrama actual,etc.

	if (atrib == NULL) {
		// crea el atributo y lo agrega al atributo compuesto del modelo
		atrib = new Atributo();
		atrib->setCodigo(GeneradorCodigo::getInstance()->siguienteCodigo());
		vatribPadre->getAtributo()->agregarAtributo(atrib);
	}

	VistaAtributo *vatrib = new VistaAtributo(atrib);
	vatribPadre->agregarAtributo(vatrib);
	vatrib->setPadre(vatribPadre);
	VistaLinea * lineaAtributoAtributo = new VistaLinea();
	lineaAtributoAtributo->setComponenteDesde(vatribPadre);
	lineaAtributoAtributo->setComponenteHasta(vatrib);
	lineaAtributoAtributo->setCodigoREP(GeneradorCodigo::getInstance()->getSiguienteCodigo());
	vatrib->setLinea(lineaAtributoAtributo);

	//Agrego vatributo y vlinea a el diag
	diagramaActual->agregarComponente(vatrib);
	diagramaActual->agregarComponente(lineaAtributoAtributo);
	return vatrib;

}

VistaJerarquia* ComponentsBuilder::crearJerarquiaEnDiagrama(VistaDiagrama *diagramaActual,
		Jerarquia *j) {
	if (diagramaActual == NULL) {
		diagramaActual = Ide::getInstance()->getDiagActual();
	}
	if (j == NULL) {
		j = new Jerarquia();
		j->setCodigo(GeneradorCodigo::getInstance()->siguienteCodigo());
		diagramaActual->getDiagrama()->agregarJerarquia(j);
	}

	VistaJerarquia * vJerarquia = new VistaJerarquia(j);

	diagramaActual->agregarComponente(vJerarquia);
	//cout << "JERAQUIA CREADA EN PANEL" << endl;
	return vJerarquia;
}

/*
 VistaDiagrama* ComponentsBuilder::getDiagramaActual(){
 return this->ide->getDiagActual();
 }*/

VistaEntidadGlobal * ComponentsBuilder::crearEntidadGlobalEnDiagrama(VistaDiagrama * diagramaActual,
		const std::string & nombreEntidadNueva, EntidadGlobal * entidadGlobal) {

	// Variables Locales
	VistaEntidadGlobal * vistaEntidadGlobal;
	VistaEntidadNueva * vistaEntidadNueva;
	std::string nombreAncestro;

	//BuscarDiagramaAncestroYEntidadNueva
	vistaEntidadNueva = diagramaActual->buscarEntidadNuevaEnAncestro(nombreEntidadNueva,
			nombreAncestro);

	if (vistaEntidadNueva == NULL) {
		throw NullPointer("NullPointer: no se encontró la Entidad Nueva");
	}

	if (!entidadGlobal) {
		// Crea la entidad y la agrega al diagrama del modelo
		entidadGlobal = new EntidadGlobal();
		entidadGlobal->setCodigo(GeneradorCodigo::getInstance()->siguienteCodigo());
		diagramaActual->getDiagrama()->agregarEntidadGlobal(entidadGlobal);
	}

	entidadGlobal->setDiagramaAncestro(nombreAncestro);
	entidadGlobal->setEntidadNueva(vistaEntidadNueva->getEntidadNueva());

	vistaEntidadGlobal = new VistaEntidadGlobal(entidadGlobal);

	diagramaActual->agregarComponente(vistaEntidadGlobal);
	vistaEntidadGlobal->setPadre(vistaEntidadNueva);
	// Para la carga de la persistencia, necesito guardar todas las vistaEntidadGLobal como VistaEntidad
	diagramaActual->agregarVistaEntidad(vistaEntidadGlobal);
	return vistaEntidadGlobal;
}

VistaRelacion * ComponentsBuilder::crearRelacionEnDiagrama(VistaDiagrama *diagramaActual,
		Relacion * relacion) {

	VistaRelacion * vistaRelacion;

	if (relacion == NULL) {
		relacion = new Relacion();
		relacion->setCodigo(GeneradorCodigo::getInstance()->getSiguienteCodigo());
		diagramaActual->getDiagrama()->agregarRelacion(relacion);
	}

	vistaRelacion = new VistaRelacion(relacion);
	diagramaActual->agregarComponente(vistaRelacion);
	return vistaRelacion;
}

VistaUnionEntidadRelacion * ComponentsBuilder::crearUnionEntidadRelacion(
		VistaDiagrama *diagramaActual, VistaEntidad * entidad, VistaRelacion *relacion,
		UnionEntidadRelacion * unionEntidadRelacion) {
	VistaUnionEntidadRelacion * vistaUnion;

	if (unionEntidadRelacion == NULL) {
		unionEntidadRelacion = new UnionEntidadRelacion(entidad->getEntidad(),
				relacion->getRelacion());
		unionEntidadRelacion->setCodigo(GeneradorCodigo::getInstance()->getSiguienteCodigo());
	}
	vistaUnion = new VistaUnionEntidadRelacion(unionEntidadRelacion, entidad, relacion);
	//TODO NO. faltaba asociar los vistamodelos
	relacion->agregarUnion(vistaUnion);

	diagramaActual->agregarComponente(vistaUnion);
	// Para el cargar de la persistencia
	diagramaActual->agregarVistaUnionEntidadRelacion(vistaUnion);
	return vistaUnion;
}

VistaAtributo * ComponentsBuilder::crearAtributoEnRelacion(VistaDiagrama *diagramaActual,
		VistaRelacion * relacion, Atributo * atributo) {
	VistaAtributo *vistaAtributo = NULL;
	cout<<"llego11"<<endl;
	if (relacion == NULL) {
		throw NullPointer("NullPointer: El atributo padre no puede ser nulo");
	}
	cout<<"llego12"<<endl;
	if (atributo == NULL) {
		cout<<"llego13"<<endl;
		// crea el atributo y lo agrega al atributo compuesto del modelo
		atributo = new Atributo();
		atributo->setCodigo(GeneradorCodigo::getInstance()->siguienteCodigo());
		relacion->getRelacion()->agregarAtributo(atributo);
		cout<<"llego14"<<endl;
	}

	cout<<"llego15"<<endl;
	vistaAtributo = new VistaAtributo(atributo);
	relacion->agregarAtributo(vistaAtributo);
	VistaLinea * lineaAtributoAtributo = new VistaLinea();
	lineaAtributoAtributo->setComponenteDesde(relacion);
	lineaAtributoAtributo->setComponenteHasta(vistaAtributo);
	lineaAtributoAtributo->setCodigoREP(GeneradorCodigo::getInstance()->getSiguienteCodigo());
	cout<<"llego16"<<endl;
	//Agrego vatributo y vlinea a el diag
	diagramaActual->agregarComponente(vistaAtributo);
	cout<<"llego17"<<endl;
	diagramaActual->agregarComponente(lineaAtributoAtributo);
	cout<<"llego18"<<endl;
	return vistaAtributo;

}

VistaIdentificador * ComponentsBuilder::crearIdentificadorEnEntidad(VistaDiagrama *diagramaActual,
		VistaEntidadNueva *entidad, Identificador*identificador) {
	if (entidad == NULL) {
		throw NullPointer("NullPointer: Entidad no puede ser nulo");
	}

	if (identificador == NULL) {
		identificador = new Identificador();
		entidad->getEntidadNueva()->agregarIdentificador(identificador);
	}

	VistaIdentificador * vistaIdentificador = new VistaIdentificador(identificador);

	//TODO NO.Agregue una lista de vistaIdentificadores a vistaEntidad
	entidad->agregarIdentificador(vistaIdentificador);

	diagramaActual->agregarComponente(vistaIdentificador);
	diagramaActual->agregarVistaIdentificador(vistaIdentificador);

	return vistaIdentificador;
}

void ComponentsBuilder::agregarAtributoAIdentificador(VistaIdentificador * vistaIdentificador,
		VistaAtributo * vistaAtributo) {
	if (vistaIdentificador == NULL) {
		throw NullPointer("NullPointer: vistaIdentificador no puede ser nulo");
	}
	if (vistaAtributo == NULL) {
		throw NullPointer("NullPointer: vistaAtributo no puede ser nulo");
	}
	// todo VERRRR guarda 2 veces lo mismo
	vistaIdentificador->getIdentificador()->agregarCodigoAtributo(
			vistaAtributo->getAtributo()->getCodigo());
	vistaIdentificador->agregarAtributo(vistaAtributo);

}

void ComponentsBuilder::agregarEntidadFuerteAIdentificador(VistaIdentificador * vistaIdentificador,
		VistaUnionEntidadRelacion * vistaUnion) {
	if (vistaIdentificador == NULL) {
		throw NullPointer("NullPointer: vistaIdentificador no puede ser nulo");
	}
	if (vistaUnion == NULL) {
		throw NullPointer("NullPointer: vistaUnion no puede ser nulo");
	}

	vistaIdentificador->getIdentificador()->agregarCodigoRelacion(
			vistaUnion->getUnion()->getRelacion()->getCodigo());
	vistaIdentificador->agregarEntidadFuerte(vistaUnion);
}

// todo verrrr guarda 2 veces

void ComponentsBuilder::agregarJerarquiaHijaDeEntidad(VistaJerarquia * vistaJerarquia, VistaEntidad*vistaEntidad) {
	if (vistaJerarquia == NULL) {
		throw NullPointer("NullPointer: vistaJerarquia no puede ser nulo");
	}
	if (vistaEntidad == NULL) {
		throw NullPointer("NullPointer: vistaEntidad no puede ser nulo");
	}
	vistaEntidad->getEntidad()->setJerarquiaHija(vistaJerarquia->getJerarquia());
	vistaJerarquia->getJerarquia()->setEntidadGeneral(vistaEntidad->getEntidad());
	vistaJerarquia->setEntidadPadre(vistaEntidad);
}

void ComponentsBuilder::agregarJerarquiaPadreDeEntidad(VistaJerarquia *vistaJerarquia,
		VistaEntidadNueva*vistaEntidadNueva) {
	if (vistaJerarquia == NULL) {
		throw NullPointer("NullPointer: vistaJerarquia no puede ser nulo");
	}
	if (vistaEntidadNueva == NULL) {
		throw NullPointer("NullPointer: vistaEntidad no puede ser nulo");
	}

	vistaEntidadNueva->getEntidadNueva()->agregarJerarquiaPadre(vistaJerarquia->getJerarquia());

	// todo
	vistaJerarquia->getJerarquia()->agregarEntidadEspecializada(
			vistaEntidadNueva->getEntidadNueva());

	vistaJerarquia->agregarEntidadEspecializada(vistaEntidadNueva);
}
