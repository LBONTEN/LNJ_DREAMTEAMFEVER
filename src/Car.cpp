//
// Created by Joren Van Borm & Lenny Bontenakel
//

#include "Car.h"
#include "Road.h"
#include "RoadSystem.h"
#include "design_by_contract.h"

///--- global variables (definitions) ---///
extern const unsigned int stdCarLength = 3;

extern const VehicleLimits stdCarLimits(-8, 2, 0, 42);


///--- Car ---///
Car::Car() : Vehicle::Vehicle()
{
    typeName = "Car";

    ENSURE(typeName == "Car", "Car constructor failed to set typeName");
}

Car::Car(RoadSystem* environment, const string& licensePlate, Road* currentRoad) :
        Vehicle::Vehicle(environment, licensePlate, stdCarLength, &stdCarLimits, currentRoad),
        snapShot()
{
    typeName = "Car";

    ENSURE(typeName == "Car", "Car constructor failed to set typeName");
    ENSURE(!updateReady(), "Just initialised car can't be ready for updating");
}

Car::Car(RoadSystem* environment, const string& licensePlate, Road* currentRoad, int acceleration, unsigned int speed, unsigned int position) :
        Vehicle::Vehicle(environment, licensePlate, stdCarLength, &stdCarLimits, currentRoad, acceleration, speed, position),
        snapShot()
{
    typeName = "Car";

    ENSURE(typeName == "Car", "Car constructor failed to set typeName");
    ENSURE(!updateReady(), "Just initialised car can't be ready for updating");
}

        
bool Car::updateReady()
{
    REQUIRE(properlyInitialised(), "car wasn't properly initialised");
    return snapShot.prepared;
}

void Car::prepUpdate()
{
    REQUIRE(properlyInitialised(), "car wasn't properly initialised");
    
    snapShot.setNextCar(nextVeh());
    snapShot.prepared = true;
    
    ENSURE(updateReady(), "car failed to prepare update");
}

void Car::cancelPrep()
{
    REQUIRE(properlyInitialised(), "car wasn't properly initialised");
    
    snapShot.prepared = false;
    
    ENSURE(!updateReady(), "car failed to prepare update");
}

void Car::execUpdate()
{
    REQUIRE(properlyInitialised(), "car wasn't properly initialised");
    REQUIRE(updateReady(), "car wasn't ready to update");
    REQUIRE(getEnv() == NULL || getEnv()->simulationActive(), "car can't update in an inactive simulation");
    
    stepAcceleration();
    stepSpeed();
    stepPosition();
    snapShot.prepared = false;
    
    ENSURE(limits->minAcc <= getAcceleration() && getAcceleration() <= limits->maxAcc, "Car acceleration out of range");
    ENSURE(limits->minSpd <= getSpeed() && getAcceleration() <= limits->maxAcc, "Car speed out of range");
    ENSURE(0 <= getPosition() && (getCurrentRoad()==NULL || getPosition() <= getCurrentRoad()->getLength()), "Car position out of range");
    ENSURE(getCurrentRoad() == NULL || getSpeed() < getCurrentRoad()->getMaximumSpeed(), "Car speed out of range");
    ENSURE(!updateReady(), "ready status wasn't removed after updating");
}

void Car::stepAcceleration() {
    if (snapShot.nextCarCopy == NULL) {
        hardSetAcceleration(limits->maxAcc);
        return;
    }
    
    unsigned int targetDistance = 0.75 * getSpeed() + snapShot.nextCarCopy->length + minimumSpace;
    unsigned int actualDistance = snapShot.nextCarCopy->position - getPosition() - snapShot.nextCarCopy->length;
    
    int newAcceleration = 0.5 * (actualDistance - targetDistance);
    
    if (newAcceleration < limits->minAcc) {
        newAcceleration = limits->minAcc;
    }
    
    if (newAcceleration > limits->maxAcc) {
        newAcceleration = limits->maxAcc;
    }
    ENSURE(limits->minSpd <= getSpeed() && getAcceleration() <= limits->maxAcc, "Car speed out of range");
    ENSURE(0 <= getPosition() && (getCurrentRoad()==NULL || getPosition() <= getCurrentRoad()->getLength()), "Car position out of range");
    
    hardSetAcceleration(newAcceleration);
}

void Car::stepSpeed() {
    unsigned int newSpeed = getSpeed() + getAcceleration();
    
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

void Car::stepPosition() {
    unsigned int newPos = getPosition() + getSpeed();
    
    while (getCurrentRoad() and newPos > getCurrentRoad()->getLength()) {
        newPos -= getCurrentRoad()->getLength();
        getCurrentRoad()->removeVehicle(this);
        hardSetRoad(getCurrentRoad()->getConnection());
    }
    
    hardSetPosition(newPos);
}
