/*      created by Van Borm Joren & Bontenakel Lenny         */

#include "Road.h"
#include "RoadSigns.h"
#include "RoadSystem.h"
#include <iostream>

extern const unsigned int minimumSpace= 2;


/* Helper function --------------------------------------------------- */
/* Road functions ---------------------------------------------------- */
Road::Road() :
name(""),
length(1),
speedLimit(1),
connection(NULL),
laneCount(1)
{
    lanes.push_back(new Lane(this, 0));
    ENSURE(properlyInitialised(), "Road default construction failed");
}


Road::Road(std::string name, unsigned int length, int maxSpeed, unsigned int laneCount, Road* connection) :
name(name),
length(length),
speedLimit(maxSpeed),
connection(connection),
laneCount(laneCount)
{
    for(unsigned int i = 0; i < laneCount; i++)
    {
        lanes.push_back(new Lane(this, i));
    }

    ENSURE(properlyInitialised(), "Road construction failed");
}


Road::~Road()
{
    for(unsigned long i = 0; i < lanes.size(); i++) delete lanes[i];
    lanes.clear();
    clearAllSigns();
}


bool Road::properlyInitialised() const
{
    if (length <= 0) return false;
    if(name.empty()) return false;
    if(speedLimit <= 0) return false;
    if(laneCount <= 0) return false;
    if(lanes.size() > laneCount) return false;

    return true;
}


void Road::setConnection(Road* newConnection)
{
    REQUIRE(properlyInitialised(), "Road: setConnection: Not properly initialised.");
    REQUIRE(newConnection->properlyInitialised(), "Road: setConnection: newConnection not properly initialised.");
    connection = newConnection;
    ENSURE(connection == newConnection, "Road: setConnection: Failed setting connection.");
}


void Road::clearConnection()
{
    REQUIRE(properlyInitialised(), "Road: clearConnection: Not properly initialised.");
    connection = NULL;
    ENSURE(connection == NULL, "Road: setConnection: Failed clearing connection.");
}


void Road::addZone(Zone* newZone)
{
    REQUIRE(properlyInitialised(), "Road: addZone: Not properly initialised.");
    unsigned long oldSize = zones.size();
    zones.push_back(newZone);
    ENSURE(getZones().size() == oldSize + 1, "Road: addZone: adding zone failed.");
}


void Road::addTrafficLight(TrafficLight* newLight)
{
    REQUIRE(properlyInitialised(), "Road: addTrafficLight: Not properly initialised.");
    unsigned long oldSize= trafficLights.size();
    trafficLights.push_back(newLight);
    ENSURE(getTrafficLights().size() == oldSize + 1, "Road: addTrafficLight: adding trafficlight failed.");
}


void Road::addBusstop(BusStop* newStop)
{
    REQUIRE(properlyInitialised(), "Road: addBusStop: Not properly initialised.");
    unsigned long oldSize = busStops.size();
    busStops.push_back(newStop);
    ENSURE(getBusStops().size() == oldSize + 1, "Road: addBusStop: adding busstp failed.");
}


bool Road::isFree() const
{
    REQUIRE(properlyInitialised(), "Road: isFree: not properly initialised.");

    for(vector<Lane*>::const_iterator i = lanes.begin(); i != lanes.end(); i++)
    {
        if(!(*i)->isFree())
        {
            return false;
        }
    }
    return true;
}


void Road::clearAllSigns()
{
    REQUIRE(properlyInitialised(), "Road: ClearAllSigns: Not properly initialised.");

    clearZones();
    clearTrafficLights();
    clearBusStops();

    ENSURE(getZones().empty(), "Road: clearAllSigns: zones has not been emptied.");
    ENSURE(getTrafficLights().empty(), "Road: clearAllSigns: trafficLights has not been empties.");
    ENSURE(getBusStops().empty(), "Road: clearAllSigns: busStops has not been emptied.");

}


void Road::clearZones()
{
    REQUIRE(properlyInitialised(), "Road: ClearZones: Not properly initialised.");
    if(zones.empty()) return;

    for(unsigned long i = 0; i < zones.size(); i++)
    {
        delete zones[i];
    }

    zones.clear();
    ENSURE(getZones().empty(), "Road: clearZones: zones has not been emptied.");
}


void Road::clearTrafficLights()
{
    REQUIRE(properlyInitialised(), "Road: ClearTrafficLights: Not properly initialised.");
    if(trafficLights.empty()) return;

    for(unsigned long i = 0; i < trafficLights.size(); i++)
    {
        delete trafficLights[i];
    }

    trafficLights.clear();
    ENSURE(getTrafficLights().empty(), "Road: clearTrafficLights: trafficLights has not been empties.");
}


void Road::clearBusStops()
{
    REQUIRE(properlyInitialised(), "Road: ClearBusStops: Not properly initialised.");
    if(busStops.empty()) return;

    for(unsigned long i = 0; i < busStops.size(); i++)
    {
        delete busStops[i];
    }

    busStops.clear();
    ENSURE(getBusStops().empty(), "Road: clearBusStops: busStops has not been emptied.");
}

