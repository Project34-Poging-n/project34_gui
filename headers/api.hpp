#pragma once


#include <json/json.h>
#include <string>


#ifndef __PROJECT34__API__
#define __PROJECT34__API__


Json::Value get_default_template(
    std::string fc,
    std::string fb,
    std::string tc,
    std::string tb,
    std::string acc,
    std::string pin
);
std::string json_to_string(Json::Value &object);
Json::Value string_to_json(std::string &string);
Json::Value get_data(std::string url, std::string id);
Json::Value send_data(std::string url, Json::Value &object);


#endif