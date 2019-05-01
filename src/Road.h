/* created by Van Borm Joren & Bontenakel Lenny
 */

#include "Vehicle.h"
#include "TypedVehicles.h"
#include "RoadSigns.h"
#include "design_by_contract.h"

#include <sstream>
#include <cstring>
#include <vector>
#include <list>

class RoadSystem;
class Lane;

#ifndef LNJPSE_PROJECT_ROAD_H
#define LNJPSE_PROJECT_ROAD_H

extern const unsigned int minimumSpace;

class Road
{
public:

    Road();
/** ---------------------------------------------------------------------
 * Road
 *
 *  Postcondition:
 *      Road object is properly initialised.
 *
 --------------------------------------------------------------------- */


    Road(string name, unsigned int length, int maxSpeed, unsigned int laneCount = 1, Road* connection = NULL);
/** ---------------------------------------------------------------------
 * Road
 *
 *  IN:
 *      - name: Name to be given to the road
 *      - length: Length of the road
 *      - maximumSpeed: Speed limit allowed on the road
 *      - laneCount:  amount of lanes the road has
 *
 *  Postcondition:
 *      Road object is properly initialised.
 *
 --------------------------------------------------------------------- */


    ~Road();
/** ---------------------------------------------------------------------
 * ~Road
 *
 *  Postcondition:
 *      Road and its lanes erased.
 *
 --------------------------------------------------------------------- */


    bool properlyInitialised() const;
/** ---------------------------------------------------------------------
 * properlyInitialised
 *
 *  OUT:
 *     false when:
 *          - Length of Road may not be 0 or less
 *          - Name may not be an empty string.
 *          - speedLimit must be higher than 0
 *
 --------------------------------------------------------------------- */


    void setConnection(Road* newConnection);
/** ---------------------------------------------------------------------
 * setConnection:
 *
 *  IN:
 *      newConnection: Road to add as a connection to subjected road
 *
 *  Precondition:
 *      Both roads involved in the function must be properly initialised for proper execution.
 *
 *  Postcondition:
 *      Road's connection has been changed.
 *
 --------------------------------------------------------------------- */


    void clearConnection();
/** ---------------------------------------------------------------------
 * clearConnection:
 *
 *  IN:
 *      connectionToRemove: a pointer to the connection to the remove
 *
 *  OUT:
 *      The subjected road will have a new connection added to its list
 *
 *  Precondition:
 *      Road must be properly initialised
 *
 *  Postcondition:
 *      Road has a an extra connection added to back of vector of connection.
 *
 --------------------------------------------------------------------- */


    void addZone(Zone* newZone);
/** ---------------------------------------------------------------------
 * addZone:
 *
 *  IN:
 *      newStop: Zone to add to Road.
 *
 *  Precondition:
 *      Road must be properly initialised.
 *
 *  Postcondition:
 *      Road contains a new Zone.
 *      zones has increased by one.
 *
 --------------------------------------------------------------------- */

    void addTrafficLight(TrafficLight* newLight);
/** ---------------------------------------------------------------------
 * addBusStop:
 *
 *  IN:
 *      newLight: trafficLight to add to Road.
 *
 *  Precondition:
 *      Road must be properly initialised.
 *
 *  Postcondition:
 *      Road contains a new TrafficLight.
 *      trafficLights has increased by one.
 *
 --------------------------------------------------------------------- */


    void addBusstop(BusStop* newStop);
/** ---------------------------------------------------------------------
 * addBusStop:
 *
 *  IN:
 *      newStop: BusStop to add to Road.
 *
 *  Precondition:
 *      Road must be properly initialised.
 *
 *  Postcondition:
 *      Road contains a new BusStop.
 *      busStops has increased by one.
 *
 --------------------------------------------------------------------- */

    bool isFree() const;
/** ---------------------------------------------------------------------
 * isFree
 *
 *  OUT:
 *      True when all lanes are free.
 *
 --------------------------------------------------------------------- */

    void clearAllSigns();
/** ---------------------------------------------------------------------
 * clearAllSigns:
 *
 *  PostCondition:
 *      zones, trafficLights and busStops will be empty.
 *
 --------------------------------------------------------------------- */


    void clearZones();
/** ---------------------------------------------------------------------
 * clearZones:
 *
 *  PostCondition:
 *      zones will be empty.
 *
 --------------------------------------------------------------------- */


    void clearTrafficLights();
/** ---------------------------------------------------------------------
 * clearTrafficLights:
 *
 *  PostCondition:
 *      trafficLights will be empty.
 *
 --------------------------------------------------------------------- */