vector<RoadSign*> Road::getAllSigns() const
{
    REQUIRE(properlyInitialised(), "Road: getAllSigns: Not properly initialised.");

    unsigned long zonesSize = zones.size();
    unsigned long trafficLightsSize = trafficLights.size();
    unsigned long busStopsSize = busStops.size();

    vector<RoadSign*> allSigns;

    allSigns.insert(allSigns.end(), zones.begin(), zones.end());
    allSigns.insert(allSigns.end(), trafficLights.begin(), trafficLights.end());
    allSigns.insert(allSigns.end(), busStops.begin(), busStops.end());

    ENSURE(zonesSize == getZones().size(), "Road: getAllSigns: Zones have been changed");
    ENSURE(trafficLightsSize == getTrafficLights().size(), "Road: getAllSigns: Traffic lights have been changed");
    ENSURE(busStopsSize == getBusStops().size(), "Road: getAllSigns: Bus stops have been changed");

    return allSigns;
}


const vector<Zone*>& Road::getZones() const
{
    REQUIRE(properlyInitialised(), "Road: getZones: Not properly initialised.");
    unsigned long zonesSize = zones.size();
    ENSURE(zonesSize == getZones().size(), "Road: getAllSigns: Zones have been changed");

    return zones;
}


const vector<TrafficLight*>& Road::getTrafficLights() const
{
    REQUIRE(properlyInitialised(), "Road: getTrafficLights: Not properly initialised.");
    unsigned long trafficLightsSize = trafficLights.size();
    ENSURE(trafficLightsSize == getTrafficLights().size(), "Road: getAllSigns: Traffic lights have been changed");

    return trafficLights;
}


const vector<BusStop*>& Road::getBusStops() const
{
    REQUIRE(properlyInitialised(), "Road: getBusStops: Not properly initialised.");
    unsigned long busStopsSize = busStops.size();
    ENSURE(busStopsSize == getBusStops().size(), "Road: getAllSigns: Bus stops have been changed");

    return busStops;

}


RoadSign* const Road::getSignOnPosition(unsigned int position, bool inclusive) const
{
    REQUIRE(properlyInitialised(), "Road: getSignOnPosition: Not properly Initialised.");
    REQUIRE(position < getLength(), "Road: getSignOnPosition:: Invalid position.");

    vector<RoadSign*> signs = getAllSigns();
    if(signs.empty())
    {
        return NULL;
    }

    RoadSign* nextSign = NULL;
    for(vector<RoadSign*>::const_iterator i = signs.begin(); i != signs.end(); i++)
    {
        if(inclusive && (*i)->getPosition() == position)
        {
            return (*i);
        }

        if((*i)->getPosition() > position)
        {
            if (nextSign == NULL || ((*i)->getPosition() - position) < (nextSign->getPosition() - position))
            {
                nextSign = (*i);
            }
        }
    }
    return nextSign;
}


Zone* const Road::getZoneStartOnPosition(unsigned int position, bool inclusive) const
{
    REQUIRE(properlyInitialised(), "Road: getZoneStartOnPosition: Not properly Initialised.");
    REQUIRE(position < getLength(), "Road: getZoneStartOnPosition:: Invalid position.");

    if(zones.empty())
    {
        return NULL;
    }

    Zone* nextZoneStart = NULL;
    for(vector<Zone*>::const_iterator i = zones.begin(); i != zones.end(); i++)
    {
        if(inclusive && (*i)->getPosition() == position)
        {
            return (*i);
        }

        if((*i)->getPosition() > position)
        {
            if (nextZoneStart == NULL || ((*i)->getPosition() - position) < (nextZoneStart->getPosition() - position))
            {
                nextZoneStart = (*i);
            }
        }
    }
    return nextZoneStart;
}

TrafficLight* const Road::getTrafficLightOnPosition(unsigned int position, bool inclusive) const
{
    REQUIRE(properlyInitialised(), "Road: getTrafficLightOnPosition: Not properly Initialised.");
    REQUIRE(position < getLength(), "Road: getTrafficLightOnPosition:: Invalid position.");


    if(trafficLights.empty())
    {
        return NULL;
    }

    TrafficLight* nextLight = NULL;
    for(vector<TrafficLight*>::const_iterator i = trafficLights.begin(); i != trafficLights.end(); i++)
    {
        if(inclusive && (*i)->getPosition() == position)
        {
            return (*i);
        }

        if((*i)->getPosition() > position)
        {
            if (nextLight == NULL || ((*i)->getPosition() - position) < (nextLight->getPosition() - position))
            {
                nextLight = (*i);
            }
        }
    }
    return nextLight;
}

