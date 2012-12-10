#include "VistaDiagrama.h"
#include <gdkmm.h>
#include <iostream>

#include <algorithm>

using namespace std;

double VistaDiagrama::paso_zoom = 0.1;

VistaDiagrama::VistaDiagrama(Diagrama * diagramaModelo, int a) {

	// para persistencia
	this->estado = "sin_validar";

	this->diagrama = diagramaModelo;
	this->zoom = ZOOM_DEFECTO;
	this->ancho = 800;
	this->alto = 600;

	//this->get_parent()->get_size_request(this->ancho,this->alto);

	this->set_size_request(this->ancho, this->alto);

	//this->estaRedimensionandoElemento = false;

	// Habilito el evento de apretar el boton del mouse
	this->add_events(Gdk::BUTTON_PRESS_MASK | Gdk::POINTER_MOTION_MASK);

	this->signal_button_press_event().connect(
			sigc::mem_fun(*this, &VistaDiagrama::on_button_press_event));
	this->signal_button_release_event().connect(
			sigc::mem_fun(*this, &VistaDiagrama::on_button_release_event));
	this->signal_motion_notify_event().connect(
			sigc::mem_fun(*this, &VistaDiagrama::on_mouse_motion_event));

	configurar_drag_and_drop();

	this->diagramaAncestro = NULL;

	// TEST

	// NO SACAR EL IF SI PRUEBAN EL TEST 4
	this->zoom = 1;
	//test_1_builder();
	if (a == 0) {
		test_3_builder();
		//test_6_builder();
		//test_5_builder_interfaz_grafica();
		//test_5_builder_persistencia();
	}
}

// ENTIDAD
void VistaDiagrama::test_1_builder() {
	// POR INTERFAZ GRAFICA
	VistaEntidadNueva * ve1;
	ve1 = ComponentsBuilder::getInstance()->crearEntidadNuevaEnDiagrama(this);

	ve1->setposini(1, 1);
	ve1->setposfin(100, 50);
	ve1->setNombre("Entidad");

	/************ POR PERSISTENCIA *************/
	// CREO EL MODELO A MANO
	EntidadNueva * e2 = new EntidadNueva();
	e2->setCodigo(GeneradorCodigo::getInstance()->getSiguienteCodigo());
	VistaEntidadNueva * ve2;

	ve2 = ComponentsBuilder::getInstance()->crearEntidadNuevaEnDiagrama(this, e2);

	ve2->setposini(200, 1);
	ve2->setposfin(500, 50);
	ve2->setNombre("Entidad");
}

// ATRIBUTOS
void VistaDiagrama::test_2_builder() {
	// POR INTERFAZ GRAFICA
	VistaEntidadNueva * ve1;
	VistaAtributo * va1;
	VistaAtributo * va2;
	VistaAtributo * va21;
	VistaAtributo * va22;

	ve1 = ComponentsBuilder::getInstance()->crearEntidadNuevaEnDiagrama(this);

	ve1->setposini(150, 150);
	ve1->setposfin(220, 175);
	ve1->setNombre("Entidad 1");

	va1 = ComponentsBuilder::getInstance()->crearAtributoEnEntidad(this, ve1);
	va1->setposini(80, 160);
	va1->setNombre("Atributo 1");

	va2 = ComponentsBuilder::getInstance()->crearAtributoEnEntidad(this, ve1);
	va2->setposini(280, 150);
	va2->setNombre("Atributo 2");

	va21 = ComponentsBuilder::getInstance()->crearAtributoEnAtributo(this, va2);
	va21->setposini(350, 140);
	va21->setNombre("Atributo 2:1");

	va22 = ComponentsBuilder::getInstance()->crearAtributoEnAtributo(this, va2);
	va22->setposini(380, 160);
	va22->setNombre("Atributo 2:2");

	/************ POR PERSISTENCIA *************/
	VistaEntidadNueva * ve2;
	Atributo * a3;
	Atributo * a4;
	Atributo * a41;
	Atributo * a42;
	VistaAtributo * va3;
	VistaAtributo * va4;
	VistaAtributo * va41;
	VistaAtributo * va42;

	ve2 = ComponentsBuilder::getInstance()->crearEntidadNuevaEnDiagrama(this);

	ve2->setposini(150, 200);
	ve2->setposfin(220, 225);
	ve2->setNombre("Entidad 2");

	// CREO EL MODELO A MANO
	a3 = new Atributo();
	a3->setCodigo(GeneradorCodigo::getInstance()->getSiguienteCodigo());
	a4 = new Atributo();
	a4->setCodigo(GeneradorCodigo::getInstance()->getSiguienteCodigo());
	a41 = new Atributo();
	a41->setCodigo(GeneradorCodigo::getInstance()->getSiguienteCodigo());
	a42 = new Atributo();
	a42->setCodigo(GeneradorCodigo::getInstance()->getSiguienteCodigo());
	ve2->getEntidadNueva()->agregarAtributo(a3);
	ve2->getEntidadNueva()->agregarAtributo(a4);
	a4->agregarAtributo(a41);
	a4->agregarAtributo(a42);

	va3 = ComponentsBuilder::getInstance()->crearAtributoEnEntidad(this, ve2, a3);
	va3->setposini(80, 215);
	va3->setNombre("Atributo 3");

	va4 = ComponentsBuilder::getInstance()->crearAtributoEnEntidad(this, ve2, a4);
	va4->setposini(280, 215);
	va4->setNombre("Atributo 4");

	va41 = ComponentsBuilder::getInstance()->crearAtributoEnAtributo(this, va4, a41);
	va41->setposini(350, 250);
	va41->setNombre("Atributo 4:1");

	va42 = ComponentsBuilder::getInstance()->crearAtributoEnAtributo(this, va4, a42);
	va42->setposini(380, 230);
	va42->setNombre("Atributo 4:2");

}

// RELACION-ENTIDAD
void VistaDiagrama::test_3_builder() {
	/**********       POR INTERFAZ GRAFICA      **********/
	VistaEntidadNueva * ve1;
	VistaEntidadNueva * ve2;
	VistaRelacion * vr2;
	VistaUnionEntidadRelacion * vu1;
	VistaUnionEntidadRelacion * vu2;

	ve1 = ComponentsBuilder::getInstance()->crearEntidadNuevaEnDiagrama(this);

	ve1->setposini(150, 150);
	ve1->setposfin(220, 175);
	ve1->setNombre("Entidad 1");

	ve2 = ComponentsBuilder::getInstance()->crearEntidadNuevaEnDiagrama(this);

	ve2->setposini(360, 150);
	ve2->setposfin(430, 175);
	ve2->setNombre("Entidad 2");

	vr2 = ComponentsBuilder::getInstance()->crearRelacionEnDiagrama(this);

	vr2->setposini(251, 140);
	vr2->setposfin(330, 180);
	vr2->setNombre("Relacion");

	vu1 = ComponentsBuilder::getInstance()->crearUnionEntidadRelacion(this, ve1, vr2);

	vu2 = ComponentsBuilder::getInstance()->crearUnionEntidadRelacion(this, ve2, vr2);

	/************ POR PERSISTENCIA *************/
	// CREO EL MODELO A MANO
	EntidadNueva * e3 = new EntidadNueva();
	e3->setCodigo(GeneradorCodigo::getInstance()->getSiguienteCodigo());
	EntidadNueva * e4 = new EntidadNueva();
	e4->setCodigo(GeneradorCodigo::getInstance()->getSiguienteCodigo());
	Relacion * r2 = new Relacion();
	r2->setCodigo(GeneradorCodigo::getInstance()->getSiguienteCodigo());
	UnionEntidadRelacion * u3 = new UnionEntidadRelacion(e3, r2);
	u3->setCodigo(GeneradorCodigo::getInstance()->getSiguienteCodigo());
	UnionEntidadRelacion * u4 = new UnionEntidadRelacion(e4, r2);
	u4->setCodigo(GeneradorCodigo::getInstance()->getSiguienteCodigo());

	VistaEntidadNueva * ve3;
	VistaEntidadNueva * ve4;
	VistaRelacion * vr1;
	VistaUnionEntidadRelacion * vu3;
	VistaUnionEntidadRelacion * vu4;

	ve3 = ComponentsBuilder::getInstance()->crearEntidadNuevaEnDiagrama(this);

	ve3->setposini(150, 200);
	ve3->setposfin(220, 225);
	ve3->setNombre("Entidad 1");

	ve4 = ComponentsBuilder::getInstance()->crearEntidadNuevaEnDiagrama(this);

	ve4->setposini(360, 200);
	ve4->setposfin(430, 225);
	ve4->setNombre("Entidad 2");

	vr1 = ComponentsBuilder::getInstance()->crearRelacionEnDiagrama(this, r2);

	vr1->setposini(251, 190);
	vr1->setposfin(330, 230);
	vr1->setNombre("Relacion");

	vu3 = ComponentsBuilder::getInstance()->crearUnionEntidadRelacion(this, ve3, vr1, u3);

	vu4 = ComponentsBuilder::getInstance()->crearUnionEntidadRelacion(this, ve4, vr1, u4);
}

