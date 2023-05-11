#pragma once


#include <json/json.h>
#include <string>


#ifndef __PROJECT34__API__
#define __PROJECT34__API__


std::string jsonToString(Json::Value &object);
Json::Value stringToJson(std::string &string);
Json::Value get_data(unsigned int id);
void send_data(Json::Value &object);


#endif