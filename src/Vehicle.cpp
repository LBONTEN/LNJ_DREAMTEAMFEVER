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

Vehicle::Vehicle(RoadSystem* environment, const string& licensePlate, unsigned int length, const VehicleLimits* limits, Road* currentRoad) :
                 limits(limits),
                 licensePlate(licensePlate),
                 acceleration(0),
                 speed(0),
                 position(0),
                 len(length),
                 environment(environment),
                 selfPtr(this)
{
    REQUIRE(limits != NULL, "Vehicle limits must be set");

    if(currentRoad != NULL) currentLane = currentRoad->getLanes()[0];
    else currentLane = NULL;

    ENSURE(properlyInitialised(), "Car constructor failed");
    ENSURE(getEnv()==environment &&
           getLicensePlate()==licensePlate &&
           getLen()==length &&
           getLimits()==limits &&
           getCurrentRoad() == currentRoad,
           "Car constructor failed to assign variable(s)");
    ENSURE(getAcceleration()==0 &&
           getSpeed()==0 &&
           getPosition()==0,
           "Car constructor failed to assign kinetic information");
}

Vehicle::Vehicle(RoadSystem* environment, const string& licensePlate, unsigned int length, const VehicleLimits* limits, Road* currentRoad, int acceleration, int speed,
                 unsigned int position) :
                 limits(limits),
                 licensePlate(licensePlate),
                 acceleration(acceleration),
                 speed(speed),
                 position(position),
                 len(length),
                 environment(environment),
                 selfPtr(this)
{
    REQUIRE(limits != NULL, "Vehicle limits must be set");

    if(currentRoad != NULL) currentLane = currentRoad->getLanes()[0];

    ENSURE(properlyInitialised(), "Car constructor failed");
    ENSURE(getEnv() == environment &&
           getLicensePlate() == licensePlate &&
           getLen() == length &&
           getLimits() == limits &&
           getCurrentRoad() == currentRoad,
           "Car constructor failed to assign variable(s)");
    ENSURE(getAcceleration()==acceleration &&
           getSpeed()==speed &&
           getPosition()==position,
           "Car constructor failed to assign kinetic information");
}

Vehicle::~Vehicle()
{
    // can't use getters here in case vehicle isn't initialised
    if (currentLane != NULL)
    {
        currentLane->removeVehicle(this);
        ENSURE(!getCurrentLane()->getVehicle(this->getLicensePlate()), "Vehicle destructor failed to remove self from road");
    }
    
    if (environment != NULL)
    {
        environment->removeVehicle(this);
        ENSURE(!getEnv()->contains(this), "Vehicle destructor failed to remove self from road system");
    }
}

