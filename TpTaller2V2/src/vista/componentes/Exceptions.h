/*
 * Exceptions.h
 *
 *  Created on: 08/04/2012
 *      Author: pablo
 */

#ifndef _EXCEPCION_H_INCLUDED_
#define _EXCEPCION_H_INCLUDED_

class Exception {
public:
	virtual std::string getMsjError() = 0;
	virtual ~Exception() {
	}
};

// Excepciones de Xml

class AtributoInvalidoExc : public Exception {
private:
	std::string name;
public:
	AtributoInvalidoExc( std::string name  )
	:name ( name ) {
	}
	std::string getMsjError() {
		std::string msj( "El 'ObjetoConAtriibutos' no posee un attr de nombre " );
		msj += name;
		return msj;
	}
};

class ErrorAlAbrirXmlDoc : public Exception {
	std::string getMsjError() {
		return "Error ";
	}
};

class DocumentoSinContextoXpathExc : public Exception {
public:
	std::string getMsjError() {
		std::string msj( "Se debe crear el contexto con crearContextoXpath()" );
		return msj;
	}
};

class XmlArchivoInvalidoExc: public Exception {
	private:
		std::string path;
	public:
		XmlArchivoInvalidoExc( std::string path  )
		:path ( path ) {
		}
		std::string getMsjError() {
			std::string msj( "XmlException: El archivo " );
			msj += path;
			msj += " no es un XML valido ( parserError )";
			return msj;
	}
};

//Excepciones en XmlNodeSet

class IndexFueraDeRangoEnNodeSetExc : public Exception {
private:
	int size;
	int index;
public:
	IndexFueraDeRangoEnNodeSetExc( int size, int index  )
	:size(size), index(index) {
	}
	std::string getMsjError() {
		std::string msj( "Intentando acceder a pocision " );
		msj += index;
		msj += " de un set que va desde 0 ..";
		msj += (size-1);
		return msj;
	}
};

// Excepciones en XmlNodo
class NullNodeExc: public Exception {
public:
	std::string getMsjError() {
		std::string msj( "XmlException: Llamando a metodo sobre nodo null" );
	return msj;
	}
};

class NotElementNodeExc: public Exception {
private:
    std::string name;
public:
	NotElementNodeExc( std::string nombreNodo  )
	:name ( nombreNodo ) {
	}
	std::string getMsjError() {
		std::string msj( "XmlException: El nodo " );
		msj += name;
		msj += " no tiene contenido";
		return msj;
	}
};


// Se lanza en caso de que se le el contenido de un nodo_name
// que debe tener un valor entero y se encuentra como contenido
// una cadena vacia.

class ContenidoIntVacioExc: public Exception {
private:
	std::string name;
public:
	ContenidoIntVacioExc( std::string nombreNodo  )
	:name ( nombreNodo ) {
	}
	std::string getMsjError() {
		std::string msj( "XmlException: El nodo " );
		msj += name;
		msj += " no tiene contenido tipo Int(vacío)";
		return msj;
	}
};

// Se lanza en caso de que se le el contenido de un nodo_name
// no tenga como valor un booleano que puede ser:
// XML_BOOL_TRUE o XML_BOOL_FALSE definidos en XmlNodo.h

class ContenidoBoolInvalidoExc: public Exception {
private:
    std::string name;
public:
	ContenidoBoolInvalidoExc( std::string nombreNodo  )
	:name ( nombreNodo ) {
	}
	std::string getMsjError() {
		std::string msj( "XmlException: El nodo " );
		msj += name;
		msj += " no tiene contenido bool";
		return msj;
	}
};

class NodoXmlIncorrectoExc: public Exception {
private:
	std::string nameEsperado;
    std::string nameEncontrado;

public:
	NodoXmlIncorrectoExc( const std::string& esperado, const std::string& encontrado  )
	:nameEsperado ( esperado ), nameEncontrado(encontrado) {
	}
	std::string getMsjError() {
		std::string msj( "XmlException: El nodo es incorrecto.Se esperaba nodo_name=" );
		msj += nameEsperado;
		msj += " y se obtuvo nodo_name=";
		msj += nameEncontrado;
		return msj;
	}
};

#endif
