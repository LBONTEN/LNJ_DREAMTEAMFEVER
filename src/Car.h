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
    Car(RoadSystem* environment, const string& licensePlate, Road* currentRoad, int acceleration, unsigned int speed, int position);
};


#endif //DAPIZZAPROJECT_CAR_H
