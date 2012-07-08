/* Diagrama.h
 *  Created on: 30/04/2012
 *      Author: Gonzalo Ferrero 89657
 */

#ifndef DIAGRAMA_H_
#define DIAGRAMA_H_

#include <vector>
#include <string>
#include "EntidadNueva.h"
#include "EntidadGlobal.h"
#include "Relacion.h"
#include "Jerarquia.h"
#include "Componente.h"
#include "ConstantesModelo.h"

//Persistencia
#include "persistencia/Persistencia.h"

class Diagrama {

private:
	// Modelo
	std::string nombre;
	Diagrama* diagramaAncestro;
	std::vector<Diagrama*> diagramasHijos;
	std::vector<EntidadNueva*> entidadesNuevas;
	std::vector<EntidadGlobal*> entidadesGlobales;
	std::vector<Relacion*> relaciones;
	std::vector<Jerarquia*> jerarquias;
	std::vector<Componente*> componentes; // No se persiste, es solo para iterarla desde afuera.

	// Persistencia
	bool diagramaValidoCOMP;

	void agregarComponente(Componente*);
	void quitarComponente(Componente*);

	void borrarDiagramasHijos();
	void borrarEntidadesNuevas();
	void borrarEntidadesGlobales();
	void borrarJerarquias();
	void borrarRelaciones();


	// PERSISTENCIA COMP
	/*
	void agregarPropiedadesXmlCOMP(XmlNodo*);
	void obtenerPropiedadesXmlCOMP(XmlNodo*);

	void obtenerComponentesXmlCOMP(XmlNodo*);

	void agregarNodoDiagramaAncestroXmlCOMP(XmlNodo*);

	void guardarEntidadesNuevasXmlCOMP(XmlNodo*);
	void guardarEntidadesGlobalesXmlCOMP(XmlNodo*);
	void guardarRelacionesXmlCOMP(XmlNodo*);
	void guardarJerarquiasXmlCOMP(XmlNodo*);

	void cargarXmlCOMP(XmlNodo*);
	XmlNodo guardarXmlCOMP();
	*/

public:

	Diagrama();
	Diagrama(const std::string);
	virtual ~Diagrama();

	void setNombre(const std::string);
	std::string getNombre() const;

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

	Entidad* getEntidadByCodigo(int);
	EntidadNueva* getEntidadNuevaByCodigo(int);
	EntidadGlobal* getEntidadGlobalByCodigo(int);
	Relacion* getRelacionByCodigo(int);
	Jerarquia* getJerarquiaByCodigo(int);
	Componente* getComponenteByCodigo(int);


	// PERSITENCIA COMP
	/*
	void abrirXmlCOMP(const std::string&);
	bool isOpenXmlCOMP() const;
	void guardarDiagramaXmlCOMP(const std::string&);
	*/
};

#endif /* DIAGRAMA_H_ */
