//
// Created by Joren Van Borm on 2019-04-26.
//

#include "DefaultVehicle.h"
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
DefaultVehicle::DefaultVehicle() : Vehicle::Vehicle()
{
    typeName = "Car";
    
    ENSURE(typeName == "Car", "DefaultVehicle default constructor failed to set typeName");
}

DefaultVehicle::DefaultVehicle(RoadSystem* environment, const string& licensePlate, Road* currentRoad,
                 std::string typeName, unsigned int len, const VehicleLimits* limits) :
        Vehicle::Vehicle(environment, licensePlate, stdCarLength, limits, currentRoad),
        snapShot()
{
    REQUIRE(typeName == "MotorCycle" || typeName == "Car" || typeName == "Truck", "Invalid typeName for DefaultVehicle");
    
    this->typeName = typeName;
    
    ENSURE(this->typeName == typeName, "DefaultVehicle constructor failed to set typeName");
    ENSURE(!updateReady(), "Just initialised DefaultVehicle can't be ready for updating");
}

DefaultVehicle::DefaultVehicle(RoadSystem* environment, const string& licensePlate, Road* currentRoad, int acceleration, int speed, unsigned int position,
                 std::string typeName, unsigned int len, const VehicleLimits* limits) :
        Vehicle::Vehicle(environment, licensePlate, stdCarLength, &stdCarLimits, currentRoad, acceleration, speed, position),
        snapShot()
{
    REQUIRE(typeName == "MotorCycle" || typeName == "Car" || typeName == "Truck", "Invalid typeName for DefaultVehicle");
    
    this->typeName = typeName;
    
    ENSURE(this->typeName == typeName, "DefaultVehicle constructor failed to set typeName");
    ENSURE(!updateReady(), "Just initialised DefaultVehicle can't be ready for updating");
}


bool DefaultVehicle::updateReady()
{
    REQUIRE(properlyInitialised(), "DefaultVehicle wasn't properly initialised");
    return snapShot.prepared;
}

void DefaultVehicle::prepUpdate()
{
    REQUIRE(properlyInitialised(), "DefaultVehicle wasn't properly initialised");
    
    snapShot.setNextVeh(nextVeh());
    snapShot.prepared = true;
    
    ENSURE(updateReady(), "DefaultVehicle failed to prepare update");
}

void DefaultVehicle::cancelPrep()
{
    REQUIRE(properlyInitialised(), "DefaultVehicle wasn't properly initialised");
    
    snapShot.prepared = false;
    
    ENSURE(!updateReady(), "DefaultVehicle failed to prepare update");
}

void DefaultVehicle::execUpdate()
{
    REQUIRE(properlyInitialised(), "DefaultVehicle wasn't properly initialised");
    REQUIRE(updateReady(), "DefaultVehicle wasn't ready to update");
    REQUIRE(getEnv() == NULL || getEnv()->simulationActive(), "DefaultVehicle can't update in an inactive simulation");
    
    stepPosition();
    stepSpeed();
    stepAcceleration();
    snapShot.prepared = false;
    
    ENSURE(limits->minAcc <= getAcceleration() && getAcceleration() <= limits->maxAcc, "DefaultVehicle acceleration out of range");
    ENSURE(limits->minSpd <= getSpeed() && getAcceleration() <= limits->maxAcc, "DefaultVehicle speed out of range");
    ENSURE(0 <= getPosition() && (getCurrentRoad()==NULL || getPosition() <= getCurrentRoad()->getLength()), "DefaultVehicle position out of range");
    ENSURE(getCurrentRoad() == NULL || getSpeed() < getCurrentRoad()->getMaximumSpeed(), "DefaultVehicle speed out of range");
    ENSURE(!updateReady(), "ready status wasn't removed after updating");
}

void DefaultVehicle::fullStop(unsigned int distance)
{
    int newAcceleration = - getSpeed()*getSpeed() / distance;
    
    if (getCurrentRoad() and getSpeed()+newAcceleration > getCurrentRoad()->getMaximumSpeed())
    {
        newAcceleration = getCurrentRoad()->getMaximumSpeed() - getSpeed();
    }
    
    if (newAcceleration < limits->minAcc) {
        newAcceleration = limits->minAcc;
    }
    
    if (newAcceleration > limits->maxAcc) {
        newAcceleration = limits->maxAcc;
    }
}

void DefaultVehicle::stepAcceleration() {
    if (snapShot.nextVehCopy == NULL) {
        hardSetAcceleration(limits->maxAcc);
        return;
    }
    
    unsigned int targetDistance = 0.75 * getSpeed() + snapShot.nextVehCopy->length + minimumSpace;
    unsigned int actualDistance = snapShot.nextVehCopy->position - getPosition() - snapShot.nextVehCopy->length;
    
    int newAcceleration = 0.5 * (actualDistance - targetDistance);
    
    if (getCurrentRoad() and getSpeed()+newAcceleration > getCurrentRoad()->getMaximumSpeed())
    {
        newAcceleration = getCurrentRoad()->getMaximumSpeed() - getSpeed();
    }
    
    if (newAcceleration < limits->minAcc)
    {
        newAcceleration = limits->minAcc;
    }
    
    if (newAcceleration > limits->maxAcc)
    {
        newAcceleration = limits->maxAcc;
    }
    
    ENSURE(limits->minSpd <= getSpeed() && getAcceleration() <= limits->maxAcc, "DefaultVehicle speed out of range");
    ENSURE(0 <= getPosition() && (getCurrentRoad()==NULL || getPosition() <= getCurrentRoad()->getLength()), "DefaultVehicle position out of range");
    
    hardSetAcceleration(newAcceleration);
}

void DefaultVehicle::stepSpeed() {
    int newSpeed = getSpeed() + getAcceleration();
    
    if (newSpeed < limits->minSpd) {
        newSpeed = limits->minSpd;
    }
    
    if (newSpeed > limits->maxSpd) {
        newSpeed = limits->maxSpd;
    }
    
    hardSetSpeed(newSpeed);
}

void DefaultVehicle::stepPosition() {
    unsigned int newPos = getPosition() + getSpeed();
    
    while (getCurrentRoad() and newPos > getCurrentRoad()->getLength()) {
        newPos -= getCurrentRoad()->getLength();
        getCurrentRoad()->removeVehicle(this);
        hardSetRoad(getCurrentRoad()->getConnection());
        if (getCurrentRoad()) getCurrentRoad()->addVehicle(this);
    }
    
    hardSetPosition(newPos);
}