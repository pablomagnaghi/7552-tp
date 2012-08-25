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
#include "../vista/componentes/VistaJerarquia.h"


class VistaProyecto;
class VistaAtributo;
class VistaEntidadNueva;
class VistaDiagrama;
class VistaJerarquia;

class ComponentsBuilder {
private:
	ComponentsBuilder();
	static ComponentsBuilder * instancia;
public:
	static ComponentsBuilder * getInstance();
	virtual ~ComponentsBuilder();
	/*
	 * SI diagramaActual es NULL utilizara El diagrama actual del ide
	 * Si entidad Nueva es null creara un nuevo modelo de entidad nueva
	 */
	VistaEntidadNueva * crearEntidadNuevaEnDiagrama(VistaDiagrama *diagramaActual, EntidadNueva *entidadNueva);

	/*
	 *ventidad no puede ser NULL
	 *SI diagramaActual es NULL utilizara El diagrama actual del ide, sino deberia pasarsele el mismo diagrama donde se encuentra la ventidad
	 *Si atrib es null se creara uno nuevo sino se utilizara el modelo pasado
	 */
	VistaAtributo * crearAtributoEnEntidad(VistaEntidadNueva *ventidad,VistaDiagrama *diagramaActual, Atributo *atrib);
	/*
	*vatribPadre no puede ser NULL
	*SI diagramaActual es NULL utilizara El diagrama actual del ide, sino deberia pasarsele el mismo diagrama donde se encuentra la atribPadre
	*Si atrib es null se creara uno nuevo sino se utilizara el modelo pasado
	*/
	VistaAtributo * crearAtributoEnAtributo(VistaAtributo *atribPadre,VistaDiagrama *diagramaActual,Atributo *atrib);

	/*
	 * SI diagramaActual es NULL utilizara El diagrama actual del ide
	 */
	VistaJerarquia* crearJerarquiaEnDiagrama(VistaDiagrama *diagramaActual);

};

#endif /* COMPONENTSBUILDER_H_ */
