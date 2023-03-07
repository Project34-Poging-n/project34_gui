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

    while (1) {
        std::cout << listener.sread() << std::endl;
    }
    listener.sclose();

    return 0;
}