// ENTIDAD GLOBAL
void VistaDiagrama::test_4_builder() {
	/************   OJO CON EL 1, SOLO PARA DEBUG (GONZALO) *************/
	/************   NO PONERLO EN 0                         *************/
	Diagrama * diagramaHijo = new Diagrama();
	VistaDiagrama * vistaDiagramaHijo = new VistaDiagrama(diagramaHijo, 1);
	diagramaHijo->setNombre("Diagrama Hijo 1");
	this->agregarDiagramaHijo(vistaDiagramaHijo);

	/**********       POR INTERFAZ GRAFICA      **********/
	VistaEntidadNueva * ve1;
	VistaEntidadGlobal * vg1;

	ve1 = ComponentsBuilder::getInstance()->crearEntidadNuevaEnDiagrama(this);

	ve1->setposini(150, 100);
	ve1->setposfin(220, 125);
	ve1->setNombre("Entidad 1");

	vg1 = ComponentsBuilder::getInstance()->crearEntidadGlobalEnDiagrama(vistaDiagramaHijo,
			"Entidad 1");
	vg1->setposini(140, 100);
	vg1->setposfin(230, 125);
	vg1->setNombre("Entidad Global 1");

	/************ POR PERSISTENCIA *************/
	// CREO EL MODELO A MANO
	EntidadNueva * e2 = new EntidadNueva();
	e2->setCodigo(GeneradorCodigo::getInstance()->getSiguienteCodigo());
	EntidadGlobal * g2 = new EntidadGlobal();
	g2->setCodigo(GeneradorCodigo::getInstance()->getSiguienteCodigo());
	g2->setEntidadNueva(e2);

	VistaEntidadNueva * ve2;
	VistaEntidadGlobal * vg2;

	ve2 = ComponentsBuilder::getInstance()->crearEntidadNuevaEnDiagrama(this, e2);

	ve2->setposini(150, 150);
	ve2->setposfin(220, 175);
	ve2->setNombre("Entidad 2");

	vg2 = ComponentsBuilder::getInstance()->crearEntidadGlobalEnDiagrama(vistaDiagramaHijo,
			"Entidad 2", g2);
	vg2->setposini(140, 150);
	vg2->setposfin(230, 175);
	vg2->setNombre("Entidad Global 2");

}

//IDENTIFICADOR
void VistaDiagrama::test_5_builder_interfaz_grafica() {
	/**********       POR INTERFAZ GRAFICA      **********/
	VistaEntidadNueva * ve1;
	VistaEntidadNueva * ve2;
	VistaRelacion * vr1;
	VistaUnionEntidadRelacion *vu1;
	VistaUnionEntidadRelacion *vu2;
	VistaAtributo * va1;
	VistaAtributo * va2;
	VistaAtributo * va3;
	VistaAtributo * va4;
	VistaAtributo * va41;
	VistaAtributo * va42;
	VistaAtributo * va5;
	VistaIdentificador * vi1;
	VistaIdentificador * vi2;
	VistaIdentificador * vi3;
	VistaIdentificador * vi4;

	ve1 = ComponentsBuilder::getInstance()->crearEntidadNuevaEnDiagrama(this);
	ve1->setposini(150, 150);
	ve1->setposfin(220, 175);
	ve1->setNombre("Entidad 1");
	va1 = ComponentsBuilder::getInstance()->crearAtributoEnEntidad(this, ve1);
	va1->setposini(80, 160);
	va1->setNombre("Atributo 1");
	va2 = ComponentsBuilder::getInstance()->crearAtributoEnEntidad(this, ve1);
	va2->setposini(150, 100);
	va2->setNombre("Atributo 2");
	va3 = ComponentsBuilder::getInstance()->crearAtributoEnEntidad(this, ve1);
	va3->setposini(220, 100);
	va3->setNombre("Atributo 3");
	va4 = ComponentsBuilder::getInstance()->crearAtributoEnEntidad(this, ve1);
	va4->setposini(250, 150);
	va4->setNombre("Atributo 4");
	va41 = ComponentsBuilder::getInstance()->crearAtributoEnAtributo(this, va4);
	va41->setposini(370, 140);
	va41->setNombre("Atributo 4:1");
	va42 = ComponentsBuilder::getInstance()->crearAtributoEnAtributo(this, va4);
	va42->setposini(370, 180);
	va42->setNombre("Atributo 4:2");
	va5 = ComponentsBuilder::getInstance()->crearAtributoEnEntidad(this, ve1);
	va5->setposini(80, 220);
	va5->setNombre("Atributo 5");

	vi1 = ComponentsBuilder::getInstance()->crearIdentificadorEnEntidad(this, ve1);
	ComponentsBuilder::getInstance()->agregarAtributoAIdentificador(vi1, va1);

	vi2 = ComponentsBuilder::getInstance()->crearIdentificadorEnEntidad(this, ve1);
	ComponentsBuilder::getInstance()->agregarAtributoAIdentificador(vi2, va2);
	ComponentsBuilder::getInstance()->agregarAtributoAIdentificador(vi2, va3);

	vi3 = ComponentsBuilder::getInstance()->crearIdentificadorEnEntidad(this, ve1);
	ComponentsBuilder::getInstance()->agregarAtributoAIdentificador(vi3, va4);

	vr1 = ComponentsBuilder::getInstance()->crearRelacionEnDiagrama(this);
	vr1->setposini(150, 220);
	vr1->setposfin(220, 255);
	vr1->setNombre("Relacion");
	ve2 = ComponentsBuilder::getInstance()->crearEntidadNuevaEnDiagrama(this);
	ve2->setposini(150, 300);
	ve2->setposfin(220, 325);
	ve2->setNombre("Entidad 2");
	vu1 = ComponentsBuilder::getInstance()->crearUnionEntidadRelacion(this, ve1, vr1);
	vu2 = ComponentsBuilder::getInstance()->crearUnionEntidadRelacion(this, ve2, vr1);

	vi4 = ComponentsBuilder::getInstance()->crearIdentificadorEnEntidad(this, ve1);
	ComponentsBuilder::getInstance()->agregarAtributoAIdentificador(vi4, va5);
	ComponentsBuilder::getInstance()->agregarEntidadFuerteAIdentificador(vi4, vu2);
}

