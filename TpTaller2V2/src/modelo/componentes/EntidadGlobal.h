#ifndef ENTIDADGLOBAL_H_
#define ENTIDADGLOBAL_H_

#include <string>
#include "Entidad.h"
#include "EntidadNueva.h"
#include "../../excepciones/NullPointer.h"

class EntidadGlobal: public Entidad {

private:
	std::string diagramaAncestro;
	EntidadNueva * entidadNueva; // Codigo de la EntidadNueva en el diagrama ancestro.

	// PERSITENCIA COMP
	/*
	 void obtenerComponentesXmlCOMP(XmlNodo*);
	 */

protected:
	// PERSISTENCIA COMP
	// si hay que agregar más propiedades, se redefinen
	/*
	 virtual void agregarPropiedadesXmlCOMP(XmlNodo*);
	 virtual void obtenerPropiedadesXmlCOMP(XmlNodo*);
	 */

public:
	EntidadGlobal();

	virtual ~EntidadGlobal();

	void setDiagramaAncestro(const std::string&);
	std::string getDiagramaAncestro() const;

	void setEntidadNueva(EntidadNueva * entidadNueva) throw (NullPointer);
	EntidadNueva * getEntidadNueva() const;

	virtual bool getEsDebil();

	// PERSISTENCIA COMP
	/*
	 EntidadGlobal(XmlNodo*);
	 XmlNodo guardarXmlCOMP();
	 */
};

#endif /* ENTIDADGLOBAL_H_ */
