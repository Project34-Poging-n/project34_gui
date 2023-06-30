#pragma once


#include <gtkmm.h>
#include <memory>
#include <string>


#ifndef __PROJECT34__BILJETSCREEN__
#define __PROJECT34__BILJETSCREEN__



class Biljetscreen
{  
    private:
        unsigned int _biljet50   = 50;
        unsigned int _biljet20   = 20;
        unsigned int _biljet5    = 5;

    protected:
        Gtk::Box side_box1;
        Gtk::Box side_box2;
        Gtk::Box side_box3;
        Gtk::Box side_box4;
        Gtk::Label l_label1;
        Gtk::Label l_label2;
        Gtk::Label l_label3;
        Gtk::Image logo;
        Gtk::Label fastp;
        Gtk::Label slowp;
        Gtk::Label back;
        Gtk::Label fastp2;
        Gtk::Label fastp3;

    public:
        Gtk::Box vbox;

        Biljetscreen();
        virtual ~Biljetscreen();

       //  Gtk::Box *getVBox();
       int getPageNumber();
       unsigned int getBiljet50();
       unsigned int getBiljet20();
       unsigned int getBiljet5();
};

#endif