#ifndef ENTIDADNUEVA_H_
#define ENTIDADNUEVA_H_

#include <string>
#include "Entidad.h"
#include "Atributo.h"
#include "Identificador.h"
#include "UnionEntidadRelacion.h"
#include "Jerarquia.h"
#include "../../excepciones/NullPointer.h"

class EntidadNueva: public Entidad {

private:
	// Modelo
	bool esDebil;
	std::vector<Atributo*> atributos;
	std::vector<Identificador*> identificadores;
	std::vector<Jerarquia *> jerarquiasPadre;
	std::string tipo; // Esta en el enunciado: cosa, historica, dominio, programada

	void borrarAtributos();
	void borrarIdentificadores();

	// PERSITENCIA COMP

	// GUARDAR
	void guardarAtributosXmlCOMP(XmlNodo*);
	void guardarIdentificadoresXmlCOMP(XmlNodo*);

	void guardarAtributosIdentificadorXmlCOMP(XmlNodo*, Identificador*);
	void guardarRelacionesIdentificadorXmlCOMP(XmlNodo*, Identificador*);
	XmlNodo guardarIdentificadorXmlCOMP();

	// CARGAR
	void obtenerComponentesXmlCOMP(XmlNodo*);

	// Agrega los atributos y relaciones a los vectores de
	// atributos y relaciones del identificador
	void obtenerComponentesIdentificadorXmlCOMP(XmlNodo*, Identificador*);
	Atributo* obtenerAtributo(int codigo);

protected:
	 // PERSISTENCIA COMP
	 // si hay que agregar más propiedades, se redefinen

	 // GUARDAR
	 virtual void agregarPropiedadesXmlCOMP(XmlNodo*);

	 // CARGAR
	 virtual void obtenerPropiedadesXmlCOMP(XmlNodo*);

public:
	EntidadNueva();
	virtual ~EntidadNueva();

	Atributo* getAtributoByCodigo(int);

	// REFACTORIZACION DE METODOS vGF1
	// La información  que una entidad es débil está en la entidad Nueva, no en la global
	void setEsDebil(bool);
	virtual bool getEsDebil();

	// Solo se puede agregar y sacar atributos a la entidad nueva
	void agregarAtributo(Atributo*) throw (NullPointer);
	void quitarAtributo(Atributo*) throw (NullPointer);

	void agregarJerarquiaPadre(Jerarquia *) throw (NullPointer);
	void quitarJerarquiaPadre(Jerarquia *) throw (NullPointer);
	void quitarJerarquiasPadre();


	void agregarIdentificador(Identificador*) throw (NullPointer);
	void quitarIdentificador(Identificador*) throw (NullPointer);
	void quitarIdentificadores();

	std::string getTipo() const;
	void setTipo(const std::string&);

	std::vector<Atributo*>::iterator atributosBegin();
	std::vector<Atributo*>::iterator atributosEnd();

	std::vector<Jerarquia*>::iterator jerarquiasPadreBegin();
	std::vector<Jerarquia*>::iterator jerarquiasPadreEnd();

	std::vector<Identificador*>::iterator identificadoresBegin();
	std::vector<Identificador*>::iterator identificadoresEnd();

	// Devuelve true si la entidad tiene un atributo con ese nombre.
	// No tiene en cuenta los subatributos.
	bool existeAtributo(const std::string&);

	void accept(ModeloVisitor*);

	// PERSISTENCIA COMP
	// CARGAR
	EntidadNueva(XmlNodo*);
	// GUARDAR
	XmlNodo guardarXmlCOMP();

};

#endif /* ENTIDADNUEVA_H_ */
