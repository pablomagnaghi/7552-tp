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
	/*
	 void obtenerComponentesXmlCOMP(XmlNodo*);

	 void guardarAtributosXmlCOMP(XmlNodo*);
	 void guardarIdentificadoresXmlCOMP(XmlNodo*);
	 void guardarJerarquiasXmlCOMP(XmlNodo*);

	 void guardarAtributosIdentificadorXmlCOMP(XmlNodo*, Identificador*);
	 void guardarRelacionesIdentificadorXmlCOMP(XmlNodo*, Identificador*);
	 XmlNodo guardarIdentificadorXmlCOMP();

	 // Agrega los atributos y relaciones a los vectores de
	 // atributos y relaciones del identificador
	 void obtenerComponentesIdentificadorXmlCOMP(XmlNodo*, Identificador*);
	 Atributo* obtenerAtributo(int codigo);
	 */

protected:
	// PERSISTENCIA COMP
	// si hay que agregar más propiedades, se redefinen
	/*
	 virtual void agregarPropiedadesXmlCOMP(XmlNodo*);
	 virtual void obtenerPropiedadesXmlCOMP(XmlNodo*);
	 */

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

	void agregarIdentificador(Identificador*) throw (NullPointer);
	void quitarIdentificador(Identificador*) throw (NullPointer);

	std::string getTipo() const;
	void setTipo(const std::string&);

	std::vector<Atributo*>::iterator atributosBegin();
	std::vector<Atributo*>::iterator atributosEnd();

	std::vector<Jerarquia*>::iterator jerarquiasPadreBegin();
	std::vector<Jerarquia*>::iterator jerarquiasPadreEnd();

	std::vector<Identificador*>::iterator identificadoresBegin();
	std::vector<Identificador*>::iterator identificadoresEnd();

	// PERSISTENCIA COMP
	/*
	 EntidadNueva(XmlNodo*);
	 XmlNodo guardarXmlCOMP();
	 */
};

#endif /* ENTIDADNUEVA_H_ */
