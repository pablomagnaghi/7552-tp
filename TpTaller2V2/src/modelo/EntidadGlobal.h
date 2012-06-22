/*
 * EntidadGlobal.h
 *
 *  Created on: 14/05/2012
 */

#ifndef ENTIDADGLOBAL_H_
#define ENTIDADGLOBAL_H_

#include <string>
#include "Entidad.h"

// Persistencia
#include "persistencia/Persistencia.h"

class EntidadGlobal : public Entidad {

private:

	std::string diagramaAncestro;
	int codigoEntidadNueva; // Codigo de la EntidadNueva en el diagrama ancestro.

	// PERSITENCIA COMP
	void obtenerComponentesXmlCOMP(XmlNodo*);

protected:
	// PERSISTENCIA COMP
	// si hay que agregar más propiedades, se redefinen
	virtual void agregarPropiedadesXmlCOMP(XmlNodo*);
	virtual void obtenerPropiedadesXmlCOMP(XmlNodo*);

public:

	EntidadGlobal();

	virtual ~EntidadGlobal();

	void setDiagramaAncestro(const std::string&);
	std::string getDiagramaAncestro() const;

	void setCodigoEntidadNueva(int);
	int getCodigoEntidadNueva() const;

	// PERSISTENCIA COMP
	//EntidadGlobal(XmlNodo*, const std::vector<Relacion*>&);
	XmlNodo guardarXmlCOMP();
};

#endif /* ENTIDADGLOBAL_H_ */
