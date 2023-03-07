#include "serial.hpp"
#include<iostream>
#include<string>

// Check if the program is runned on windows, then include the windows api library
#ifdef _WIN32
#include<Windows.h>
#endif

#ifdef __unix__
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()
#endif


/**
 * 
 */
SerialListener::SerialListener()
{

}


/**
 * 
 */
void SerialListener::sopen(std::string s_port)
{
#ifdef _WIN32
    this->_h_serial = CreateFile(
        s_port.c_str(), 
        GENERIC_READ | GENERIC_WRITE, 
        0, 
        NULL, 
        OPEN_ALWAYS, 
        FILE_FLAG_NO_BUFFERING | FILE_FLAG_OVERLAPPED, 
        NULL
    );

    std::cout << "[info]\t\tFile info: " << this->getHSerial() << std::endl;

    if (this->_h_serial == INVALID_HANDLE_VALUE) {
        if (GetLastError() == ERROR_FILE_NOT_FOUND) {
            std::cout << "[error]\t\tCan't find the comm file!\n";
        }

        std::cout << "[error]\t\tThe handle that is created is invalid!\n";
    }

    DCB dcbSerialParam = {0};
    dcbSerialParam.DCBlength = sizeof(dcbSerialParam);

    if (!GetCommState(this->_h_serial, &dcbSerialParam)) {
        std::cout << "[error]\t\tCan't get the com state from the operating system\n";
        exit(1);
    }

    dcbSerialParam.BaudRate     = CBR_115200;       // Set baudrate
    dcbSerialParam.ByteSize     = 8;                // Set bitsize 
    dcbSerialParam.StopBits     = ONESTOPBIT;       // Set stopbit to one
    dcbSerialParam.Parity       = NOPARITY;         // Set no parity

    if (!SetCommState(this->_h_serial, &dcbSerialParam)) {
        std::cout << "[error]\t\tCan't set the settings for the com state to open the serial port\n";
        exit(1);
    }
#endif

#ifdef __unix__
    memset(&this->_port_settings, 0, sizeof(this->_port_settings));

    this->_h_serial = open("", O_RDWR | O_NOCTTY | O_NDELAY);

    if (this->getHSerial() == -1) {
        perror("[info]\t\t");
    } else {
        fcntl(this->getHSerial(), F_SETFL, 0);
        std::cout << "[info]\t\tDe poort is open!\n";
    }

    cfsetispeed(&this->_port_settings, B115200);    // Set the input speed
    cfsetospeed(&this->_port_settings, B115200);    // Set the output speed

    this->_port_settings.c_cflag &= ~PARENB;        // No parity
    this->_port_settings.c_cflag &= ~CSTOPB;        // Set stop bits
    this->_port_settings.c_cflag &= ~CSIZE;         // Set Bit size
    this->_port_settings.c_cflag |= CS8;            // ????

    // Set the atrribute 
    if (tcsetattr(this->getHSerial(), TCSANOW, &this->_port_settings) != 0) {
        
    }
#endif
}


/**
 * 
 */
void SerialListener::sclose()
{
#ifdef _WIN32
    CloseHandle(this->_h_serial);
#endif

#ifdef __unix__
    close(this->getHSerial());
#endif
}


/**
 * 
 */
int SerialListener::sread()
{
    return 1;
}


/**
 * 
 */
void SerialListener::swrite(unsigned int const &message)
{

}


#ifdef _WIN32
/**
 * 
 */
void SerialListener::setHSerial(HANDLE handle)
{
    this->_h_serial = handle;
}


/**
 * 
 */
HANDLE SerialListener::getHSerial()
{
    return this->_h_serial;
}
#endif


#ifdef __unix__
/**
 * 
 */
void SerialListener::setHSerial(int file)
{
    this->_h_serial = file;
}


/**
 * 
 */
int SerialListener::getHSerial()
{
    return this->_h_serial;
}
#endif