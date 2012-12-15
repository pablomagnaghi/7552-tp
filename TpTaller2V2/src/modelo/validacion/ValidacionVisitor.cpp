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
	} else if (entidadNueva->getTipo().compare(TIPO_ENTIDAD_COSA) != 0 &&
			entidadNueva->getTipo().compare(TIPO_ENTIDAD_DOMINIO) != 0 &&
			entidadNueva->getTipo().compare(TIPO_ENTIDAD_HISTORICA) != 0 &&
			entidadNueva->getTipo().compare(TIPO_ENTIDAD_PROGRAMADA) != 0){
		this->imprimirMensaje("La entidad nueva " + entidadNueva->getNombre() + " no tiene asignado un tipo válido.");
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
		this->imprimirMensaje("El atributo " + atributo->getNombre() + " no tiene asignada la cardinalidad mínima.");
		this->invalidarDiagrama();
	}
	if (atributo->getCardinalidadMaxima().compare("") == 0){
		this->imprimirMensaje("El atributo " + atributo->getNombre() + " no tiene asignada la cardinalidad máxima.");
		this->invalidarDiagrama();
	}

	// Tipo
	if (atributo->getTipo().compare("") == 0){
		this->imprimirMensaje("El atributo " + atributo->getNombre() + " no tiene asignado un tipo.");
		this->invalidarDiagrama();
	} else if (atributo->getTipo().compare(TIPO_ATRIBUTO_CALCULADO) != 0 &&
			atributo->getTipo().compare(TIPO_ATRIBUTO_CARACTERIZACION) != 0 &&
			atributo->getTipo().compare(TIPO_ATRIBUTO_COPIADO) != 0){
		this->imprimirMensaje("El atributo " + atributo->getNombre() + " no tiene asignado un tipo válido.");
		this->invalidarDiagrama();
	} else if (atributo->getTipo().compare(TIPO_ATRIBUTO_CALCULADO) == 0 && atributo->getExpresion().compare("") == 0){
		this->imprimirMensaje("El atributo " + atributo->getNombre() + " es calculado y no tiene asignada la expresión.");
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
		this->imprimirMensaje("La relación " + relacion->getNombre() + " no tiene asignado un tipo.");
		this->invalidarDiagrama();
	} else if (relacion->getTipo().compare(TIPO_RELACION_ASOCIACION) != 0 &&
			relacion->getTipo().compare(TIPO_RELACION_COMPOSICION) != 0) {
		this->imprimirMensaje("La relación " + relacion->getNombre() + " no tiene asignado un tipo válido.");
		this->invalidarDiagrama();
	}

	// Uniones
	int cantidadEntidades = 0;
	std::vector<UnionEntidadRelacion*>::iterator itUniones = relacion->unionesAEntidadBegin();
	while (itUniones != relacion->unionesAEntidadEnd()){
		cantidadEntidades++;
		itUniones++;
	}
	if (cantidadEntidades < 2){
		this->imprimirMensaje("La relación " + relacion->getNombre() + " debe tener 2 o más entidades asociadas.");
		this->invalidarDiagrama();
	}
}

void ValidacionVisitor::visit(Jerarquia* jerarquia){
	// Nombre
	if (jerarquia->getNombre().compare("") == 0){
		this->imprimirMensaje("Una de las jerarquías no tiene un nombre asignado.");
		this->invalidarDiagrama();
	}

	// Entidad general
	if (jerarquia->getEntidadGeneral() == NULL){
		this->imprimirMensaje("La jerarquía " + jerarquia->getNombre() + " no tiene una entidad general asignada.");
		this->invalidarDiagrama();
	}

	// Entidades especializadas
	if (jerarquia->entidadesEspecializadasBegin() == jerarquia->entidadesEspecializadasEnd()){
		this->imprimirMensaje("La jerarquía " + jerarquia->getNombre() + " no tiene asignada ninguna entidad especializada.");
		this->invalidarDiagrama();
	}

	// Cobertura
	if (jerarquia->getCobertura().compare(TIPO_COBERTURA_PARCIAL) != 0 &&
			jerarquia->getCobertura().compare(TIPO_COBERTURA_TOTAL) != 0){
		this->imprimirMensaje("La jerarquía " + jerarquia->getNombre() + " no tiene asignada una cobertura válida.");
		this->invalidarDiagrama();
	}

	// Intersección
	if (jerarquia->getInterseccion().compare(TIPO_INTERSECCION_EXCLUSIVA) != 0 &&
			jerarquia->getInterseccion().compare(TIPO_INTERSECCION_SUPERPUESTA) != 0){
		this->imprimirMensaje("La jerarquía " + jerarquia->getNombre() + " no tiene asignada una intersección válida.");
		this->invalidarDiagrama();
	}
}

void ValidacionVisitor::visit(UnionEntidadRelacion* unionEntidadRelacion){
	// Relación
	if (unionEntidadRelacion->getRelacion() == NULL){
		this->imprimirMensaje("Hay una unión entidad relación que no pertenecea ninguna relación.");
		this->invalidarDiagrama();
	} else {

		// Entidad
		if (unionEntidadRelacion->getEntidad() == NULL){
			this->imprimirMensaje("Una de las uniones de la relación " + unionEntidadRelacion->getRelacion()->getNombre()
					+ "no tiene una entidad asociada.");
			this->invalidarDiagrama();
		}
	}

	// Cardinalidades
	if (unionEntidadRelacion->getCardinalidadMinima().compare("") == 0){
		this->imprimirMensaje("Una de las uniones de la relación " + unionEntidadRelacion->getRelacion()->getNombre()
				+ " no tiene asignada la cardinalidad mínima.");
		this->invalidarDiagrama();
	}
	if (unionEntidadRelacion->getCardinalidadMaxima().compare("") == 0){
		this->imprimirMensaje("Una de las uniones de la relación " + unionEntidadRelacion->getRelacion()->getNombre()
				+ " no tiene asignada la cardinalidad máxima.");
		this->invalidarDiagrama();
	}

	// Rol
	if (unionEntidadRelacion->getRol().compare("") == 0){
		this->imprimirMensaje("Una de las uniones de la relación " + unionEntidadRelacion->getRelacion()->getNombre() +
				" no tiene asignado el rol.");
		// No se invalida el diagrama porque el rol no es obligatorio.
	}
}