    void clearBusStops();
/** ---------------------------------------------------------------------
 * clearBusStops:
 *
 *  PostCondition:
 *      busStops will be empty.
 *
 --------------------------------------------------------------------- */


    vector<RoadSign*> getAllSigns() const;
/** ---------------------------------------------------------------------
* getAllSigns
**
*  OUT:
*      Returns concatenation of zones, trafficLights and busStops.
*
*  Precondition:
*       Road must be properly Initialised.
*
*   Postcondition:
*       No members of Road have been changed.
*
--------------------------------------------------------------------- */


    const vector<Zone*>& getZones() const;
/** ---------------------------------------------------------------------
* getZoness
*
*  OUT:
*      Returns zones
*
*  Precondition:
*       Road must be properly Initialised
*
--------------------------------------------------------------------- */


    const vector<TrafficLight*>& getTrafficLights() const;
/** ---------------------------------------------------------------------
* getAllSigns
*
*  OUT:
*      concatenation of zones, trafficLights and busStops
*
*  Precondition:
*       Road must be properly Initialised
*
--------------------------------------------------------------------- */


    const vector<BusStop*>& getBusStops() const;
/** ---------------------------------------------------------------------
* getAllSigns
*
*  OUT:
*      concatenation of zones, trafficLights and busStops
*
*  Precondition:
*       Road must be properly Initialised
*
--------------------------------------------------------------------- */


    RoadSign* const getSignOnPosition(unsigned int position, bool inclusive) const;
/** ---------------------------------------------------------------------
 * getSignOnPosition:
 *
 *  OUT:
 *      if inclusive is true:
 *          Returns RoadSign from signs on given position if there is one.
 *          Else the next one on the Road will be returned.
 *      if inclusive is false:
 *          Returns first Sign past given position.
 *      returns NULL if no signs are encountered past given position on the Road
 *      or if zones, trafficLights and busStops are empty.
 *
 *  Precondition:
 *      Road must be properly initialised.
 *
 --------------------------------------------------------------------- */


    Zone* const getZoneStartOnPosition(unsigned int position, bool inclusive) const;
/** ---------------------------------------------------------------------
 * getZoneStartOnPosition:
 *
 *  OUT:
 *      if inclusive is true:
 *          Returns ZoneStart from signs on given position if there is one.
 *          Else the next one on the Road will be returned.
 *      if inclusive is false:
 *          Returns first ZoneStart past given position.
 *      returns NULL if no ZoneStarts are encountered past given position on the Road.
 *      or if zones is empty.
 *
 *  Precondition:
 *      Road must be properly initialised.
 *
 --------------------------------------------------------------------- */


    TrafficLight* const getTrafficLightOnPosition(unsigned int position, bool inclusive) const;
/** ---------------------------------------------------------------------
 * getTrafficLightOnPosition:
 *
 *  OUT:
 *      if inclusive is true:
 *          Returns TrafficLight from signs on given position if there is one.
 *          Else the next one on the Road will be returned.
 *      if inclusive is false:
 *          Returns first TrafficLight past given position.
 *      returns NULL if no trafficLights are encountered past given position on the Road
 *      or if trafficLights is empty.
 *
 *  Precondition:
 *      Road must be properly initialised.
 *
 --------------------------------------------------------------------- */


    BusStop* const getBusStopOnPosition(unsigned int position, bool inclusive) const;
/** ---------------------------------------------------------------------
 * getBusStopOnPosition:
 *
 *  OUT:
 *      if inclusive is true:
 *          Returns BusStop from signs on given position if there is one.
 *          Else the next one on the Road will be returned.
 *      if inclusive is false:
 *          Returns first BusStop past given position.
 *      Returns NULL if no BusStops are encountered past given position on the Road
 *      or if busStops is empty.
 *
 *  Precondition:
 *      Road must be properly initialised.
 *
 --------------------------------------------------------------------- */



    unsigned int getLength() const;
/** ---------------------------------------------------------------------
 * getLength:
 *
 *  Precondition
 *      Road must be properly initialised.
 *
 --------------------------------------------------------------------- */


    const string& getName() const;
/** ---------------------------------------------------------------------
 * getName:
 *
 *  Precondition
 *      Road must be properly initialised.
 *
 --------------------------------------------------------------------- */


    Road* getConnection() const;
/** ---------------------------------------------------------------------
 * getConnection
 *
 *  OUT:
 *      returns connected road.
 *
 *  Precondition
 *      Road must be properly initialised.
 *
 --------------------------------------------------------------------- */


    const int getSpeedLimit() const;
/** ---------------------------------------------------------------------
 * getMaximumSpeed
 *
 *  OUT:
 *      returns the speed limit on current Road.
 *
 *  Precondition
 *      Road must be properly initialised.
 *
 --------------------------------------------------------------------- */


