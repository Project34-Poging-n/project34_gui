#include "serial.hpp"
#include <iostream>
#include <string>
#include <fstream>

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
        OPEN_EXISTING, 
        FILE_ATTRIBUTE_NORMAL,// FILE_FLAG_NO_BUFFERING | FILE_FLAG_OVERLAPPED, 
        NULL
    );

    if (this->_h_serial == INVALID_HANDLE_VALUE) {
        if (GetLastError() == ERROR_FILE_NOT_FOUND) {
            std::cout << "[error]\t\tCan't find the comm file!\n";
        }

        std::cout << "[error]\t\tThe handle that is created is invalid!\n";
    }

    DCB dcbSerialParam = {0};
    dcbSerialParam.DCBlength = sizeof(dcbSerialParam);

    if (!GetCommState(this->_h_serial, &dcbSerialParam)) {
        std::cout << "[error]\t\tCan't get the com state from the operating system: " << GetLastError() << std::endl;
        exit(1);
    }

    dcbSerialParam.BaudRate     = CBR_115200;       // Set baudrate
    dcbSerialParam.ByteSize     = 8;                // Set bitsize 
    dcbSerialParam.StopBits     = ONESTOPBIT;       // Set stopbit to one
    dcbSerialParam.Parity       = NOPARITY;         // Set no parity

    if (!SetCommState(this->_h_serial, &dcbSerialParam)) {
        std::cout << "[error]\t\tCan't set the settings for the com state to open the serial port: " << GetLastError() << std::endl;
        exit(1);
    }

    COMMTIMEOUTS timeout = {0};
    timeout.ReadIntervalTimeout             = 60;
    timeout.ReadTotalTimeoutConstant        = 60;
    timeout.ReadTotalTimeoutMultiplier      = 15;
    timeout.WriteTotalTimeoutConstant       = 60;
    timeout.WriteTotalTimeoutMultiplier     = 8;

    if (!SetCommTimeouts(this->getHSerial(), &timeout)) {
        std::cout << "[error]\t\tCan't set the comm timeout: " << GetLastError() << std::endl;
    }
#endif

#ifdef __unix__
    // memset(&this->_port_settings, 0, sizeof(this->_port_settings));

    this->_h_serial = open(s_port.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);

    if (this->getHSerial() == -1) {
        perror("[info]\t\tCan't find the serial port!");
        exit(1);
    } else {
        fcntl(this->getHSerial(), F_SETFL, 0);
        std::cout << "[info]\t\tThe serial port is open!\n";
    }

    cfsetispeed(&this->_port_settings, B115200);    // Set the input speed
    cfsetospeed(&this->_port_settings, B115200);    // Set the output speed

    this->_port_settings.c_iflag &= ~IGNBRK;
    this->_port_settings.c_lflag = 0;
    this->_port_settings.c_oflag = 0;
    this->_port_settings.c_cc[VMIN] = 0;
    this->_port_settings.c_cc[VTIME] = 5;

    this->_port_settings.c_cflag &= ~PARENB;        // No parity
    this->_port_settings.c_cflag &= ~CSTOPB;        // Set stop bits
    this->_port_settings.c_cflag &= ~CSIZE;         // Set Bit size
    this->_port_settings.c_cflag |= CS8;            // ????

    // Set the atrribute 
    if (tcsetattr(this->getHSerial(), TCSANOW, &this->_port_settings) != 0) {
        perror("[error]\tCan't save the serial port settings!\n");
        exit(1);
    }

#endif

    std::cout << "[info]\t\tSerial port is open at: " << s_port << std::endl;
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
    int rc = close(this->getHSerial());
    if (rc != 0) {
        perror("");
        exit(1);
    }
#endif
}


/**
 * 
 */
std::string SerialListener::sread()
{
#ifdef _WIN32
    char sBuffer[7] = {0};
    DWORD dwRead = 0;

    SetFilePointer(this->getHSerial(), 0, NULL, FILE_BEGIN);
    if (!ReadFile(this->getHSerial(), sBuffer, 7, &dwRead, NULL)) {
        std::cout << "[error]\t\tCan't read from serial port: " << GetLastError() << std::endl;
    }
#endif

#ifdef __unix__
    char sBuffer[100] = {0};

    int n = read(this->getHSerial(), sBuffer, sizeof(sBuffer));
    // std::cout << "[info]\t\tText: " << buffer[n] << "\n";
#endif
    return sBuffer;
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