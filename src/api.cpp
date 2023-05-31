#include "api.hpp"
#include <json/json.h>
#include <curl/curl.h>
#include <iostream>
#include <string>


#define RESPONSE_BUFFER_SIZE        1000


static char* read_buffer = nullptr;
static char *write_buffer = nullptr;


/**
 * Convert json object to a string
 * 
 * @param object
 * @return std::string
*/
std::string json_to_string(Json::Value &object)
{
    Json::StreamWriterBuilder wbuilder;
    wbuilder["indentation"] = "";
    return Json::writeString(wbuilder, object);
}


/**
 * Convert a string to a json object
 * 
 * @param string
 * @return Json::Value
*/
Json::Value string_to_json(std::string &string)
{
    Json::Value root;
    Json::Reader reader;

    reader.parse(string, root);
    return root;
}


/**
 * Function to get the callback with the response data of the api
 * 
 * @param contents
 * @param size
 * @param nmemb
 * @param userp
 * @return size_t
*/
size_t writeCallback(char *contents, size_t size, size_t nmemb, void *userp)
{
    // char *buffer = static_cast<char *>(userp);

    // buffer = (char *)realloc(buffer, (size*nmemb) + strlen(buffer) + 1);s

    size_t realsize = size*nmemb;
    std::cout << "[into]\tData: " 
        << contents 
        << " with size: " 
        << size << " and nmemb: " 
        << nmemb 
        << "\n";

    char *buffer = static_cast<char *>(userp);
    memcpy(buffer, contents, realsize);
    buffer[realsize] = '\0';
    return realsize;
}


/**
 * Function to get data from the api
 * 
 * @param url
 * @param id
 * @return Json::Value
*/
Json::Value get_data(std::string url, std::string id)
{
    CURL *curl = curl_easy_init();
    // Buffer to store the data
    char data[RESPONSE_BUFFER_SIZE];

    try {
        if (curl) {
            url.append(id);

            std::cout << "[GET]\turl: " << url << "\n";

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

            // setup headers for call
            struct curl_slist *headers = NULL;
            headers = curl_slist_append(headers, "Content-Type: application/json");
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
            // curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
            curl_easy_setopt(curl, CURLOPT_HTTPGET, 1);
            curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

            // Set a write function that will be called with the received data
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, data);

            // Perform the transfer
            CURLcode res;
            if (curl != NULL) {
                res = curl_easy_perform(curl);
            } else {
                res = CURLE_FAILED_INIT;
            }

            // Check for errors and print the fetched data
            if (res == CURLE_OK) {
                std::cout << "Fetched data: " << data << std::endl;
            } else {
                std::cerr << "Error fetching data: " << curl_easy_strerror(res) << std::endl;
            }
            
            // Clean up
            curl_slist_free_all(headers);
            curl_easy_cleanup(curl);
        }
    } catch (const std::exception &e) {
        // std::cout << "[error]\terror: " << e << "\n";
    }

    std::string t = data;
    return string_to_json(t);
}


/**
 * Function to post data to a rest api
 * 
 * @param url
 * @param object
*/
void send_data(std::string url, Json::Value &object)
{
    CURL *curl = curl_easy_init();

    try {
        if (curl) {
            const int timeout = 30;
            std::string body = json_to_string(object);

            std::cout << "[info]\tsend: " << url.c_str() << "\n";

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

            // setup headers for call
            struct curl_slist *headers = NULL;
            headers = curl_slist_append(headers, "Content-Type: application/json");
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

            // Set certificate options
            // curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);

            // Set the data in the headers
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
            curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, body.length());
            curl_easy_setopt(curl, CURLOPT_POST, 1L);
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout);

            char data[RESPONSE_BUFFER_SIZE];

            // Set a write function that will be called with the received data
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, data);

            // Perform the transfer
            CURLcode res;
            if (curl != NULL) {
                res = curl_easy_perform(curl);
            } else {
                res = CURLE_FAILED_INIT;
            }

            if (res == CURLE_OK) {
                std::cout << "Fetched data: " << data << std::endl;
            } else {
                std::cerr << "Error fetching data: " << curl_easy_strerror(res) << std::endl;
            }

            // Clean up
            curl_slist_free_all(headers);
            curl_easy_cleanup(curl);
        }
    } catch (const std::exception &e) {

    }
}


/**
 * Function to get a default json template to send the data
 * 
 * @return Json::Value
*/
Json::Value get_default_template()
{
    Json::Value root;

    // Head information
    root["head"]["fromCtry"]    = "UK";
    root["head"]["fromBank"]    = "YOMAMA";
    root["head"]["toCtry"]      = "UK";
    root["head"]["toBank"]      = "exit";

    // Body information
    root["body"]["accNo"]       = "ASDASDA";
    root["body"]["pin"]         = "";

    return root;
}