// IDENTIFICADOR
void VistaDiagrama::test_5_builder_persistencia() {
	/************ POR PERSISTENCIA *************/
	// CREO EL MODELO A MANO
	EntidadNueva * e1 = new EntidadNueva();
	EntidadNueva * e2 = new EntidadNueva();
	Relacion *r1 = new Relacion();
	UnionEntidadRelacion * u1 = new UnionEntidadRelacion(e1, r1);
	UnionEntidadRelacion * u2 = new UnionEntidadRelacion(e2, r1);
	Atributo * a1 = new Atributo();
	Atributo * a2 = new Atributo();
	Atributo * a3 = new Atributo();
	Atributo * a4 = new Atributo();
	Atributo * a41 = new Atributo();
	Atributo * a42 = new Atributo();
	Atributo * a5 = new Atributo();
	Identificador * i1 = new Identificador();
	Identificador * i2 = new Identificador();
	Identificador * i3 = new Identificador();
	Identificador * i4 = new Identificador();
	e1->setCodigo(GeneradorCodigo::getInstance()->getSiguienteCodigo());
	e2->setCodigo(GeneradorCodigo::getInstance()->getSiguienteCodigo());
	r1->setCodigo(GeneradorCodigo::getInstance()->getSiguienteCodigo());
	u1->setCodigo(GeneradorCodigo::getInstance()->getSiguienteCodigo());
	u2->setCodigo(GeneradorCodigo::getInstance()->getSiguienteCodigo());
	a1->setCodigo(GeneradorCodigo::getInstance()->getSiguienteCodigo());
	a2->setCodigo(GeneradorCodigo::getInstance()->getSiguienteCodigo());
	a3->setCodigo(GeneradorCodigo::getInstance()->getSiguienteCodigo());
	a4->setCodigo(GeneradorCodigo::getInstance()->getSiguienteCodigo());
	a41->setCodigo(GeneradorCodigo::getInstance()->getSiguienteCodigo());
	a42->setCodigo(GeneradorCodigo::getInstance()->getSiguienteCodigo());
	a5->setCodigo(GeneradorCodigo::getInstance()->getSiguienteCodigo());
	e1->agregarAtributo(a1);
	e1->agregarAtributo(a2);
	e1->agregarAtributo(a3);
	e1->agregarAtributo(a4);
	a4->agregarAtributo(a41);
	a4->agregarAtributo(a42);
	e1->agregarAtributo(a5);
	i1->agregarCodigoAtributo(a1->getCodigo());
	i2->agregarCodigoAtributo(a2->getCodigo());
	i2->agregarCodigoAtributo(a3->getCodigo());
	i3->agregarCodigoAtributo(a4->getCodigo());
	i4->agregarCodigoAtributo(a5->getCodigo());
	i4->agregarCodigoRelacion(r1->getCodigo());

	VistaEntidadNueva * ve1;
	VistaEntidadNueva * ve2;
	VistaRelacion * vr1;
	VistaUnionEntidadRelacion *vu1;
	VistaUnionEntidadRelacion *vu2;
	VistaAtributo * va1;
	VistaAtributo * va2;
	VistaAtributo * va3;
	VistaAtributo * va4;
	VistaAtributo * va41;
	VistaAtributo * va42;
	VistaAtributo * va5;
	VistaIdentificador * vi1;
	VistaIdentificador * vi2;
	VistaIdentificador * vi3;
	VistaIdentificador * vi4;

	ve1 = ComponentsBuilder::getInstance()->crearEntidadNuevaEnDiagrama(this, e1);
	ve1->setposini(150, 150);
	ve1->setposfin(220, 175);
	ve1->setNombre("Entidad 1");
	va1 = ComponentsBuilder::getInstance()->crearAtributoEnEntidad(this, ve1, a1);
	va1->setposini(80, 160);
	va1->setNombre("Atributo 1");
	va2 = ComponentsBuilder::getInstance()->crearAtributoEnEntidad(this, ve1, a2);
	va2->setposini(150, 100);
	va2->setNombre("Atributo 2");
	va3 = ComponentsBuilder::getInstance()->crearAtributoEnEntidad(this, ve1, a3);
	va3->setposini(220, 100);
	va3->setNombre("Atributo 3");
	va4 = ComponentsBuilder::getInstance()->crearAtributoEnEntidad(this, ve1, a4);
	va4->setposini(250, 150);
	va4->setNombre("Atributo 4");
	va41 = ComponentsBuilder::getInstance()->crearAtributoEnAtributo(this, va4, a41);
	va41->setposini(370, 140);
	va41->setNombre("Atributo 4:1");
	va42 = ComponentsBuilder::getInstance()->crearAtributoEnAtributo(this, va4, a41);
	va42->setposini(370, 180);
	va42->setNombre("Atributo 4:2");
	va5 = ComponentsBuilder::getInstance()->crearAtributoEnEntidad(this, ve1, a5);
	va5->setposini(80, 220);
	va5->setNombre("Atributo 5");

	vi1 = ComponentsBuilder::getInstance()->crearIdentificadorEnEntidad(this, ve1, i1);
	ComponentsBuilder::getInstance()->agregarAtributoAIdentificador(vi1, va1);

	vi2 = ComponentsBuilder::getInstance()->crearIdentificadorEnEntidad(this, ve1, i2);
	ComponentsBuilder::getInstance()->agregarAtributoAIdentificador(vi2, va2);
	ComponentsBuilder::getInstance()->agregarAtributoAIdentificador(vi2, va3);

	vi3 = ComponentsBuilder::getInstance()->crearIdentificadorEnEntidad(this, ve1, i3);
	ComponentsBuilder::getInstance()->agregarAtributoAIdentificador(vi3, va4);

	vr1 = ComponentsBuilder::getInstance()->crearRelacionEnDiagrama(this, r1);
	vr1->setposini(150, 220);
	vr1->setposfin(220, 255);
	vr1->setNombre("Relacion");
	ve2 = ComponentsBuilder::getInstance()->crearEntidadNuevaEnDiagrama(this, e2);
	ve2->setposini(150, 300);
	ve2->setposfin(220, 325);
	ve2->setNombre("Entidad 2");
	vu1 = ComponentsBuilder::getInstance()->crearUnionEntidadRelacion(this, ve1, vr1, u1);
	vu2 = ComponentsBuilder::getInstance()->crearUnionEntidadRelacion(this, ve2, vr1, u2);

	vi4 = ComponentsBuilder::getInstance()->crearIdentificadorEnEntidad(this, ve1, i4);
	ComponentsBuilder::getInstance()->agregarAtributoAIdentificador(vi4, va5);
	ComponentsBuilder::getInstance()->agregarEntidadFuerteAIdentificador(vi4, vu2);
}

