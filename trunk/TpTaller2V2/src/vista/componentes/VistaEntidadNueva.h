#ifndef VISTAENTIDADNUEVA_H_
#define VISTAENTIDADNUEVA_H_
#include "VistaEntidad.h"
#include "../../controlador/AsistenteEntidad.h"
#include "../../controlador/AsistenteIdentificador.h"
#include "../../modelo/componentes/EntidadNueva.h"
#include "../VistaConstantes.h"
#include <vector>
#include "VistaAtributo.h"
#include "InterfazRemoverAtributo.h"

class VistaAtributo;

class VistaEntidadNueva: public VistaEntidad, public InterfazRemoverAtributo{
private:
	friend class AsistenteEntidad;

	EntidadNueva * entidad;
	std::vector<VistaAtributo*> vistaAtributos;
	std::vector<VistaIdentificador*> vistaIdentificadores;
	void calcular_ancho_a_partir_del_nombre();
	void dibujarFiguraDeEntidad(Cairo::RefPtr<Cairo::Context> cr);
	void dibujarCirculosDeRedimension(Cairo::RefPtr<Cairo::Context> cr);
	bool prop_lanzada;
	bool ident_lanzada;

public:
	VistaEntidadNueva(EntidadNueva *);
	virtual ~VistaEntidadNueva();

	std::vector<VistaAtributo*>::iterator atributosBegin();
	std::vector<VistaAtributo*>::iterator atributosEnd();

	std::vector<VistaIdentificador*>::iterator identificadoresBegin();
	std::vector<VistaIdentificador*>::iterator identificadoresEnd();

	void resetearLanzarProp();

	void resetearLanzarIdent();

	// Solo se puede agregar y sacar atributos a la entidad nueva
	bool agregarAtributo(VistaAtributo* atrib);
	virtual bool quitarAtributo(VistaAtributo* atrib);

	bool agregarIdentificador(VistaIdentificador* ident);
	virtual bool quitarIdentificador(VistaIdentificador* ident);

	//Dibuja el objeto en el contexto cairo pasado como parametro.
	virtual void dibujar(Cairo::RefPtr<Cairo::Context> cr);

	//Lanza el asistente de prpiedades del objeto en cuestion.
	virtual bool lanzarProp();

	// Verifica si el punto cae dentro de este componente
	virtual bool contieneAEstePunto(double x, double y);

	virtual void calcularDimensionesAPartirDeTexto(Cairo::TextExtents * textExtents);

	// Verifica si el punto cae dentro de un punto para redimensionar el elemento
	virtual bool esPuntoDeRedimension(double x, double y);

	virtual void setMouseArriba(double x, double y);

	virtual void redimensionar(double x, double y);

	virtual void setNombre(const std::string & nombre);
	virtual  std::string getNombre() const;

	virtual bool contieneEsteComponente(VistaComponente *);

	void setEsDebil(bool);

	bool esDebil();

	virtual Entidad * getEntidad();
	EntidadNueva * getEntidadNueva();

	void eliminarComponentesAdyacentes(Diagrama * diagrama,std::vector<VistaComponente *> & componentes, VistaComponente * componenteEliminado);

	virtual bool hayQueEliminarlo();

	virtual bool identificador_en_popup();

	virtual void on_popup_boton_Identificadores();
};

#endif /* VISTAENTIDADNUEVA_H_ */
