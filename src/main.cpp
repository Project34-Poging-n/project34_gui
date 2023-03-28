#include<iostream>
#include <gtkmm.h>
#include <thread>
#include <string>
#include "serial.hpp"
#include "loginscreen.hpp"


#ifdef _WIN32
#define SERIAL_PORT "COM5"
#else
#define SERIAL_PORT "/dev/ttyACM0"
#endif


SerialListener listener;
std::string streamBuffer;


/**
 * 
 */
void openSerialPort()
{
    listener.sopen(SERIAL_PORT);

    while (1) {
        streamBuffer = listener.sread();
        std::cout << streamBuffer << std::endl;
    }
    //listener.sclose();
}


/**
 * 
 */
void guiInterface(int argc, char *argv[])
{
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.project34");
    Loginscreen screen;
    app->run(screen);
}


/**
 * 
 */
int main(int argc, char *argv[])
{
    std::thread serialListenerThread(openSerialPort);
    std::thread guiInterfaceThread(guiInterface, argc, argv);

    if (serialListenerThread.joinable()) {
        std::cout << "[info]\t\tJoin the the serial listener thread!\n";
        serialListenerThread.join();
    }

    if (guiInterfaceThread.joinable()) {
        std::cout << "[info]\t\tJoin the gui listener thread!\n";
        guiInterfaceThread.join();
    }

    // auto app = Gtk::Application::create(argc, argv, "org.gtkmm.project34");
    // Loginscreen screen;

    // screen.signal_show().connect([&screen]() {
    //     // screen.run();
    // });

    // app->run(screen);
    
    return 1;
}