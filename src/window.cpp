#include "window.hpp"
#include <string>
#include <gtkmm.h>
#include <iostream>


#define WINDOW_WIDTH    1280
#define WINDOW_HEIGHT   720
#define DEFAULT_PATH_FOR_CSS "../css/style.css"


/**
 * Constructor 
 */
Window::Window(std::string title)  
{
    set_title(title);
    set_default_size(WINDOW_WIDTH, WINDOW_HEIGHT);
    set_position(Gtk::WIN_POS_CENTER);
    
    // Default container properties
    set_border_width(10);

    // Configure css file
    Glib::ustring cssPath = "../css/style.css";
    // auto css = Gtk::CssProvider::create();
    // css->load_from_file(cssPath);
    // get_style_context()->add_provider_for_screen(Gdk::Screen::get_default(), css, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    // set_show_tabs(true);
}


/**
 * Destructor 
 */
Window::~Window()
{

}