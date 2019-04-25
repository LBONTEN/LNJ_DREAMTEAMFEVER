/*      created by Van Borm Joren & Bontenakel Lenny         */

#include "Road.h"
#include "RoadSystem.h"

extern const unsigned int minimumSpace= 200;

    /***********************
     *    ~Constructor~    *
     ***********************/

/** ---------------------------------------------------------------------
 * Road
 *
 *  Postcondition:
 *      Road object is properly initialised.
 --------------------------------------------------------------------- */
Road::Road(string name, unsigned int length, unsigned int maxSpeed, RoadSystem* environment) :
    // environment(environment),
    name(name),
    length(length),
    maximumSpeed(maxSpeed)
{
    ENSURE(properlyInitialised(), "Constructor failed");
}


    /*******************
     *    ~Setters~    *
     *******************/


/** ---------------------------------------------------------------------
 * setConnection:
 *
 *  IN:
 *      newConnection: Road to add as a connection to subjected road
 *
 *  OUT:
 *      The subjected road will have a new connection added to its list
 *
 *  Precondition:
 *      Both roads involved in the function must be properly initialised for proper execution.
 *
 *  Postcondition:
 *      Road has a an extra connection added to back of vector of connection.
 *
 --------------------------------------------------------------------- */
void Road::setConnection(Road* newConnection)
{
    REQUIRE(properlyInitialised(), "Road is not properly initialised, unable to alter state.");
    REQUIRE(newConnection->properlyInitialised(), "Road is not properly initialised, unable to alter state.");

    connections.push_back(newConnection);

    ENSURE(connections[connections.size() - 1] == newConnection, "Failed setting connection.");
}

/** ---------------------------------------------------------------------
 * setVehicle:
 *
 *  IN:
 *      newVehicle: Road to add as a connection to subjected road
 *
 *  Precondition:
 *      The Road and vehicle involved in the function must be properly initialised for proper execution.
 *      Also, there must be sufficient remaining space on the Road to add a new vehicle.
 *
 *  Postcondition:
 *      A new Vehicle will be added to the back of vector containing vehicles.
 *      amount of cars on the Road has increased by one.
 *
 --------------------------------------------------------------------- */
void Road::addVehicle(Vehicle* newVehicle)
{
    REQUIRE(properlyInitialised(), "Road is not properly initialised, thus we're unable to alter state.");
    REQUIRE(newVehicle->properlyInitialised(), "Vehicle is not properly initialised, thus we're unable to alter state.");
    REQUIRE(remainingSpace() > newVehicle->getLen(), "Too many vehicles are already present on the Road for there to be added more.");

    vehicles.push_front(newVehicle);

    ENSURE(*vehicles.begin() == newVehicle, "Function failed");
}


    /*******************
     *    ~Getters~    *
     *******************/


/** ---------------------------------------------------------------------
 * getLength:
 *
 *  Précondition:
 *      A properly initialised road.
 *
 *  Postcondition:
 *      State of Road must remain the same before and after function.
 *
 --------------------------------------------------------------------- */
unsigned int Road::getLength() const
{
    REQUIRE(properlyInitialised(), "Road is not properly initialised, thus we're unable to retrieve state.");

    return  length;
}


/* ---------------------------------------------------------------------
 * getName:
 *
 *  Précondition:
 *      A properly initialised road.
 *
 *  Postcondition:
 *      State of Road must remain the same before and after function.
 *
 --------------------------------------------------------------------- */
const string& Road::getName() const
{
    REQUIRE(properlyInitialised(), "Road is not properly initialised, thus we're unable to retrieve state.");

    return name;
}


/** ---------------------------------------------------------------------
 * getConnections:
 *
 *  OUT:
 *      All roads connected to subjected road.
 *
 *  Précondition:
 *      subjected road must be properly initialised.
 *
 --------------------------------------------------------------------- */
const vector<Road*>& Road::getConnections() const
{
    REQUIRE(properlyInitialised(), "Road is not empty, thus we're unable to retrieve current state right now.");

    return connections;
}


/** ---------------------------------------------------------------------
 * getVehicles:
 *
 *  OUT:
 *      A reference to the vehicles vector in Road object
 *
 *  Précondition:
 *      Road must be properly initialised
 *
 --------------------------------------------------------------------- */
const list<Vehicle*>& Road::getVehicles() const
{
    REQUIRE(properlyInitialised(), "Road is not empty, thus we're unable to retrieve current state right now.");

    return vehicles;
}


/** ---------------------------------------------------------------------
 * getConnection
 *
 *  OUT:
 *      returns the first road connection on index.
 *
 *  Précondition:
 *      Must be properly initialised
 *
 *  Postcondition:
 *      Road may not be altered
 *
 --------------------------------------------------------------------- */
Road* Road::getConnection() const
{
    REQUIRE(properlyInitialised(), "Road must be properly initialised.");

    if (connections.empty()) return NULL;

    return connections[0];
}

/** ---------------------------------------------------------------------
 * getMaximumSpeed
 *
 *  OUT:
 *      returns maximum speed of current Road.
 *
 *  Précondition:
 *      Must be properly initialised
 *
 *  Postcondition:
 *      Road may not be altered
 *
 --------------------------------------------------------------------- */
