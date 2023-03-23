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

    public:
        Window(std::string title);
        virtual ~Window();
};



#endif