//
// Created by Joren Van Borm & Lenny Bontenakel
//

#include "Vehicle.h"

Vehicle::Vehicle() : selfPtr(NULL) {}

Vehicle::Vehicle(RoadSystem* environment, const string& licensePlate, Road* currentRoad) :
                 licensePlate(licensePlate),
                 currentRoad(currentRoad),
                 acceleration(0),
                 speed(0),
                 position(0),
                 environment(environment),
                selfPtr(this) {}

Vehicle::Vehicle(RoadSystem* environment, const string& licensePlate, Road* currentRoad, double acceleration, double speed,
                 double position) :
                 licensePlate(licensePlate),
                 currentRoad(currentRoad),
                 acceleration(acceleration),
                 speed(speed),
                 position(position),
                 environment(environment),
                 selfPtr(this) {}
