/* created by Van Borm Joren & Bontenakel Lenny
 */

#include <stdexcept>
#include <iostream>
#include <cstdlib>
#include "XMLParser.h"
#include "RoadSystem.h"
#include "Car.h"
#include "cmath"


XmlParser::XmlParser() {}


/** ---------------------------------------------------------------------
 *
 *
 --------------------------------------------------------------------- */
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

    for(pugi::xml_node xmlNode = root.child("BAAN"); xmlNode; xmlNode = xmlNode.next_sibling("BAAN"))
    {
        string name = xmlNode.child("naam").text().as_string();
        roads[name.c_str()] = parseRoad(xmlNode, newSystem);
    }

    for(pugi::xml_node xmlNode = root.first_child(); xmlNode; xmlNode = xmlNode.next_sibling())
    {
        string type = xmlNode.name();

        if(type == "BAAN")
        {
            string connectionName = xmlNode.child("verbinding").text().as_string();
            string currRoadName = xmlNode.child("naam").text().as_string();

            Road *connection = roads[connectionName.c_str()];
            Road *currentRoad = roads[currRoadName.c_str()];
            
            if (connection != NULL)
            {
                currentRoad->setConnection(connection);
            }
            
            
            newSystem->addRoad(currentRoad);
        }
        if(type == "VOERTUIG")
        {
            string currRoadName = xmlNode.child("baan").text().as_string();

            Road* currentRoad = roads[currRoadName.c_str()];
            Vehicle* newVehicle = parseVehicle(xmlNode, newSystem, currentRoad);
            newSystem->addVehicle(newVehicle);
            currentRoad->addVehicle(newVehicle);
        }
    }
    return newSystem;
}

Road* XmlParser::parseRoad(const pugi::xml_node& baan, RoadSystem* environment)
{
    string name = baan.child("naam").text().as_string();
    int maxSpeed = baan.child("snelheidslimiet").text().as_int();
    int length = baan.child("lengte").text().as_int();

    return new Road(name, length, maxSpeed, environment);
}

Vehicle* XmlParser::parseVehicle(const pugi::xml_node& voertuig, RoadSystem* environment, Road* currentRoad)
{
    string type = voertuig.child("type").text().as_string();
    if(type == "AUTO")
    {
        string licensePlate = voertuig.child("nummerplaat").text().as_string();
        int acceleration = 0;
        unsigned int speed = voertuig.child("snelheid").text().as_uint() ;
        unsigned int position = voertuig.child("positie").text().as_uint();

        return new Car(environment, licensePlate, currentRoad, acceleration, int(speed*3.6), position);
    }
    return NULL;
}
