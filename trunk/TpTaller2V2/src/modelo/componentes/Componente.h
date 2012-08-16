#ifndef COMPONENTE_H_
#define COMPONENTE_H_

#include <string>

#include "../../excepciones/ArgumentoInvalido.h"

// Persistencia
#include "../persistencia/Persistencia.h"

class Componente {

protected:
	// Codigo para la persistencia
	int codigo;
	// Nombre es común a todos los componentes
	std::string nombre;

	// PERSITENCIA COMP
	// si hay que agregar más propiedades, se redefinen
	/*
	virtual void obtenerPropiedadesXmlCOMP(XmlNodo*);
	*/

	// GUARDAR
	virtual void agregarPropiedadesXmlCOMP(XmlNodo*);

	Componente(const Componente &);

public:
	// CONSTRUCTOR PARA QUE SE LE PUEDA AGREGAR EL NOMBRE O CODIGO AL CONSTRUIRLO
	Componente(int codigo = -1, const std::string & nombre = "");
	virtual ~Componente();

	int getCodigo() const;
	void setCodigo(int);

	std::string getNombre() const;
	void setNombre(const std::string &);
};

#endif /* COMPONENTE_H_ */
