#include <gtkmm.h>
#include "homescreen.hpp"


Homescreen::Homescreen()
    : Window("GUI bank")
{    
    this->vbox.set_spacing(10);
    this->vbox.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    this->vbox.override_background_color(Gdk::RGBA("#B9DBF5"));

    // Set child elements
    this->b_saldo.set_text("Saldo bekijken    (1)");
    this->b_saldo.override_background_color(Gdk::RGBA("#B9DBF5"));
    this->b_saldo.override_color(Gdk::RGBA("#FF4C4F"));\
    Pango::FontDescription font_desc1;
    font_desc1.set_size(30 * PANGO_SCALE);
    this->b_saldo.override_font(font_desc1);
    this->b_saldo.set_margin_top(30);
    this->b_saldo.set_margin_bottom(30);
    this->b_saldo.set_margin_start(270);
    this->b_saldo.set_margin_end(30);
    this->b_saldo.set_alignment(0.9, 0.5);
    

    this->b_get.set_text("Saldo opnemen     (2)");
    this->b_get.override_background_color(Gdk::RGBA("#B9DBF5"));
    this->b_get.override_color(Gdk::RGBA("#FF4C4F"));
    this->b_get.override_font(font_desc1);
    this->b_get.set_margin_top(30);
    this->b_get.set_margin_bottom(30);
    this->b_get.set_margin_start(270);
    this->b_get.set_margin_end(30);
    this->b_get.set_alignment(0.9, 0.5);
    
    this->b_put.set_text("Saldo storten     (3)");
    this->b_put.override_background_color(Gdk::RGBA("#B9DBF5"));
    this->b_put.override_color(Gdk::RGBA("#FF4C4F"));
    this->b_put.override_font(font_desc1);
    this->b_put.set_margin_top(30);
    this->b_put.set_margin_bottom(30);
    this->b_put.set_margin_start(270);
    this->b_put.set_margin_end(30);
    this->b_put.set_alignment(0.9, 0.5);

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

    // Pack the widgets into the vertical box
    this->side_box1.pack_start(this->logo);

    this->side_box4.pack_start(this->b_saldo);
    this->side_box4.pack_start(this->b_get);
    this->side_box4.pack_start(this->b_put);

    // show_all_children();
}


Homescreen::~Homescreen()
{
    
}           


// Gtk::Box* Homescreen::getVBox()
// {
//     return this->vbox;
// }