#include<iostream>
#include <gtkmm.h>
#include <thread>
#include <string>
#include "serial.hpp"
#include "window.hpp"
#include "api.hpp"


#ifdef _WIN32
#define INPUT_SERIAL_PORT   "COM5"
#define OUTPUT_SERIAL_PORT  ""
#else
#define INPUT_SERIAL_PORT   "/dev/ttyACM0"
#endif
#define APPLICATION_TITLE   "ATM GUI"


SerialListener ilistener;
// SerialListener olistener;


/**
 * Function to read data from the input node of the atm
 * 
 * @param signal
 */
void openSerialPort(sigc::signal<void, std::string> &signal)
{
    ilistener.sopen(INPUT_SERIAL_PORT);
    std::string streamBuffer = "";

    while (1) {
        streamBuffer = ilistener.sread();
        
        if (streamBuffer != "") {
            signal.emit(streamBuffer);
            streamBuffer = "";
        } 
    }

    ilistener.sclose();
}


/**
 * Function to set up a thread with the gui interface of the atm
 * 
 * @param argc
 * @param argv
 * @param signal
 */
void guiInterface(int argc, char *argv[], sigc::signal<void, std::string> &signal)
{
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.project34");
    Window screen(APPLICATION_TITLE, signal);
    app->run(screen);
}


/**
 * Main function
 * 
 * @param argc
 * @param argv
 */
int main(int argc, char *argv[])
{
    sigc::signal<void, std::string> dataSignal;

    get_data("http://127.0.0.1:3000/", 10);
    Json::Value yomama = get_default_template();

    send_data("http://127.0.0.1:3000/henk", yomama);

    std::thread serialListenerThread(openSerialPort, std::ref(dataSignal));
    std::thread guiInterfaceThread(guiInterface, argc, argv, std::ref(dataSignal));

    if (serialListenerThread.joinable()) {
        std::cout << "[info]\t\tJoin the the serial listener thread!\n";
        serialListenerThread.join();
    }

    if (guiInterfaceThread.joinable()) {
        std::cout << "[info]\t\tJoin the gui listener thread!\n";
        guiInterfaceThread.join();
    }
    
    return 1;
}