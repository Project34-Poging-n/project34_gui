#pragma once


#include <gtkmm.h>
#include <string>
#include "loginscreen.hpp"
#include "homescreen.hpp"
#include "checkoutscreen.hpp"
#include "saldoscreen.hpp"
#include "slowcheckoutscreen.hpp"
#include "successscreen.hpp"


#ifndef __PROJECT34__WINDOW__
#define __PROJECT34__WINDOW__


class Window : public Gtk::Window
{
    private:
        int _currentPageNumber;
        bool _ready_for_next_page;
        void checkLogin(std::string data);

    protected:
        Gtk::Notebook notebook;
        Gtk::Frame frame;
        Gtk::Box vbox;

        Loginscreen ls;
        Homescreen hs;
        Saldoscreen ss;
        Checkoutscreen cs;
        SlowCheckoutscreen scs;
        Successscreen sss;

    public:
        Window(std::string title, sigc::signal<void, std::string> &signal);
        virtual ~Window();

        void navigation(std::string data);

        void setPageReady(bool ready);
        bool getPageReady();
        int getPageNumber();
        void setCurrentPageNumber(int number);
        int getCurrentPageNumber();
};


#endif