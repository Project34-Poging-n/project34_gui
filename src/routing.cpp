#include <string>
#include "routing.hpp"


static struct s_routingCell routingTable[] = {
    { "", "" },
};


/**
 * Function to check if a route exists in the routing table, or else send the
 * request to the country server
 * 
 * @param bankcode
*/
std::string route_lookup(std::string &bankcode)
{
    size_t totalRoutes = sizeof(routingTable[0]) / sizeof(routingTable);

    std::string url;
    for (int i = 0; i < totalRoutes; i++) {
        if (routingTable[i].bankcode == bankcode) {
            return routingTable[i].route;
        }
    }

    return "";
}