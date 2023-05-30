#pragma once


#include <json/json.h>
#include <string>


#ifndef __PROJECT34__API__
#define __PROJECT34__API__


Json::Value get_default_template();
std::string json_to_string(Json::Value &object);
Json::Value string_to_json(std::string &string);
Json::Value get_data(std::string url, unsigned int id);
void send_data(std::string url, Json::Value &object);


#endif