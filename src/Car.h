//
// Created by Joren Van Borm & Lenny Bontenakel
//

#ifndef DAPIZZAPROJECT_CAR_H
#define DAPIZZAPROJECT_CAR_H


#include "Vehicle.h"


///--- global variables (declarations) ---///

extern const int stdCarLength;

extern const VehicleLimits stdCarLimits;


///--- Classes ---///

class Car: public Vehicle {
public:
    /**
     * Default constructor
     * ENSURE NOT properly initialised
     */
    Car();
    
    /**
     * Minimal constructor
     * Acceleration, speed and position are assumed to be 0
     * ENSURE properly initialised
     */
    Car(RoadSystem* environment, const string& licensePlate, Road* currentRoad);
    
    /**
     * Maximal constructor
     * ENSURE properly initialised
     */
    Car(RoadSystem* environment, const string& licensePlate, Road* currentRoad, int acceleration, int speed, int position);
    
    /**
     * Funtion purely to check pre- and postconditions
     * REQUIRE properly initialised
     */
    bool updateReady();
    
    /**
     * In case changes need to happen between preparing and updating, use this for safety
     * REQUIRE properly initialised
     * ENSURE update not ready
     */
    void cancelPrep();
    
    /**
     * Gather the required information for updating
     * REQUIRE properly initialised
     * ENSURE update ready
     */
    virtual void prepUpdate();
    
    /**
     * Upate acceleration, speed and position (and possibly currentRoad)
     * REQUIRE properly initialised, update prepared, simulation active
     * ENSURE get<acc/spd/pos> is within limits, minimum distance is respected
     */
    virtual void execUpdate();

private:
    void stepAcceleration();
    void stepSpeed();
    void stepPosition();
    
    SimulationInfo snapShot;
};


#endif //DAPIZZAPROJECT_CAR_H
