//
// Created by Joren Van Borm & Lenny Bontenakel
//

#include "Car.h"

///--- global variables (definitions) ---///
extern const int stdCarLength = 300;

extern const VehicleLimits stdCarLimits(-8, 2, 0, 150);


///--- Car ---///
Car::Car() : Vehicle::Vehicle() {}

Car::Car(RoadSystem* environment, const string& licensePlate, Road* currentRoad) :
        Vehicle::Vehicle(environment, licensePlate, stdCarLength, &stdCarLimits, currentRoad) {}

Car::Car(RoadSystem* environment, const string& licensePlate, Road* currentRoad, int acceleration, int speed, int position) :
        Vehicle::Vehicle(environment, licensePlate, stdCarLength, &stdCarLimits, currentRoad, acceleration, speed, position) {}