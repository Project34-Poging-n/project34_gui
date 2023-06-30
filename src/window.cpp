#include "window.hpp"
#include <string>
#include <gtkmm.h>
#include <iostream>
#include <chrono>
#include "api.hpp"
#include "usermodel.hpp"


#define WINDOW_WIDTH            1280
#define WINDOW_HEIGHT           720
#define DEFAULT_PATH_FOR_CSS    "../css/style.css"
#define PAGINATION_SIZE         5
#define PAGINATION_STACK_SIZE   30
#define FAST_MONEY              75


static struct s_pageCell paginationTable[] = {
    { 0, "*", { 4, -1, -1, -1, -1} },
    { 1, "ABC", { 2, 3, 0, -1, -1 } },
    { 2, "#", { 1, -1, -1, -1, -1 } },
    { 3, "AB#", { 4, 6, 1, -1, 1 } },
    { 4, "*#", { 8, 3, -1, -1, -1 } },
    { 5, "", { 1, -1, -1, -1, -1, } },
    { 6, "*#", { 7, 3, -1, -1, -1 } },
    { 7, "ABC#", { 4, 4, 4, 6, -1} },
    { 8, "AB", { 5, 5, -1, -1, -1 } }
};


static int pp = 0;
static int paginationStack[PAGINATION_STACK_SIZE];


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
    // Glib::ustring cssPath = "../css/style.css";
    // auto css = Gtk::CssProvider::create();
    // css->load_from_file(cssPath);
    // get_style_context()->add_provider_for_screen(Gdk::Screen::get_default(), css, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    // set_show_tabs(true);

    // Connect
    signal.connect(sigc::mem_fun(this, &Window::checkLogin));

    this->scs.setSignal(signal);
    this->sss.setSignal(signal);
    this->ss.setSignal(signal);

    // Add all pages to the nodebook
    this->notebook.append_page(this->ls.vbox, "Loginscreen");
    this->notebook.append_page(this->hs.vbox, "Homescreen");
    this->notebook.append_page(this->ss.vbox, "Saldoscreen");
    this->notebook.append_page(this->cs.vbox, "Checkoutscreen");
    this->notebook.append_page(this->scs.vbox, "FastCheckout");
    this->notebook.append_page(this->sss.vbox, "Successscreen");
    this->notebook.append_page(this->fcs.vbox, "Fastjemoeder");
    this->notebook.append_page(this->bjs.vbox, "Biljetscreen");
    this->notebook.set_show_tabs(false);

    add(this->notebook);

    this->setCurrentPageNumber(0);
    paginationStack[pp] = 0;
    pp++;

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
    for (int i = 0; i < PAGINATION_SIZE; i++) {
        if (paginationTable[i].page == this->getCurrentPageNumber()) {
            size_t commandSize = paginationTable[i].commands.length();
            for (int j = 0; j < commandSize; j++) {
                if (this->getCurrentPageNumber() == 0 && data.length() >= 14) {
                    data = this->scs.trim(data);
                    paginationStack[++pp] = 4;
                    set_iban(data);
                    std::cout << "[info]\tlength: " << data.length() << "\n";
                } else if (data.find(paginationTable[i].commands[j]) != std::string::npos) {
                    // if (paginationTable[i].commands[j] == '#') {
                    //     pp--;
                    //     break;
                    // }
                    
                    if (paginationStack[pp] == 4) {
                        std::cout << "[info]\tPrevious: " << paginationStack[pp-1];

                        if (paginationStack[pp-1] == 0 && this->scs.check_pincode() && paginationTable[i].commands[j] == '*') {
                            paginationStack[++pp] = 1;
                        } else if (this->scs.check_pincode() && (paginationStack[pp-1] == 3) && paginationTable[i].commands[j] == '*') {
                            Json::Value root;
                            root["account"]     = get_iban();
                            root["pincode"]     = get_password();
                            root["balance"]     = FAST_MONEY;

                            std::string bp = "dd-mm-yyyy_13:00:00_" + std::to_string(FAST_MONEY) + "_" + get_iban() + "_" + "print";
                            this->sss.writeToDispenser(bp.c_str());

                            std::cout << bp.c_str() << "\n";

                            send_data("http://145.24.222.207:5000/withdraw", root);
                            // send_data("http://127.0.0.1:3000/henk/"+get_iban(), root);
                            paginationStack[++pp] = 5;
                        } else if (this->scs.check_pincode() && (paginationStack[pp-1] == 7) && paginationTable[i].commands[j] == '*') {
                            
                        }

                        if ((paginationStack[pp-1] == 6) && paginationTable[i].commands[i] == '*') {

                        }

                        if ((paginationStack[pp-1] == 6) && paginationTable[i].commands[i] == 'A') {
                            this->_money = 50;
                        } else if ((paginationStack[pp-1] == 6) && paginationTable[i].commands[i] == 'B') {
                            this->_money = 20;
                        } else if ((paginationStack[pp-1] == 6) && paginationTable[i].commands[i] == 'C') {
                            this->_money = 5;
                        }


                    } else if (paginationStack[pp] == 1 && paginationTable[i].commands[j] == 'c') { 
                        reset_stack_to_position(0);
                        set_username("");
                        // set_iban("");
                        set_password("");
                    }else {
                        paginationStack[++pp] = paginationTable[i].newpage[j];
                    }
                }
            }
        }
    }

    this->setCurrentPageNumber(paginationStack[pp]);
    this->scs._get_current_number = paginationStack[pp];
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


/**
 * Function to add a pagination to the pagination stack
 * 
 * @param page
*/
void add_to_pagination_stack(int page)
{
    paginationStack[++pp] = page;
}


/**
 * 
 * 
*/
int get_current_stack_position()
{
    return paginationStack[pp];
}


/**
 * 
 * 
*/
void reset_stack_to_position(int p)
{
    pp = p;
}


/**
 * 
 * 
*/
void Window::setCurrentPageNumber(int number)
{
    this->_currentPageNumber = number;
    this->notebook.set_current_page(number);
}


/**
 * 
 * 
*/
int Window::getCurrentPageNumber()
{
    return this->_currentPageNumber;
}