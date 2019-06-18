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
 *  ENSURE(properlyInitialised(), "Road default construction failed");
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
 *  ENSURE(properlyInitialised(), "Road construction failed");
 --------------------------------------------------------------------- */


    ~Road();


    bool properlyInitialised() const;
/** ---------------------------------------------------------------------
 * properlyInitialised
 *
 *  OUT:
 *     false when:
 *          - Length of Road may not be 0 or less
 *          - Name may not be an empty string.
 *          - speedLimit must be higher than 0
 --------------------------------------------------------------------- */


    void setConnection(Road* newConnection);
/** ---------------------------------------------------------------------
 * setConnection:
 *
 *  IN:
 *      newConnection: Road to add as a connection to subjected road
 *
 *  REQUIRE(properlyInitialised(), "Road: setConnection: Not properly initialised.");
 *  REQUIRE(newConnection->properlyInitialised(), "Road: setConnection: newConnection not properly initialised.");
 *
 *  ENSURE(connection == newConnection, "Road: setConnection: Failed setting connection.");
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
 *  REQUIRE(properlyInitialised(), "Road: clearConnection: Not properly initialised.");
 *
 *  ENSURE(connection == NULL, "Road: setConnection: Failed clearing connection.");
 --------------------------------------------------------------------- */


    void addZone(Zone* newZone);
/** ---------------------------------------------------------------------
 * addZone:
 *
 *  IN:
 *      newStop: Zone to add to Road.
 *
 *  REQUIRE(properlyInitialised(), "Road: addZone: Not properly initialised.");
 *
 *  ENSURE(zones.size() == oldSize + 1, "Road: addZone: adding zone failed.");
 --------------------------------------------------------------------- */

    void addTrafficLight(TrafficLight* newLight);
/** ---------------------------------------------------------------------
 * addBusStop:
 *
 *  IN:
 *      newLight: trafficLight to add to Road.
 *
 *  REQUIRE(properlyInitialised(), "Road: addTrafficLight: Not properly initialised.");
 *
 *  ENSURE(getTrafficLights().size() == oldSize + 1, "Road: addTrafficLight: adding trafficlight failed.");
 --------------------------------------------------------------------- */


    void addBusstop(BusStop* newStop);
/** ---------------------------------------------------------------------
 * addBusStop:
 *
 *  IN:
 *      newStop: BusStop to add to Road.
 *
 *  REQUIRE(properlyInitialised(), "Road: addBusStop: Not properly initialised.");
 *
 *  ENSURE(getBusStops().size() == oldSize + 1, "Road: addBusStop: adding busstp failed.");
 --------------------------------------------------------------------- */

    bool isFree() const;
/** ---------------------------------------------------------------------
 * isFree
 *
 *  OUT:
 *      True when all lanes are free.
 --------------------------------------------------------------------- */

    void clearAllSigns();
/** ---------------------------------------------------------------------
 * clearAllSigns:
 *
 *  ENSURE(getZones().empty(), "Road: clearZones: zones has not been emptied.");
 *  ENSURE(getTrafficLights().empty(), "Road: clearTrafficLights: trafficLights has not been empties.");
 *  ENSURE(getBusStops().empty(), "busStops has not been emptied.");
 --------------------------------------------------------------------- */


    void clearZones();
/** ---------------------------------------------------------------------
 * clearZones:
 *
 *  ENSURE(getZones().empty(), "Road: clearZones: zones has not been emptied.");
 --------------------------------------------------------------------- */


    void clearTrafficLights();
/** ---------------------------------------------------------------------
 * clearTrafficLights:
 *
 *  ENSURE(getTrafficLights().empty(), "Road: clearTrafficLights: trafficLights has not been empties.");
 --------------------------------------------------------------------- */


    void clearBusStops();
/** ---------------------------------------------------------------------
 * clearBusStops:
 *
 *  ENSURE(getBusStops().empty(), "busStops has not been emptied.");
 --------------------------------------------------------------------- */


    vector<RoadSign*> getAllSigns() const;
/** ---------------------------------------------------------------------
* getAllSigns
**
*  OUT:
*      Returns concatenation of zones, trafficLights and busStops.
*
*  REQUIRE(properlyInitialised(), "Road: getAllSigns: Not properly initialised.");
*
*  ENSURE(zonesSize == getZones().size(), "Road: getAllSigns: Zones have been changed");
*  ENSURE(trafficLightsSize == getTrafficLights().size(), "Road: getAllSigns: Traffic lights have been changed");
*  ENSURE(busStopsSize == getBusStops().size(), "Road: getAllSigns: Bus stops have been changed");
--------------------------------------------------------------------- */


    const vector<Zone*>& getZones() const;
/** ---------------------------------------------------------------------
* getZoness
*
*  OUT:
*      Returns zones
*
*  REQUIRE(properlyInitialised(), "Road: getZones: Not properly initialised.");
*
*  ENSURE(zonesSize == getZones().size(), "Road: getAllSigns: Zones have been changed");
--------------------------------------------------------------------- */


    const vector<TrafficLight*>& getTrafficLights() const;
/** ---------------------------------------------------------------------
* getAllSigns
*
*  OUT:
*      concatenation of zones, trafficLights and busStops
*
*  REQUIRE(properlyInitialised(), "Road: getTrafficLights: Not properly initialised.");
*
*  ENSURE(trafficLightsSize == getTrafficLights().size(), "Road: getAllSigns: Traffic lights have been changed");
--------------------------------------------------------------------- */


    const vector<BusStop*>& getBusStops() const;
