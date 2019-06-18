//
// Created by Joren Van Borm & Lenny Bontenakel
//

#ifndef LNJPSE_CAR_H
#define LNJPSE_CAR_H


#include "DefaultVehicle.h"
#include "Logger.h"


///--- global variables (declarations) ---///

extern const unsigned int stdMotorCycleLength;
extern const VehicleLimits stdMotorCycleLimits;

extern const unsigned int stdCarLength;
extern const VehicleLimits stdCarLimits;

extern const unsigned int stdBusLength;
extern const VehicleLimits stdBusLimits;

extern const unsigned int stdTruckLength;
extern const VehicleLimits stdTruckLimits;


///--- Classes ---///

class MotorCycle : public DefaultVehicle {
public:
    /**
     * Default constructor
     * Does NOT create a properly initialised vehicle
     * @ENSURE(getTypeName() == "MotorCycle");
     * @ENSURE(getLimits() == &stdMotorCycleLimits);
     * @ENSURE(getLen() == stdMotorCycleLength);
     * + pre- & postconditions from the corresponding method in DefaultVehicle
     */
    MotorCycle();
    
    /**
     * Minimal constructor
     * Acceleration, speed and position are assumed to be 0
     * @ENSURE(getTypeName() == "MotorCycle");
     * @ENSURE(getLimits() == &stdMotorCycleLimits);
     * @ENSURE(getLen() == stdMotorCycleLength);
     * + pre- & postconditions from the corresponding method in DefaultVehicle
     */
    MotorCycle(RoadSystem* environment, const string& licensePlate, Road* currentRoad);
    
    /**
     * Maximal constructor
     * @ENSURE(getTypeName() == "MotorCycle");
     * @ENSURE(getLimits() == &stdMotorCycleLimits);
     * @ENSURE(getLen() == stdMotorCycleLength);
     * + pre- & postconditions from the corresponding method in DefaultVehicle
     */
    MotorCycle(RoadSystem* environment, const string& licensePlate, Road* currentRoad, int acceleration, int speed, unsigned int position);
};

class Car: public DefaultVehicle {
public:
    /**
     * Default constructor
     * Does NOT create a properly initialised vehicle
     * @ENSURE(getTypeName() == "Car");
     * @ENSURE(getLimits() == &stdCarLimits);
     * @ENSURE(getLen() == stdCarLength);
     * + pre- & postconditions from the corresponding method in DefaultVehicle
     */
    Car();
    
    /**
     * Minimal constructor
     * Acceleration, speed and position are assumed to be 0
     * @ENSURE(getTypeName() == "Car");
     * @ENSURE(getLimits() == &stdCarLimits);
     * @ENSURE(getLen() == stdCarLength);
     * + pre- & postconditions from the corresponding method in DefaultVehicle
     * */
    Car(RoadSystem* environment, const string& licensePlate, Road* currentRoad);
    
    /**
     * Maximal constructor
     * @ENSURE(getTypeName() == "Car");
     * @ENSURE(getLimits() == &stdCarLimits);
     * @ENSURE(getLen() == stdCarLength);
     * + pre- & postconditions from the corresponding method in DefaultVehicle
     */
    Car(RoadSystem* environment, const string& licensePlate, Road* currentRoad, int acceleration, int speed, unsigned int position);
};

class Bus: public DefaultVehicle {
public:
    /**
     * Default constructor
     * Does NOT create a properly initialised vehicle
     * @ENSURE(getTypeName() == "Bus");
     * @ENSURE(getLimits() == &stdBusLimits);
     * @ENSURE(getLen() == stdBusLength);
     * + pre- & postconditions from the corresponding method in DefaultVehicle
     */
    Bus();
    
    /**
     * Minimal constructor
     * Acceleration, speed and position are assumed to be 0
     * @ENSURE(getTypeName() == "Bus");
     * @ENSURE(getLimits() == &stdBusLimits);
     * @ENSURE(getLen() == stdBusLength);
     * + pre- & postconditions from the corresponding method in DefaultVehicle
     */
    Bus(RoadSystem* environment, const string& licensePlate, Road* currentRoad);
    
    /**
     * Maximal constructor
     * @ENSURE(getTypeName() == "Bus");
     * @ENSURE(getLimits() == &stdBusLimits);
     * @ENSURE(getLen() == stdBusLength);
     * + pre- & postconditions from the corresponding method in DefaultVehicle
     */
    Bus(RoadSystem* environment, const string& licensePlate, Road* currentRoad, int acceleration, int speed, unsigned int position);
    
    /**
     * Update acceleration, speed and position (and possibly currentRoad)
     * stops for bus stops
     * otherwise, respects same rules as DefaultVehicle's execUpdate()
     * 
     * pre- & postconditions respect those of the corresponding method in DefaultVehicle
     */
    virtual void execUpdate();

private:
    int busStopCooldown;
};


class Truck: public DefaultVehicle {
public:
    /**
     * Default constructor
     * Does NOT create a properly initialised vehicle
     * @ENSURE(getTypeName() == "Truck");
     * @ENSURE(getLimits() == &stdTruckLimits);
     * @ENSURE(getLen() == stdTruckLength);
     * + pre- & postconditions from the corresponding method in DefaultVehicle
     */
    Truck();
    
    /**
     * Minimal constructor
     * Acceleration, speed and position are assumed to be 0
     * @ENSURE(getTypeName() == "Truck");
     * @ENSURE(getLimits() == &stdTruckLimits);
     * @ENSURE(getLen() == stdTruckLength);
     * + pre- & postconditions from the corresponding method in DefaultVehicle
     */
    Truck(RoadSystem* environment, const string& licensePlate, Road* currentRoad);
    
    /**
     * Maximal constructor
     * @ENSURE(getTypeName() == "Truck");
     * @ENSURE(getLimits() == &stdTruckLimits);
     * @ENSURE(getLen() == stdTruckLength);
     * + pre- & postconditions from the corresponding method in DefaultVehicle
     */
    Truck(RoadSystem* environment, const string& licensePlate, Road* currentRoad, int acceleration, int speed, unsigned int position);
};


#endif //LNJPSE_CAR_H
