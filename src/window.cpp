#include "window.hpp"
#include <string>
#include <gtkmm.h>
#include <iostream>


#define WINDOW_WIDTH            1280
#define WINDOW_HEIGHT           720
#define DEFAULT_PATH_FOR_CSS    "../css/style.css"
#define PAGINATION_SIZE         5


static struct s_pageCell paginationTable[] = {
    { 0, "", { -1, -1, -1, -1, -1} },
    { 1, "ABC", { 2, 3, -1, -1, -1 } },
    { 2, "9", { 1, -1, -1, -1, -1 } },
    { 3, "ABCD9", { 4, 4, 4, 4, 1 } },
    { 4, "A9", { 5, 3, -1, -1, -1 } },
    { 5, "", { 1, -1, -1, -1, -1, } }
};


/**
 * Constructor 
 * 
 * @param title
 * @param signal
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

    this->scs.setSignal(signal);

    // Add all pages to the nodebook
    this->notebook.append_page(this->ls.vbox, "Loginscreen");
    this->notebook.append_page(this->hs.vbox, "Homescreen");
    this->notebook.append_page(this->ss.vbox, "Saldoscreen");
    this->notebook.append_page(this->cs.vbox, "Checkoutscreen");
    this->notebook.append_page(this->scs.vbox, "FastCheckout");
    this->notebook.append_page(this->sss.vbox, "Successscreen");

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

    if (this->getCurrentPageNumber() == 0) {
        this->setCurrentPageNumber(1);
    }

    for (int i = 0; i < PAGINATION_SIZE; i++) {
        if (paginationTable[i].page == this->getCurrentPageNumber()) {
            size_t commandSize = paginationTable[i].commands.length();
            std::cout << "[info]\tPagination command size: " << commandSize << " with page number: " << this->getCurrentPageNumber() << "\n";

            for (int j = 0; j < commandSize; j++) {
                if (data.find(paginationTable[i].commands[j]) != std::string::npos) {
                    if (paginationTable[i].newpage[j] == 5) {
                        if (this->scs.check_pincode()) {
                            this->sss.writeToDispenser("20");
                        }
                    } else {
                        this->setCurrentPageNumber(paginationTable[i].newpage[j]);
                        this->scs._get_current_number = paginationTable[i].newpage[j];
                    }
                }
            }
        }
    }
}


/**
 * Function to set if the page is ready
 * 
 * @param ready
*/
void Window::setPageReady(bool ready)
{
    this->_ready_for_next_page = ready;
}


/**
 * Function
 * 
*/
bool Window::getPageReady()
{
    return this->_ready_for_next_page;
}


void Window::setCurrentPageNumber(int number)
{
    this->_currentPageNumber = number;
    this->notebook.set_current_page(number);
}


int Window::getCurrentPageNumber()
{
    return this->_currentPageNumber;
}