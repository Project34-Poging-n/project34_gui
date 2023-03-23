#pragma once


#include <gtkmm.h>
#include <memory>
#include "window.hpp"


#ifndef __PROJECT34__HOMESCREEN__
#define __PROJECT34__HOMESCREEN__



class Homescreen : public Window
{
    protected:
        Gtk::Frame m_frame;

    public:
        Homescreen();
        virtual ~Homescreen();
};

#endif