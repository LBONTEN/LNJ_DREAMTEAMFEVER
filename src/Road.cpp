/*      created by Van Borm Joren & Bontenakel Lenny         */

#include "Road.h"
#include "RoadSigns.h"
#include "RoadSystem.h"
#include <iostream>

extern const unsigned int minimumSpace= 2;


/*  Road functions ---------------------------------------------------- */

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


Road::Road(string name, unsigned int length, int maxSpeed, unsigned int laneCount, Road* connection) :
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
    lanes.clear();
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
    REQUIRE(properlyInitialised(), "Road is not properly initialised, unable to alter state.");
    REQUIRE(newConnection->properlyInitialised(), "Road is not properly initialised, unable to alter state.");

    connection = newConnection;

    ENSURE(connection == newConnection, "Failed setting connection.");
}


void Road::clearConnection()
{
    REQUIRE(properlyInitialised(), "Road must be properly initialised to execute function.");

    connection = NULL;
}


void Road::addSign()
{
    // TODO: fix using templates if possible
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


RoadSign* const Road::getSignOnPosition(Type type, unsigned int position, bool inclusive) const
{
    // TODO: fix using templates if possible

//    REQUIRE(properlyInitialised(), "Road: getSignOnPosition: Not properly Initialised.");
//
//    template <class T>
//    if(signs.empty())
//    {
//        return NULL;
//    }
//
//    RoadSign* nextSign = NULL;
//    for(vector<RoadSign*>::const_iterator i = signs.begin(); i != signs.end(); i++)
//    {
//        if(inclusive && (*i)->getPosition() == position)
//        {
//            return (*i);
//        }
//
//        if((*i)->getPosition() > position)
//        {
//            if (nextSign == NULL || ((*i)->getPosition() - position) < (nextSign->getPosition() - position))
//            {
//                nextSign = (*i);
//            }
//        }
//    }
//    return nextSign;
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

    int maxPos;
    int currentLimit = speedLimit;
    for(vector<Zone*>::const_iterator i = zones.begin(); i != zones.end(); i++)
    {
        if((*i)->getPosition() <= pos && (*i)->getPosition() > maxPos)
        {
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

    ENSURE(*vehicles.begin() == newVehicle, "Function failed");
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
    return parentRoad->getConnection()->getLanes()[order];
}