BusStop* const Road::getBusStopOnPosition(unsigned int position, bool inclusive) const
{
    REQUIRE(properlyInitialised(), "Road: getBusStopOnPosition: Not properly Initialised.");
    REQUIRE(position < getLength(), "Road: getBusStopOnPosition:: Invalid position.");

    if(busStops.empty()) return NULL;

    BusStop* nextBusStop = NULL;
    for(vector<BusStop*>::const_iterator i = busStops.begin(); i != busStops.end(); i++)
    {
        if(inclusive && (*i)->getPosition() == position)
        {
            return (*i);
        }

        if((*i)->getPosition() > position)
        {
            if (nextBusStop == NULL || ((*i)->getPosition() - position) < (nextBusStop->getPosition() - position))
            {
                nextBusStop = (*i);
            }
        }
    }
    return nextBusStop;
}


unsigned int Road::getLength() const
{
    REQUIRE(properlyInitialised(), "Road: getLength: Not properly Initialised.");

    return  length;
}


const string& Road::getName() const
{
    REQUIRE(properlyInitialised(), "Road: getName: Not properly Initialised.");

    return name;
}


Road* Road::getConnection() const
{
    REQUIRE(properlyInitialised(), "Road: getConnection: Not properly Initialised.");

    return connection;
}


const int Road::getSpeedLimit() const
{
    REQUIRE(properlyInitialised(), "Road: getSpeedLimit: Not properly Initialised.");

    return speedLimit;
}


const int Road::getSpeedLimit(unsigned int pos) const
{
    REQUIRE(properlyInitialised(), "Road: getSpeedLimit: Not properly Initialised.");

    unsigned int maxPos = 0;
    int currentLimit = speedLimit;
    for(vector<Zone*>::const_iterator i = zones.begin(); i != zones.end(); i++)
    {
        if((*i)->getPosition() <= pos && (*i)->getPosition() >= maxPos)
        {
            maxPos = (*i)->getPosition();
            currentLimit = (*i)->getNewSpeedLimit();
        }
    }
    return currentLimit;
}


const vector<Lane*>& Road::getLanes() const
{
    REQUIRE(properlyInitialised(), "Road: getLanes: Not properly Initialised.");
    return lanes;
}


/** Lane functions ---------------------------------------------- **/

Lane::Lane(Road* parentRoad, int order) :
    parentRoad(parentRoad),
    order(order)
    {}


void Lane::addVehicle(Vehicle* newVehicle)
{
    REQUIRE(newVehicle->properlyInitialised(), "Vehicle is not properly initialised, thus we're unable to alter state.");
    REQUIRE(calculateRemainingSpace() > newVehicle->getLen(), "Too many vehicles are already present on the Road for there to be added more.");

    vehicles.push_front(newVehicle);

    ENSURE(*vehicles.begin() == newVehicle, "Lanes: addVehicle: adding vehicle failed");
}


void Lane::removeVehicle(Vehicle* vehicToRemove)
{
    for(list<Vehicle *>::iterator i = vehicles.begin(); i != vehicles.end(); i++)
    {
        if((*i) == vehicToRemove)
        {
            vehicles.erase(i);
            break;
        }
    }
    ENSURE(!getVehicle(vehicToRemove->getLicensePlate()), "Vehicle removal unsuccessful");
}


unsigned int Lane::calculateRemainingSpace() const
{
    unsigned int remainingSpace = parentRoad->getLength();
    for (list<Vehicle*>::const_iterator i = vehicles.begin(); i != vehicles.end(); i++)
    {
        remainingSpace = remainingSpace - ((*i)->getLen() + minimumSpace);

        if (remainingSpace <= 0)
        {
            return 0;
        }
    }
    return remainingSpace;
}


bool Lane::isFree() const
{
    return vehicles.empty();
}


Vehicle* const Lane::getCarOnPosition(unsigned int position, bool inclusive) const
{
    if(vehicles.empty())
    {
        return NULL;
    }

    Vehicle* nextVehic = NULL;
    for(list<Vehicle*>::const_iterator i = vehicles.begin(); i != vehicles.end(); i++)
    {
        if(inclusive && (*i)->getPosition() == position)
        {
            return (*i);
        }

        if((*i)->getPosition() > position)
        {
            if (nextVehic == NULL || ((*i)->getPosition() - position) < (nextVehic->getPosition() - position))
            {
                nextVehic = (*i);
            }
        }
    }
    return nextVehic;
}


bool Lane::checkIfClosest(const Vehicle &vehicToCheck, unsigned int position) const
{
    for (list<Vehicle*>::const_iterator i = vehicles.begin(); i != vehicles.end(); i++)
    {
        if ((position - (*i)->getPosition()) < (position - vehicToCheck.getPosition()) )
        {
            return false;
        }
    }
    return true;
}


Vehicle* const Lane::getVehicle(string licensePlate) const
{
    for (list<Vehicle*>::const_iterator i = vehicles.begin(); i != vehicles.end(); i++)
    {
        if((*i)->getLicensePlate() == licensePlate)
        {
            return (*i);
        }
    }
    return NULL;
}


const list<Vehicle*>& Lane::getVehicles() const
{
    return vehicles;
}


Road* const Lane::getParentRoad() const
{
    return parentRoad;
}


Lane* const Lane::getConnectingLane() const
{
    if(parentRoad->getConnection() == NULL) return NULL;
    return parentRoad->getConnection()->getLanes()[order];
}
