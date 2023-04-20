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
Window::Window(std::string title, sigc::signal<void, std::string> &signal)  
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

    // Connect
    signal.connect(sigc::mem_fun(this, &Window::checkLogin));

    // Add all pages to the nodebook
    this->notebook.append_page(this->ls.vbox, "Loginscreen");
    this->notebook.append_page(this->hs.vbox, "Homescreen");
    this->notebook.append_page(this->ss.vbox, "Saldoscreen");
    this->notebook.append_page(this->cs.vbox, "Checkoutscreen");
    this->notebook.append_page(this->scs.vbox, "FastCheckout");

    add(this->notebook);

    set_position(Gtk::WIN_POS_CENTER);
    show_all_children();
}


/**
 * Destructor 
 */
Window::~Window()
{

}


/**
 * @brief Function to check the page navigation
 * 
 * @brief data
 */
void Window::checkLogin(std::string data)
{
    std::cout << "Dit is: " << data << "\n";
    // this->notebook.set_current_page(2);

    if (this->getCurrentPageNumber() == 1) {
        if (data.find("1") != std::string::npos) {

        } else if (data.find("2") != std::string::npos) {

        } else if (data.find("3") != std::string::npos) {
            
        }
    } else if (this->getCurrentPageNumber() == 2) {
    
    } else if (this->getCurrentPageNumber() == 3) {

    } else if (this->getCurrentPageNumber() == 4) {

    }
}


void Window::setPageReady(bool ready)
{
    this->_ready_for_next_page = ready;
}


bool Window::getPageReady()
{
    return this->_ready_for_next_page;
}


void Window::setCurrentPageNumber(int number)
{
    this->_currentPageNumber = number;
}


int Window::getCurrentPageNumber()
{
    return this->_currentPageNumber;
}