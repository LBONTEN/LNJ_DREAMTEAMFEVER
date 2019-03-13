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
    string path = "../IO/" + fileName;

    // Load content from given input
    if (!doc.LoadFile(path.c_str())) {
        return NULL;
    }

    // set a pointer to first tag of input xml
    TiXmlElement*firstRoad = doc.FirstChildElement("BAAN");
    // If input xml contains nothing, return nothing
    if (firstRoad == NULL)
    {
        return NULL;
    }

    map<string, string> data;
    map<string, Road *> roads;
    for (TiXmlElement *elem = firstRoad; elem != NULL; elem = elem->NextSiblingElement("BAAN"))
    {
        for (TiXmlElement *child = elem->FirstChildElement(); child != NULL; child = elem->NextSiblingElement())
        {
            data = map<string, string>();
            if(child->ValueTStr() != "verbinding")
            {
                string xmlTag = child->Value();
                string xmlTagData = child->GetText();

                cout << xmlTag << " " << xmlTagData << endl;

                data[xmlTag]= xmlTagData;
            }
        }

        string name = data.at("naam");
        int length = atoi(data.at("lengte").c_str());
        int maxSpeed = atoi(data.at("maximumsnelheid").c_str());

        roads[name]= new Road(name, length, maxSpeed);
    }

    vector<Road*> newRoads;
    for(TiXmlElement* elem = firstRoad; elem != NULL; elem = elem->NextSiblingElement("BAAN"))
    {
        Road* connection = NULL;
        Road* road = roads.at(elem->FirstChildElement("naam")->GetText());
        try
        {
            connection = roads.at(elem->FirstChildElement("verbinding")->GetText());
        }
        catch(const std::out_of_range& oops) {}

        road->setConnections(connection);
        newRoads.push_back(road);
    }
    vector<Vehicle*> newVehicles;

    return new RoadSystem(newRoads, newVehicles);
}