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

	// PERSITENCIA DER
	void obtenerComponentesXmlDER (XmlNodo* nodo);

protected:
	// PERSISTENCIA DER
	// si hay que agregar más propiedades, se redefinen
	virtual void agregarPropiedadesXmlDER(XmlNodo*);
	virtual void obtenerPropiedadesXmlDER(XmlNodo*);

public:

	EntidadGlobal();

	virtual ~EntidadGlobal();

	void setDiagramaAncestro(const std::string);
	std::string getDiagramaAncestro() const;

	void setCodigoEntidadNueva(int);
	int getCodigoEntidadNueva() const;

	// PERSISTENCIA DER
	EntidadGlobal(XmlNodo* nodo);
	XmlNodo guardarXmlDER();
};

#endif /* ENTIDADGLOBAL_H_ */
