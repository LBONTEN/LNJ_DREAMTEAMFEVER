//
// Created by Joren Van Borm & Lenny Bontenakel
//

#include "Vehicle.h"
#include "RoadSystem.h"
#include "design_by_contract.h"
#include <iostream>


///--- Vehicle --- ///

Vehicle::Vehicle() : snapShot(), selfPtr(NULL) {}

Vehicle::Vehicle(RoadSystem* environment, const string& licensePlate, Road* currentRoad) :
                 snapShot(),
                 licensePlate(licensePlate),
                 currentRoad(currentRoad),
                 acceleration(0),
                 speed(0),
                 position(0),
                 environment(environment),
                 selfPtr(this) {}

Vehicle::Vehicle(RoadSystem* environment, const string& licensePlate, Road* currentRoad, int acceleration, int speed,
                 int position) :
                 snapShot(),
                 licensePlate(licensePlate),
                 currentRoad(currentRoad),
                 acceleration(acceleration),
                 speed(speed),
                 position(position),
                 environment(environment),
                 selfPtr(this) {}

void Vehicle::setLicensePlate(const string& licensePlate) {
    REQUIRE(properlyInitialised(), "Vehicle was not initialised");
    REQUIRE(getEnv()->simulationActive(), "Can't use setters while simulation active");
    
    hardSetLicencePlate(licensePlate);
    
    ENSURE(getLicensePlate() == licensePlate, "Failed to set licenceplate");
}
void Vehicle::setRoad(Road* newRoad) {
    REQUIRE(properlyInitialised(), "Vehicle was not initialised");
    REQUIRE(getEnv()->simulationActive(), "Can't use setters while simulation active");
    
    hardSetRoad(newRoad);
    
    ENSURE(getCurrentRoad() == newRoad, "Failed to set road");
}
void Vehicle::setAcceleration(int acceleration) {
    REQUIRE(properlyInitialised(), "Vehicle was not initialised");
    REQUIRE(getEnv()->simulationActive(), "Can't use setters while simulation active");
    
    hardSetAcceleration(acceleration);
    
    ENSURE(getAcceleration() == acceleration, "Failed to set acceleration");
}
void Vehicle::setSpeed(int speed) {
    REQUIRE(properlyInitialised(), "Vehicle was not initialised");
    REQUIRE(getEnv()->simulationActive(), "Can't use setters while simulation active");
    
    hardSetSpeed(speed);
    
    ENSURE(getSpeed() == speed, "Failed to set speed");
}
void Vehicle::setPosition(int position) {
    REQUIRE(properlyInitialised(), "Vehicle was not initialised");
    REQUIRE(getEnv()->simulationActive(), "Can't use setters while simulation active");
    
    hardSetPosition(position);
    
    ENSURE(getPosition() == position, "Failed to set position");
}

RoadSystem* Vehicle::getEnv() {
    REQUIRE(properlyInitialised(), "Vehicle was not initialised");
    return environment;
}
string Vehicle::getLicensePlate() {
    REQUIRE(properlyInitialised(), "Vehicle was not initialised");
    return licensePlate;
}
Road* Vehicle::getCurrentRoad() {
    REQUIRE(properlyInitialised(), "Vehicle was not initialised");
    return currentRoad;
}
int Vehicle::getAcceleration() {
    REQUIRE(properlyInitialised(), "Vehicle was not initialised");
    return acceleration;
}
int Vehicle::getSpeed() {
    REQUIRE(properlyInitialised(), "Vehicle was not initialised");
    return speed;
}
int Vehicle::getPosition() {
    REQUIRE(properlyInitialised(), "Vehicle was not initialised");
    return position;
}

bool Vehicle::properlyInitialised() {
    return this == selfPtr;
}
bool Vehicle::updateReady() {
    return snapShot.prepared;
}

void Vehicle::prepUpdate() {
    snapShot.nextCarCopy = VehicleSnap(nextCar());
    snapShot.prepared = true;
}

void Vehicle::cancelPrep() {
    snapShot.prepared = false;
}

void Vehicle::execUpdate() {
    stepAcceleration();
    stepSpeed();
    stepPosition();
    snapShot.prepared = false;
}

void Vehicle::stepAcceleration() {
    cout << "heyy \n";
}

void Vehicle::stepSpeed() {
    cout << "heyyy \n";
}

void Vehicle::stepPosition() {
    cout << "heyyyy \n";
}

Vehicle* Vehicle::nextCar() {
    // TODO: make this return the next car on the same road
    return NULL;
}


///--- VehicleSnap ---///
VehicleSnap::VehicleSnap() : licensePlate(), acceleration(), speed(), position() {}

VehicleSnap::VehicleSnap(Vehicle* source) : licensePlate(source->getLicensePlate()),
                                            acceleration(source->getAcceleration()),
                                            speed(source->getSpeed()),
                                            position(source->getPosition()) {}


///--- SimulationInfo ---///
