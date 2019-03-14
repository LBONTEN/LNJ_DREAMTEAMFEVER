/* created by Van Borm Joren & Bontenakel Lenny
 */

#include <stdexcept>
#include <iostream>
#include "./tinystuff/tinyxml.h"
#include "XMLParser.h"
#include "RoadSystem.h"

XmlParser::XmlParser() {}

RoadSystem* XmlParser::parseRoadSystem(const string& fileName)
{
    TiXmlDocument doc;
    RoadSystem* newSystem = new RoadSystem();

    string path = "../IO/" + fileName;

    // Load content from given input
    if (!doc.LoadFile(path.c_str()))
    {
        return NULL;
    }

    // set a pointer to first tag of input xml
    TiXmlElement* root = doc.FirstChildElement();
    // If input xml contains nothing, return nothing
    if (root == NULL)
    {
        return NULL;
    }

    map<string, Road *> roads;

    for (TiXmlElement *elem = root; elem != NULL; elem = elem->NextSiblingElement())
    {
        if(elem->ValueTStr() == "BAAN")
        {
            roads[elem->FirstChildElement("naam")->GetText()] = parseRoad(*elem);
        }
        if(elem->ValueTStr() == "VOERTUIG")
        {
            newSystem->pushVehicle(*parseVehicle(*elem));
        }
    }

    Road* road;
    Road* connection;
    for(TiXmlElement* elem = root; elem != NULL; elem = elem->NextSiblingElement("BAAN"))
    {
        connection = roads[elem->FirstChildElement("verbinding")->Value()];
        road = roads[elem->FirstChildElement("naam")->Value()];
        road->pushConnections(connection);
        newSystem->pushRoad(*road);
    }
    return newSystem;
}

Road* XmlParser::parseRoad(TiXmlElement & baan)
{
    map<string, string> roadData;
    for (TiXmlElement *child = baan.FirstChildElement(); child != NULL; child = baan.NextSiblingElement())
    {
        if (child->ValueTStr() != "verbinding")
        {
            roadData[child->Value()] = child->GetText();
        }
    }

    string name = roadData["naam"];
    int maxSpeed = atoi(roadData["snelheidslimiet"].c_str());
    int length = atoi(roadData["lengte"].c_str());

    return new Road(name, length, maxSpeed);
}

Vehicle* XmlParser::parseVehicle(TiXmlElement&)
{
    return new Vehicle;
}