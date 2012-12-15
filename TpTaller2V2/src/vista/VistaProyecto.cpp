#include "VistaProyecto.h"

VistaProyecto::VistaProyecto(Proyecto * proyectoModelo) {
	//Prueba
	this->proyecto = proyectoModelo;
	this->diagramaPrincipal = new VistaDiagrama(proyectoModelo->getDiagramaPrincipal());

}


VistaProyecto::~VistaProyecto() {
	// TODO Auto-generated destructor stub
	delete this->diagramaPrincipal;

}

void VistaProyecto::testCargarDiagramas() {
	/*VistaDiagrama* diagrama = new VistaDiagrama(new Diagrama("Sub Diag Prueba1"));
	 this->getDiagramaPrincipal()->getDiagrama()->agregarDiagramaHijo(diagrama->getDiagrama());

	 diagrama = new VistaDiagrama(new Diagrama("SUB SUB DIAG 1"));
	 (*(this->getDiagramaPrincipal()->getDiagrama()->diagramasHijosBegin()))->agregarDiagramaHijo(diagrama->getDiagrama());

	 diagrama = new VistaDiagrama(new Diagrama("Sub Diag Prueba2 0.75"));
	 diagrama->setZoom(0.75);
	 this->getDiagramaPrincipal()->getDiagrama()->agregarDiagramaHijo(diagrama->getDiagrama());*/
	VistaDiagrama * diag;
	this->diagramaPrincipal->crearDiagramaHijo("Sub Diag Prueba1");
	this->diagramaPrincipal->crearDiagramaHijo("Sub Diag Prueba2");
	diag = this->diagramaPrincipal->crearDiagramaHijo("Sub Diag Prueba3 0,75");
	//diag->setZoom(0.75);

}

void VistaProyecto::eliminarModelo(){
	delete this->proyecto;
	this->proyecto = NULL;
}

VistaDiagrama* VistaProyecto::getDiagramaPrincipal() {
	return this->diagramaPrincipal;
}

void VistaProyecto::setNombre(const std::string & nombre) {
	this->proyecto->setNombre(nombre);
}

void VistaProyecto::get_diagramas(list<VistaDiagrama*> & lista){
	diagramas_recur(this->diagramaPrincipal, lista);
}

void VistaProyecto::diagramas_recur(VistaDiagrama* diag, list<VistaDiagrama*> & lista){
	lista.push_back(diag);
	std::vector<VistaDiagrama*>::iterator it = diag->vdiagramasBegin();
	std::vector<VistaDiagrama*>::iterator it1 = diag->vdiagramasEnd();
	while (it != it1){
		diagramas_recur(*it,lista);
		it++;
	}
}

std::string VistaProyecto::getNombre(){
	return this->proyecto->getNombre();
}
