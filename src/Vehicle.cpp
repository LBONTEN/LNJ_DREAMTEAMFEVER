//
// Created by Joren Van Borm & Lenny Bontenakel
//

#include "Vehicle.h"
#include "RoadSystem.h"
#include "design_by_contract.h"
#include <iostream>


///--- Vehicle --- ///

Vehicle::Vehicle() : selfPtr(NULL)
{
    ENSURE(!properlyInitialised(), "Car constructor failed");
}

Vehicle::Vehicle(RoadSystem* environment, const string& licensePlate, int length, const VehicleLimits* limits, Road* currentRoad) :
                 limits(limits),
                 licensePlate(licensePlate),
                 currentRoad(currentRoad),
                 acceleration(0),
                 speed(0),
                 position(0),
                 len(length),
                 environment(environment)
{
    selfPtr = this;
    
    ENSURE(properlyInitialised(), "Car constructor failed");
    ENSURE(getEnv()==environment && getLicensePlate()==licensePlate && getLen()==length && getLimits()==limits && getCurrentRoad()==currentRoad,
            "Car constructor failed to assign variable(s)");
    ENSURE(getAcceleration()==0 && getSpeed()==0 && getPosition()==0, "Car constructor failed to assign kinetic information");
}

Vehicle::Vehicle(RoadSystem* environment, const string& licensePlate, int length, const VehicleLimits* limits, Road* currentRoad, int acceleration, int speed,
                 int position) :
                 limits(limits),
                 licensePlate(licensePlate),
                 currentRoad(currentRoad),
                 acceleration(acceleration),
                 speed(speed),
                 position(position),
                 len(length),
                 environment(environment),
                 selfPtr(this)
{
    ENSURE(properlyInitialised(), "Car constructor failed");
    ENSURE(getEnv()==environment && getLicensePlate()==licensePlate && getLen()==length && getLimits()==limits && getCurrentRoad()==currentRoad,
           "Car constructor failed to assign variable(s)");
    ENSURE(getAcceleration()==acceleration && getSpeed()==speed && getPosition()==position, "Car constructor failed to assign kinetic information");
}

Vehicle::~Vehicle()
{
    // can't use getters here in case vehicle isn't initialised
    currentRoad->removeVehicle(this);
    environment->removeVehicle(this);
}

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
void Vehicle::setLen(int cm) {
    REQUIRE(properlyInitialised(), "Vehicle was not initialised");
    REQUIRE(getEnv()->simulationActive(), "Can't use setters while simulation active");
    
    hardSetPosition(cm);
    
    ENSURE(getLen() == cm, "Failed to set position");
}


RoadSystem* Vehicle::getEnv() const {
    REQUIRE(properlyInitialised(), "Vehicle was not initialised");
    return environment;
}
string Vehicle::getLicensePlate() const {
    REQUIRE(properlyInitialised(), "Vehicle was not initialised");
    return licensePlate;
}
Road* Vehicle::getCurrentRoad() const {
    REQUIRE(properlyInitialised(), "Vehicle was not initialised");
    return currentRoad;
}
int Vehicle::getAcceleration() const {
    REQUIRE(properlyInitialised(), "Vehicle was not initialised");
    return acceleration;
}
int Vehicle::getSpeed() const {
    REQUIRE(properlyInitialised(), "Vehicle was not initialised");
    return speed;
}
int Vehicle::getPosition() const {
    REQUIRE(properlyInitialised(), "Vehicle was not initialised");
    return position;
}
int Vehicle::getLen() const {
    REQUIRE(properlyInitialised(), "Vehicle was not initialised");
    return len;
}
const VehicleLimits* Vehicle::getLimits() {
    REQUIRE(properlyInitialised(), "Vehicle was not initialised");
    return limits;
}

bool Vehicle::operator < (const Vehicle& vehic) const
{
    REQUIRE(properlyInitialised(), "Vehicle was not properly initialised.");
    return position < vehic.position;
}


bool Vehicle::properlyInitialised() const {
    return this == selfPtr;
}


Vehicle* Vehicle::nextCar() {
    // TODO: make this return the next car on the same road
    return NULL;
}


///--- VehicleSnap ---///

VehicleSnap::VehicleSnap() : licensePlate(), acceleration(), speed(), position(), length() {}

VehicleSnap::VehicleSnap(Vehicle* source) : licensePlate(source->getLicensePlate()),
                                            acceleration(source->getAcceleration()),
                                            speed(source->getSpeed()),
                                            position(source->getPosition()),
                                            length(source->getLen()) {}

VehicleSnap::VehicleSnap(const string& licensePlate, int acceleration, unsigned int speed, int position, int length)
        : licensePlate(licensePlate), acceleration(acceleration), speed(speed), position(position), length(length) {}


///--- SimulationInfo ---///

void SimulationInfo::setNextCar(Vehicle* vehicle) {
    delete nextCarCopy;
    if (vehicle) {
        nextCarCopy = new VehicleSnap(vehicle);
    }
    else {
        nextCarCopy = NULL;
    }
}