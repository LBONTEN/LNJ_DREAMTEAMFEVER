/* created by Van Borm Joren & Bontenakel Lenny
 */

#include <stdexcept>
#include <iostream>
#include <cstdlib>
#include "XMLParser.h"
#include "RoadSystem.h"

XmlParser::XmlParser() {}

RoadSystem* XmlParser::parseRoadSystem(const string& fileName)
{
    pugi::xml_document doc;
    RoadSystem* newSystem = new RoadSystem();

    string path = "../IO/" + fileName;
    pugi::xml_parse_result fileContent = doc.load_file(path.c_str());

    if(!fileContent)
    {
        return NULL;
    }

    pugi::xml_node root = doc.root();

    map<string, Road*> roads;
    for(pugi::xml_node child = root.child("BAAN"); child; child = child.next_sibling("BAAN"))
    {
        roads[child.name()] = parseRoad(child);
    }

    for(pugi::xml_node child = root.first_child(); child; child.next_sibling())
    {
        if(child.name() == string("BAAN").c_str()) {
            Road *connection = roads[child.child_value("verbinding")];
            Road *current_baan = roads[child.child_value("naam")];

            current_baan->pushConnections(connection);
            newSystem->pushRoad(*current_baan);
        }
        if(child.name() == string("VOERTUIG").c_str())
        {
            Road* current_baan = roads[child.child_value("baan")];
            newSystem->pushVehicle(*parseVehicle(child, newSystem, current_baan));
        }
    }

    return newSystem;
}

Road* XmlParser::parseRoad(const pugi::xml_node& baan)
{
    string name = baan.child_value("naam");
    int maxSpeed = atoi(baan.child_value("snelheidslimiet"));
    int length = atoi(baan.child_value("lengte"));

    return new Road(name, length, maxSpeed);
}

Vehicle* XmlParser::parseVehicle(const pugi::xml_node& voertuig, RoadSystem* environment, Road* current_baan)
{
    string licensePlate = voertuig.child_value("nummerplaat");
    int acceleration = 0;
    int speed = atoi(voertuig.child_value("snelheid"));
    int position = atoi(voertuig.child_value("positie"));

    return new Vehicle(environment, licensePlate, current_baan, acceleration, speed, position);
}