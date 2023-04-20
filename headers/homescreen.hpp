#pragma once


#include <gtkmm.h>
#include <memory>


#ifndef __PROJECT34__HOMESCREEN__
#define __PROJECT34__HOMESCREEN__



class Homescreen
{  
    protected:
        Gtk::Box side_box1;
        Gtk::Box side_box2;
        Gtk::Box side_box3;
        Gtk::Box side_box4;
        Gtk::Label l_label1;
        Gtk::Image logo;

        Gtk::Label b_saldo;
        Gtk::Label b_get;
        Gtk::Label b_put;
        Gtk::Label back;

    public:
        Gtk::Box vbox;

        Homescreen();
        virtual ~Homescreen();
       //  Gtk::Box *getVBox();
       int getPageNumber();
};

#endif