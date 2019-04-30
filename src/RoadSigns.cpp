/* created by Van Borm Joren & Bontenakel Lenny
 */

#include "RoadSigns.h"
#include "Road.h"
#include "design_by_contract.h"

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
TrafficLight::TrafficLight(unsigned int position, Road *road, unsigned long offset, unsigned long activeTime) :
RoadSign::RoadSign(trafficLight, position, road),
redTime(30),
orangeTime(5),
greenTime(30),
offset(offset)
{
    updateState(activeTime);
}


Color TrafficLight::getState() const
{
    REQUIRE(properlyInitialised(), "TrafficLight: getState: Not properly initialised.");
    return state;
}


void TrafficLight::updateState(unsigned long activeTime)
{
    REQUIRE(properlyInitialised(), "TrafficLight: updateState: Not properly initialised.");

    unsigned long cycleDuration = redTime + orangeTime + greenTime;
    unsigned long currentCycleTime = (activeTime + offset) % cycleDuration;

    if(currentCycleTime < greenTime) state = green;
    else if(currentCycleTime < greenTime + orangeTime) state = orange;
    else state = red;
}


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