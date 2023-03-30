#pragma once


#include <gtkmm.h>
#include <string>


#ifndef __PROJECT34__WINDOW__
#define __PROJECT34__WINDOW__


class Window : public Gtk::Window
{
    private:

    protected:
        Gtk::Frame frame;
        Gtk::Box vbox;
        // Glib::Dispatcher dispatcher;

    public:
        Window(std::string title);
        virtual ~Window();

        // Glib::Dispatcher getDispatcher();
};



#endif