//JERARQUIA
void VistaDiagrama::test_6_builder() {
	/**********       POR INTERFAZ GRAFICA      **********/
	VistaEntidadNueva * ve1;
	VistaEntidadNueva * ve2;
	VistaEntidadNueva * ve3;
	VistaJerarquia * vj1;

	ve1 = ComponentsBuilder::getInstance()->crearEntidadNuevaEnDiagrama(this);
	ve1->setposini(150, 50);
	ve1->setposfin(220, 75);
	ve1->setNombre("Entidad 1");
	ve2 = ComponentsBuilder::getInstance()->crearEntidadNuevaEnDiagrama(this);
	ve2->setposini(100, 150);
	ve2->setposfin(170, 175);
	ve2->setNombre("Entidad 2");
	ve3 = ComponentsBuilder::getInstance()->crearEntidadNuevaEnDiagrama(this);
	ve3->setposini(200, 150);
	ve3->setposfin(270, 175);
	ve3->setNombre("Entidad 3");
	vj1 = ComponentsBuilder::getInstance()->crearJerarquiaEnDiagrama(this);

	ComponentsBuilder::getInstance()->agregarJerarquiaHijaDeEntidad(vj1, ve1);
	ComponentsBuilder::getInstance()->agregarJerarquiaPadreDeEntidad(vj1, ve2);
	ComponentsBuilder::getInstance()->agregarJerarquiaPadreDeEntidad(vj1, ve3);

	/************ POR PERSISTENCIA *************/
	// CREO EL MODELO A MANO
	EntidadNueva * e4 = new EntidadNueva();
	EntidadNueva * e5 = new EntidadNueva();
	EntidadNueva * e6 = new EntidadNueva();
	Jerarquia * j2 = new Jerarquia();
	j2->setEntidadGeneral(e4);
	j2->agregarEntidadEspecializada(e5);
	j2->agregarEntidadEspecializada(e6);
	e4->setJerarquiaHija(j2);
	e5->agregarJerarquiaPadre(j2);
	e6->agregarJerarquiaPadre(j2);

	VistaEntidadNueva * ve4;
	VistaEntidadNueva * ve5;
	VistaEntidadNueva * ve6;
	VistaJerarquia * vj2;

	ve4 = ComponentsBuilder::getInstance()->crearEntidadNuevaEnDiagrama(this, e4);
	ve4->setposini(150, 250);
	ve4->setposfin(220, 275);
	ve4->setNombre("Entidad 1");
	ve5 = ComponentsBuilder::getInstance()->crearEntidadNuevaEnDiagrama(this, e5);
	ve5->setposini(100, 350);
	ve5->setposfin(170, 375);
	ve5->setNombre("Entidad 2");
	ve6 = ComponentsBuilder::getInstance()->crearEntidadNuevaEnDiagrama(this, e6);
	ve6->setposini(200, 350);
	ve6->setposfin(270, 375);
	ve6->setNombre("Entidad 3");
	vj2 = ComponentsBuilder::getInstance()->crearJerarquiaEnDiagrama(this, j2);

	ComponentsBuilder::getInstance()->agregarJerarquiaHijaDeEntidad(vj2, ve4);
	ComponentsBuilder::getInstance()->agregarJerarquiaPadreDeEntidad(vj2, ve5);
	ComponentsBuilder::getInstance()->agregarJerarquiaPadreDeEntidad(vj2, ve6);
}

VistaDiagrama::~VistaDiagrama() {
	this->eliminar();
}

void VistaDiagrama::eliminar() {
	// REGLA, LA VISTA NO BORRA AL MODELO
	/*if(this->diagrama!=NULL){
	 delete this->diagrama;
	 }*/

	std::vector<VistaComponente *>::iterator i;
	std::vector<VistaDiagrama *>::iterator j;

	for (i = this->componentesBegin(); i != this->componentesEnd(); i++) {
		delete (*i);
	}

	for (j = this->diagramas.begin(); j != this->diagramas.end(); j++) {
		delete (*j);
	}

	this->componentes.clear();
	this->diagramas.clear();

}

void VistaDiagrama::obtenerVistaAPartirDeRelacion(VistaRelacion * vRelacion,
		std::vector<VistaEntidadNueva *> &vistasEntidadesACrear,
		std::vector<UnionEntidadRelacion *> &unionesACrear) {
	vistasEntidadesACrear.clear();
	unionesACrear.clear();

	std::vector<UnionEntidadRelacion *> uniones = vRelacion->getUniones();
	std::vector<UnionEntidadRelacion *>::iterator i;
	std::vector<VistaComponente *>::iterator j;
	Componente * componente;
	for (i = uniones.begin(); i != uniones.end(); i++) {
		componente = (*i)->getEntidad();
		for (j = this->componentes.begin(); j != this->componentes.end(); j++) {
			if ((*j)->contieneEsteComponente(componente)) {
				vistasEntidadesACrear.push_back(dynamic_cast<VistaEntidadNueva *>(*j));
				unionesACrear.push_back(*i);
				cout << "A" << endl;
				break;
			}
		}
	}
}



bool VistaDiagrama::on_expose_event(GdkEventExpose* e) {
	this->set_size_request(this->ancho, this->alto);
	Cairo::RefPtr<Cairo::Context> context;
	context = this->get_window()->create_cairo_context();
	context->set_source_rgba(1, 1, 1, 1); // white
	context->paint();
	context->scale(this->zoom, this->zoom);

	this->dibujarComponentes(context, true);

	//Glib::RefPtr < Pango::Layout > layout = this->create_pango_layout("Hola");
	//	layout
	//cr->move_to(100, 100);
	//layout->update_from_cairo_context(cr);
	//layout->show_in_cairo_context(cr);

	return true;
}

void VistaDiagrama::dibujarComponentes(Cairo::RefPtr<Cairo::Context>& context,
		bool dibujarSeleccionado) {
	double pos_x, pos_y;
	std::vector<VistaComponente *>::iterator componenteActual;

	if (dibujarSeleccionado) {
		for (componenteActual = this->componentes.begin();
				componenteActual != this->componentes.end(); componenteActual++) {
			(*componenteActual)->dibujar(context);
		}
	} else {
		for (componenteActual = this->componentes.begin();
				componenteActual != this->componentes.end(); componenteActual++) {
			if ((*componenteActual)->estaSeleccionado()) {
				(*componenteActual)->getposseleccion(pos_x, pos_y);
				(*componenteActual)->deseleccionar();
				(*componenteActual)->dibujar(context);
				(*componenteActual)->seleccionar(pos_x, pos_y);
			} else {
				(*componenteActual)->dibujar(context);
			}
		}
	}
}

void VistaDiagrama::lanzarMenuPopup(VistaComponente * vistaComponente, GdkEventButton* event) {
	// Creo el menú Pop Up, Tendría que ser un singleton
	Gtk::Menu* m_pMenuPopup;
	Glib::RefPtr<Gtk::UIManager> userInterfaceManager;

	Glib::RefPtr<Gtk::ActionGroup> actionGroup;

	actionGroup = Gtk::ActionGroup::create();

	//actionGroup->add(Gtk::Action::create("ContextMenu", "Context Menu"));

	actionGroup->add(Gtk::Action::create("ContextPropiedades", "Propiedades"),
			sigc::mem_fun(*vistaComponente, &VistaComponente::on_popup_boton_propiedades));

	actionGroup->add(Gtk::Action::create("ContextEliminar", "Eliminar"),
			sigc::bind<VistaComponente *>(sigc::mem_fun(*this, &VistaDiagrama::quitarComponente),
					vistaComponente));

	userInterfaceManager = Gtk::UIManager::create();
	userInterfaceManager->insert_action_group(actionGroup);

	//Layout the actions in a menubar and toolbar:
	Glib::ustring ui_info = "<ui>"
			"  <popup name='PopupMenu'>"
			"    <menuitem action='ContextEliminar'/>"
			"    <menuitem action='ContextPropiedades'/>"
			"  </popup>"
			"</ui>";
	try {
		userInterfaceManager->add_ui_from_string(ui_info);

	} catch (const Glib::Error& ex) {
		std::cerr << "building menus failed: " << ex.what();
	}

	m_pMenuPopup = dynamic_cast<Gtk::Menu*>(userInterfaceManager->get_widget("/PopupMenu"));
	if (!m_pMenuPopup)
		g_warning("menu not found");
	else
		m_pMenuPopup->popup(event->button, event->time);
}

bool VistaDiagrama::on_button_press_event(GdkEventButton* event) {
	VistaComponente * componente;
	cout << "X= " << event->x << " Y=" << event->y << endl;
	cout << "Event button: " << event->button << endl;

	if ((event->type == GDK_BUTTON_PRESS) && (event->button == 3)) {
		componente = obtenerComponenteEnPos(event->x / this->zoom, event->y / this->zoom);
		if (componente != NULL) {
			if (!componente->estaSeleccionado()) {
				seleccionar_componente_clickeado(event->x / this->zoom, event->y / this->zoom);
			}
			lanzarMenuPopup(componente, event);
		}
	} else {
		seleccionar_componente_clickeado(event->x / this->zoom, event->y / this->zoom);

		if (this->componentes_seleccionados.size() == 1
				&& this->componentes_seleccionados[0]->esPuntoDeRedimension(event->x / this->zoom,
						event->y / this->zoom)) {
			this->estaRedimensionandoElemento = true;
		} else {
			this->estaRedimensionandoElemento = false;
		}
	}

	this->x_button_press = event->x / this->zoom;
	this->y_button_press = event->y / this->zoom;

	// Para redibujar el area de dibujo
	this->queue_draw();
	return true;
}