void Vehicle::setLicensePlate(const string& licensePlate) {
    REQUIRE(properlyInitialised(), "Vehicle was not initialised");
    REQUIRE(getEnv() == NULL || !getEnv()->simulationActive(), "Can't use setters while simulation active");
    
    hardSetLicencePlate(licensePlate);
    
    ENSURE(getLicensePlate() == licensePlate, "Failed to set licenceplate");
}
void Vehicle::setLane(Lane* newLane)
{
    REQUIRE(properlyInitialised(), "Vehicle was not initialised");
    if (getEnv() != NULL) REQUIRE(!getEnv()->simulationActive(), "Can't use setters while simulation active");

    if(newLane == NULL)
    {
        currentLane->removeVehicle(this);
        currentLane = NULL;
    }
    else
    {
        if (currentLane == NULL) currentLane = newLane;
        else
        {
            currentLane->removeVehicle(this);
            hardSetLane(newLane);
        }
    }
    ENSURE(getCurrentLane() == newLane, "Failed to set lane");
}
void Vehicle::setAcceleration(int acceleration) {
    REQUIRE(properlyInitialised(), "Vehicle was not initialised");
    REQUIRE(getEnv() == NULL || !getEnv()->simulationActive(), "Can't use setters while simulation active");
    
    if (acceleration < limits->minAcc) {
        acceleration = limits->minAcc;
    }
    
    if (acceleration > limits->maxAcc) {
        acceleration = limits->maxAcc;
    }
    
    hardSetAcceleration(acceleration);
    
    ENSURE(getAcceleration() == acceleration, "Failed to set acceleration");
}
void Vehicle::setSpeed(int speed) {
    REQUIRE(properlyInitialised(), "Vehicle was not initialised");
    REQUIRE(getEnv() == NULL || !getEnv()->simulationActive(), "Can't use setters while simulation active");
    
    if (speed < limits->minSpd) {
        speed = limits->minSpd;
    }
    
    if (speed > limits->maxSpd) {
        speed = limits->maxSpd;
    }
    
    if (getCurrentRoad() and speed > getCurrentRoad()->getSpeedLimit()) {
        speed = getCurrentRoad()->getSpeedLimit();
    }
    
    hardSetSpeed(speed);
    
    ENSURE(getSpeed() == speed, "Failed to set speed");
}
void Vehicle::setPosition(unsigned int position) {
    REQUIRE(properlyInitialised(), "Vehicle was not initialised");
    REQUIRE(getEnv() == NULL || !getEnv()->simulationActive(), "Can't use setters while simulation active");
    
    if (position < 0) {
        position = 0;
    }
    
    if (getCurrentRoad() and position > getCurrentRoad()->getLength()) {
        position = getCurrentRoad()->getLength();
    }
    
    hardSetPosition(position);
    
    ENSURE(getPosition() == position, "Failed to set position");
}
void Vehicle::setLen(unsigned int len) {
    REQUIRE(properlyInitialised(), "Vehicle was not initialised");
    REQUIRE(getEnv() == NULL || !getEnv()->simulationActive(), "Can't use setters while simulation active");
    
    hardSetLen(len);
    
    ENSURE(getLen() == len, "Failed to set position");
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
    if (currentLane == NULL) return NULL;
    return currentLane->getParentRoad();
}
Lane* Vehicle::getCurrentLane() const{
    REQUIRE(properlyInitialised(), "Vehicle was not initialised");
    return currentLane;
}
int Vehicle::getAcceleration() const {
    REQUIRE(properlyInitialised(), "Vehicle was not initialised");
    return acceleration;
}
int Vehicle::getSpeed() const {
    REQUIRE(properlyInitialised(), "Vehicle was not initialised");
    return speed;
}
unsigned int Vehicle::getPosition() const {
    REQUIRE(properlyInitialised(), "Vehicle was not initialised");
    return position;
}

unsigned int Vehicle::getLen() const {
    REQUIRE(properlyInitialised(), "Vehicle was not initialised");
    return len;
}
const VehicleLimits* Vehicle::getLimits() const {
    REQUIRE(properlyInitialised(), "Vehicle was not initialised");
    return limits;
}
const string& Vehicle::getTypeName() const {
    return typeName;
}


bool Vehicle::properlyInitialised() const {
    return this == selfPtr;
}


Vehicle* Vehicle::nextVeh() {
    REQUIRE(properlyInitialised(), "Vehicle was not initialised");

    if (currentLane == NULL) return NULL;
    
    Vehicle* next = currentLane->getCarOnPosition(getPosition(), false);
    
    Lane* ln = NULL;
    
    if (getCurrentRoad()->getConnection())
    {
        ln = getCurrentLane()->getConnectingLane();
    }
    
    while (!next and ln)
    {
        next = ln->getCarOnPosition(0, true);
        ln = getCurrentLane()->getConnectingLane();
    }
    
    return next;
}


///--- VehicleSnap ---///

VehicleSnap::VehicleSnap() : licensePlate(), acceleration(), speed(), position(), length() {}

VehicleSnap::VehicleSnap(Vehicle* source) : licensePlate(source->getLicensePlate()),
                                            acceleration(source->getAcceleration()),
                                            speed(source->getSpeed()),
                                            position(source->getPosition()),
                                            length(source->getLen()) {}

VehicleSnap::VehicleSnap(const string& licensePlate, int acceleration, int speed, unsigned int position, unsigned int length)
        : licensePlate(licensePlate), acceleration(acceleration), speed(speed), position(position), length(length) {}


///--- SimulationInfo ---///

void SimulationInfo::setNextVeh(Vehicle* vehicle) {
    delete nextVehCopy;
    if (vehicle) {
        nextVehCopy = new VehicleSnap(vehicle);
    }
    else {
        nextVehCopy = NULL;
    }
}