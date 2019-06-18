/* created by Van Borm Joren & Bontenakel Lenny
 */

#include <stdexcept>
#include <iostream>
#include <cstdlib>
#include "XMLParser.h"
#include "RoadSystem.h"
#include "TypedVehicles.h"
#include "RoadSigns.h"
#include "Logger.h"
#include "cmath"


XmlParser::XmlParser() {}

/* --------------------------------------------------------------------- */
RoadSystem* XmlParser::parseRoadSystem(const std::string& fileName)
{
    pugi::xml_document doc;
    RoadSystem* newSystem = new RoadSystem();
    map<string, Road*> roads;

    // Load File
    if(!doc.load_file(fileName.c_str()))
        return NULL;

    // Get root
    pugi::xml_node root = doc.child("ROOT");

    ENSURE(root == doc.first_child(), "Xml file must have leading ROOT tag.");
    ENSURE(!root.empty(), "Given file is not valid.");

    // Parse all Roads
    for(pugi::xml_node xmlNode = root.child("BAAN"); xmlNode; xmlNode = xmlNode.next_sibling("BAAN"))
    {
        string name = xmlNode.child("naam").text().as_string();
        Road* newRoad = parseRoad(xmlNode);
        if(newRoad)
            roads[name.c_str()] = newRoad;
        else
            *logging::globalLog << "Road not included due to incorrect formatting.\n"
                                   "Please check input .xml file.\n";
    }

    if(roads.empty())
        return  newSystem;

    // Set connections for all Roads and parse all Vehicles
    for(pugi::xml_node xmlNode = root.first_child(); xmlNode; xmlNode = xmlNode.next_sibling())
    {
        string type = xmlNode.name();

        if(type == "BAAN")
        {
            string currRoadName = xmlNode.child("naam").text().as_string();
            if(roads.find(currRoadName) != roads.end())
            {
                Road *currentRoad = roads[currRoadName.c_str()];
                if (!xmlNode.child("verbinding").empty())
                {
                    string connectionName = xmlNode.child("verbinding").text().as_string();
                    if (roads.find(connectionName) != roads.end())
                    {
                        Road *connection = roads[connectionName.c_str()];
                        currentRoad->setConnection(connection);
                    }
                }
                newSystem->addRoad(currentRoad);
            }
            else *logging::globalLog << "Road not included due to incorrect formatting.\n"
                                        "Please check input .xml file.\n";

        }
        else if(type == "VOERTUIG")
        {
            string currRoadName = xmlNode.child("baan").text().as_string();

            if(roads.find(currRoadName) != roads.end())
            {
                Road *currentRoad = roads[currRoadName];
                Vehicle *newVehicle = parseVehicle(xmlNode, newSystem, currentRoad);
                newSystem->addVehicle(newVehicle);
                currentRoad->getLanes()[0]->addVehicle(newVehicle);
            }
            else *logging::globalLog << "Road for Vehicle has not been found.";
        }
        else if(type == "VERKEERSTEKEN")
        {
            string tekenBaan = xmlNode.child("baan").text().as_string();
            Road* road = roads[tekenBaan];

            parseRoadSign(xmlNode, road);
        }
        else *logging::globalLog << "Possible objects are BAAN, VOERTUIG or VERKEERSTEKEN.";
    }
    return newSystem;
}

Road* XmlParser::parseRoad(const pugi::xml_node& baan)
{
    string name = baan.child("naam").text().as_string();
    int speedLimit = (int) (baan.child("snelheidslimiet").text().as_int() / 3.6);
    int length = baan.child("lengte").text().as_int();
    unsigned int laneCount = baan.child("rijstroken").text().as_uint();
    if(laneCount == (unsigned int) 0) laneCount = 1;

    if(name == "" || speedLimit == (unsigned int) 0 || length == (unsigned int) 0)
    {
        *logging::globalLog << "Road is not included because it is not properly defined.";
        return NULL;
    }
    return new Road(name, length, speedLimit, laneCount);
}

Vehicle* XmlParser::parseVehicle(const pugi::xml_node& voertuig, RoadSystem* environment, Road* currentRoad)
{
    string type = voertuig.child("type").text().as_string();

    string licensePlate = voertuig.child("nummerplaat").text().as_string();
    int acceleration = 0;
    int speed = int (voertuig.child("snelheid").text().as_int() / 3.6); // speed converted from km/h to m/s here
    unsigned int position = voertuig.child("positie").text().as_uint();

    if (type == "MOTORFIETS")
        return new MotorCycle(environment, licensePlate, currentRoad, acceleration, speed, position);

    else if(type == "AUTO")
        return new Car(environment, licensePlate, currentRoad, acceleration, speed, position);

    else if (type == "BUS")
        return new Bus(environment, licensePlate, currentRoad, acceleration, speed, position);

    else if (type == "VRACHTWAGEN")
        return new Truck(environment, licensePlate, currentRoad, acceleration, speed, position);

    *logging::globalLog << "Given vehicle type is not defined.";
    return NULL;
}

void XmlParser::parseRoadSign(const pugi::xml_node& verkeersteken, Road* road)
{
    string tekenType = verkeersteken.child("type").text().as_string();
    unsigned int tekenPositie = verkeersteken.child("positie").text().as_uint();

    if(tekenType == "ZONE")
    {
        int snelheidsLimiet = (int) (verkeersteken.child("snelheidslimiet").text().as_int() / 3.6);
        road->addZone(new Zone(tekenPositie, road, snelheidsLimiet));
    }

    else if(tekenType == "VERKEERSLICHT")
    {
        unsigned long offset = 0;
        road->addTrafficLight(new TrafficLight(tekenPositie, road, offset));
    }

    else if(tekenType == "BUSHALTE")
        road->addBusstop(new BusStop(tekenPositie, road));
}