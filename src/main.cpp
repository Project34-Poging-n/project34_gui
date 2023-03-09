#include<iostream>
#include <gtkmm/application.h>
#include "serial.hpp"
#include "homescreen.hpp"

#ifdef _WIN32
HANDLE h_serial;
#endif


int main(int argc, char *argv[])
{
//     SerialListener listener;

// #ifdef _WIN32
//     listener.sopen("COM5");
// #endif

// #ifdef __unix__
//     listener.sopen("");
// #endif

//     while (1) {
//         std::cout << listener.sread() << std::endl;
//     }
//     listener.sclose();

    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");
    Window gtk_window;

    return app->run(gtk_window);
}