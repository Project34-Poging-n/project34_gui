#pragma once


#include <gtkmm.h>
#include <memory>
#include "window.hpp"


#ifndef __PROJECT34__LOGINSCREEN__
#define __PROJECT34__LOGINSCREEN__


class Loginscreen : public Window
{  
    protected:
        Gtk::Box side_box1;
        Gtk::Box side_box2;
        Gtk::Box side_box3;
        Gtk::Box side_box4;
        Gtk::Label l_label1;
        Gtk::Entry l_entry1;
        Gtk::Image logo;
        
    public:
        Loginscreen();
        virtual ~Loginscreen();

        void setPageReady(bool ready);
        bool getPageReady();
        void run();
        
    private:
        bool _ready_for_next_page;
        
};

#endif