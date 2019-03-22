//
// Created by Joren Van Borm & Lenny Bontenakel
//

#include "Car.h"
#include "Road.h"

///--- global variables (definitions) ---///
extern const int stdCarLength = 300;

extern const VehicleLimits stdCarLimits(-8, 2, 0, 150);


///--- Car ---///
Car::Car() : Vehicle::Vehicle() {}

Car::Car(RoadSystem* environment, const string& licensePlate, Road* currentRoad) :
        Vehicle::Vehicle(environment, licensePlate, stdCarLength, &stdCarLimits, currentRoad),
        snapShot() {}

Car::Car(RoadSystem* environment, const string& licensePlate, Road* currentRoad, int acceleration, int speed, int position) :
        Vehicle::Vehicle(environment, licensePlate, stdCarLength, &stdCarLimits, currentRoad, acceleration, speed, position),
        snapShot() {}
        
bool Car::updateReady() {
    return snapShot.prepared;
}

void Car::prepUpdate() {
    snapShot.setNextCar(nextCar());
    snapShot.prepared = true;
}

void Car::cancelPrep() {
    snapShot.prepared = false;
}

void Car::execUpdate() {
    stepAcceleration();
    stepSpeed();
    stepPosition();
    snapShot.prepared = false;
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
