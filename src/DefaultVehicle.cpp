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
    REQUIRE(typeName == "MotorCycle" || typeName == "Car" || typeName == "Bus" || typeName == "Truck", "Invalid typeName for DefaultVehicle");
    
    this->typeName = typeName;
    
    ENSURE(this->typeName == typeName, "DefaultVehicle constructor failed to set typeName");
    ENSURE(!updateReady(), "Just initialised DefaultVehicle can't be ready for updating");
}

DefaultVehicle::DefaultVehicle(RoadSystem* environment, const string& licensePlate, Road* currentRoad, int acceleration, int speed, unsigned int position,
                 std::string typeName, unsigned int len, const VehicleLimits* limits) :
        Vehicle::Vehicle(environment, licensePlate, len, limits, currentRoad, acceleration, speed, position),
        snapShot()
{
    REQUIRE(typeName == "MotorCycle" || typeName == "Car" || typeName == "Bus" || typeName == "Truck", "Invalid typeName for DefaultVehicle");
    
    this->typeName = typeName;
    
    ENSURE(this->typeName == typeName, "DefaultVehicle constructor failed to set typeName");
    ENSURE(!updateReady(), "Just initialised DefaultVehicle can't be ready for updating");
}


bool DefaultVehicle::updateReady()
{
    REQUIRE(properlyInitialised(), "DefaultVehicle wasn't properly initialised");
    return snapShot.prepared;
}

void DefaultVehicle::prepUpdate() // TODO: change title to reflect functionality
{
    REQUIRE(properlyInitialised(), "DefaultVehicle wasn't properly initialised");
    
    stepPosition();
    stepSpeed();
    
    snapShot.prepared = true;
    
    ENSURE(updateReady(), "DefaultVehicle failed to prepare update");
}

void DefaultVehicle::cancelPrep()
{
    REQUIRE(properlyInitialised(), "DefaultVehicle wasn't properly initialised");
    
    snapShot.prepared = false;
    
    ENSURE(!updateReady(), "DefaultVehicle failed to prepare update");
}

void DefaultVehicle::execUpdate() // TODO: change title to reflect functionality
{
    REQUIRE(properlyInitialised(), "DefaultVehicle wasn't properly initialised");
    REQUIRE(updateReady(), "DefaultVehicle wasn't ready to update");
    REQUIRE(getEnv() == NULL || getEnv()->simulationActive(), "DefaultVehicle can't update in an inactive simulation");
    
    snapShot.setNextVeh(nextVeh()); // TODO: snapshots have become useless due to update order
    stepAcceleration();
    snapShot.prepared = false;
    
    ENSURE(limits->minAcc <= getAcceleration() && getAcceleration() <= limits->maxAcc, "DefaultVehicle acceleration out of range");
    // ENSURE(limits->minSpd <= getSpeed() && getAcceleration() <= limits->maxAcc, "DefaultVehicle speed out of range");
    ENSURE(0 <= getPosition() && (getCurrentRoad()==NULL || getPosition() <= getCurrentRoad()->getLength()), "DefaultVehicle position out of range");
    // ENSURE(getCurrentRoad() == NULL || getSpeed() < getCurrentRoad()->getSpeedLimit(), "DefaultVehicle speed out of range");
    ENSURE(!updateReady(), "ready status wasn't removed after updating");
}

void DefaultVehicle::fullStop(unsigned int distance)
{
    int newAcceleration = - (getSpeed()*getSpeed() / distance);
    
    if (getCurrentRoad() and getSpeed()+newAcceleration > getCurrentRoad()->getSpeedLimit(getPosition()))
    {
        newAcceleration = getCurrentRoad()->getSpeedLimit() - getSpeed();
    }
    
    if (newAcceleration < limits->minAcc) {
        newAcceleration = limits->minAcc;
    }
    
    if (newAcceleration > limits->maxAcc) {
        newAcceleration = limits->maxAcc;
    }
    
    hardSetAcceleration(newAcceleration);
}

void DefaultVehicle::stepAcceleration()
{
    int newAcceleration;
    
    unsigned int targetDistance = 0.75 * 3.6 * getSpeed() + minimumSpace;
    
    // default to max acceleration
    if (snapShot.nextVehCopy == NULL)
    {
        newAcceleration = limits->maxAcc;
    }
    // keep a good following distance
    else
    {
        unsigned int actualDistance = snapShot.nextVehCopy->position;
        Lane* checkingLane = getCurrentLane();
        while (!checkingLane->getVehicle(snapShot.nextVehCopy->licensePlate))
        {
            actualDistance += checkingLane->getParentRoad()->getLength();
            checkingLane = checkingLane->getConnectingLane();
        }
        actualDistance -= getPosition() + snapShot.nextVehCopy->length;
    
        newAcceleration = 0.5 * ((long) actualDistance - (long) targetDistance);
    }
    
    // stop for traffic lights
    TrafficLight* nextLight = getCurrentRoad() ? getCurrentRoad()->getTrafficLightOnPosition(getPosition(), true) : NULL;
    unsigned int distanceToLight;
    
    if (nextLight
        and nextLight->getState() != green
        and (distanceToLight = nextLight->getPosition() - getPosition()) < 2*targetDistance)
    {
        if (distanceToLight == 0)
        {
            hardSetSpeed(0);
            hardSetAcceleration(0);
        }
        else
        {
            fullStop(distanceToLight);
    
            newAcceleration = min(getAcceleration(), newAcceleration);
        }
    }
    
    // try to respect speed limits
    if (getCurrentRoad() and getSpeed()+newAcceleration > getCurrentRoad()->getSpeedLimit(getPosition()))
    {
        newAcceleration = getCurrentRoad()->getSpeedLimit() - getSpeed();
    }
    
    if (getSpeed()+newAcceleration > limits->maxSpd)
    {
        newAcceleration = limits->maxSpd - getSpeed();
    }
    
    if (getSpeed()+newAcceleration < limits->minSpd)
    {
        newAcceleration = limits->minSpd - getSpeed();
    }
    
    // force to respect acceleration limits
    if (newAcceleration < limits->minAcc)
    {
        newAcceleration = limits->minAcc;
    }
    
    if (newAcceleration > limits->maxAcc)
    {
        newAcceleration = limits->maxAcc;
    }
    
    // applly acceleration
    hardSetAcceleration(newAcceleration);
    
    ENSURE(limits->minSpd <= getSpeed() && getAcceleration() <= limits->maxAcc, "DefaultVehicle speed out of range");
    ENSURE(0 <= getPosition() && (getCurrentRoad()==NULL || getPosition() <= getCurrentRoad()->getLength()), "DefaultVehicle position out of range");
}

void DefaultVehicle::stepSpeed() {
    hardSetSpeed(getSpeed() + getAcceleration());
}

void DefaultVehicle::stepPosition() {
    unsigned int newPos = getPosition() + getSpeed();
    
    while (getCurrentRoad() and newPos >= getCurrentRoad()->getLength()) {
        newPos -= getCurrentRoad()->getLength();
        getCurrentLane()->removeVehicle(this);
        
        if (getCurrentRoad()->getConnection())
        {
            hardSetLane(getCurrentLane()->getConnectingLane());
        }
        else
        {
            hardSetLane(NULL);
        }
        
        if (getCurrentLane()) getCurrentLane()->addVehicle(this);
    }
    
    hardSetPosition(newPos);
}