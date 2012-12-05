#include "ImpresionDiagrama.h"

#include <iostream>
using namespace std;

Glib::RefPtr<ImpresionDiagrama> ImpresionDiagrama::create() {
	return Glib::RefPtr<ImpresionDiagrama>(new ImpresionDiagrama());
}

ImpresionDiagrama::ImpresionDiagrama() {
}

ImpresionDiagrama::~ImpresionDiagrama() {

}

void ImpresionDiagrama::set_diagrama(VistaDiagrama & diag){
	this->diagrama = &diag;
}

void ImpresionDiagrama::on_begin_print(const Glib::RefPtr<Gtk::PrintContext>& print_context) {
	ancho = print_context->get_width();
	alto = print_context->get_height();
}

void ImpresionDiagrama::on_draw_page(const Glib::RefPtr<Gtk::PrintContext>& print_context, int page_nr) {
	std::cout << "on_draw_page" << endl;
	Cairo::RefPtr<Cairo::Context> cairo_ctx = print_context->get_cairo_context();

	int zoom;
	int rotacion;


	diagrama->dibujarComponentes(cairo_ctx);
	std::cout << "on_draw_page" << endl;
}
