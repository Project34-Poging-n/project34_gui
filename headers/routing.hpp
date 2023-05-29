#pragma once


#include <string>


#ifndef __PROJECT34__ROUTING__
#define __PROJECT34__ROUTING__


struct s_routingCell
{
    std::string bankcode;
    std::string route;
};


std::string route_lookup(std::string &bankcode);


#endif