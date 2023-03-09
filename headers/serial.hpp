#pragma once


#include <string>
#ifdef _WIN32
#include <Windows.h>      // Check if the program is runned on windows, then include the windows api library
#endif
#ifdef __unix__
#include <termios.h>
#endif


#ifndef  __PROJECT34__SERIAL__
#define  __PROJECT34__SERIAL__


class SerialListener
{
    private:
#ifdef _WIN32
        HANDLE _h_serial;
#endif
#ifdef __unix__
        int _h_serial;
        struct termios _port_settings;
#endif

    public:
        SerialListener();
        void sopen(std::string s_port);
        void sclose();
        std::string sread();
        void swrite(unsigned int const &message);

#ifdef _WIN32 
        void setHSerial(HANDLE handle);
        HANDLE getHSerial();
#endif

#ifdef __unix__
        void setHSerial(int file);
        int getHSerial();
#endif
};


#endif