#include <gtkmm.h>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include "successscreen.hpp"
#include "serial.hpp"
#include "homescreen.hpp"
#include "window.hpp"


#define OUTPUT_SERIAL_PORT  "/dev/ttyACM1"


SerialListener olistener;


Successscreen::Successscreen()
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
    // this->side_box4.pack_start(this->l_label1);

    // Add the vertical box to the LoginScreen

    // Set LoginScreen properties

    // Print the money

}


Successscreen::~Successscreen()
{
    
}


void Successscreen::writeToDispenser(const char *amount)
{
    std::cout << "[info]\tMoneyDispenser called\n";
    olistener.sopen(OUTPUT_SERIAL_PORT);
    olistener.swrite(amount);
    olistener.sclose();
}


void Successscreen::trigger_timer(std::string data)
{
    if (get_current_stack_position() == 5) {
        std::chrono::milliseconds delay(3000);
        std::this_thread::sleep_for(delay);

        reset_stack_to_position(2);
        this->getSignal().emit("");
    }
}


/**
 * Function to enable the signal
 * 
 * @param signal 
 */
void Successscreen::setSignal(sigc::signal<void, std::string> &signal)
{
    this->signal = signal;
    this->signal.connect(sigc::mem_fun(this, &Successscreen::trigger_timer));
}


/**
 * Functio to get the signal for sending data over the threads
 * 
 * @return sigc::signal<void, std::string>
 */
sigc::signal<void, std::string> Successscreen::getSignal()
{
    return this->signal;
}