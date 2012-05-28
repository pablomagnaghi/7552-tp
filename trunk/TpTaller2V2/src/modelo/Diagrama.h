/* Diagrama.h
 *  Created on: 30/04/2012
 *      Author: Gonzalo Ferrero 89657
 */

#ifndef DIAGRAMA_H_
#define DIAGRAMA_H_


#define XMLNS "xmlns:xsi"
#define INSTANCE "http:\/\/www.w3.org/2001/XMLSxhema-instance"
#define XSI "xsi:noNamespaceSchemaLocation"
#define COMPOSICION "composicion.xsd"

#include <vector>
#include <string>
#include "EntidadNueva.h"
#include "EntidadGlobal.h"
#include "Relacion.h"
#include "Jerarquia.h"
#include "Componente.h"
#include "ConstantesModelo.h"

class Diagrama {

private:

	std::string nombre;
	std::string estado;
	Diagrama* diagramaAncestro;
	std::vector<Diagrama*> diagramasHijos;
	std::vector<EntidadNueva*> entidadesNuevas;
	std::vector<EntidadGlobal*> entidadesGlobales;
	std::vector<Relacion*> relaciones;
	std::vector<Jerarquia*> jerarquias;
	std::vector<Componente*> componentes; // No se persiste, es solo para iterarla desde afuera.

	void agregarComponente(Componente*);
	void quitarComponente(Componente*);

	void borrarDiagramasHijos();
	void borrarEntidadesNuevas();
	void borrarEntidadesGlobales();
	void borrarJerarquias();
	void borrarRelaciones();

	/* PERSISTENCIA DER
	// void agregarPropiedadesDER (XmlNodo*);
	// void obtenerPropiedadesDER (XmlNodo*);

	// void guardarEntidadesNuevasXmlDER(XmlNodo *nodo) {
	// void guardarEntidadesGlobalesXmlDER(XmlNodo *nodo) {
	// void guardarRelacionesXmlDER(XmlNodo *nodo) {
	// void guardarJerarquiasXmlDER(XmlNodo *nodo) {
	*/

public:

	Diagrama();
	Diagrama(const std::string nombre);
	virtual ~Diagrama();

	void setNombre(const std::string);
	std::string getNombre() const;

	void setEstado(const std::string);
	std::string getEstado() const;

	void setDiagramaAncestro(Diagrama*);
	Diagrama* getDiagramaAncestro() const;

	void agregarDiagramaHijo(Diagrama*);
	void quitarDiagramaHijo(Diagrama*);

	void agregarEntidadNueva(EntidadNueva*);
	void quitarEntidadNueva(EntidadNueva*);

	void agregarEntidadGlobal(EntidadGlobal*);
	void quitarEntidadGlobal(EntidadGlobal*);

	void agregarRelacion(Relacion*);
	void quitarRelacion(Relacion*);

	void agregarJerarquia(Jerarquia*);
	void quitarJerarquia(Jerarquia*);

	std::vector<Diagrama*>::iterator diagramasHijosBegin();
	std::vector<Diagrama*>::iterator diagramasHijosEnd();

	std::vector<EntidadNueva*>::iterator entidadesNuevasBegin();
	std::vector<EntidadNueva*>::iterator entidadesNuevasEnd();

	std::vector<EntidadGlobal*>::iterator entidadesGlobalesBegin();
	std::vector<EntidadGlobal*>::iterator entidadesGlobalesEnd();

	std::vector<Relacion*>::iterator relacionesBegin();
	std::vector<Relacion*>::iterator relacionesEnd();

	std::vector<Jerarquia*>::iterator jerarquiasBegin();
	std::vector<Jerarquia*>::iterator jerarquiasEnd();

	std::vector<Componente*>::iterator componentesBegin();
	std::vector<Componente*>::iterator componentesEnd();

	EntidadNueva* getEntidadNuevaByCodigo(int);
	EntidadGlobal* getEntidadGlobalByCodigo(int);
	Relacion* getRelacionByCodigo(int);
	Jerarquia* getJerarquiaByCodigo(int);
	Componente* getComponenteByCodigo(int);


	/* PERSITENCIA DER
	// Diagrama(XmlNodo*);
	// XmlNodo guardarXmlDER() {
	*/
};

#endif /* DIAGRAMA_H_ */
