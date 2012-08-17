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

void ComponentsBuilder::setIde(Ide *ide){
	this->ide = ide;
}

VistaEntidadNueva * ComponentsBuilder::crearEntidadNuevaEnDiagrama(VistaDiagrama *vdiag) {
	if (this->ide != NULL) {
		EntidadNueva * entidadNueva = new EntidadNueva();
		VistaEntidadNueva * vEntidadNueva = new VistaEntidadNueva(entidadNueva);
		vdiag->getDiagrama()->agregarEntidadNueva(entidadNueva);
		vdiag->agregarComponente(vEntidadNueva);
		return vEntidadNueva;
	}else return NULL;
}

VistaAtributo * ComponentsBuilder::crearAtributoEnEntidad(VistaEntidadNueva *ventidad){
	if (this->ide != NULL){
		//enlazar con la entidad crear union, poner en diagrama actual,etc.
		Atributo *atrib = new Atributo();
		VistaAtributo *vatrib = new VistaAtributo(atrib);
		ventidad->getEntidad()->agregarAtributo(atrib);
		ventidad->agregarAtributo(vatrib);
		VistaLinea * lineaEntidadAtributo = new VistaLinea();
		lineaEntidadAtributo->setComponenteDesde(ventidad);
		lineaEntidadAtributo->setComponenteHasta(vatrib);

		//Agrego vatributo y vlinea a el diag
		this->ide->getDiagActual()->agregarComponente(vatrib);
		this->ide->getDiagActual()->agregarComponente(lineaEntidadAtributo);
		return vatrib;
	} else return NULL;
}

VistaAtributo * ComponentsBuilder::crearAtributoEnAtributo(VistaAtributo *vatribPadre){
	if (this->ide != NULL){
		//enlazar con el atributo crear union, poner en diagrama actual,etc.
		Atributo *atrib = new Atributo();
		VistaAtributo *vatrib = new VistaAtributo(atrib);
		vatribPadre->getAtributo()->agregarAtributo(atrib);
		vatribPadre->agregarAtributo(vatrib);
		VistaLinea * lineaAtributoAtributo = new VistaLinea();
		lineaAtributoAtributo->setComponenteDesde(vatribPadre);
		lineaAtributoAtributo->setComponenteHasta(vatrib);

		//Agrego vatributo y vlinea a el diag
		this->ide->getDiagActual()->agregarComponente(vatrib);
		this->ide->getDiagActual()->agregarComponente(lineaAtributoAtributo);
		return vatrib;
	} else return NULL;
}




