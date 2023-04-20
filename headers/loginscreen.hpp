#pragma once


#include <gtkmm.h>
#include <memory>


#ifndef __PROJECT34__LOGINSCREEN__
#define __PROJECT34__LOGINSCREEN__


class Loginscreen
{  
    protected:
        Gtk::Box side_box1;
        Gtk::Box side_box2;
        Gtk::Box side_box3;
        Gtk::Box side_box4;
        Gtk::Label l_label1;
        Gtk::Entry l_entry1;
        Gtk::Image logo;
        Gtk::Image contactless;
        
    public:
        Gtk::Box vbox;

        Loginscreen();
        virtual ~Loginscreen();
        
    private:

};

#endif