#include<iostream>
#include<Windows.h>
#include "serial.hpp"


#ifdef _WIN32
HANDLE h_serial;
#endif


int main()
{
    SerialListener listener;
    listener.sopen("COM5");

    return 0;
}