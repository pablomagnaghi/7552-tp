#include "ImpresionDiagrama.h"

#include "componentes/Geometria.h"

#include <iostream>
using namespace std;

#define DEBUG_IMPRESION 0

Glib::RefPtr<ImpresionDiagrama> ImpresionDiagrama::create() {
	return Glib::RefPtr<ImpresionDiagrama>(new ImpresionDiagrama());
}

ImpresionDiagrama::ImpresionDiagrama() {
}

ImpresionDiagrama::~ImpresionDiagrama() {

}

void ImpresionDiagrama::set_diagrama(VistaDiagrama & diag) {
	this->diagrama = &diag;
}

void ImpresionDiagrama::on_begin_print(const Glib::RefPtr<Gtk::PrintContext>& print_context) {
	context_width = print_context->get_width();
	context_height = print_context->get_height();
#if DEBUG_IMPRESION==1
	std::cout << "Dimensiones Hoja = (" << context_width << ":";
	std::cout << context_height << ")" << std::endl;
#endif
	set_n_pages(1);
}

void ImpresionDiagrama::on_draw_page(const Glib::RefPtr<Gtk::PrintContext>& print_context,
		int page_nr) {

	double ancho_diagrama, alto_diagrama;
	double offset_x, offset_y;
	double traslacion_x = 0, traslacion_y = 0;
	double zoom = 1.4, rotacion = 0;

	diagrama->getDimensionesDelDiagrama(offset_x, offset_y, ancho_diagrama, alto_diagrama);

#if DEBUG_IMPRESION==1
	std::cout << "offset (" << offset_x << ":" << offset_y << ") dimensiones ( " << ancho_diagrama;
	std::cout << ":" << alto_diagrama << ")" << std::endl;
#endif

	if(ancho_diagrama == offset_x || alto_diagrama == offset_y){
		return;
	}

	Geometria::calcularAjusteDiagrama(offset_x, offset_y, ancho_diagrama, alto_diagrama, rotacion,
			zoom, traslacion_x, traslacion_y, this->context_width, this->context_height);

#if DEBUG_IMPRESION==1
	std::cout << "traslacion (" << traslacion_x << ":" << traslacion_y << ") zoom: " << zoom;
	std::cout << " rotacion: " << rotacion << std::endl;
#endif

	Cairo::RefPtr<Cairo::Context> cairo_ctx = print_context->get_cairo_context();

	/*cairo_ctx->set_source_rgb(0, 1, 0);
	 cairo_ctx->move_to(this->context_width / 2, this->context_height / 2);
	 cairo_ctx->arc(this->context_width / 2, this->context_height / 2, 3, 0, 2 * M_PI);
	 cairo_ctx->fill();
	 cairo_ctx->move_to(0, 0);
	 cairo_ctx->rectangle(0, 0, this->context_width, this->context_height);
	 cairo_ctx->stroke();*/

	cairo_ctx->translate(traslacion_x, traslacion_y);
	cairo_ctx->rotate_degrees(rotacion);
	cairo_ctx->scale(zoom, zoom);

	diagrama->dibujarComponentes(cairo_ctx, false);

	/*cairo_ctx->set_source_rgb(1, 0, 0);
	 cairo_ctx->move_to(offset_x, offset_y);
	 cairo_ctx->arc(offset_x, offset_y, 3 / zoom, 0, 2 * M_PI);
	 cairo_ctx->fill();
	 cairo_ctx->move_to(offset_x + ancho_diagrama / 2, offset_y + alto_diagrama / 2);
	 cairo_ctx->arc(offset_x + ancho_diagrama / 2, offset_y + alto_diagrama / 2, 3 / zoom, 0,
	 2 * M_PI);
	 cairo_ctx->fill();
	 cairo_ctx->move_to(offset_x, offset_y);
	 cairo_ctx->rectangle(offset_x, offset_y, ancho_diagrama, alto_diagrama);
	 cairo_ctx->stroke();*/

}

Gtk::Widget* ImpresionDiagrama::on_create_custom_widget() {
	set_custom_tab_label("My custom tab");

	Gtk::HBox* hbox = new Gtk::HBox(8);
	hbox->set_border_width(6);

	Gtk::Label* label = Gtk::manage(new Gtk::Label("Enter some text: "));
	hbox->pack_start(*label, false, false);
	label->show();

	hbox->pack_start(m_Entry, false, false);
	m_Entry.show();

	return hbox;
}
