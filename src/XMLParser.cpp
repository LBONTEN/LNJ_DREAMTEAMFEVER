/* created by Van Borm Joren & Bontenakel Lenny
 */

#include <stdexcept>
#include "./tinystuff/tinyxml.h"
#include "XMLParser.h"
#include "RoadSystem.h"

RoadSystem* XmlParser::parseRoadSystem(const string& fileName)
{
    TiXmlDocument inputfile;
    string path = "../IO/" + fileName;

    // Load content from given input
    if (!inputfile.LoadFile(path.c_str())) {
        return NULL;
    }

    // set a pointer to first tag of input xml
    TiXmlNode*firstRoad = inputfile.FirstChild("BAAN");
    // If input xml contains nothing, return nothing
    if (firstRoad == NULL)
    {
        return NULL;
    }

    map<string, Road *> roads;
    for (TiXmlNode *elem = firstRoad; elem != NULL; elem = elem->NextSibling("BAAN"))
    {
        map<string, string> childContent;
        for (TiXmlNode *child = elem->FirstChild(); child != NULL; child = elem->IterateChildren(child))
        {
            if(child->ValueTStr() != "verbinding")
            {
                childContent.insert(pair<string, string>(child->Value(), child->ToText()->Value()));

            }
        }
        string name = childContent.at("naam");
        int length = atoi(childContent.at("lengte").c_str());
        int maxSpeed = atoi(childContent.at("maximumsnelheid").c_str());

        roads.insert(pair<string, Road*>(name, new Road(name, length, maxSpeed)));
    }

    vector<Road*> newRoads;
    for(TiXmlNode* elem = firstRoad; elem != NULL; elem = elem->NextSibling("BAAN"))
    {
        Road* connection = NULL;
        Road* road = roads.at(elem->FirstChild("naam")->ToText()->Value());
        try
        {
            connection = roads.at(elem->FirstChild("verbinding")->ToText()->Value());
        }
        catch(const std::out_of_range& oops) {}

        road->setConnections(connection);
        newRoads.push_back(road);
    }
    vector<Vehicle*> newVehicles;

    return new RoadSystem(newRoads, newVehicles);
}