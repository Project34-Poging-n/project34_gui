#pragma once


#include <string>


#ifndef __PROJECT34__USERMODEL__
#define __PROJECT34__USERMODEL__


void set_username(std::string const &name);
std::string get_username();

void set_password(std::string const &password);
std::string get_password();

void set_iban(std::string const &iban);
std::string get_iban();


#endif