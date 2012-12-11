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
	int codigoEntidadNueva; // Para buscar la entidadNueva en el diagrama

protected:
	// PERSISTENCIA COMP
	// si hay que agregar más propiedades, se redefinen

	// CARGAR
	 virtual void obtenerPropiedadesXmlCOMP(XmlNodo*);
	// GUARDAR
	virtual void agregarPropiedadesXmlCOMP(XmlNodo*);

public:
	EntidadGlobal();

	virtual ~EntidadGlobal();

	void setDiagramaAncestro(const std::string&);
	std::string getDiagramaAncestro() const;

	void setEntidadNueva(EntidadNueva * entidadNueva) throw (NullPointer);
	EntidadNueva * getEntidadNueva() const;

	virtual bool getEsDebil();

	void accept(ModeloVisitor*);

	// PERSISTENCIA COMP
	int getCodigoEntidadNueva();
	// CARGAR
	EntidadGlobal(XmlNodo*);
	// GUARDAR
	XmlNodo guardarXmlCOMP();
};

#endif /* ENTIDADGLOBAL_H_ */
