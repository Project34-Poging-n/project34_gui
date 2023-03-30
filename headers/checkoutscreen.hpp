#pragma once


#include <gtkmm.h>
#include <memory>
#include "window.hpp"


#ifndef __PROJECT34__CHECKOUTSCREEN__
#define __PROJECT34__CHECKOUTSCREEN__



class Checkoutscreen : public Window
{  
    protected:

        Gtk::Box side_box1;
        Gtk::Box side_box2;
        Gtk::Box side_box3;
        Gtk::Box side_box4;
        Gtk::Label l_label1;
        Gtk::Image logo;

    public:
        Gtk::Box vbox;

        Checkoutscreen();
        virtual ~Checkoutscreen();

       //  Gtk::Box *getVBox();
};

#endif