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


VistaEntidadNueva * ComponentsBuilder::crearEntidadNuevaEnDiagrama(VistaDiagrama *diagramaActual=NULL, EntidadNueva *entidadNueva=NULL) {
	if (diagramaActual == NULL){
		diagramaActual = Ide::getInstance()->getDiagActual();
	}
	if (entidadNueva == NULL){
		entidadNueva = new EntidadNueva();
	}
	VistaEntidadNueva * vEntidadNueva = new VistaEntidadNueva(entidadNueva);
	diagramaActual->getDiagrama()->agregarEntidadNueva(entidadNueva);
	diagramaActual->agregarComponente(vEntidadNueva);
	diagramaActual->agregarVistaEntidadNueva(vEntidadNueva);
	return vEntidadNueva;
}

VistaAtributo * ComponentsBuilder::crearAtributoEnEntidad(VistaEntidadNueva *ventidad,VistaDiagrama *diagramaActual=NULL, Atributo *atrib=NULL){
	if (ventidad != NULL){
		if (atrib == NULL){
			atrib = new Atributo();
		}
		if (diagramaActual == NULL){
				diagramaActual = Ide::getInstance()->getDiagActual();
		}
		//enlazar con la entidad crear union, poner en diagrama actual,etc.
		VistaAtributo *vatrib = new VistaAtributo(atrib);
		ventidad->getEntidad()->agregarAtributo(atrib);
		ventidad->agregarAtributo(vatrib);
		VistaLinea * lineaEntidadAtributo = new VistaLinea();
		lineaEntidadAtributo->setComponenteDesde(ventidad);
		lineaEntidadAtributo->setComponenteHasta(vatrib);

		//Agrego vatributo y vlinea a el diag
		diagramaActual->agregarComponente(vatrib);
		diagramaActual->agregarComponente(lineaEntidadAtributo);
		return vatrib;
	} else return NULL;
}

VistaAtributo * ComponentsBuilder::crearAtributoEnAtributo(VistaAtributo *vatribPadre,VistaDiagrama *diagramaActual=NULL, Atributo *atrib=NULL){
	if (vatribPadre != NULL){
		//enlazar con el atributo crear union, poner en diagrama actual,etc.
		if (atrib == NULL){
			atrib = new Atributo();
		}
		if (diagramaActual == NULL){
			diagramaActual = Ide::getInstance()->getDiagActual();
		}
		VistaAtributo *vatrib = new VistaAtributo(atrib);
		vatribPadre->getAtributo()->agregarAtributo(atrib);
		vatribPadre->agregarAtributo(vatrib);
		VistaLinea * lineaAtributoAtributo = new VistaLinea();
		lineaAtributoAtributo->setComponenteDesde(vatribPadre);
		lineaAtributoAtributo->setComponenteHasta(vatrib);

		//Agrego vatributo y vlinea a el diag
		diagramaActual->agregarComponente(vatrib);
		diagramaActual->agregarComponente(lineaAtributoAtributo);
		return vatrib;
	} else return NULL;
}

VistaJerarquia* ComponentsBuilder::crearJerarquiaEnDiagrama(){
	//if (this->ide != NULL) {
		Jerarquia * j = new Jerarquia();
		VistaJerarquia * vJerarquia = new VistaJerarquia(j);
		Ide::getInstance()->getDiagActual()->getDiagrama()->agregarJerarquia(j);
		Ide::getInstance()->getDiagActual()->agregarComponente(vJerarquia);
		cout<<"JERAQUIA CREADA EN PANEL"<<endl;
		return vJerarquia;
	//}else return NULL;
}

/*
VistaDiagrama* ComponentsBuilder::getDiagramaActual(){
	return this->ide->getDiagActual();
}*/


