#pragma once


#include <gtkmm.h>
#include <memory>
#include "window.hpp"


#ifndef __PROJECT34__SALDOSCREEN__
#define __PROJECT34__SALDOSCREEN__



class Saldoscreen : public Window
{  
    protected:

        Gtk::Box side_box1;
        Gtk::Box side_box2;
        Gtk::Box side_box3;
        Gtk::Box side_box4;
        Gtk::Label l_label1;
        Gtk::Label l_label2;
        Gtk::Label l_label3;
        Gtk::Image logo;

    public:
        Gtk::Box vbox;

        Saldoscreen();
        virtual ~Saldoscreen();

       //  Gtk::Box *getVBox();
};

#endif