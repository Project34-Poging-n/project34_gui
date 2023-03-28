#include <gtkmm.h>
#include <iostream>
#include <string>
#include "loginscreen.hpp"
#include "serial.hpp"


Loginscreen::Loginscreen()
    : Window("GUI bank")
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

    // Pack the widgets into the vertical box
    this->side_box1.pack_start(this->logo);
    this->side_box4.pack_start(this->l_label1);
    this->side_box4.pack_start(this->l_entry1);

    // Add the vertical box to the LoginScreen
    add(this->vbox);

    // Set LoginScreen properties
    set_position(Gtk::WIN_POS_CENTER);
    show_all_children();
}


Loginscreen::~Loginscreen()
{
    
}


void Loginscreen::run()
{
    SerialListener listener;
    std::string streamBuffer;

    listener.sopen("/dev/ttyACM0");
    while(this->getPageReady() != true) {
        streamBuffer = listener.sread();
        std::cout << streamBuffer << "\n";

        if (streamBuffer == "4") {
            std::cout << "[info]\t\tU bent ingelogd!\n";
            this->setPageReady(true);
            listener.sclose();
        }
    }
}


void Loginscreen::setPageReady(bool ready)
{
    this->_ready_for_next_page = ready;
}


bool Loginscreen::getPageReady()
{
    return this->_ready_for_next_page;
}