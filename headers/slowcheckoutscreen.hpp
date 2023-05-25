#pragma once


#include <gtkmm.h>


#ifndef __PROJECT34__SLOW__CHECKOUTSCREEN__
#define __PROJECT34__SLOW__CHECKOUTSCREEN__


class SlowCheckoutscreen
{  
    private:
        void update_textbox(std::string data);
        sigc::signal<void, std::string> signal;
        int _size;

    protected:
        Gtk::Box side_box1;
        Gtk::Box side_box2;
        Gtk::Box side_box3;
        Gtk::Box side_box4;
        Gtk::Label l_label1;
        Gtk::Image logo;
        Gtk::Label title;
        Gtk::Entry textbox;
        Gtk::Label back;

    public:
        Gtk::Box vbox;

        SlowCheckoutscreen();
        virtual ~SlowCheckoutscreen();
        void setSignal(sigc::signal<void, std::string> &signal);
        sigc::signal<void, std::string> getSignal();
        std::string trim(const std::string& str);
};

#endif