    const int getSpeedLimit(unsigned int pos) const;
/** ---------------------------------------------------------------------
 * getMaximumSpeed
 *
 *  OUT:
 *      returns the speed limit on current Road.
 *
 *  Precondition
 *      Road must be properly initialised.
 *
 --------------------------------------------------------------------- */


    const vector<Lane*>& getLanes() const;
/** ---------------------------------------------------------------------
 * getMaximumSpeed
 *
 *  OUT:
 *      returns vector of lanes .
 *
 *  Precondition
 *      Road must be properly initialised.
 *
 --------------------------------------------------------------------- */


private:
    string name;
    unsigned int length;
    const int speedLimit;
    Road* connection;
    unsigned int laneCount;
    vector<Lane*> lanes;
    vector<Zone*> zones;
    vector<TrafficLight*> trafficLights;
    vector<BusStop*> busStops;
};


class Lane
{
public:

    Lane(Road* parentRoad, int order);
/** ---------------------------------------------------------------------
 * Lane
 *
 *  Postcondition:
 *      Lane object is properly initialised.
 *
 --------------------------------------------------------------------- */


    void addVehicle(Vehicle* newVehicle);
/** ---------------------------------------------------------------------
 * addVehicle:
 *
 *  IN:
 *      newVehicle: Road to add as a connection to subjected road
 *
 *  Precondition:
 *      Vehicle must be properly initialised.
 *      Also, there must be sufficient remaining space on the Road to add a new vehicle.
 *
 *  Postcondition:
 *      A new Vehicle will be added to the back of vector containing vehicles.
 *      amount of cars on the Road has increased by one.
 *
 --------------------------------------------------------------------- */


    void removeVehicle(Vehicle* vehicToRemove);
/** ---------------------------------------------------------------------
 * removeVehicle
 *
 *  IN:
 *      pointer to vehicle to remove from list.
 *
 *  Postcondition:
 *      Vehicle object is removed from the list of vehicles.
 *
 --------------------------------------------------------------------- */


    unsigned int calculateRemainingSpace() const;
/** ---------------------------------------------------------------------
 * calculateRemainingSpace
 *
 *  OUT:
 *      int remainingSpace: an integer that indicates the amount of free space left on the Road, in centimeter.
 *
 *  Precondition:
 *      Road must be properly initialised.
 *
 --------------------------------------------------------------------- */


    bool isFree() const;
/** ---------------------------------------------------------------------
 * isFree
 *
 *  OUT:
 *      Boolean that is true when there are no vehicles on the lane.
 *
 --------------------------------------------------------------------- */


    bool checkIfClosest(const Vehicle& vehicToCheck, unsigned int position) const;
/** ---------------------------------------------------------------------
 * checkIfClosest:
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
 --------------------------------------------------------------------- */


    Vehicle* const getCarOnPosition(unsigned int position, bool inclusive) const;
/** ---------------------------------------------------------------------
 * getCarOnPosition
 *
 *  OUT:
 *     if inclusive is true:
 *          Returns Vehicle pointer from vehicles on given position if there is one.
 *          Else the next one on the Lane will be returned.
 *      if inclusive is false:
 *          Returns first vehicle past given position.
 *      returns NULL if no vehicles are encountered past given position on the Lane.
 *
 *  Precondition:
 *      Must be properly initialised
 *
 --------------------------------------------------------------------- */


    Vehicle* const getVehicle(string licensePlate) const;
/** ---------------------------------------------------------------------
 * getVehicle:
 *
 *  IN:
 *      license plate as key
 *
 *  OUT:
 *      returns vehicle with corresponding license plate.
 *
 *  Précondition:
 *      Must be properly initialised
 *
 --------------------------------------------------------------------- */


    const list<Vehicle*>& getVehicles() const;
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


    Road* const getParentRoad() const;
/** ---------------------------------------------------------------------
 * getParentRoad:
 *
 *  OUT:
 *      Pointer to parentRoad of Lane
 *
 *  Précondition:
 *      Road must be properly initialised
 *
 --------------------------------------------------------------------- */


Lane* const getConnectingLane() const;
/** ---------------------------------------------------------------------
 * getParentRoad:
 *
 *  OUT:
 *      Pointer to connecting Lane of next connecting Road
 *
 *  Précondition:
 *      Road must be properly initialised
 *
 --------------------------------------------------------------------- */


private:
    Road* parentRoad;
    list<Vehicle*> vehicles;
    int order;
};

#endif //LNJPSE_PROJECT_ROAD_H
