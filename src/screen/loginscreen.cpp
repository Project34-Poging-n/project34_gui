#include <gtkmm.h>
#include <iostream>
#include <string>
#include "loginscreen.hpp"
#include "serial.hpp"
#include "homescreen.hpp"


Loginscreen::Loginscreen()
{
    this->vbox.set_spacing(0);
    this->vbox.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    this->vbox.override_background_color(Gdk::RGBA("#B9DBF5")); // Red: #FF4C4F Blauw: #B9DBF5

    // Create the widgets
    this->l_label1.set_text("Ik ben een henker");
    this->l_label1.override_background_color(Gdk::RGBA("#FF4C4F"));

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

    Glib::RefPtr<Gdk::Pixbuf> pixbuf2 = Gdk::Pixbuf::create_from_file("../img/contactless.png");
    pixbuf2 = pixbuf2->scale_simple(500, 300, Gdk::INTERP_BILINEAR);
    this->contactless.set(pixbuf2);
    this->contactless.set_size_request(pixbuf2->get_width(), pixbuf2->get_height());
    this->contactless.override_color(Gdk::RGBA("#FFFFFF"));

    // Pack the widgets into the vertical box
    this->side_box1.pack_start(this->logo);
    // this->side_box4.pack_start(this->l_label1);
    this->side_box4.pack_start(this->contactless);

    // Add the vertical box to the LoginScreen

    // Set LoginScreen properties
}


Loginscreen::~Loginscreen()
{
    
}
