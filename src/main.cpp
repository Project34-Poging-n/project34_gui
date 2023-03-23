#include<iostream>
#include <gtkmm/application.h>
#include "serial.hpp"
#include "homescreen.hpp"


#ifdef _WIN32
#define SERIAL_PORT "COM5"
#else
#define SERIAL_PORT "/dev/ttyACM0"
#endif


int main(int argc, char *argv[])
{
    SerialListener listener;

#ifdef __unix__
    listener.sopen(SERIAL_PORT);
#endif

    while (1) {
        std::cout << listener.sread() << std::endl;
    }
    //listener.sclose();

    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.project34");
    Homescreen homescreen;

    return app->run(homescreen);
}