//
// Created by Joren Van Borm & Lenny Bontenakel
//

#include "TypedVehicles.h"

#include "Road.h"
#include "RoadSystem.h"
#include "design_by_contract.h"
#include "Logger.h"
#include <limits>



///--- global variables (definitions) ---///

extern const unsigned int stdMotorCycleLength = 1;
extern const VehicleLimits stdMotorCycleLimits(-10, 4, 0, 50);

extern const unsigned int stdCarLength = 3;
extern const VehicleLimits stdCarLimits(-8, 2, 0, 42);

extern const unsigned int stdBusLength = 10;
extern const VehicleLimits stdBusLimits(-7, 1, 0, 19);

extern const unsigned int stdTruckLength = 15;
extern const VehicleLimits stdTruckLimits(-6, 1, 0, 25);


///--- MotorCycle ---///

MotorCycle::MotorCycle() :
        DefaultVehicle::DefaultVehicle()
{
    typeName = "MotorCycle";
    limits = &stdMotorCycleLimits;
    hardSetLen(stdMotorCycleLength);
    
    ENSURE(getTypeName() == "MotorCycle", "MotorCycle constructor failed to set typeName");
    ENSURE(getLimits() == &stdMotorCycleLimits, "MotorCycle constructor failed to set limits");
    ENSURE(getLen() == stdMotorCycleLength, "MotorCycle constructor failed to set length");
}

MotorCycle::MotorCycle(RoadSystem* environment, const string& licensePlate, Road* currentRoad) :
        DefaultVehicle::DefaultVehicle(environment, licensePlate, currentRoad, "MotorCycle", stdMotorCycleLength, &stdMotorCycleLimits)
{
    ENSURE(getTypeName() == "MotorCycle", "MotorCycle constructor failed to set typeName");
    ENSURE(getLimits() == &stdMotorCycleLimits, "MotorCycle constructor failed to set limits");
    ENSURE(getLen() == stdMotorCycleLength, "MotorCycle constructor failed to set length");
}

MotorCycle::MotorCycle(RoadSystem* environment, const string& licensePlate, Road* currentRoad, int acceleration,
                       int speed, unsigned int position) :
        DefaultVehicle::DefaultVehicle(environment, licensePlate, currentRoad, acceleration, speed, position, "MotorCycle", stdMotorCycleLength, &stdMotorCycleLimits)
{
    ENSURE(getTypeName() == "MotorCycle", "MotorCycle constructor failed to set typeName");
    ENSURE(getLimits() == &stdMotorCycleLimits, "MotorCycle constructor failed to set limits");
    ENSURE(getLen() == stdMotorCycleLength, "MotorCycle constructor failed to set length");
}


///--- Car ---///

Car::Car() :
        DefaultVehicle::DefaultVehicle()
{
    typeName = "Car";
    limits = &stdCarLimits;
    hardSetLen(stdCarLength);

    ENSURE(getTypeName() == "Car", "Car constructor failed to set typeName");
    ENSURE(getLimits() == &stdCarLimits, "Car constructor failed to set limits");
    ENSURE(getLen() == stdCarLength, "Car constructor failed to set length");
}

Car::Car(RoadSystem* environment, const string& licensePlate, Road* currentRoad) :
        DefaultVehicle::DefaultVehicle(environment, licensePlate, currentRoad, "Car", stdCarLength, &stdCarLimits)
{
    ENSURE(getTypeName() == "Car", "Car constructor failed to set typeName");
    ENSURE(getLimits() == &stdCarLimits, "Car constructor failed to set limits");
    ENSURE(getLen() == stdCarLength, "Car constructor failed to set length");
}

Car::Car(RoadSystem* environment, const string& licensePlate, Road* currentRoad, int acceleration, int speed,
         unsigned int position) :
        DefaultVehicle::DefaultVehicle(environment, licensePlate, currentRoad, acceleration, speed, position, "Car", stdCarLength, &stdCarLimits)
{
    ENSURE(getTypeName() == "Car", "Car constructor failed to set typeName");
    ENSURE(getLimits() == &stdCarLimits, "Car constructor failed to set limits");
    ENSURE(getLen() == stdCarLength, "Car constructor failed to set length");
}


///--- Bus ---///

Bus::Bus() :
        DefaultVehicle::DefaultVehicle(),
        busStopCooldown(30)
{
    typeName = "Bus";
    limits = &stdBusLimits;
    hardSetLen(stdBusLength);
    
    ENSURE(getTypeName() == "Bus", "Bus constructor failed to set typeName");
    ENSURE(getLimits() == &stdBusLimits, "Bus constructor failed to set limits");
    ENSURE(getLen() == stdBusLength, "Bus constructor failed to set length");
}

