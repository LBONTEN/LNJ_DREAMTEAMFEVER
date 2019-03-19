/* created by Van Borm Joren & Bontenakel Lenny
 */

#include "pugixml.hpp"
#include <string>
#include <map>
using namespace std;

class RoadSystem;
class Road;
class Vehicle;
class Car;

#ifndef DAPIZZAPROJECT_XMLPARSER_H
#define DAPIZZAPROJECT_XMLPARSER_H

class XmlParser
{
public:

    XmlParser();

    RoadSystem* parseRoadSystem(const string& filename);
    Road* parseRoad(const pugi::xml_node& baan);
    Vehicle* parseVehicle(const pugi::xml_node& voertuig, RoadSystem* environment, Road* current_baan);

private:
    pugi::xml_node root;
};

#endif //DAPIZZAPROJECT_XMLPARSER_H
