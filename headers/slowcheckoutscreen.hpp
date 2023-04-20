#pragma once


#include <gtkmm.h>


#ifndef __PROJECT34__SLOW__CHECKOUTSCREEN__
#define __PROJECT34__SLOW__CHECKOUTSCREEN__


class SlowCheckoutscreen
{  
    protected:
        Gtk::Box side_box1;
        Gtk::Box side_box2;
        Gtk::Box side_box3;
        Gtk::Box side_box4;
        Gtk::Label l_label1;
        Gtk::Image logo;
        Gtk::Label title;
        Gtk::Entry textbox;

    public:
        Gtk::Box vbox;

        SlowCheckoutscreen();
        virtual ~SlowCheckoutscreen();
};

#endif