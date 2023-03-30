#pragma once


#include <gtkmm.h>
#include <memory>
#include "window.hpp"
#include "homescreen.hpp"
#include "checkoutscreen.hpp"
#include "saldoscreen.hpp"


#ifndef __PROJECT34__LOGINSCREEN__
#define __PROJECT34__LOGINSCREEN__


class Loginscreen : public Window
{  
    protected:
        Gtk::Notebook notebook;
        Gtk::Box side_box1;
        Gtk::Box side_box2;
        Gtk::Box side_box3;
        Gtk::Box side_box4;
        Gtk::Label l_label1;
        Gtk::Entry l_entry1;
        Gtk::Image logo;
        Gtk::Image contactless;

        Homescreen hs;
        Saldoscreen ss;
        Checkoutscreen cs;
        
    public:
        Loginscreen(Glib::Dispatcher &dispatcher);
        virtual ~Loginscreen();

        void setPageReady(bool ready);
        bool getPageReady();
        
    private:
        bool _ready_for_next_page;
        void checkLogin();
        
};

#endif