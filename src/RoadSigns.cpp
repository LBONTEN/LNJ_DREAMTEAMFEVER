/* created by Van Borm Joren & Bontenakel Lenny
 */

#include "RoadSigns.h"

/** RoadSign functions ------------------------------------------ */

RoadSign::RoadSign(Type type, unsigned int position, Road* road) :
    type(type),
    position(position),
    road(road)
{
    ENSURE(properlyInitialised(), "RoadSign: RoadSign: Construction failed.");
}


bool RoadSign::properlyInitialised() const
{
    if(position > road->getLength()) return false;

    return true;
}


Type RoadSign::getType() const
{
    REQUIRE(properlyInitialised(), "RoadSign: getType: Not properly Initialised.");
    return type;
}


 const unsigned int RoadSign::getPosition() const
 {
    REQUIRE(properlyInitialised(), "RoadSign: getPosition: Not properly Initialised.");
    return position;
 }


 Road*const RoadSign::getRoad() const
 {
    REQUIRE(properlyInitialised(), "RoadSign: getRoad: Not properly Initialised.");
    return road;
 }


/** Zone functions ---------------------------------------------- */

Zone::Zone(unsigned int position, Road *road, int newSpeedLimit) :
    RoadSign::RoadSign(zoneStart, position, road),
    newSpeedLimit(newSpeedLimit)
{}

const int Zone::getNewSpeedLimit() const
{
    REQUIRE(properlyInitialised(), "Zone: getNewSpeedLimit: Not properly initialised.");
    return newSpeedLimit;
}


/** TrafficLight functions ------------------------------------- */
TrafficLight::TrafficLight(unsigned int position, Road *road) :
    RoadSign::RoadSign(trafficLight, position, road),
    state(red)
{}

/** BusStop functions  ----------------------------------------- */
BusStop::BusStop(unsigned int position, Road *road, bool rainProtection) :
    RoadSign::RoadSign(busStop, position, road),
    rainProtection(rainProtection)
{}

bool BusStop::doesItProtecc()
{
    REQUIRE(properlyInitialised(), "hi");
    return rainProtection;
}