#include <gtkmm.h>
#include "saldoscreen.hpp"


Saldoscreen::Saldoscreen()
{    
    this->vbox.set_spacing(0);
    this->vbox.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    this->vbox.override_background_color(Gdk::RGBA("#B9DBF5"));

    // Set child elements
    this->l_label1.set_text("Uw Saldo: ");
    this->l_label1.override_color(Gdk::RGBA("#B9DBF5"));
    Pango::FontDescription font_desc1;
    font_desc1.set_size(40 * PANGO_SCALE);
    this->l_label1.override_font(font_desc1);

    this->l_label2.set_text("€ 500.00");
    this->l_label2.override_color(Gdk::RGBA("#B9DBF5"));
    Pango::FontDescription font_desc2;
    font_desc2.set_size(40 * PANGO_SCALE);
    this->l_label2.override_font(font_desc2);
    this->l_label2.set_alignment(0.5, 0.0);

    this->l_label3.set_text("Terug    (3)");
    this->l_label3.override_background_color(Gdk::RGBA("#B9DBF5"));
    this->l_label3.override_color(Gdk::RGBA("#FF4C4F"));\
    Pango::FontDescription font_desc3;
    font_desc3.set_size(18 * PANGO_SCALE);
    this->l_label3.override_font(font_desc3);
    this->l_label3.set_margin_top(240);
    this->l_label3.set_margin_bottom(30);
    this->l_label3.set_margin_start(570);
    this->l_label3.set_margin_end(0);
    this->l_label3.set_alignment(0.9, 0.5);

    // Add the sideboxes
    this->vbox.pack_start(this->side_box1);
    this->vbox.pack_start(this->side_box2);
    this->vbox.pack_start(this->side_box3);
    this->vbox.pack_start(this->side_box4);

    // Create a vertical box to hold the widgets
    this->side_box1.set_size_request(380, 720);
    this->side_box2.set_size_request(20, 720);
    this->side_box3.set_size_request(40, 720);
    this->side_box4.set_size_request(840, 720);

    this->side_box2.override_background_color(Gdk::RGBA("#FF4C4F"));

    this->side_box4.set_orientation(Gtk::ORIENTATION_VERTICAL);
    this->side_box4.override_background_color(Gdk::RGBA("#FF4C4F"));

    // Add the logo settings
    Glib::RefPtr<Gdk::Pixbuf> pixbuf = Gdk::Pixbuf::create_from_file("../img/logo.png");
    pixbuf = pixbuf->scale_simple(240, 300, Gdk::INTERP_BILINEAR);
    this->logo.set(pixbuf);
    this->logo.set_size_request(pixbuf->get_width(), pixbuf->get_height());

    this->side_box4.pack_start(this->l_label1);
    this->side_box4.pack_start(this->l_label2);
    this->side_box4.pack_start(this->l_label3);

    // Pack the widgets into the vertical box
    this->side_box1.pack_start(this->logo);

    // show_all_children();
}


Saldoscreen::~Saldoscreen()
{
    
}   