bool VistaDiagrama::on_button_release_event(GdkEventButton* event) {

	this->estaRedimensionandoElemento = false;
	cout << "Release X= " << event->x << " Y= " << event->y << endl;

	this->queue_draw();
	return true;
}

void VistaDiagrama::seleccionar_componente_clickeado(gdouble x, gdouble y) {

	std::vector<VistaComponente *>::iterator componenteActual;

	// IF NOT APRETO CONTROL
	componentes_seleccionados.clear();

	for (componenteActual = this->componentes.begin(); componenteActual != this->componentes.end();
			componenteActual++) {
		if ((*componenteActual)->contieneAEstePunto(x, y)) {
			(*componenteActual)->seleccionar(x, y);
			componentes_seleccionados.push_back((*componenteActual));
			componenteActual++;
			// if(!apreto_control){
			break;
			//} else {
			//return;
			//}
		} else {
			(*componenteActual)->deseleccionar();
		}
		//(*componenteActual)->dibujar(cr);
	}

	while (componenteActual != this->componentes.end()) {
		(*componenteActual)->deseleccionar();
		componenteActual++;
	}
}

int VistaDiagrama::getAlto() {
	return this->alto;
}

int VistaDiagrama::getAncho() {
	return this->ancho;
}

VistaDiagrama* VistaDiagrama::crearDiagramaHijo(string nombre) {
	Diagrama * nuevoDiagrama = new Diagrama();
	nuevoDiagrama->setNombre(nombre);
	this->diagrama->agregarDiagramaHijo(nuevoDiagrama);
	VistaDiagrama* diagramaHijo = new VistaDiagrama(nuevoDiagrama);
	this->diagramas.push_back(diagramaHijo);
	return diagramaHijo;
}

bool VistaDiagrama::on_mouse_motion_event(GdkEventMotion * event) {
	std::vector<VistaComponente *>::iterator componenteActual;

	if (!this->estaRedimensionandoElemento) {
		for (componenteActual = this->componentes.begin();
				componenteActual != this->componentes.end(); componenteActual++) {
			(*componenteActual)->setMouseArriba(event->x / this->zoom, event->y / this->zoom);
		}
	}
#ifdef DEBUG
	cout << "Mouse Motion X= " << event->x << " Y= " << event->y << endl;
#endif
	this->queue_draw();
	return true;
}

void VistaDiagrama::configurar_drag_and_drop() {
	// Drag And Drop

	// Defino las cosas que se pueden arrastrar
	std::vector<Gtk::TargetEntry> listaDeTargets;
	listaDeTargets.push_back(Gtk::TargetEntry("Entidad"));
	listaDeTargets.push_back(Gtk::TargetEntry("Relacion"));
	listaDeTargets.push_back(Gtk::TargetEntry("Union"));
	// TODO crear Comentarios
	listaDeTargets.push_back(Gtk::TargetEntry("Comentario"));

	// Configuro el widget origen
	this->drag_source_set(listaDeTargets, Gdk::BUTTON1_MASK, Gdk::ACTION_MOVE);
	this->signal_drag_begin().connect(sigc::mem_fun(*this, &VistaDiagrama::drag_begin));
	this->signal_drag_motion().connect(sigc::mem_fun(*this, &VistaDiagrama::drag_motion));
	//this->signal_drag_data_delete().connect(sigc::mem_fun(*this,
	//		&VistaDiagrama::drag_data_delete));
	//this->signal_drag_data_get().connect(sigc::mem_fun(*this,
	//		&VistaDiagrama::drag_data_get));
	//this->signal_drag_drop().connect(sigc::mem_fun(*this,
	//		&VistaDiagrama::drag_drop));
	this->signal_drag_end().connect(sigc::mem_fun(*this, &VistaDiagrama::drag_end));
	//this->signal_drag_failed().connect(sigc::mem_fun(*this,
	//		&VistaDiagrama::drag_failed));
	//this->signal_drag_leave().connect(sigc::mem_fun(*this,
	//		&VistaDiagrama::drag_leave));

	// Configuro el widget destino
	this->drag_dest_set(listaDeTargets, Gtk::DEST_DEFAULT_ALL, Gdk::ACTION_MOVE);
	//this->signal_drag_data_received().connect(sigc::mem_fun(*this,
	//		&VistaDiagrama::drag_data_received));
}

void VistaDiagrama::drag_begin(const Glib::RefPtr<Gdk::DragContext>&context) {
	Glib::ustring seleccion = context->get_selection();
	//Glib::RefPtr<Gdk::Pixbuf> icono = Gdk::Pixbuf::create_from_inline(0,NULL,false);
	// Le saco el icono
	Cairo::RefPtr<Cairo::ImageSurface> imSur = Cairo::ImageSurface::create(Cairo::FORMAT_RGB24, 1,
			1);
	Glib::RefPtr<Gdk::Pixbuf> pixbuf = Gdk::Pixbuf::create_from_data(imSur->get_data(),
			Gdk::COLORSPACE_RGB, false, 8, 1, 1, imSur->get_stride());

	context->set_icon(pixbuf, 0, 0);
#ifdef DEBUG
	cout << "DRAG_BEGIN " << seleccion << endl;
#endif
}

bool VistaDiagrama::drag_motion(const Glib::RefPtr<Gdk::DragContext>& context, gint x_actual,
		gint y_actual, guint timestamp) {

	std::vector<VistaComponente *>::iterator componenteSeleccionado;
	//double x0, y0;

	if (!this->estaRedimensionandoElemento) {
		for (componenteSeleccionado = componentes_seleccionados.begin();
				componenteSeleccionado != componentes_seleccionados.end();
				componenteSeleccionado++) {
			//(*componenteSeleccionado)->getposini(x0, y0);
			//if (x0 > 1 && y0 > 1) {
			(*componenteSeleccionado)->mover(x_actual / this->zoom, y_actual / this->zoom);
			//}
			//(*componenteSeleccionado)->setposini(x_actual, y_actual);
			//(*componenteSeleccionado)->setposfin(x_actual + 50, y_actual + 40);
		}
#ifdef DEBUG
		cout << "Arrastrando X= " << x_actual << " Y= " << y_actual << endl;
#endif
	} else {
		this->componentes_seleccionados[0]->redimensionar(x_actual / this->zoom,
				y_actual / this->zoom);
		//context->drag_finish(true, true, timestamp);
#ifdef DEBUG
		cout << "Redimensionando X= " << x_actual << " Y= " << y_actual << endl;
#endif
	}

	this->queue_draw();
	return true;
}

void VistaDiagrama::drag_data_get(const Glib::RefPtr<Gdk::DragContext>&context,
		Gtk::SelectionData& selection_data, guint info, guint timestamp) {

	// 8 bits format
	// 9 the length of I'm Data! in bytes
	selection_data.set(selection_data.get_target(), 8, (const guchar*) "I'm Data!", 9);
#ifdef DEBUG
	cout << "DRAG_DATA_GET " << endl;
#endif
}

bool VistaDiagrama::drag_drop(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y,
		guint timestamp) {
#ifdef DEBUG
	cout << "DRAG_DROP" << endl;
#endif
	return true;
}

