#include<iostream>
#include<Windows.h>


void serial_open() 
{
    HANDLE h_serial;
    // h_serial = CreateFile("");

    if (h_serial == INVALID_HANDLE_VALUE) {
        if (GetLastError() == ERROR_FILE_NOT_FOUND) {

        }
    }
}


int main()
{
    std::cout << "Hello, cmake of iets ik heb geen idee!!!!!\n";

    while (1);

    return 0;
}