//
// Created by Joren Van Borm on 2019-04-26.
//

#include "CarLike.h"
#include "Road.h"
#include "RoadSystem.h"
#include "design_by_contract.h"

/*
///--- global variables (definitions) ---///

extern const unsigned int stdMotorCycleLength = 1;
extern const VehicleLimits stdMotorCycleLimits(-10, 4, 0, 50);

extern const unsigned int stdCarLength = 3;
extern const VehicleLimits stdCarLimits(-8, 2, 0, 42);

extern const unsigned int stdTruckLength = 15;
extern const VehicleLimits stdTruckLimits(-6, 1, 0, 25);
*/

///--- CarLike ---///
CarLike::CarLike() : Vehicle::Vehicle()
{
    typeName = "Car";
    
    ENSURE(typeName == "Car", "CarLike default constructor failed to set typeName");
}

CarLike::CarLike(RoadSystem* environment, const string& licensePlate, Road* currentRoad,
                 std::string typeName, unsigned int len, const VehicleLimits* limits) :
        Vehicle::Vehicle(environment, licensePlate, stdCarLength, limits, currentRoad),
        snapShot()
{
    REQUIRE(typeName == "MotorCycle" || typeName == "Car" || typeName == "Truck", "Invalid typeName for CarLike");
    
    this->typeName = typeName;
    setLen(len);
    
    ENSURE(this->typeName == typeName, "CarLike constructor failed to set typeName");
    ENSURE(!updateReady(), "Just initialised CarLike can't be ready for updating");
}

CarLike::CarLike(RoadSystem* environment, const string& licensePlate, Road* currentRoad, int acceleration, int speed, unsigned int position,
                 std::string typeName, unsigned int len, const VehicleLimits* limits) :
        Vehicle::Vehicle(environment, licensePlate, stdCarLength, &stdCarLimits, currentRoad, acceleration, speed, position),
        snapShot()
{
    REQUIRE(typeName == "MotorCycle" || typeName == "Car" || typeName == "Truck", "Invalid typeName for CarLike");
    
    this->typeName = typeName;
    
    this->typeName = typeName;
    setLen(len);
    
    ENSURE(this->typeName == typeName, "CarLike constructor failed to set typeName");
    ENSURE(!updateReady(), "Just initialised CarLike can't be ready for updating");
}


bool CarLike::updateReady()
{
    REQUIRE(properlyInitialised(), "CarLike wasn't properly initialised");
    return snapShot.prepared;
}

void CarLike::prepUpdate()
{
    REQUIRE(properlyInitialised(), "CarLike wasn't properly initialised");
    
    snapShot.setNextVeh(nextVeh());
    snapShot.prepared = true;
    
    ENSURE(updateReady(), "CarLike failed to prepare update");
}

void CarLike::cancelPrep()
{
    REQUIRE(properlyInitialised(), "CarLike wasn't properly initialised");
    
    snapShot.prepared = false;
    
    ENSURE(!updateReady(), "CarLike failed to prepare update");
}

void CarLike::execUpdate()
{
    REQUIRE(properlyInitialised(), "CarLike wasn't properly initialised");
    REQUIRE(updateReady(), "CarLike wasn't ready to update");
    REQUIRE(getEnv() == NULL || getEnv()->simulationActive(), "CarLike can't update in an inactive simulation");
    
    stepPosition();
    stepSpeed();
    stepAcceleration();
    snapShot.prepared = false;
    
    ENSURE(limits->minAcc <= getAcceleration() && getAcceleration() <= limits->maxAcc, "CarLike acceleration out of range");
    ENSURE(limits->minSpd <= getSpeed() && getAcceleration() <= limits->maxAcc, "CarLike speed out of range");
    ENSURE(0 <= getPosition() && (getCurrentRoad()==NULL || getPosition() <= getCurrentRoad()->getLength()), "CarLike position out of range");
    ENSURE(getCurrentRoad() == NULL || getSpeed() < getCurrentRoad()->getMaximumSpeed(), "CarLike speed out of range");
    ENSURE(!updateReady(), "ready status wasn't removed after updating");
}

void CarLike::stepAcceleration() {
    if (snapShot.nextVehCopy == NULL) {
        hardSetAcceleration(limits->maxAcc);
        return;
    }
    
    unsigned int targetDistance = 0.75 * getSpeed() + snapShot.nextVehCopy->length + minimumSpace;
    unsigned int actualDistance = snapShot.nextVehCopy->position - getPosition() - snapShot.nextVehCopy->length;
    
    int newAcceleration = 0.5 * (actualDistance - targetDistance);
    
    if (newAcceleration < limits->minAcc) {
        newAcceleration = limits->minAcc;
    }
    
    if (newAcceleration > limits->maxAcc) {
        newAcceleration = limits->maxAcc;
    }
    ENSURE(limits->minSpd <= getSpeed() && getAcceleration() <= limits->maxAcc, "CarLike speed out of range");
    ENSURE(0 <= getPosition() && (getCurrentRoad()==NULL || getPosition() <= getCurrentRoad()->getLength()), "CarLike position out of range");
    
    hardSetAcceleration(newAcceleration);
}

void CarLike::stepSpeed() {
    int newSpeed = getSpeed() + getAcceleration();
    
    if (newSpeed < limits->minSpd) {
        newSpeed = limits->minSpd;
    }
    
    if (newSpeed > limits->maxSpd) {
        newSpeed = limits->maxSpd;
    }
    
    if (getCurrentRoad() and newSpeed > getCurrentRoad()->getMaximumSpeed()) {
        newSpeed = getCurrentRoad()->getMaximumSpeed();
    }
    
    hardSetSpeed(newSpeed);
}

void CarLike::stepPosition() {
    unsigned int newPos = getPosition() + getSpeed();
    
    while (getCurrentRoad() and newPos > getCurrentRoad()->getLength()) {
        newPos -= getCurrentRoad()->getLength();
        getCurrentRoad()->removeVehicle(this);
        hardSetRoad(getCurrentRoad()->getConnection());
    }
    
    hardSetPosition(newPos);
}
