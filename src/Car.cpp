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
Car::Car() : CarLike::CarLike()
{
    typeName = "Car";

    ENSURE(typeName == "Car", "Car constructor failed to set typeName");
}

Car::Car(RoadSystem* environment, const string& licensePlate, Road* currentRoad) :
        CarLike::CarLike(environment, licensePlate, currentRoad, "Car", stdCarLength, &stdCarLimits)
{

}

Car::Car(RoadSystem* environment, const string& licensePlate, Road* currentRoad, int acceleration, int speed,
         unsigned int position) :
        CarLike::CarLike(environment, licensePlate, currentRoad, acceleration, speed, position, "Car", stdCarLength, &stdCarLimits)
{

}
