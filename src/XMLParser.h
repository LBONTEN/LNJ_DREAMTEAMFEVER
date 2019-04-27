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

#ifndef LNJPSE_XMLPARSER_H
#define LNJPSE_XMLPARSER_H

class XmlParser
{
public:

    XmlParser();
    RoadSystem* parseRoadSystem(const string& filename);

private:

    Road* parseRoad(const pugi::xml_node& road);
    Vehicle* parseVehicle(const pugi::xml_node& vehicle, RoadSystem* environment, Road* currentRoad);
};

#endif //LNJPSE_XMLPARSER_H