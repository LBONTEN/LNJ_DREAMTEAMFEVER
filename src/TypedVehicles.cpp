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

///--- Car ---///

Car::Car() : DefaultVehicle::DefaultVehicle()
{
    typeName = "Car";

    ENSURE(typeName == "Car", "Car constructor failed to set typeName");
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
