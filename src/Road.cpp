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
Road::Road(string name, int length, int maxSpeed, RoadSystem* environment) :

    name(name),
    length(length),
    maximumSpeed(maxSpeed),
    environment(environment)
{
    ENSURE(properlyInitialised(), "Constructor failed");
}

    /***********************
     *    ~Destructor~    *
     ***********************/

/** ---------------------------------------------------------------------
 *  ~Road
 *
 *  Postcondition:
 *      All references of this Road are deleted.
 *
 --------------------------------------------------------------------- */
Road::~Road()
{
    if (environment == NULL) return;
    
    environment->removeRoad(this);
    
    for (vector<Road*>::const_iterator i = environment->getVectorOfRoads().begin(); i != environment->getVectorOfRoads().end(); i++)
    {
        for (vector<Road*>::const_iterator ii = (*i)->getConnections().begin(); ii != environment->getVectorOfRoads().end(); ii++) {
            if (*ii == this) {
                (*i)->connections.erase(ii);
                continue;
            }
        }
    }
    
    for (list<Vehicle*>::iterator i = vehicles.begin(); i != vehicles.end(); i++)
    {
        delete *i;
    }
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
    REQUIRE(properlyInitialised(), "Road is not properly initialised, thus we're unable to alter state.");
    REQUIRE(newConnection->properlyInitialised(), "Road is not properly initialised, thus we're unable to alter state.");

    connections.push_back(newConnection);

    ENSURE(connections[connections.size() - 1] == newConnection, "Function failed.");
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
int Road::getLength() const
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
 *      subjected  Roads must be properly initialised and collection of roads must not be empty.
 *
 --------------------------------------------------------------------- */
const vector<Road*>& Road::getConnections() const
{
    REQUIRE(properlyInitialised(), "Road is not empty, thus we're unable to retrieve current state right now.");
    REQUIRE(!connections.empty(), "Can't get connections if there aren't any.");

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


/* ---------------------------------------------------------------------
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
    
    if (connections.size() == 0) return NULL;
    
    return connections[0];
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
        }
    }

    ENSURE(!getVehicle(vehicToRemove->getLicensePlate()), "Removal unsuccessful");
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
int Road::remainingSpace() const
{
    REQUIRE(properlyInitialised(), "Road must be properly initialised to execute function.");

    int remainingSpace = length;
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
 *      Road object may not have been altered
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

    for(list<Vehicle*>::const_iterator i = vehicles.begin(); i != vehicles.end(); i++)
    {
        if( (*i)->getPosition() > position && !inclusive)
        {
            return (*i);
        }

        if( (*i)->getPosition() >= position && inclusive )
        {
            return (*i);
        }
    }

    return NULL;
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

    if( name.size() <= 0 )
    {
        return false;
    }

    if( maximumSpeed <= 0 )
    {
        return false;
    }

    return true;
}

int Road::getMaximumSpeed() const
{
    return maximumSpeed;
}
