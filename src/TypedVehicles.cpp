//
// Created by Joren Van Borm & Lenny Bontenakel
//

#include "TypedVehicles.h"

#include "Road.h"
#include "RoadSystem.h"
#include "design_by_contract.h"


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
    
    ENSURE(getTypeName() == "MotorCycle", "MotorCycle constructor failed to set typeName");
}

MotorCycle::MotorCycle(RoadSystem* environment, const string& licensePlate, Road* currentRoad) :
        DefaultVehicle::DefaultVehicle(environment, licensePlate, currentRoad, "MotorCycle", stdMotorCycleLength, &stdMotorCycleLimits)
{
}

MotorCycle::MotorCycle(RoadSystem* environment, const string& licensePlate, Road* currentRoad, int acceleration,
                       int speed, unsigned int position) :
        DefaultVehicle::DefaultVehicle(environment, licensePlate, currentRoad, acceleration, speed, position, "MotorCycle", stdMotorCycleLength, &stdMotorCycleLimits)
{
}


///--- Car ---///

Car::Car() :
        DefaultVehicle::DefaultVehicle()
{
}

Car::Car(RoadSystem* environment, const string& licensePlate, Road* currentRoad) :
        DefaultVehicle::DefaultVehicle(environment, licensePlate, currentRoad, "Car", stdCarLength, &stdCarLimits)
{
}

Car::Car(RoadSystem* environment, const string& licensePlate, Road* currentRoad, int acceleration, int speed,
         unsigned int position) :
        DefaultVehicle::DefaultVehicle(environment, licensePlate, currentRoad, acceleration, speed, position, "Car", stdCarLength, &stdCarLimits)
{
}


///--- Bus ---///

Bus::Bus() :
        DefaultVehicle::DefaultVehicle(),
        busStopCooldown(30)
{
    typeName = "Bus";
    
    ENSURE(getTypeName() == "Bus", "Bus constructor failed to set typeName");
}

Bus::Bus(RoadSystem* environment, const string& licensePlate, Road* currentRoad) :
        DefaultVehicle::DefaultVehicle(environment, licensePlate, currentRoad, "Bus", stdBusLength, &stdBusLimits),
        busStopCooldown(30)
{
}

Bus::Bus(RoadSystem* environment, const string& licensePlate, Road* currentRoad, int acceleration,
             int speed, unsigned int position) :
        DefaultVehicle::DefaultVehicle(environment, licensePlate, currentRoad, acceleration, speed, position, "Bus", stdBusLength, &stdBusLimits),
        busStopCooldown(30)
{
}

void Bus::execUpdate()
{
    unsigned int dToStop = std::numeric_limits<unsigned int>::max(); // TODO: set dToStop to actual distance
    
    // waiting at bus stop
    if (dToStop == 0 and busStopCooldown > 0)
    {
        hardSetSpeed(0);
        hardSetAcceleration(0);
        
        --busStopCooldown;
    
        return;
    }
    
    // slowing down for bus stop
    else if (dToStop <= 2 * (0.75*getSpeed()+getLen()) )
    {
        stepPosition();
        stepSpeed();
        
        fullStop(dToStop);
        
        return;
    }
    
    // default driving behavior
    else
    {
        DefaultVehicle::execUpdate();
    
        return;
    }
}


///--- Truck ---///

Truck::Truck() :
        DefaultVehicle::DefaultVehicle()
{
    typeName = "Truck";
    
    ENSURE(getTypeName() == "Truck", "Truck constructor failed to set typeName");
}

Truck::Truck(RoadSystem* environment, const string& licensePlate, Road* currentRoad) :
        DefaultVehicle::DefaultVehicle(environment, licensePlate, currentRoad, "Truck", stdTruckLength, &stdTruckLimits)
{
}

Truck::Truck(RoadSystem* environment, const string& licensePlate, Road* currentRoad, int acceleration,
                       int speed, unsigned int position) :
        DefaultVehicle::DefaultVehicle(environment, licensePlate, currentRoad, acceleration, speed, position, "Truck", stdTruckLength, &stdTruckLimits)
{
}