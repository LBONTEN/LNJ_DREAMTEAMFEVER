//
// Created by Joren Van Borm & Lenny Bontenakel
//

#include "Car.h"
#include "Road.h"
#include "RoadSystem.h"
#include "design_by_contract.h"

///--- global variables (definitions) ---///
extern const int stdCarLength = 300;

extern const VehicleLimits stdCarLimits(-8, 2, 0, 150);


///--- Car ---///
Car::Car() : Vehicle::Vehicle()
{
    typeName = "Car";
}

Car::Car(RoadSystem* environment, const string& licensePlate, Road* currentRoad) :
        Vehicle::Vehicle(environment, licensePlate, stdCarLength, &stdCarLimits, currentRoad),
        snapShot()
{
    typeName = "Car";
}

Car::Car(RoadSystem* environment, const string& licensePlate, Road* currentRoad, int acceleration, int speed, int position) :
        Vehicle::Vehicle(environment, licensePlate, stdCarLength, &stdCarLimits, currentRoad, acceleration, speed, position),
        snapShot()
{
    typeName = "Car";
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
    REQUIRE(getEnv()->simulationActive(), "car can't update in an inactive simulation");
    
    stepAcceleration();
    stepSpeed();
    stepPosition();
    snapShot.prepared = false;
    
    ENSURE(limits->minAcc < getAcceleration() && getAcceleration() < limits->maxAcc, "Car acceleration out of range");
    ENSURE(limits->minSpd < getSpeed() && getAcceleration() < limits->maxSpd, "Car speed out of range");
    ENSURE(0 < getPosition() && getAcceleration() < getCurrentRoad()->getLength(), "Car position out of range");
}

void Car::stepAcceleration() {
    if (snapShot.nextCarCopy == NULL) {
        hardSetAcceleration(stdCarLimits.maxAcc);
        return;
    }
    
    int targetDistance = 0.75 * getSpeed() + snapShot.nextCarCopy->length + 2; //TODO: clean up this line to be less hard-coded
    int actualDistance = snapShot.nextCarCopy->position - getPosition() - snapShot.nextCarCopy->length;
    
    int newAcceleration = 0.5 * (actualDistance - targetDistance);
    
    if (newAcceleration < stdCarLimits.minAcc) {
        newAcceleration = stdCarLimits.minAcc;
    }
    
    if (newAcceleration > stdCarLimits.maxAcc) {
        newAcceleration = stdCarLimits.maxAcc;
    }
    
    hardSetAcceleration(newAcceleration);
}

void Car::stepSpeed() {
    int newSpeed = getSpeed() + getAcceleration();
    
    if (newSpeed < stdCarLimits.minSpd) {
        newSpeed = stdCarLimits.minSpd;
    }
    
    if (newSpeed > stdCarLimits.maxSpd) {
        newSpeed = stdCarLimits.maxSpd;
    }
    
    hardSetSpeed(newSpeed);
}

void Car::stepPosition() {
    int newPos = getPosition() + getSpeed();
    
    while (newPos > getCurrentRoad()->getLength()) {
        newPos -= getCurrentRoad()->getLength();
        hardSetRoad(getCurrentRoad()->getConnection());
    }
}
