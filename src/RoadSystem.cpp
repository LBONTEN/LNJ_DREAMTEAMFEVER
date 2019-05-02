/* created by Van Borm Joren & Bontenakel Lenny
 */

#include "RoadSystem.h"
#include "Road.h"
#include <string>


RoadSystem::RoadSystem() : vectorOfRoads(), vectorOfVehicles(), active(false), time(0), selfPtr(this)
{
    ENSURE(properlyInitialised(), "Roadsystem failed to initialise");
    ENSURE(getVectorOfVehicles().empty(), "Failed to initialise vector of vehicles");
    ENSURE(getVectorOfRoads().empty(), "Failed to initialise vector of roads");
    ENSURE(!simulationActive() && timeActive() == 0, "Just initialised system can't be active / have active time");
}

RoadSystem::RoadSystem(const vector<Road*>& roads, const vector<Vehicle*>& vehicles) :
        vectorOfRoads(roads), vectorOfVehicles(vehicles), active(false), time(0), selfPtr(this)
{
    for(vector<Vehicle*>::const_iterator i = vehicles.begin(); i != vehicles.end(); i++)
    {
        (*i)->setEnv(this);
    }
    ENSURE(properlyInitialised(), "Roadsystem failed to initialise");
    ENSURE(getVectorOfVehicles() == vehicles, "Failed to initialise vector of vehicles");
    ENSURE(getVectorOfRoads() == roads, "Failed to initialise vector of roads");
    ENSURE(!simulationActive() && timeActive() == 0, "Just initialised system can't be active / have active time");
}

        
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
    REQUIRE(properlyInitialised(), "Roadsystem wasn't initialised");
    return vectorOfRoads;
}

const vector<Vehicle*>& RoadSystem::getVectorOfVehicles() const
{
    REQUIRE(properlyInitialised(), "Roadsystem wasn't initialised");
    return vectorOfVehicles;
}


bool RoadSystem::simulationActive() const
{
    REQUIRE(properlyInitialised(), "Roadsystem wasn't initialised");
    return active;
}

bool RoadSystem::empty() const
{
    REQUIRE(properlyInitialised(), "Roadsystem wasn't initialised");
    return vectorOfVehicles.empty();
}

unsigned long RoadSystem::timeActive() const
{
    REQUIRE(properlyInitialised(), "Roadsystem wasn't initialised");
    return time;
}

bool RoadSystem::properlyInitialised() const
{
    return this == selfPtr;
}

bool RoadSystem::contains(const Vehicle* querry) const
{
    REQUIRE(properlyInitialised(), "Roadsystem wasn't initialised");
    
    for (unsigned long vIndex = 0; vIndex < vectorOfVehicles.size(); vIndex++)
    {
        if (vectorOfVehicles[vIndex] == querry) return true;
    }
    return false;
}

bool RoadSystem::contains(const Road* querry) const
{
    REQUIRE(properlyInitialised(), "Roadsystem wasn't initialised");
    
    for (unsigned long rIndex = 0; rIndex < vectorOfRoads.size(); rIndex++)
    {
        if (vectorOfRoads[rIndex] == querry) return true;
    }
    return false;
}


void RoadSystem::setVectorOfRoads(const vector<Road*>& newVectorOfRoads)
{
    REQUIRE(properlyInitialised(), "Roadsystem wasn't initialised");
    
    vectorOfRoads = newVectorOfRoads;
    
    ENSURE(getVectorOfRoads() == vectorOfRoads, "failed to set vector of roads");
}

void RoadSystem::setVectorOfVehicles(const vector<Vehicle*>& newVectorOfVehicles)
{
    REQUIRE(properlyInitialised(), "Roadsystem wasn't initialised");
    
    vectorOfVehicles = newVectorOfVehicles;
    
    ENSURE(getVectorOfVehicles() == vectorOfVehicles, "failed to set vector of vehicles");
}


void RoadSystem::addVehicle(Vehicle* newVehicle)
{
    REQUIRE(properlyInitialised(), "Roadsystem wasn't initialised");
    
    vectorOfVehicles.push_back(newVehicle);
    
    ENSURE(contains(newVehicle), "failed to add vehicle to roadsystem");
}

void RoadSystem::addRoad(Road* newRoad)
{
    REQUIRE(properlyInitialised(), "Roadsystem wasn't initialised");
    
    vectorOfRoads.push_back(newRoad);
    
    ENSURE(contains(newRoad), "failed to add road to roadsystem");
}


void RoadSystem::removeVehicle(Vehicle* oldVeh)
{
    REQUIRE(properlyInitialised(), "Roadsystem wasn't initialised");
    
    for (unsigned long vIndex = 0; vIndex < vectorOfVehicles.size(); vIndex++)
    {
        if (vectorOfVehicles[vIndex] == oldVeh)
        {
            vectorOfVehicles.erase(vectorOfVehicles.begin()+vIndex);
            return;
        }
    }
    
    ENSURE(!contains(oldVeh), "failed to add vehicle to roadsystem");
}

void RoadSystem::removeRoad(Road* oldRoad)
{
    REQUIRE(properlyInitialised(), "Roadsystem wasn't initialised");
    
    for (unsigned long rIndex = 0; rIndex < vectorOfRoads.size(); rIndex++)
    {
        if (vectorOfRoads[rIndex] == oldRoad)
        {
            vectorOfRoads.erase(vectorOfRoads.begin()+rIndex);
            return;
        }
    }
    
    ENSURE(!contains(oldRoad), "failed to add road to roadsystem");
}


void RoadSystem::activate()
{
    REQUIRE(properlyInitialised(), "Roadsystem wasn't initialised");
    
    active = true;
    
    ENSURE(simulationActive(), "failed to activate simulation");
}

void RoadSystem::advanceSimulation()
{
    REQUIRE(properlyInitialised(), "Roadsystem wasn't initialised");
    REQUIRE(simulationActive(), "Can't advance an inactive simulation");
    
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
            delete current;
        }
    }

    for(unsigned long rIndex = 0; rIndex < vectorOfRoads.size(); rIndex++)
    {
        vector<TrafficLight*> lightsOnRoad = vectorOfRoads[rIndex]->getTrafficLights();
        for(unsigned long lIndex = 0; lIndex < lightsOnRoad.size(); lIndex++)
        {
            lightsOnRoad[lIndex]->updateState(timeActive());
        }
    }

    time++;
}

void RoadSystem::untilEmpty()
{
    REQUIRE(properlyInitialised(), "Roadsystem wasn't initialised");
    
    activate();
    
    while (not empty())
    {
        advanceSimulation();
    }
    
    ENSURE(empty(), "untilEmpty stopped before simulation empty");
    ENSURE(simulationActive(), "simulation not activate after simulating");
}

void RoadSystem::untilTime(unsigned long seconds)
{
    REQUIRE(properlyInitialised(), "Roadsystem wasn't initialised");
    
    activate();
    
    unsigned long iteration;
    for (iteration = 0; iteration < seconds; iteration++)
    {
        advanceSimulation();
        
        if (empty()) break;
    }
    
    ENSURE(empty() || iteration >= seconds, "untilEmpty stopped before meeting its goal");
    ENSURE(simulationActive(), "simulation not activate after simulating");
}