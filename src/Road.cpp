/*      created by Van Borm Joren & Bontenakel Lenny         */

#include "Road.h"
#include "RoadSystem.h"

extern const unsigned int minimumSpace= 200;


/*  Road functions ---------------------------------------------------- */

Road::Road()
{
    name = "";
    length = 1;
    speedLimit = 1;
    laneCount = 1;

    lanes.push_back(new Lane(this));

    ENSURE(properlyInitialised(), "Road default construction failed");
}


Road::Road(string name, unsigned int length, int maxSpeed, unsigned int laneCount) :
    name(name),
    length(length),
    speedLimit(maxSpeed),
    connection(),
    laneCount(laneCount)
{
    for(int i = 0; i < laneCount; i++)
    {
        lanes.push_back(new Lane(this));
    }

    ENSURE(properlyInitialised(), "Road construction failed");
}

Road::~Road()
{
    for(vector<Lane*>::iterator i = lanes.begin(); i != lanes.end(); i++)
    {
        delete (*i);
    }
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


bool Road::isFree() const
{
    REQUIRE(properlyInitialised(), "Road: \'isFree\': not properly initialised.");

    for(vector<Lane*>::const_iterator i = lanes.begin(); i != lanes.end(); i++)
    {
        if(!(*i)->isFree())
        {
            return false;
        }
    }
    return true;
}


unsigned int Road::getLength() const
{
    REQUIRE(properlyInitialised(), "Road must be properly initialised to execute function.");

    return  length;
}


const string& Road::getName() const
{
    REQUIRE(properlyInitialised(), "Road must be properly initialised to execute function.");

    return name;
}


Road* Road::getConnection() const
{
    REQUIRE(properlyInitialised(), "Road must be properly initialised to execute function.");

    return connection;
}


int Road::getSpeedLimit() const
{
    REQUIRE(properlyInitialised(), "Road must be properly initialised to execute function.");

    return speedLimit;
}


const vector<Lane*>& Road::getLanes() const
{
    REQUIRE(properlyInitialised(),"Road must be properly initialised.");
    return lanes;
}


/*  Lane functions ---------------------------------------------- */

Lane::Lane(const Road* parentRoad) :
    parentRoad(parentRoad)
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


Vehicle* Lane::getCarOnPosition(unsigned int position, bool inclusive) const
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
            if(nextVehic == NULL)
            {
                nextVehic = (*i);
            }
            else if (((*i)->getPosition() - position) < (nextVehic->getPosition() - position))
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


Vehicle* Lane::getVehicle(string licensePlate) const
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
