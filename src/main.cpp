#include<iostream>
#include <gtkmm.h>
#include <thread>
#include <string>
#include "serial.hpp"
#include "loginscreen.hpp"


#ifdef _WIN32
#define SERIAL_PORT "COM5"
#else
#define SERIAL_PORT "/dev/ttyACM1"
#endif


SerialListener listener;


/**
 * 
 */
void openSerialPort(Glib::Dispatcher &dispatcher)
{
    listener.sopen(SERIAL_PORT);
    std::string streamBuffer;

    while (1) {
        streamBuffer = listener.sread();
        std::cout << streamBuffer << std::endl;

        if (streamBuffer.find("4") != std::string::npos) {
            dispatcher.emit();
        }
    }
    listener.sclose();
}


/**
 * 
 */
void guiInterface(int argc, char *argv[], Glib::Dispatcher &dispatcher)
{
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.project34");
    Loginscreen screen(dispatcher);
    app->run(screen);
}


/**
 * 
 */
int main(int argc, char *argv[])
{
    Glib::Dispatcher dispatcher;

    std::thread serialListenerThread(openSerialPort, std::ref(dispatcher));
    std::thread guiInterfaceThread(guiInterface, argc, argv, std::ref(dispatcher));

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