Bus::Bus(RoadSystem* environment, const string& licensePlate, Road* currentRoad) :
        DefaultVehicle::DefaultVehicle(environment, licensePlate, currentRoad, "Bus", stdBusLength, &stdBusLimits),
        busStopCooldown(30)
{
    ENSURE(getTypeName() == "Bus", "Bus constructor failed to set typeName");
    ENSURE(getLimits() == &stdBusLimits, "Bus constructor failed to set limits");
    ENSURE(getLen() == stdBusLength, "Bus constructor failed to set length");
}

Bus::Bus(RoadSystem* environment, const string& licensePlate, Road* currentRoad, int acceleration,
             int speed, unsigned int position) :
        DefaultVehicle::DefaultVehicle(environment, licensePlate, currentRoad, acceleration, speed, position, "Bus", stdBusLength, &stdBusLimits),
        busStopCooldown(30)
{
    ENSURE(getTypeName() == "Bus", "Bus constructor failed to set typeName");
    ENSURE(getLimits() == &stdBusLimits, "Bus constructor failed to set limits");
    ENSURE(getLen() == stdBusLength, "Bus constructor failed to set length");
}

void Bus::execUpdate()
{
    unsigned int dToStop = std::numeric_limits<unsigned int>::max();
    if (getCurrentRoad()
        and getCurrentRoad()->getBusStopOnPosition(getPosition(), true))
    {
        dToStop = getCurrentRoad()->getBusStopOnPosition(getPosition(), true)->getPosition() - getPosition();
    }
    
    unsigned int targetDistance = 0.75*3.6*getSpeed()+minimumSpace;
    
    // waiting at bus stop
    if (dToStop == 0 and busStopCooldown > 0)
    {
        if (!willStop()) {
            *logging::globalLog  << "Bus failed to fully stop for bus stop\n";
        
            hardSetSpeed(0);
            hardSetAcceleration(0);
        }
        
        --busStopCooldown;
    
        return;
    }
    
    // slowing down for bus stop
    else if (dToStop <= 2*targetDistance and busStopCooldown > 0)
    {
        fullStop(dToStop);
        
        int stopAcc = getAcceleration();
        
        DefaultVehicle::execUpdate();
        
        hardSetAcceleration(min(stopAcc, getAcceleration()));
        
        return;
    }
    
    // default driving behavior
    else
    {
        unsigned int oldPos = getPosition();
        Road* oldRoad = getCurrentRoad();
        
        // reset cooldown once past the stop
        if (dToStop != 0)
        {
            busStopCooldown = 30;
        }
        
        DefaultVehicle::execUpdate();
        
        unsigned int newPos = getPosition();
        Road* newRoad = getCurrentRoad();
    
        if (!newRoad)
            return;
        
        BusStop* nextStop = getCurrentRoad()->getBusStopOnPosition(oldPos, false);
    
        if (nextStop && (oldRoad != newRoad || newPos > nextStop->getPosition()))
        {
            *logging::globalLog << "vehicle crossed traffic light illegally\n";
        }
    
        return;
    }
}


///--- Truck ---///

Truck::Truck() :
        DefaultVehicle::DefaultVehicle()
{
    typeName = "Truck";
    limits = &stdTruckLimits;
    hardSetLen(stdTruckLength);
    
    ENSURE(getTypeName() == "Truck", "Truck constructor failed to set typeName");
    ENSURE(getLimits() == &stdTruckLimits, "Truck constructor failed to set limits");
    ENSURE(getLen() == stdTruckLength, "Truck constructor failed to set length");
}

Truck::Truck(RoadSystem* environment, const string& licensePlate, Road* currentRoad) :
        DefaultVehicle::DefaultVehicle(environment, licensePlate, currentRoad, "Truck", stdTruckLength, &stdTruckLimits)
{
    ENSURE(getTypeName() == "Truck", "Truck constructor failed to set typeName");
    ENSURE(getLimits() == &stdTruckLimits, "Truck constructor failed to set limits");
    ENSURE(getLen() == stdTruckLength, "Truck constructor failed to set length");
}

Truck::Truck(RoadSystem* environment, const string& licensePlate, Road* currentRoad, int acceleration,
             int speed, unsigned int position) :
        DefaultVehicle::DefaultVehicle(environment, licensePlate, currentRoad, acceleration, speed, position, "Truck", stdTruckLength, &stdTruckLimits)
{
    ENSURE(getTypeName() == "Truck", "Truck constructor failed to set typeName");
    ENSURE(getLimits() == &stdTruckLimits, "Truck constructor failed to set limits");
    ENSURE(getLen() == stdTruckLength, "Truck constructor failed to set length");
}