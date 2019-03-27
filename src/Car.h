//
// Created by Joren Van Borm & Lenny Bontenakel
//

#ifndef LNJPSE_CAR_H
#define LNJPSE_CAR_H


#include "Vehicle.h"


///--- global variables (declarations) ---///

extern const int stdCarLength;

extern const VehicleLimits stdCarLimits;


///--- Classes ---///

class Car: public Vehicle {
public:
    /**
     * Default constructor
     * @RENSURE NOT properly initialised
     */
    Car();
    
    /**
     * Minimal constructor
     * Acceleration, speed and position are assumed to be 0
     * @RENSURE properly initialised
     */
    Car(RoadSystem* environment, const string& licensePlate, Road* currentRoad);
    
    /**
     * Maximal constructor
     * @RENSURE properly initialised
     */
    Car(RoadSystem* environment, const string& licensePlate, Road* currentRoad, int acceleration, int speed, int position);
    
    /**
     * Funtion purely to check pre- and postconditions
     * @REQUIRE properly initialised
     */
    virtual bool updateReady();
    
    /**
     * In case changes need to happen between preparing and updating, use this for safety
     * @REQUIRE properly initialised
     * @RENSURE update not ready
     */
    virtual void cancelPrep();
    
    /**
     * Gather the @REQUIREd information for updating
     * @REQUIRE properly initialised
     * @RENSURE update ready
     */
    virtual void prepUpdate();
    
    /**
     * Upate acceleration, speed and position (and possibly currentRoad)
     * @REQUIRE properly initialised, update prepared, simulation active
     * @RENSURE get<acc/spd/pos> is within limits, minimum distance is respected
     */
    virtual void execUpdate();

private:
    void stepAcceleration();
    void stepSpeed();
    void stepPosition();
    
    SimulationInfo snapShot;
};


#endif //LNJPSE_CAR_H
