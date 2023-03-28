#include <gtkmm.h>
#include "homescreen.hpp"


Homescreen::Homescreen()
    : Window("GUI bank")
{
    add(this->frame);

    
    this->frame.set_label("Homescreen");
    this->frame.set_label_align(Gtk::ALIGN_END, Gtk::ALIGN_START);

    // Set child elements
    

    show_all_children();
}


Homescreen::~Homescreen()
{
    
}