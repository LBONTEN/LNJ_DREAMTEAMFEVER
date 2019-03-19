/* created by Van Borm Joren & Bontenakel Lenny
 */

#include <stdexcept>
#include <iostream>
#include <cstdlib>
#include "XMLParser.h"
#include "RoadSystem.h"
#include "Car.h"


XmlParser::XmlParser() {}

RoadSystem* XmlParser::parseRoadSystem(const std::string& fileName)
{
    pugi::xml_document doc;
    RoadSystem* newSystem = new RoadSystem();
    map<string, Road*> roads;

    // Load File
    if(!doc.load_file(fileName.c_str()))
    {
        return NULL;
    }

    // Get root
    pugi::xml_node root = doc.first_child();

    for(pugi::xml_node it = root.child("BAAN"); it; it = it.next_sibling("BAAN"))
    {
        string a = it.child("naam").text().as_string();
        roads[a.c_str()] = parseRoad(it);
    }

    for(pugi::xml_node it = root.first_child(); it; it = it.next_sibling())
    {
        string name = it.name();

        cout << name << endl;

        if(name == "BAAN") {
            string connectionName = it.child("verbinding").text().as_string();
            string currRoadName = it.child("naam").text().as_string();

            Road *connection = roads[connectionName.c_str()];
            Road *currentRoad = roads[currRoadName.c_str()];

            currentRoad->pushConnections(connection);
            newSystem->pushRoad(*currentRoad);
        }
        if(name == "VOERTUIG")
        {
            string currRoadName = it.child("baan").text().as_string();

            Road* currentRoad = roads[currRoadName.c_str()];
            newSystem->pushVehicle(*parseVehicle(it, newSystem, currentRoad));
        }
    }
    return newSystem;
}

Road* XmlParser::parseRoad(const pugi::xml_node& baan)
{
    string name = baan.child("naam").text().as_string();
    int maxSpeed = baan.child("snelheidslimiet").text().as_int();
    int length = baan.child("lengte").text().as_int();

    return new Road(name, length, maxSpeed);
}

Vehicle* XmlParser::parseVehicle(const pugi::xml_node& voertuig, RoadSystem* environment, Road* currentRoad)
{
    string type = voertuig.child("TYPE").text().as_string();
    if(type == "AUTO")
    {
        string licensePlate = voertuig.child("nummerplaat").text().as_string();
        int acceleration = 0;
        unsigned int speed = voertuig.child("snelheid").text().as_uint();
        int position = voertuig.child("positie").text().as_int();

        return new Car(environment, licensePlate, currentRoad, acceleration, speed, position);
    }
    return NULL;
}
