#include <gtkmm.h>
#include "biljetscreen.hpp"


#define BAR_MARGIN 10


Biljetscreen::Biljetscreen()
{    
    this->vbox.set_spacing(0);
    this->vbox.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    this->vbox.override_background_color(Gdk::RGBA("#B9DBF5"));

    // Set child elements
    // Add the sideboxes
    this->vbox.pack_start(this->side_box1);
    this->vbox.pack_start(this->side_box2);
    this->vbox.pack_start(this->side_box3); 
    this->vbox.pack_start(this->side_box4);

    // Set child elements
    this->fastp.set_text("€ 50     (A)");
    this->fastp.override_background_color(Gdk::RGBA("#B9DBF5"));
    this->fastp.override_color(Gdk::RGBA("#FF4C4F"));\
    Pango::FontDescription font_desc1;
    font_desc1.set_size(30 * PANGO_SCALE);
    this->fastp.override_font(font_desc1);
    this->fastp.set_margin_top(BAR_MARGIN);
    this->fastp.set_margin_bottom(BAR_MARGIN);
    this->fastp.set_margin_start(270);
    this->fastp.set_margin_end(30);
    this->fastp.set_alignment(0.9, 0.5);

    this->slowp.set_text("€ 20     (B)");
    this->slowp.override_background_color(Gdk::RGBA("#B9DBF5"));
    this->slowp.override_color(Gdk::RGBA("#FF4C4F"));\
    font_desc1.set_size(30 * PANGO_SCALE);
    this->slowp.override_font(font_desc1);
    this->slowp.set_margin_top(BAR_MARGIN);
    this->slowp.set_margin_bottom(BAR_MARGIN);
    this->slowp.set_margin_start(270);
    this->slowp.set_margin_end(30);
    this->slowp.set_alignment(0.9, 0.5);

    this->slowpp.set_text("€ 5      (C)");
    this->slowpp.override_background_color(Gdk::RGBA("#B9DBF5"));
    this->slowpp.override_color(Gdk::RGBA("#FF4C4F"));\
    font_desc1.set_size(30 * PANGO_SCALE);
    this->slowpp.override_font(font_desc1);
    this->slowpp.set_margin_top(BAR_MARGIN);
    this->slowpp.set_margin_bottom(BAR_MARGIN);
    this->slowpp.set_margin_start(270);
    this->slowpp.set_margin_end(30);
    this->slowpp.set_alignment(0.9, 0.5);

    this->back.set_text("Terug    (#)");
    this->back.override_background_color(Gdk::RGBA("#B9DBF5"));
    this->back.override_color(Gdk::RGBA("#FF4C4F"));\
    Pango::FontDescription font_desc3;
    font_desc3.set_size(18 * PANGO_SCALE);
    this->back.override_font(font_desc3);
    this->back.set_margin_top(50);
    this->back.set_margin_bottom(30);
    this->back.set_margin_start(570);
    this->back.set_margin_end(0);
    this->back.set_alignment(0.9, 0.5);


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
    this->side_box4.pack_start(this->fastp);
    this->side_box4.pack_start(this->fastp2);
    this->side_box4.pack_start(this->fastp3);
    this->side_box4.pack_start(this->slowp);
     this->side_box4.pack_start(this->slowpp);
    this->side_box4.pack_start(this->back);

    // show_all_children();
}


Biljetscreen::~Biljetscreen()
{
    
}   


unsigned int Biljetscreen::getBiljet50()
{
    return this->_biljet50;
}


unsigned int Biljetscreen::getBiljet20()
{
    return this->_biljet20;
}


unsigned int Biljetscreen::getBiljet5()
{
    return this->_biljet5;
}