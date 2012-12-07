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

void ImpresionDiagrama::set_diagrama(VistaDiagrama & diag) {
	this->diagrama = &diag;
}

void ImpresionDiagrama::on_begin_print(const Glib::RefPtr<Gtk::PrintContext>& print_context) {
	context_width = print_context->get_width();
	context_height = print_context->get_height();
#ifdef DEBUG
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

	calcular_ajuste_del_diagrama(offset_x, offset_y, ancho_diagrama, alto_diagrama, rotacion, zoom,
			traslacion_x, traslacion_y);

	std::cout << "on_draw_page" << endl;
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

	std::cout << "on_draw_page" << endl;
}

void ImpresionDiagrama::calcular_ajuste_del_diagrama(double offset_x, double offset_y,
		double ancho_diagrama, double alto_diagrama, double & rotacion, double & zoom,
		double & traslacion_x, double & traslacion_y) {
	double aux;

	if (this->context_width > this->context_height) {
		if (ancho_diagrama > alto_diagrama) {
			rotacion = 0;
		} else {
			rotacion = 90;
		}
	} else {
		if (ancho_diagrama > alto_diagrama) {
			rotacion = 90;
		} else {
			rotacion = 0;
		}
	}

	if (rotacion == 0) {
		zoom = (this->context_width) / ancho_diagrama;
		aux = (this->context_height) / alto_diagrama;

	} else {
		zoom = (this->context_height) / ancho_diagrama;
		aux = (this->context_width) / alto_diagrama;
	}

#ifdef DEBUG
	std::cout << "ZoomH=" << zoom;
	std::cout << " ZoomV= " << aux << std::endl;
#endif

	if (aux < zoom) {
		zoom = aux;
	}

	zoom *= 0.95;

	if (rotacion == 0) {
		traslacion_x = this->context_width / 2 + ((-ancho_diagrama) / 2 - offset_x) * zoom;
		traslacion_y = this->context_height / 2 + ((-alto_diagrama) / 2 - offset_y) * zoom;
	} else {
		traslacion_x = this->context_width / 2 + ((alto_diagrama) / 2 + offset_y) * zoom;
		traslacion_y = this->context_height / 2 + ((-ancho_diagrama) / 2 - offset_x) * zoom;
	}
#ifdef DEBUG
	std::cout << "Rotacion=" << rotacion;
	std::cout << " Zoom= " << zoom;
	std::cout << " Traslacion= (" << traslacion_x << ":" << traslacion_y << ")" << std::endl;
#endif
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
