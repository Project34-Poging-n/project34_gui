#pragma once


#include <gtkmm.h>
#include <memory>


#ifndef __PROJECT34__CHECKOUTSCREEN__
#define __PROJECT34__CHECKOUTSCREEN__


class Checkoutscreen
{  
    protected:
        Gtk::Box side_box1;
        Gtk::Box side_box2;
        Gtk::Box side_box3;
        Gtk::Box side_box4;
        Gtk::Label l_label1;
        Gtk::Image logo;
        Gtk::Label fastp;
        Gtk::Label slowp;
        Gtk::Label back;
        Gtk::Label fastp2;
        Gtk::Label fastp3;

    public:
        Gtk::Box vbox;

        Checkoutscreen();
        virtual ~Checkoutscreen();

       //  Gtk::Box *getVBox();
       int getPageNumber();
};

#endif