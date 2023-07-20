#pragma once


#include <gtkmm.h>
#include <string>


#ifndef __PROJECT34__BASEVIEW__
#define __PROJECT34__BASEVIEW__


class BaseView
{
    private:
        std::string _title;         // Title of the page
        unsigned int _identifier;   // For the numbering in the pagination table

    public:
        BaseView(std::string const &title, unsigned int page);

        void setTitle(std::string const &title);
        void setIdentifier(unsigned int page);
        std::string getTitle();
        unsigned int getIdentifier();

        virtual void setOpSignal(sigc::signal<void, std::string> &signal) = 0;
        virtual sigc::signal<void, std::string> getSignal() = 0;
};


#endif