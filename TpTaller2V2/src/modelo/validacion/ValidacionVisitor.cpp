/*
 * ValidacionVisitor.cpp
 *
 *  Created on: 05/11/2012
 */

#include "ValidacionVisitor.h"

ValidacionVisitor::ValidacionVisitor() {

}

ValidacionVisitor::~ValidacionVisitor() {

}

void ValidacionVisitor::inicializar(Diagrama* diagrama){
	std::string nombreArchivo = diagrama->getNombre() + "-" + Utils::getDate();
	this->archivo.open(nombreArchivo.c_str(), std::fstream::out);

	this->diagrama = diagrama;
	diagrama->setEstado(DIAGRAMA_VALIDADO);
}

void ValidacionVisitor::imprimirMensaje(std::string mensaje){
	this->archivo << mensaje << std::endl;
}

void ValidacionVisitor::invalidarDiagrama(){
	this->diagrama->setEstado(DIAGRAMA_VALIDADO_CON_OBSERVACIONES);
}

void ValidacionVisitor::visit(Diagrama* diagrama){
	this->inicializar(diagrama);

	if (diagrama->componentesBegin() == diagrama->componentesEnd()){
		this->imprimirMensaje("El diagrama " + diagrama->getNombre() + " aún no tiene componentes.");
	}
}

void ValidacionVisitor::visit(EntidadNueva* entidadNueva){
	// Nombre
	if (entidadNueva->getNombre().compare("") == 0){
		this->imprimirMensaje("Una de las entidades nuevas no tiene un nombre asignado.");
		this->invalidarDiagrama();
	}

	// Atributos
	if (entidadNueva->atributosBegin() == entidadNueva->atributosEnd()){
		this->imprimirMensaje("La entidad nueva " + entidadNueva->getNombre() + " no tiene ningún atributo.");
		this->invalidarDiagrama();
	}

	// Identificador
	if (entidadNueva->identificadoresBegin() == entidadNueva->identificadoresEnd()){
		this->imprimirMensaje("La entidad nueva " + entidadNueva->getNombre() + " no tiene ningún identificador.");
		this->invalidarDiagrama();
	} else {
		for (std::vector<Identificador*>::iterator it = entidadNueva->identificadoresBegin(); it != entidadNueva->identificadoresEnd(); it++){
			if ((*it)->codigoAtributosBegin() == (*it)->codigoAtributosEnd()){
				this->imprimirMensaje("El identificador de la entidad nueva " + entidadNueva->getNombre() + " no tiene ningún atributo.");
				this->invalidarDiagrama();
			}
		}
	}

	// Tipo
	if (entidadNueva->getTipo().compare("") == 0){
		this->imprimirMensaje("La entidad nueva " + entidadNueva->getNombre() + " no tiene asignado un tipo.");
		this->invalidarDiagrama();
	}
}

void ValidacionVisitor::visit(EntidadGlobal* entidadGlobal){
	// Diagrama ancestro
	if (entidadGlobal->getDiagramaAncestro().compare("") == 0){
		this->imprimirMensaje("Una de las entidades globales no tiene asignado el diagrama ancestro al que pertenece.");
		this->invalidarDiagrama();
	} else {
		Diagrama* diagramaAncestro = diagrama->getDiagramaAncestro();
		bool diagramaAncestroValido = false;
		while(diagramaAncestro != NULL){
			if (diagramaAncestro->getNombre().compare(entidadGlobal->getDiagramaAncestro()) == 0){
				diagramaAncestroValido = true;
			}
			diagramaAncestro = diagramaAncestro->getDiagramaAncestro();
		}
		if (diagramaAncestroValido == false){
			this->imprimirMensaje("El diagrama ancestro " + entidadGlobal->getDiagramaAncestro() + " no existe.");
			this->invalidarDiagrama();
		}
	}

	// Entidad nueva
	if (entidadGlobal->getEntidadNueva() == NULL){
		this->imprimirMensaje("Una de las entidades globales no tiene asignada la entidad nueva correspondiente.");
		this->invalidarDiagrama();
	}
}

void ValidacionVisitor::visit(Atributo* atributo){
	// Nombre
	if (atributo->getNombre().compare("") == 0){
		this->imprimirMensaje("Una de los atributos no tiene un nombre asignado.");
		this->invalidarDiagrama();
	}

	// Cardinalidades
	if (atributo->getCardinalidadMinima().compare("") == 0){
		this->imprimirMensaje("El atributo " + atributo->getNombre() + " no tiene asignado una cardinalidad mínima.");
		this->invalidarDiagrama();
	}
	if (atributo->getCardinalidadMaxima().compare("") == 0){
		this->imprimirMensaje("El atributo " + atributo->getNombre() + " no tiene asignado una cardinalidad máxima.");
		this->invalidarDiagrama();
	}

	// Tipo
	if (atributo->getTipo().compare("") == 0){
		this->imprimirMensaje("El atributo " + atributo->getNombre() + " no tiene asignado un tipo.");
		this->invalidarDiagrama();
	} else if (atributo->getTipo() == TIPO_ATRIBUTO_CALCULADO && atributo->getExpresion().compare("") == 0){
		this->imprimirMensaje("El atributo " + atributo->getNombre() + " es calculado y no tiene asignado la expresión.");
		this->invalidarDiagrama();
	}
}

void ValidacionVisitor::visit(Identificador* identificador){
	// Las validaciones se hacen dentro del visit(EntidadNueva*)
}

void ValidacionVisitor::visit(Relacion* relacion){
	// Nombre
	if (relacion->getNombre().compare("") == 0){
		this->imprimirMensaje("Una de las relaciones no tiene un nombre asignado.");
		this->invalidarDiagrama();
	}

	// Tipo
	if (relacion->getTipo().compare("") == 0){
		this->imprimirMensaje("La relación " + relacion->getNombre() + " no tiene asignada un tipo.");
		this->invalidarDiagrama();
	}
}

void ValidacionVisitor::visit(Jerarquia* jerarquia){
	// Nombre
	if (jerarquia->getNombre().compare("") == 0){
		this->imprimirMensaje("Una de las jerarquías no tiene un nombre asignado.");
		this->invalidarDiagrama();
	}
}

void ValidacionVisitor::visit(UnionEntidadRelacion* unionEntidadRelacion){
	// Se validan en la misma relación.
}

// TODO: Falta validar que los tipos sean algunos de los definidos en las constantes, falta validar las relaciones y las jerarquias.
