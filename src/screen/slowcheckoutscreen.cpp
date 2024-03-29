#include <gtkmm.h>
#include "slowcheckoutscreen.hpp"
#include <iostream>
#include <locale>
#include <regex>
#include <chrono>
#include <thread>
#include <json/json.h>
#include "api.hpp"
#include "usermodel.hpp"


#define MAX_TEXT_INPUT_SIZE     4


static std::string od = "";
static std::string dot = "";
static unsigned int pc = 0;


/**
 * Constructor
 */
SlowCheckoutscreen::SlowCheckoutscreen()
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

    // Set child elements
    this->title.set_text("Voer uw pincode in: ");
    this->title.override_color(Gdk::RGBA("#B9DBF5"));
    Pango::FontDescription font_desc1;
    font_desc1.set_size(40 * PANGO_SCALE);
    this->title.override_font(font_desc1);

    this->textbox.set_max_length(MAX_TEXT_INPUT_SIZE);
    this->textbox.set_text("");
    this->textbox.set_margin_start(150);
    this->textbox.set_margin_end(150);
    Pango::FontDescription font_desc2;
    font_desc2.set_size(40 * PANGO_SCALE);
    this->textbox.override_font(font_desc1);

    this->m_label.set_text("");
    this->m_label.override_color(Gdk::RGBA("#FF0000"));
    font_desc1.set_size(10 * PANGO_SCALE);
    this->m_label.override_font(font_desc1);

    this->back.set_text("Terug    (#)");
    this->back.override_background_color(Gdk::RGBA("#B9DBF5"));
    this->back.override_color(Gdk::RGBA("#FF4C4F"));\
    Pango::FontDescription font_desc3;
    font_desc3.set_size(18 * PANGO_SCALE);
    this->back.override_font(font_desc3);
    this->back.set_margin_top(200);
    this->back.set_margin_bottom(30);
    this->back.set_margin_start(570);
    this->back.set_margin_end(0);
    this->back.set_alignment(0.9, 0.5);

    // Pack the widgets into the vertical box
    this->side_box1.pack_start(this->logo);
    this->side_box4.pack_start(this->title);
    this->side_box4.pack_start(this->textbox);
    this->side_box4.pack_start(this->m_label);
    this->side_box4.pack_start(this->back);

    // show_all_children();
}


/**
 * Destructor
 */
SlowCheckoutscreen::~SlowCheckoutscreen()
{
    
}   


/**
 * Function to trim the string
 * 
 * @param str
 * @return string
*/
std::string SlowCheckoutscreen::trim(const std::string& str)
{
    std::regex pattern("[^a-zA-Z0-9]");
    return std::regex_replace(str, pattern, "");
}


/**
 * Function to add the pincode to the box
 * 
 * @param data
*/
void SlowCheckoutscreen::update_textbox(std::string data)
{
    std::regex pattern("^[0-9]+$");
    data = this->trim(data);

    std::cout << "[info]\tIban: " << get_iban() << "\n";
    
    if (this->_get_current_number == 4) {
        if (this->_size < MAX_TEXT_INPUT_SIZE && data.size()>0 && od.size() < MAX_TEXT_INPUT_SIZE) {
            if (std::regex_match(data, pattern)) {
                od.append(data);
                dot.append("*");
            }
            this->textbox.set_text(dot);
        }
    } else {
        od = "";
        dot = "";
        this->textbox.set_text("");
    }

    std::cout << "[info]\tPincode: " << od << "\n";
}


/**
 * Function to check if the pincode is correct!
 * 
 * @return bool
*/
bool SlowCheckoutscreen::check_pincode()
{   
    Json::Value root;

    root["account"] = get_iban();
    root["pincode"] = od; 

    if (pc >= 3) {
        std::string url = "http://127.0.0.1:5000/block";
        send_data(url, root);
        std::cout << "[info]\tPassword blocked!\n";
        this->m_label.set_text("Password blocked!");
        pc = 0;
        return false;
    }

    if (od.size() > 0) {
        // std::string url = "http://145.24.222.207:5000/login";
        std::string url = "http://127.0.0.1:5000/login";
        Json::Value result = send_data(url, root);

        if (result["status"].asBool() == true && result["pincode"] == od) {
            std::cout << "[info]\tCorrect pincode!";
            set_password(result["pincode"].asCString());
            pc = 0;
            return true;
        } 

        pc++;
        this->m_label.set_text("Wrong pincode: " + std::to_string(3-pc) + " attempts left");
        std::cout << "[info]\tWrong pincode!\n";
        std::cout << "[info]\tTotal attemps left: " << 3-pc << "\n";
        dot = "";
        od = "";
        this->textbox.set_text(dot);

        return false;
    }

    return false;
}


/**
 * Function to enable the signal
 * 
 * @param signal 
 */
void SlowCheckoutscreen::setSignal(sigc::signal<void, std::string> &signal)
{
    this->signal = signal;
    this->signal.connect(sigc::mem_fun(this, &SlowCheckoutscreen::update_textbox));
}


/**
 * Functio to get the signal for sending data over the threads
 * 
 * @return sigc::signal<void, std::string>
 */
sigc::signal<void, std::string> SlowCheckoutscreen::getSignal()
{
    return this->signal;
}