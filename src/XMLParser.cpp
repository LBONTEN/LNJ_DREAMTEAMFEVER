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

    for (TiXmlElement *elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
    {
        if(elem->ValueTStr() == "BAAN")
        {
                string a = elem->FirstChildElement("naam")->GetText();
                Road* b = parseRoad(elem);
                roads[a] = b;
        }
        if(elem->ValueTStr() == "VOERTUIG")
        {
            newSystem->pushVehicle(*parseVehicle(elem));
        }
    }

    Road* road;
    Road* connection;
    for(TiXmlElement* elem = root->FirstChildElement("BAAN"); elem != NULL; elem = elem->NextSiblingElement("BAAN"))
    {
        connection = roads[elem->FirstChildElement("verbinding")->Value()];
        road = roads[elem->FirstChildElement("naam")->Value()];
        road->pushConnections(connection);
        newSystem->pushRoad(*road);
    }
    return newSystem;
}

Road* XmlParser::parseRoad(TiXmlElement* baan)
{
    map<string, string> roadData;
    for (TiXmlElement *child = baan->FirstChildElement(); child != NULL; child = child->NextSiblingElement())
    {
        if (child->ValueTStr() != "verbinding")
        {
            string b = child->GetText();
            string a = child->FirstChild()->Value();
            roadData[a] = b;
        }
    }

    string name = roadData["naam"];
    int maxSpeed = atoi(roadData["snelheidslimiet"].c_str());
    int length = atoi(roadData["lengte"].c_str());

    return new Road(name, length, maxSpeed);
}

Vehicle* XmlParser::parseVehicle(TiXmlElement*)
{
    return new Vehicle;
}