void VistaDiagrama::drag_end(const Glib::RefPtr<Gdk::DragContext>&context) {
	double x1, y1;
	bool cambio = false;
	std::vector<VistaComponente *>::iterator componenteSeleccionado;
	for (componenteSeleccionado = componentes_seleccionados.begin();
			componenteSeleccionado != componentes_seleccionados.end(); ++componenteSeleccionado) {
		(*componenteSeleccionado)->getposfin(x1, y1);
		if (x1 + 20 > this->ancho / this->zoom) {
			this->ancho = (x1 + 80) * this->zoom;
			cambio = true;
		}
		if (y1 + 20 > this->alto / this->zoom) {
			this->alto = (y1 + 80) * this->zoom;
			cambio = true;
		}
	}
	if (cambio) {
		this->set_size_request(this->ancho, this->alto);
		this->get_parent()->set_size_request(this->ancho, this->alto);
	}
	cout << "DRAG_END" << endl;
}

void VistaDiagrama::drag_data_delete(const Glib::RefPtr<Gdk::DragContext>&context) {
	cout << "DRAG_DELETE" << endl;
}

bool VistaDiagrama::drag_failed(const Glib::RefPtr<Gdk::DragContext>&context,
		Gtk::DragResult result) {
	cout << "DRAG_FAILED" << endl;
	return true;
}

void VistaDiagrama::drag_leave(const Glib::RefPtr<Gdk::DragContext>&context, guint timestamp) {
	cout << "DRAG_LEAVE" << endl;
}

void VistaDiagrama::drag_data_received(const Glib::RefPtr<Gdk::DragContext>& context,
		gint x_dropped, gint y_dropped, const Gtk::SelectionData& selection_data, guint info,
		guint timestamp) {
	const int length = selection_data.get_length();
	if ((length >= 0) && (selection_data.get_format() == 8)) {
		std::cout << "Received \"" << selection_data.get_data_as_string() << "\" in label "
				<< std::endl;
	}

	context->drag_finish(false, false, timestamp);
	cout << "DRAG_DATA_RECEIVED " << endl;
}

void VistaDiagrama::agregarComponente(VistaComponente *componente) {
	if (componente != NULL) {
		this->componentes.push_back(componente);
		this->queue_draw();
	}
}

void VistaDiagrama::quitarComponente(VistaComponente *componente) {
	if (componente != NULL) {

		remove(componentes.begin(), componentes.end(), componente);
		this->queue_draw();
	}
}

void VistaDiagrama::agregarVistaEntidadNueva(VistaEntidadNueva *ven) {
	if (ven != NULL) {
		this->componentes.push_back(ven);
		this->vistaEntidades.push_back(ven);
		this->queue_draw();
	}
}

// Para la carga de las vistas en la persistencia
void VistaDiagrama::agregarVistaEntidad(VistaEntidad *ven) {
	if (ven != NULL) {
		this->vEnt.push_back(ven);
	}
}

// Para la persistencia
void VistaDiagrama::agregarVistaIdentificador(VistaIdentificador *vIden) {
	if (vIden != NULL) {
		this->vIdentificador.push_back(vIden);
	}
}

// Para la persistencia
void VistaDiagrama::agregarVistaUnionEntidadRelacion(VistaUnionEntidadRelacion *vUER) {
	if (vUER != NULL) {
		this->vUnionEntidadRelacion.push_back(vUER);
	}
}

void VistaDiagrama::agregarDiagramaHijo(VistaDiagrama *vDiagrama) {
	if (vDiagrama != NULL) {
		this->diagramas.push_back(vDiagrama);
		vDiagrama->setDiagramaAncestro(this);
	}
}

std::string VistaDiagrama::getNombre() const {
	return this->diagrama->getNombre();
}

std::vector<VistaComponente*>::iterator VistaDiagrama::componentesBegin() {
	return this->componentes.begin();
}

std::vector<VistaComponente*>::iterator VistaDiagrama::componentesEnd() {
	return this->componentes.end();
}

std::vector<VistaDiagrama*>::iterator VistaDiagrama::vdiagramasBegin() {
	return this->diagramas.begin();
}

std::vector<VistaDiagrama*>::iterator VistaDiagrama::vdiagramasEnd() {
	return this->diagramas.end();
}

std::vector<VistaEntidadNueva*>::iterator VistaDiagrama::vEntidadesBegin() {
	return this->vistaEntidades.begin();
}
std::vector<VistaEntidadNueva*>::iterator VistaDiagrama::vEntidadesEnd() {
	return this->vistaEntidades.end();
}

std::vector<VistaEntidad*>::iterator VistaDiagrama::vEntBegin() {
	return this->vEnt.begin();
}
std::vector<VistaEntidad*>::iterator VistaDiagrama::vEntEnd() {
	return this->vEnt.end();
}

std::vector<VistaIdentificador*>::iterator VistaDiagrama::vIdentificadorBegin() {
	return this->vIdentificador.begin();
}
std::vector<VistaIdentificador*>::iterator VistaDiagrama::vIdentificadorEnd() {
	return this->vIdentificador.end();
}

std::vector<VistaUnionEntidadRelacion*>::iterator VistaDiagrama::vUnionEntidadRelacionBegin() {
	return this->vUnionEntidadRelacion.begin();
}
std::vector<VistaUnionEntidadRelacion*>::iterator VistaDiagrama::vUnionEntidadRelacionEnd() {
	return this->vUnionEntidadRelacion.end();
}

VistaComponente * VistaDiagrama::obtenerComponenteEnPos(gdouble x, gdouble y) {
	std::vector<VistaComponente *>::iterator i;
	for (i = this->componentes.begin(); i != this->componentes.end(); i++) {
		if ((*i)->contieneAEstePunto(x, y)) {
			return *i;
		}
	}
	return NULL;
}

Diagrama * VistaDiagrama::getDiagrama() {
	return this->diagrama;
}

void VistaDiagrama::setDiagramaAncestro(VistaDiagrama * ancestro) {
	this->diagramaAncestro = ancestro;
}

/*
 * Este metodo obtiene la entidad nueva y el nombre del diagrama ancestro
 * donde se encontro dicha entidad
 *
 * */

VistaEntidadNueva * VistaDiagrama::buscarEntidadNuevaEnAncestro(
		const std::string & nombreEntidadNueva, std::string & nombreDiagramaAncestro) {
	VistaDiagrama * diagramaActual;
	diagramaActual = this->diagramaAncestro;
	std::vector<VistaEntidadNueva *>::iterator i;

	while (diagramaActual != NULL) {
		for (i = diagramaActual->vistaEntidades.begin(); i != diagramaActual->vistaEntidades.end();
				i++) {
			if ((*i)->getNombre() == nombreEntidadNueva) {
				nombreDiagramaAncestro = diagramaActual->getNombre();
				return (*i);
			}
		}
		diagramaActual = diagramaActual->diagramaAncestro;
	}
	return NULL;
}

VistaEntidadNueva * VistaDiagrama::obtenerVistaEntidadNuevabyCodigo(int codigo) {

	std::vector<VistaEntidadNueva *>::iterator it = this->vEntidadesBegin();
	while (it != this->vEntidadesEnd()) {
		if ((*it)->getEntidad()->getCodigo() == codigo) {
			return (*it);
		}
		it++;
	}

	return NULL;
}

VistaEntidad * VistaDiagrama::obtenerVistaEntidadbyCodigo(int codigo) {

	std::vector<VistaEntidad *>::iterator it = this->vEntBegin();
	while (it != this->vEntEnd()) {
		if ((*it)->getEntidad()->getCodigo() == codigo) {
			return (*it);
		}
		it++;
	}

	return NULL;
}

// PERSISTENCIA REP

// Devuelve true si se logró abrir y cargar el documento.

bool VistaDiagrama::isOpenXmlREP() const {
	return this->diagramaValidoREP;
}

// CARGAR

// Recibe el nombre del diagrama del xml y carga el modelo y la vista a partir
// de los xml de representacion y composicion
// el xml de representacion termina con REP y el de composicion con COMP
// Ejemplo: el nombre del diagrama es Principal
// a partir de Principal-Rep y Principal-COMP se carga la vista y el modelo

