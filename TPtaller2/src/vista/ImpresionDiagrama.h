#ifndef IMPRESIONDIAGRAMA_H_
#define IMPRESIONDIAGRAMA_H_

#include <gtkmm/printoperation.h>
#include <gtkmm/printcontext.h>
#include <gtkmm.h>
#include "VistaDiagrama.h"

class ImpresionDiagrama: public Gtk::PrintOperation {
public:
	static Glib::RefPtr<ImpresionDiagrama> create();
	virtual ~ImpresionDiagrama();

	void set_diagrama(VistaDiagrama & diag);

protected:
	ImpresionDiagrama();

	virtual void on_begin_print(const Glib::RefPtr<Gtk::PrintContext>& context);
	virtual void on_draw_page(const Glib::RefPtr<Gtk::PrintContext>& print_context, int page_nr);
	virtual Gtk::Widget* on_create_custom_widget();
private:
	VistaDiagrama * diagrama;
	int context_width, context_height;
	Gtk::Entry m_Entry;

};

#endif /* IMPRESIONDIAGRAMA_H_ */
