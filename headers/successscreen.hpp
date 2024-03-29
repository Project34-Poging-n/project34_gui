#pragma once


#include <gtkmm.h>
#include <memory>


#ifndef __PROJECT34__SUCCESSSCREEN__
#define __PROJECT34__SUCCESSSCREEN__


class Successscreen
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
        Gtk::Box vbox;

        Successscreen();
        virtual ~Successscreen();
        void writeToDispenser(const char *amount);
        void setSignal(sigc::signal<void, std::string> &signal);
        sigc::signal<void, std::string> getSignal();
        void setLabelText(std::string label);
        
    private:
        sigc::signal<void, std::string> signal;
        void trigger_timer(std::string data);
};


#endif