void VistaDiagrama::abrirXml(const std::string& path) {
	// se creo el modelo con todos los diagramas
	Diagrama *diagrama = new Diagrama(path);
	this->diagrama = diagrama;
	std::string diagramaCOMP = path + EXTENSION_COMP;

	this->diagrama->abrirXmlCOMP(diagramaCOMP);

	// se crean las vistas de ese diagrama
	// todo ACA HAY PROBLEMAS
	this->crearVistasDelModelo();
	std::string diagramaREP = path + EXTENSION_REP;
	this->abrirXmlREP(diagramaREP);

	this->cargarVistaDiagramasHijos();
}

void VistaDiagrama::crearVistasDelModelo() {

	this->crearVistasEntidadNueva();
	this->crearVistasEntidadGlobal();

	this->crearVistasRelacion();

	this->crearVistasJerarquia();
	this->agregarEntidadFuerteAlIdentificador();
}

void VistaDiagrama::crearVistasEntidadNueva() {
	std::vector<EntidadNueva*>::iterator itEnt = this->getDiagrama()->entidadesNuevasBegin();
	while (itEnt != this->getDiagrama()->entidadesNuevasEnd()) {
		// el builder crea la vista entidad nueva
		VistaEntidadNueva *vEntNueva =
				ComponentsBuilder::getInstance()->crearEntidadNuevaEnDiagrama(this, (*itEnt));
		// el builder crea las vistas de los atributos de la entidad nueva
		std::vector<Atributo*>::iterator itAtrib = (*itEnt)->atributosBegin();
		while (itAtrib != (*itEnt)->atributosEnd()) {
			VistaAtributo *vAtrib = ComponentsBuilder::getInstance()->crearAtributoEnEntidad(this,
					vEntNueva, (*itAtrib));
			// el builder crea las vistas de los atributos compuestos
			std::vector<Atributo*>::iterator itAtribCompuesto = (*itAtrib)->atributosBegin();
			while (itAtribCompuesto != (*itAtrib)->atributosEnd()) {
				// La VistaAtributo* que devuelve no la utilizo en este caso
				ComponentsBuilder::getInstance()->crearAtributoEnAtributo(this, vAtrib,
						(*itAtribCompuesto));
				itAtribCompuesto++;
			}
			itAtrib++;
		}
		// identificadores
		std::vector<Identificador*>::iterator itIden = (*itEnt)->identificadoresBegin();
		while (itIden != (*itEnt)->identificadoresEnd()) {
			VistaIdentificador *vIden =
					ComponentsBuilder::getInstance()->crearIdentificadorEnEntidad(this, vEntNueva,
							(*itIden));
			// agrego la vista de atributos al identificador
			std::vector<int>::iterator itCodAtribIden = (*itIden)->codigoAtributosBegin();
			while (itCodAtribIden != (*itIden)->codigoAtributosEnd()) {
				std::vector<VistaAtributo*>::iterator itVatri = vEntNueva->atributosBegin();
				while (itVatri != vEntNueva->atributosEnd()) {
					if ((*itCodAtribIden) == (*itVatri)->getAtributo()->getCodigo())
						ComponentsBuilder::getInstance()->agregarAtributoAIdentificador(vIden,
								(*itVatri));
					itVatri++;
				}
				itCodAtribIden++;
			}
			itIden++;
		}
		itEnt++;
	}
}

void VistaDiagrama::crearVistasEntidadGlobal() {
	std::vector<EntidadGlobal*>::iterator it = this->getDiagrama()->entidadesGlobalesBegin();
	while (it != this->getDiagrama()->entidadesGlobalesEnd()) {
		int codigoEntidadNueva = (*it)->getCodigoEntidadNueva();
		EntidadNueva* entNueva = this->getDiagrama()->getEntidadNuevaByCodigo(codigoEntidadNueva);
		std::string nombreEntidadNueva = entNueva->getNombre();

		// el builder crea la vista entidad global
		ComponentsBuilder::getInstance()->crearEntidadGlobalEnDiagrama(this, nombreEntidadNueva,
				(*it));
		it++;
	}
}

void VistaDiagrama::crearVistasRelacion() {

	std::vector<Relacion*>::iterator itRel = this->getDiagrama()->relacionesBegin();
	while (itRel != this->getDiagrama()->relacionesEnd()) {
		// el builder crea la vista relacion
		VistaRelacion *vRel = ComponentsBuilder::getInstance()->crearRelacionEnDiagrama(this,
				(*itRel));
		// el builder crea las vistas de las UnionRelacion
		std::vector<UnionEntidadRelacion*>::iterator itUER = (*itRel)->unionesAEntidadBegin();

		while (itUER != (*itRel)->unionesAEntidadEnd()) {
			VistaEntidad *vEnt = this->obtenerVistaEntidadbyCodigo(
					(*itUER)->getEntidad()->getCodigo());

			ComponentsBuilder::getInstance()->crearUnionEntidadRelacion(this, vEnt, vRel, (*itUER));
			itUER++;
		}

		// el builder crea las vistas de los atributos de la relacion
		std::vector<Atributo*>::iterator itAtrib = (*itRel)->atributosBegin();
		while (itAtrib != (*itRel)->atributosEnd()) {
			VistaAtributo *vAtrib = ComponentsBuilder::getInstance()->crearAtributoEnRelacion(this,
					vRel, (*itAtrib));
			// el builder crea las vistas de los atributos compuestos
			std::vector<Atributo*>::iterator itAtribCompuesto = (*itAtrib)->atributosBegin();
			while (itAtribCompuesto != (*itAtrib)->atributosEnd()) {
				// La VistaAtributo* que devuelve no la utilizo en este caso
				ComponentsBuilder::getInstance()->crearAtributoEnAtributo(this, vAtrib,
						(*itAtribCompuesto));
				itAtribCompuesto++;
			}
			itAtrib++;
		}
		itRel++;
	}
}

void VistaDiagrama::crearVistasJerarquia() {
	std::vector<Jerarquia*>::iterator itJer = this->getDiagrama()->jerarquiasBegin();
	while (itJer != this->getDiagrama()->jerarquiasEnd()) {
		// el builder crea la vista jerarquia
		VistaJerarquia *vJer = ComponentsBuilder::getInstance()->crearJerarquiaEnDiagrama(this,
				(*itJer));

		VistaEntidad *vEnt = this->obtenerVistaEntidadbyCodigo((*itJer)->getCodigoEntidadGeneral());

		vJer->setEntidadPadre(vEnt);

		std::vector<int>::iterator itEntNueva = (*itJer)->codigosEntidadesEspecializadasBegin();
		// Para cada jerarquia agrego la entidad nueva a traves de una busqueda por su codigo
		while (itEntNueva != (*itJer)->codigosEntidadesEspecializadasEnd()) {
			VistaEntidadNueva *vEntNueva = this->obtenerVistaEntidadNuevabyCodigo((*itEntNueva));

			vJer->agregarEntidadEspecializada(vEntNueva);

			itEntNueva++;
		}

		itJer++;
	}
}

void VistaDiagrama::agregarEntidadFuerteAlIdentificador() {
	std::vector<VistaIdentificador*>::iterator itVI = this->vIdentificadorBegin();

	while (itVI != this->vIdentificadorEnd()) {

		std::vector<int>::iterator itRel = (*itVI)->getIdentificador()->codigoRelacionesBegin();

		while (itRel != (*itVI)->getIdentificador()->codigoRelacionesEnd()) {

			std::vector<VistaUnionEntidadRelacion*>::iterator itVUER =
					this->vUnionEntidadRelacionBegin();

			while (itVUER != this->vUnionEntidadRelacionEnd()) {
				// Busco el codigo de relacion que posee el identificador y lo comparo
				// con las vUnionEntidadRelacion y la que coincide la agrego a la
				// vista de identificador
				if ((*itVUER)->getUnion()->getRelacion()->getCodigo() == (*itRel)) {
					(*itVI)->agregarEntidadFuerte(*itVUER);
				}
				itVUER++;
			}
			itRel++;
		}
		itVI++;
	}
}

