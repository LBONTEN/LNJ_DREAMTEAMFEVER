/* created by Van Borm Joren & Bontenakel Lenny
 */

#include "RoadSigns.h"

/** RoadSign functions ------------------------------------------ */

RoadSign::RoadSign(const string& type, unsigned int position, Road* road) :
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


const string& RoadSign::getType() const
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