int Road::getMaximumSpeed() const
{
    REQUIRE(properlyInitialised(), "Road must be properly initialised.");

    return maximumSpeed;
}

/** ---------------------------------------------------------------------
 * getVehicle:
 *
 *  IN:
 *      license plate as key
 *
 *  OUT:
 *      returns the first road connection on index.
 *
 *  Précondition:
 *      Must be properly initialised
 *
 *  Postcondition:
 *      Road may not be altered
 *
 --------------------------------------------------------------------- */
Vehicle* Road::getVehicle(string licensePlate) const
{
    REQUIRE(properlyInitialised(), "Road must be properly initialised.");

    for (list<Vehicle*>::const_iterator i = vehicles.begin(); i != vehicles.end(); i++)
    {
        if((*i)->getLicensePlate() == licensePlate)
        {
            return (*i);
        }
    }
    return NULL;
}


    /*************************
    *    ~Public members~    *
    **************************/

/** ---------------------------------------------------------------------
 * removeVehicle
 *
 *  IN:
 *      pointer to vehicle to remove from list.
 *
 *  Précondition:
 *      Road object must be properly initialised.
 *
 *  Postcondition:
 *      Vehicle object is removed from the list of vehicles.
 *
 --------------------------------------------------------------------- */
void Road::removeVehicle(const Vehicle *vehicToRemove)
{
    REQUIRE(properlyInitialised(), "Road object must be properly initialised to execute function.");

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


/** ---------------------------------------------------------------------
 *  removeConnection:
 *
 *  IN:
 *      pointer to road to remove
 *
 *  Precondition:
 *      Road must be properly initialised
 *
 *  Postcondition:
 *      Input road will no longer be a connection.
 --------------------------------------------------------------------- */
void Road::removeConnection(const Road *connectionToRemove)
{
    REQUIRE(properlyInitialised(), "Road must be properly initialised to execute function.");

    for(long unsigned int i = 0; i < connections.size(); i++)
    {
        if(connections[i] == connectionToRemove)
        {
            connections.erase(connections.begin() + i -1);
        }
    }
}


/** ---------------------------------------------------------------------
 * remainingSpace
 *
 *  OUT:
 *      int remainingSpace: an integer that indicates the amount of free space left on the Road, in centimeter.
 *
 *  Précondition:
 *      Road must be properly initialised
 *
 *  Postcondition:
 *      No alterations may have occured to the Road object.
 *
 --------------------------------------------------------------------- */
unsigned int Road::remainingSpace() const
{
    REQUIRE(properlyInitialised(), "Road must be properly initialised to execute function.");

    unsigned int remainingSpace = length;
    for (list<Vehicle*> :: const_iterator i = vehicles.begin(); i != vehicles.end(); i++)
    {
        remainingSpace = remainingSpace - ((*i)->getLen() + minimumSpace);

        if (remainingSpace <= 0)
        {
            return 0;
        }
    }
    return remainingSpace;
}


/** ---------------------------------------------------------------------
 * isFree
 *
 *  OUT:
 *      Boolean that is true when there are no vehicles on the Road.
 *
 *  Précondition:
 *      Road must be properly initialised to start function.
 *
 *  Postcondition:
 *      Roaad remains unchanged
 *
 --------------------------------------------------------------------- */
bool Road::isFree() const
{
    REQUIRE(properlyInitialised(), "Road must be properly initialised to execute function");

    return vehicles.empty();
}


/** ---------------------------------------------------------------------
 * getCarOnPosition
 *
 *  OUT:
 *      Returns a car on a certain position.
 *
 *  Précondition:
 *      Must be properly initialised
 *
 *  Postcondition:
 *      Object remains unchanged.
 *
 --------------------------------------------------------------------- */
Vehicle* Road::getCarOnPosition(unsigned int position, bool inclusive) const
{
    REQUIRE(properlyInitialised(), "Road must be properly initialised to execute function");

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


/** ---------------------------------------------------------------------
 * checkifClosest:
 *
 * IN:
 *      - Vehicle on which the check is performed
 *      - Position that subjected vehicle should be closest to.
 *
 *  OUT:
 *      true when the car given in input is the closest to the given position on the road.
 *
 *  Precondition:
 *      Road should be properly initialised
 *
 *  Postcondition:
 *      Road remains unchanged.
 *
 --------------------------------------------------------------------- */
bool Road::checkIfClosest(const Vehicle &vehicToCheck, unsigned int position) const
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

/* ---------------------------------------------------------------------
 * properlyInitialised
 *
 *  OUT:
 *     false when:
 *          - Length of Road may not be 0 or less
 *          - Name may not be an empty string.
 *          - maximumSpeed must be greater than 0
 *
 --------------------------------------------------------------------- */
bool Road::properlyInitialised() const
{
    if ( length <= 0 )
    {
        return false;
    }

    if( name.empty() )
    {
        return false;
    }

    if( maximumSpeed <= 0 )
    {
        return false;
    }

    return true;
}

