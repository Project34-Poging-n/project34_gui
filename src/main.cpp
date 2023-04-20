#include<iostream>
#include <gtkmm.h>
#include <thread>
#include <string>
#include "serial.hpp"
#include "window.hpp"


#ifdef _WIN32
#define SERIAL_PORT "COM5"
#else
#define SERIAL_PORT "/dev/ttyACM0"
#endif
#define APPLICATION_TITLE "ATM GUI"


SerialListener listener;


/**
 * 
 */
void openSerialPort(sigc::signal<void, std::string> &signal)
{
    listener.sopen(SERIAL_PORT);
    std::string streamBuffer;

    while (1) {
        streamBuffer = listener.sread();
        signal.emit(streamBuffer);
    }
    listener.sclose();
}


/**
 * 
 */
void guiInterface(int argc, char *argv[], sigc::signal<void, std::string> &signal)
{
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.project34");
    Window screen(APPLICATION_TITLE, signal);
    app->run(screen);
}


/**
 * 
 */
int main(int argc, char *argv[])
{
    sigc::signal<void, std::string> dataSignal;

    // std::thread serialListenerThread(openSerialPort, std::ref(dataSignal));
    std::thread guiInterfaceThread(guiInterface, argc, argv, std::ref(dataSignal));

    // if (serialListenerThread.joinable()) {
    //     std::cout << "[info]\t\tJoin the the serial listener thread!\n";
    //     serialListenerThread.join();
    // }

    if (guiInterfaceThread.joinable()) {
        std::cout << "[info]\t\tJoin the gui listener thread!\n";
        guiInterfaceThread.join();
    }
    
    return 1;
}