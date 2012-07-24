/*
 * ComponentsBuilder.h
 *
 *  Created on: 21/07/2012
 *      Author: Guagnini Enzo 88325
 */

#ifndef COMPONENTSBUILDER_H_
#define COMPONENTSBUILDER_H_


#include "../vista/componentes/VistaEntidadNueva.h"
#include "../vista/componentes/VistaAtributo.h"
#include "../vista/componentes/VistaLinea.h"
#include "../vista/VistaDiagrama.h"


class VistaProyecto;
class VistaAtributo;
class VistaEntidadNueva;
class VistaDiagrama;
class Ide;

class ComponentsBuilder {
private:
	Ide *ide;
	ComponentsBuilder();
	static ComponentsBuilder * instancia;
public:
	static ComponentsBuilder * getInstance();
	void setIde(Ide *vproy);
	virtual ~ComponentsBuilder();
	VistaEntidadNueva * crearEntidadNuevaEnDiagrama(VistaDiagrama* vdiag);
	VistaAtributo * crearAtributoEnEntidad(VistaEntidadNueva *entidad);
	VistaAtributo * crearAtributoEnAtributo(VistaAtributo *atribPadre);


};

#endif /* COMPONENTSBUILDER_H_ */
