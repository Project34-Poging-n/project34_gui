#include <string>
#include "usermodel.hpp"


static std::string uname;
static std::string upassword;
static std::string uiban;


void set_username(std::string &name)
{
    uname = name;
}


std::string get_username()
{
    return uname;
}


void set_password(std::string const &password)
{
    upassword = password;
}


std::string get_password()
{
    return upassword;
}


void set_iban(std::string const &iban)
{
    uiban = iban;
}


std::string get_iban()
{
    return uiban;
}