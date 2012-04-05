/*
 * Componente.h
 *
 *  Created on: 02/04/2012
 *      Author: Guagnini Enzo 88325
 */

#ifndef COMPONENTE_H_
#define COMPONENTE_H_
#include <gtkmm.h>
#include <cairomm/cairomm.h>
#include <string>
using namespace std;

class Componente {
protected:
	double pos_ini_x;
	double pos_ini_y;
	double pos_fin_x;
	double pos_fin_y;
	double pos_selec_x;
	double pos_selec_y;
	bool dibujable;
	Gtk::Menu* m_pMenuPopup;
	string nombre;
public:
	Componente();
	virtual ~Componente();

	void getposini(double &x, double&y) const;
	void setposini(double x, double y);
	void getposfin(double&x, double&y) const;
	virtual void setposfin(double x, double y);
	void setDibujable(bool d);
	bool getDibujable();
	string getNombre()const;

	/*
	 * Dibuja el objeto en el contexto cairo pasado como parametro.
	 */
	virtual void dibujar(Cairo::RefPtr<Cairo::Context> cr) = 0;

	/*
	 * Indica q sucede cuando el objeto es seleccionado
	 */
	virtual bool esSeleccionado(double x, double y) = 0;

	/*
	 * indica q sucede con el objeto cuando deja de ser seleccionado
	 */
	virtual void finSeleccionado(double x, double y) = 0;

	/*
	 * Lanza el asistente de prpiedades del objeto en cuestion.
	 */
	virtual void lanzarProp(GdkEventButton* event) = 0;

};

#endif /* COMPONENTE_H_ */
