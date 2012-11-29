/*
 * ComponentsBuilder.h
 *
 *  Created on: 21/07/2012
 *      Author: Guagnini Enzo 88325
 */

#ifndef COMPONENTSBUILDER_H_
#define COMPONENTSBUILDER_H_

#include "../vista/componentes/VistasDeComponentes.h"
#include "../vista/VistaDiagrama.h"

class VistaProyecto;
class VistaRelacion;
class VistaEntidadNueva;
class VistaEntidadGlobal;
class VistaDiagrama;
class VistaJerarquia;
class VistaIdentificador;
class VistaAtributo;
class VistaUnionEntidadRelacion;

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
	VistaEntidadNueva * crearEntidadNuevaEnDiagrama(VistaDiagrama *diagramaActual,
			EntidadNueva *entidadNueva = NULL);

	/*
	 *ventidad no puede ser NULL
	 *SI diagramaActual es NULL utilizara El diagrama actual del ide, sino deberia pasarsele el mismo diagrama donde se encuentra la ventidad
	 *Si atrib es null se creara uno nuevo sino se utilizara el modelo pasado
	 */
	VistaAtributo * crearAtributoEnEntidad(VistaDiagrama *diagramaActual,
			VistaEntidadNueva *ventidad, Atributo *atrib = NULL);
	/*
	 *vatribPadre no puede ser NULL
	 *SI diagramaActual es NULL utilizara El diagrama actual del ide, sino deberia pasarsele el mismo diagrama donde se encuentra la atribPadre
	 *Si atrib es null se creara uno nuevo sino se utilizara el modelo pasado
	 */
	VistaAtributo * crearAtributoEnAtributo(VistaDiagrama *diagramaActual,
			VistaAtributo *atribPadre, Atributo *atrib = NULL);

	/*
	 *
	 */
	VistaJerarquia * crearJerarquiaEnDiagrama(VistaDiagrama *diagramaActual, Jerarquia *j = NULL);

	/*
	 *
	 * */

	VistaAtributo * crearAtributoEnRelacion(VistaDiagrama *, VistaRelacion *, Atributo * = NULL);
	VistaRelacion * crearRelacionEnDiagrama(VistaDiagrama *, Relacion * = NULL);
	VistaUnionEntidadRelacion * crearUnionEntidadRelacion(VistaDiagrama *, VistaEntidad *,
			VistaRelacion *, UnionEntidadRelacion * = NULL);
	VistaIdentificador * crearIdentificadorEnEntidad(VistaDiagrama *, VistaEntidadNueva *,
			Identificador* = NULL);
	VistaEntidadGlobal * crearEntidadGlobalEnDiagrama(VistaDiagrama * diagramaActual,
			const std::string & nombreEntidadNueva, EntidadGlobal * entidadGlobal = NULL);
	void agregarAtributoAIdentificador(VistaIdentificador *, VistaAtributo*);
	void agregarEntidadFuerteAIdentificador(VistaIdentificador *, VistaUnionEntidadRelacion*);
	void agregarJerarquiaHijaDeEntidad(VistaJerarquia *, VistaEntidad*);
	void agregarJerarquiaPadreDeEntidad(VistaJerarquia *, VistaEntidadNueva*);
};

#endif /* COMPONENTSBUILDER_H_ */
