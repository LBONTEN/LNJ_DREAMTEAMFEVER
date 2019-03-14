/* created by Van Borm Joren & Bontenakel Lenny
 */

#include "./tinystuff/tinyxml.h"
#include <string>
#include <map>
using namespace std;

class RoadSystem;
class Road;
class Vehicle;

#ifndef DAPIZZAPROJECT_XMLPARSER_H
#define DAPIZZAPROJECT_XMLPARSER_H

class XmlParser
{
public:

    XmlParser();

    RoadSystem* parseRoadSystem(const string& filename);
    Road* parseRoad(const TiXmlElement&);
    Vehicle* parseVehicle(const TiXmlElement&);

};

#endif //DAPIZZAPROJECT_XMLPARSER_H
