/* created by Van Borm Joren & Bontenakel Lenny
 */

#ifndef LNJPSE_PROJECT_ROADSIGNS_H
#define LNJPSE_PROJECT_ROADSIGNS_H

class Road;

enum Type {busStop, zoneStart, trafficLight};

class RoadSign
{
public:

    RoadSign(Type type, unsigned int position, Road* road);
/** ---------------------------------------------------------------------
 * RoadSign
 *
 *  Postcondition:
 *      RoadSign is properly initialised.
 --------------------------------------------------------------------- */


    bool properlyInitialised() const;
/** ---------------------------------------------------------------------
 * properlyInitialised
 *
 --------------------------------------------------------------------- */

    Type getType() const;
/** ---------------------------------------------------------------------
 * getType
 *
 *  Precondition:
 *      RoadSign properly initialised.
 --------------------------------------------------------------------- */


    const unsigned int getPosition() const;
/** ---------------------------------------------------------------------
 * getPosition
 *
 *  Precondition:
 *      RoadSign properly initialised.
 --------------------------------------------------------------------- */


    Road* const getRoad() const;
/** ---------------------------------------------------------------------
 * getRoad
 *
 *  Precondition:
 *      RoadSign properly initialised.
 --------------------------------------------------------------------- */


protected:

    Type type;
    unsigned int position;
    Road* road;
};



// Zone ----------------------------------------------------------------------
class Zone : public RoadSign
{
public:
    Zone(unsigned int position, Road* road, int newSpeedLimit);

    const int getNewSpeedLimit() const;


private:
    const int newSpeedLimit;
};



// TrafficLight --------------------------------------------------------------
enum Color {orange, red, green};

class TrafficLight : public RoadSign
{
public:
    TrafficLight(unsigned int position, Road* road, unsigned long offset, unsigned long activeTime = 0);

    Color getState() const;

    void updateState(unsigned long activeTime);


private:
    Color state;
    unsigned long redTime;
    unsigned long orangeTime;
    unsigned long greenTime;
    unsigned long offset;
};

// BusStop -------------------------------------------------------------------
class BusStop : public RoadSign
{
public:
    BusStop(unsigned int position, Road* road, bool rainProtection = true);

    bool doesItProtecc();


private:
    bool rainProtection;
};

#endif //LNJPSE_PROJECT_ROADSIGNS_H