// Abre un archivo xml, y carga un diagrama con la informacion que contenga.
void VistaDiagrama::abrirXmlREP(const std::string& path) {
	this->diagramaValidoREP = false;

	try {
		// Abro el archivo
		Xml docXml(path);
		this->diagramaValidoREP = true;

		XmlNodo* nodoRaiz = docXml.getNodoRaiz();
		XmlNodo::verificarNombre(NOMBRE_DIAGRAMA, *nodoRaiz);
		this->cargarXmlREP(nodoRaiz);
	} catch (XmlArchivoInexistenteExc* ex) {
		delete ex;
		throw new DiagramaArchivoInexistenteExc(path);
	} catch (XmlArchivoInvalidoExc* ex) {
		delete ex;
		throw new DiagramaInvalidoExc(path);
	}
}

void VistaDiagrama::cargarXmlREP(XmlNodo* nodoRaiz) {
	// archivo listo para cargar los componentes del diagrama
	this->obtenerPropiedadesXmlREP(nodoRaiz);
	XmlNodo nodo = nodoRaiz->getHijo();
	this->obtenerComponentesXmlREP(&nodo);
}

void VistaDiagrama::obtenerPropiedadesXmlREP(XmlNodo* nodo) {
	this->estado = nodo->getPropiedad("estado");
}

// se agregan los datos de color y posicion a la vista de cada uno de los componentes
void VistaDiagrama::obtenerComponentesXmlREP(XmlNodo* nodo) {
	while (nodo->esValido()) {
		if (nodo->getNombre() == "componente") {
			VistaComponente *vComponente = obtenerComponente(nodo->getPropiedadInt("codigo"));
			if (vComponente)
				vComponente->cargarDatosXmlRep(nodo);
		}
		*nodo = nodo->getHermano();
	}
}

VistaComponente* VistaDiagrama::obtenerComponente(int codigoREP) {
	std::vector<VistaComponente *>::iterator i;
	for (i = this->componentes.begin(); i != this->componentes.end(); i++) {
		if ((*i)->getCodigoREP() == codigoREP) {
			return *i;
		}
	}
	return NULL;
}

void VistaDiagrama::cargarVistaDiagramasHijos() {
	// para cada diagrama hijo se setean los datos de las vistas

	std::vector<Diagrama*>::iterator it = this->getDiagrama()->diagramasHijosBegin();

	while (it != this->getDiagrama()->diagramasHijosEnd()) {
		std::string nombre = (*it)->getNombre();
		VistaDiagrama *vDiagrama = new VistaDiagrama((*it));
		vDiagrama->abrirXml(nombre);
		this->agregarDiagramaHijo(vDiagrama);
		it++;
	}
}

// GUARDAR

// A partir del nombre del diagrama que se pasa, se guarda el modelo en el xml
// con la extesion COMP y la representacion en el xml con la extension REP

void VistaDiagrama::guardarDiagramaXml(const std::string& path) {
	std::string diagramaCOMP;
	std::string diagramaREP;
	if (path.find("/", path.size() - 1, 1) == std::string::npos) {
		diagramaCOMP = path + "/" + this->diagrama->getNombre() + EXTENSION_COMP;
		diagramaREP = path + "/" + this->diagrama->getNombre() + EXTENSION_REP;
	} else {
		diagramaCOMP = path + this->diagrama->getNombre() + EXTENSION_COMP;
		diagramaREP = path + this->diagrama->getNombre() + EXTENSION_REP;
	}

	this->diagrama->guardarDiagramaXmlCOMP(diagramaCOMP);
	this->guardarDiagramaXmlREP(diagramaREP);
}

void VistaDiagrama::guardarDiagramaXmlREP(const std::string& path) {
	Xml docXml;
	docXml.nuevoDoc();
	XmlNodo nodoDoc = this->guardarXmlREP();
	docXml.setNodoRaiz(nodoDoc);
	docXml.guardar(path);
}

XmlNodo VistaDiagrama::guardarXmlREP() {
	XmlNodo nodo("diagrama");

	this->agregarPropiedadesXmlREP(&nodo);
	this->guardarComponentesXmlREP(&nodo);

	return nodo;
}

void VistaDiagrama::agregarPropiedadesXmlREP(XmlNodo* nodo) {
	nodo->setPropiedad(XMLNS, INSTANCE);
	nodo->setPropiedad(XSI, REPRESENTACION);
	nodo->setPropiedad("estado", this->estado);
}

void VistaDiagrama::guardarComponentesXmlREP(XmlNodo *nodo) {
	std::vector<VistaComponente*>::iterator i;

	for (i = this->componentes.begin(); i != this->componentes.end(); ++i)
		nodo->agregarHijo((*i)->guardarXmlREP());
}

void VistaDiagrama::restablecerZoom() {
	this->alto /= this->zoom;
	this->ancho /= this->zoom;
	this->zoom = 1;
	this->set_size_request(this->ancho, this->alto);
	this->get_parent()->set_size_request(this->ancho, this->alto);
#ifdef DEBUG
	std::cout << "Zoom: " << this->zoom << std::endl;
#endif
	this->queue_draw();
}

void VistaDiagrama::aumentarZoom() {
	this->alto /= this->zoom;
	this->ancho /= this->zoom;
	this->zoom += VistaDiagrama::paso_zoom;
	this->alto *= this->zoom;
	this->ancho *= this->zoom;
	this->set_size_request(this->ancho, this->alto);
	this->get_parent()->set_size_request(this->ancho, this->alto);

#ifdef DEBUG
	std::cout << "Zoom: " << this->zoom << std::endl;
	std::cout << "Ancho: " << this->ancho << " Alto: " << this->alto << std::endl;
#endif
	this->queue_draw();
}

void VistaDiagrama::disminuirZoom() {
	if (this->zoom > 0.2) {
		this->alto /= this->zoom;
		this->ancho /= this->zoom;
		this->zoom -= VistaDiagrama::paso_zoom;
		this->alto *= this->zoom;
		this->ancho *= this->zoom;
		this->set_size_request(this->ancho, this->alto);
		this->get_parent()->set_size_request(this->ancho, this->alto);
#ifdef DEBUG
		std::cout << "Zoom: " << this->zoom << std::endl;
#endif
	}
	this->queue_draw();
}

void VistaDiagrama::getDimensionesDelDiagrama(double &offset_x, double& offset_y, double& ancho,
		double& alto) {
	std::vector<VistaComponente *>::iterator i;
	double x0, y0, x1, y1;
	double xc0, yc0, xc1, yc1;
	x0 = this->ancho;
	x1 = 0;
	y0 = this->alto;
	y1 = 0;

	if (!componentes.empty()) {
		for (i = this->componentes.begin(); i != this->componentes.end(); i++) {
			(*i)->getposini(xc0, yc0);
			(*i)->getposfin(xc1, yc1);
			if (xc0 < x0) {
				x0 = xc0;
			}
			if (yc0 < y0) {
				y0 = yc0;
			}
			if (xc1 > x1) {
				x1 = xc1;
			}
			if (yc1 > y1) {
				y1 = yc1;
			}
		}
		offset_x = x0;
		offset_y = y0;
		ancho = x1 - x0;
		alto = y1 - y0;
	} else {
		offset_x = 0;
		offset_y = 0;
		ancho = 0;
		alto = 0;
	}
#ifdef DEBUG
	std::cout << "Offset (" << offset_x << ":" << offset_y << ") ";
	std::cout << "Dimensiones (" << ancho << ":" << alto << ") " << std::endl;
#endif

}
