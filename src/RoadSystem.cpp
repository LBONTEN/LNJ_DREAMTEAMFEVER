/* created by Van Borm Joren & Bontenakel Lenny
 */

#include "RoadSystem.h"
#include "Road.h"
#include <string>


RoadSystem::RoadSystem() : vectorOfRoads(), vectorOfVehicles(), active(false) {}

RoadSystem::RoadSystem(const vector<Road*>& roads, const vector<Vehicle*>& vehicles) :
        vectorOfRoads(roads), vectorOfVehicles(vehicles) {}

        
RoadSystem::~RoadSystem()
{
    for (unsigned long vIndex = 0; vIndex < vectorOfVehicles.size(); vIndex++)
    {
        delete vectorOfVehicles[vIndex];
    }
    for (unsigned long rIndex = 0; rIndex < vectorOfRoads.size(); rIndex++)
    {
        delete vectorOfRoads[rIndex];
    }
}


const vector<Road*>& RoadSystem::getVectorOfRoads() const
{
    return vectorOfRoads;
}

const vector<Vehicle*>& RoadSystem::getVectorOfVehicles() const
{
    return vectorOfVehicles;
}


bool RoadSystem::simulationActive()
{
    return active;
}

bool RoadSystem::empty()
{
    return vectorOfVehicles.empty();
}


void RoadSystem::setVectorOfRoads(const vector<Road*>& vectorOfRoads)
{
    RoadSystem::vectorOfRoads = vectorOfRoads;
}

void RoadSystem::setVectorOfVehicles(const vector<Vehicle*>& vectorOfVehicles)
{
    RoadSystem::vectorOfVehicles = vectorOfVehicles;
}


bool RoadSystem::has(Vehicle* querry)
{
    for (unsigned long vIndex = 0; vIndex < vectorOfVehicles.size(); vIndex++)
    {
        if (vectorOfVehicles[vIndex] == querry) return true;
    }
    return false;
}

bool RoadSystem::has(Road* querry)
{
    for (unsigned long rIndex = 0; rIndex < vectorOfRoads.size(); rIndex++)
    {
        if (vectorOfRoads[rIndex] == querry) return true;
    }
    return false;
}


void RoadSystem::addVehicle(Vehicle* newVehicle)
{
    vectorOfVehicles.push_back(newVehicle);
}

void RoadSystem::addRoad(Road* newRoad)
{
    vectorOfRoads.push_back(newRoad);
}


void RoadSystem::removeVehicle(Vehicle* oldVeh)
{
    for (unsigned long vIndex = 0; vIndex < vectorOfVehicles.size(); vIndex++)
    {
        if (vectorOfVehicles[vIndex] == oldVeh)
        {
            vectorOfVehicles.erase(vectorOfVehicles.begin()+vIndex);
            delete oldVeh;
            return;
        }
    }
}

void RoadSystem::removeRoad(Road* oldRoad)
{
    for (unsigned long rIndex = 0; rIndex < vectorOfRoads.size(); rIndex++)
    {
        if (vectorOfRoads[rIndex] == oldRoad)
        {
            vectorOfRoads.erase(vectorOfRoads.begin()+rIndex);
            delete oldRoad;
            return;
        }
    }
}


void RoadSystem::activate()
{
    active = true;
}

void RoadSystem::advanceSimulation()
{
    for (unsigned long vIndex = 0; vIndex < vectorOfVehicles.size(); vIndex++)
    {
        vectorOfVehicles[vIndex]->prepUpdate();
    }
    
    for (unsigned long vIndex = 0; vIndex < vectorOfVehicles.size(); vIndex++)
    {
        Vehicle* current = vectorOfVehicles[vIndex];
        
        current->execUpdate();
        if (current->getCurrentRoad() == NULL)
        {
            removeVehicle(current);
        }
    }
}

void RoadSystem::untilEmpty()
{
    activate();
    
    while (not empty())
    {
        advanceSimulation();
    }
}

void RoadSystem::untilTime(unsigned long seconds)
{
    activate();
    
    for (unsigned long iteration = 0; iteration < seconds; iteration++)
    {
        advanceSimulation();
        
        if (empty()) break;
    }
}