/** ---------------------------------------------------------------------
* getAllSigns
*
*  OUT:
*      concatenation of zones, trafficLights and busStops
*
*  REQUIRE(properlyInitialised(), "Road: getBusStops: Not properly initialised.");
*
*  ENSURE(busStopsSize == getBusStops().size(), "Road: getAllSigns: Bus stops have been changed");
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
 *  REQUIRE(properlyInitialised(), "Road: getSignOnPosition: Not properly Initialised.");
 *  REQUIRE(position < getLength(), "Road: getSignOnPosition:: Invalid position.");
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
 *  REQUIRE(properlyInitialised(), "Road: getZoneStartOnPosition: Not properly Initialised.");
 *  REQUIRE(position < getLength(), "Road: getZoneStartOnPosition:: Invalid position.");
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
 *  REQUIRE(properlyInitialised(), "Road: getTrafficLightOnPosition: Not properly Initialised.");
 *  REQUIRE(position < getLength(), "Road: getTrafficLightOnPosition:: Invalid position.");
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
 *  REQUIRE(properlyInitialised(), "Road: getBusStopOnPosition: Not properly Initialised.");
 *  REQUIRE(position < getLength(), "Road: getBusStopOnPosition:: Invalid position.");
 --------------------------------------------------------------------- */



    unsigned int getLength() const;
/** ---------------------------------------------------------------------
 * getLength:
 *
 *  REQUIRE(properlyInitialised(), "Road: getLength: Not properly Initialised.");
 --------------------------------------------------------------------- */


    const string& getName() const;
/** ---------------------------------------------------------------------
 * getName:
 *
 *  REQUIRE(properlyInitialised(), "Road: getName: Not properly Initialised.");
 --------------------------------------------------------------------- */


    Road* getConnection() const;
/** ---------------------------------------------------------------------
 * getConnection
 *
 *  OUT:
 *      returns connected road.
 *
 *  REQUIRE(properlyInitialised(), "Road: getConnection: Not properly Initialised.");
 --------------------------------------------------------------------- */


    const int getSpeedLimit() const;
/** ---------------------------------------------------------------------
 * getMaximumSpeed
 *
 *  OUT:
 *      returns the speed limit on current Road.
 *
 *  REQUIRE(properlyInitialised(), "Road: getSpeedLimit: Not properly Initialised.");
 --------------------------------------------------------------------- */


    const int getSpeedLimit(unsigned int pos) const;
/** ---------------------------------------------------------------------
 * getMaximumSpeed
 *
 *  OUT:
 *      returns the speed limit on current Road.
 *
 *  REQUIRE(properlyInitialised(), "Road: getSpeedLimit: Not properly Initialised.");
 --------------------------------------------------------------------- */


    const vector<Lane*>& getLanes() const;
/** ---------------------------------------------------------------------
 * getMaximumSpeed
 *
 *  OUT:
 *      returns vector of lanes .
 *
 *  REQUIRE(properlyInitialised(), "Road: getLanes: Not properly Initialised.");
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

    
    void addVehicle(Vehicle* newVehicle);
/** ---------------------------------------------------------------------
 * addVehicle:
 *
 *  IN:
 *      newVehicle: Road to add as a connection to subjected road
 *
 *  REQUIRE(newVehicle->properlyInitialised(), "Vehicle is not properly initialised, thus we're unable to alter state.");
 *  REQUIRE(calculateRemainingSpace() > newVehicle->getLen(), "Too many vehicles are already present on the Road for there to be added more.");
 *
 *  ENSURE(*vehicles.begin() == newVehicle, "Lanes: addVehicle: adding vehicle failed");
 --------------------------------------------------------------------- */


    void removeVehicle(Vehicle* vehicToRemove);
/** ---------------------------------------------------------------------
 * removeVehicle
 *
 *  IN:
 *      pointer to vehicle to remove from list.
 *
 *  ENSURE(!getVehicle(vehicToRemove->getLicensePlate()), "Vehicle removal unsuccessful");
 --------------------------------------------------------------------- */


    unsigned int calculateRemainingSpace() const;
/** ---------------------------------------------------------------------
 * calculateRemainingSpace
 *
 *  OUT:
 *      int remainingSpace: an integer that indicates the amount of free space left on the Road, in centimeter.
 --------------------------------------------------------------------- */


    bool isFree() const;
/** ---------------------------------------------------------------------
 * isFree
 *
 *  OUT:
 *      Boolean that is true when there are no vehicles on the lane.
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
 --------------------------------------------------------------------- */


    const list<Vehicle*>& getVehicles() const;
/** ---------------------------------------------------------------------
 * getVehicles:
 *
 *  OUT:
 *      A reference to the vehicles vector in Road object
 --------------------------------------------------------------------- */


    Road* const getParentRoad() const;
/** ---------------------------------------------------------------------
 * getParentRoad:
 *
 *  OUT:
 *      Pointer to parentRoad of Lane
 --------------------------------------------------------------------- */


Lane* const getConnectingLane() const;
/** ---------------------------------------------------------------------
 * getParentRoad:
 *
 *  OUT:
 *      Pointer to connecting Lane of next connecting Road
 --------------------------------------------------------------------- */


private:
    Road* parentRoad;
    list<Vehicle*> vehicles;
    int order;
};

#endif //LNJPSE_PROJECT_ROAD_H
