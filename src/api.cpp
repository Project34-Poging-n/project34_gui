#include "api.hpp"
#include <json/json.h>
#include <curl/curl.h>
#include <iostream>
#include <string>


static char* read_buffer = nullptr;
static char *write_buffer = nullptr;


/**
 * Convert json object to a string
 * 
 * @param object
 * @return std::string
*/
std::string jsonToString(Json::Value const &object)
{
    return object.toStyledString();
}


/**
 * 
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
*/
Json::Value get_data(unsigned int id)
{
    CURL *curl = curl_easy_init();

    // std::string url = "http://145.24.222.51:8081/get-data";
    std::string url = "http://127.0.0.1:3000/";

    try {
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

            // setup headers for call
            struct curl_slist *headers = NULL;
            headers = curl_slist_append(headers, "Content-Type: application/json");
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
            // curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
            curl_easy_setopt(curl, CURLOPT_HTTPGET, 1);
            curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

            // Buffer to store the data
            char data[21];

            // Set a write function that will be called with the received data
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, data);

            // Perform the transfer
            CURLcode res;
            if (curl != NULL) {
                res = curl_easy_perform(curl);
            } else {
                res /= CURLE_FAILED_INIT;
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

    Json::Value root;

    return root;
}


void send_data(Json::Value &object)
{

}