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
     * @ENSURE NOT properly initialised, get typename = MotorCycle, get limits / len = stdMotorCylceLimits / -len
     */
    MotorCycle();
    
    /**
     * Minimal constructor
     * Acceleration, speed and position are assumed to be 0
     * @ENSURE properly initialised, get<arg> = <arg>, get typename = MotorCycle, get limits / len = stdMotorCylceLimits / -len, get <acc/spd/pos> = 0, NOT update ready
     */
    MotorCycle(RoadSystem* environment, const string& licensePlate, Road* currentRoad);
    
    /**
     * Maximal constructor
     * @ENSURE properly initialised, get<arg> = <arg>, get typename = MotorCycle, get limits / len = stdMotorCylceLimits / -len, NOT update ready
     */
    MotorCycle(RoadSystem* environment, const string& licensePlate, Road* currentRoad, int acceleration, int speed, unsigned int position);
};

class Car: public DefaultVehicle {
public:
    /**
     * Default constructor
     * @ENSURE NOT properly initialised, get typename = Car, get limits / len = stdCarLimits / -len
     */
    Car();
    
    /**
     * Minimal constructor
     * Acceleration, speed and position are assumed to be 0
     * @ENSURE properly initialised, get<arg> = <arg>, get typename = Car, get <acc/spd/pos> = 0, get limits / len = stdCarLimits / -len, NOT update ready
     */
    Car(RoadSystem* environment, const string& licensePlate, Road* currentRoad);
    
    /**
     * Maximal constructor
     * @ENSURE properly initialised, get<arg> = <arg>, get typename = Car, get limits / len = stdCarLimits / -len, NOT update ready
     */
    Car(RoadSystem* environment, const string& licensePlate, Road* currentRoad, int acceleration, int speed, unsigned int position);
};

class Bus: public DefaultVehicle {
public:
    /**
     * Default constructor
     * @ENSURE NOT properly initialised, get typename = Bus, get limits / len = stdBusLimits / -len
     */
    Bus();
    
    /**
     * Minimal constructor
     * Acceleration, speed and position are assumed to be 0
     * @ENSURE properly initialised, get<arg> = <arg>, get typename = Bus, get limits / len = stdBusLimits / -len, get <acc/spd/pos> = 0, NOT update ready
     */
    Bus(RoadSystem* environment, const string& licensePlate, Road* currentRoad);
    
    /**
     * Maximal constructor
     * @ENSURE properly initialised, get<arg> = <arg>, get typename = Bus, get limits / len = stdBusLimits / -len, NOT update ready
     */
    Bus(RoadSystem* environment, const string& licensePlate, Road* currentRoad, int acceleration, int speed, unsigned int position);
    
    /**
     * Update acceleration, speed and position (and possibly currentRoad)
     * stops for bus stops
     * otherwise, respects same rules as DefaultVehicle's execUpdate()
     * @REQUIRE properly initialised, update prepared, simulation active
     * @ENSURE get<acc/pos> is within limits, update NOT ready
     */
    virtual void execUpdate();

private:
    int busStopCooldown;
};


class Truck: public DefaultVehicle {
public:
    /**
     * Default constructor
     * @ENSURE NOT properly initialised, get typename = Truck, get limits / len = stdTruckLimits / -len
     */
    Truck();
    
    /**
     * Minimal constructor
     * Acceleration, speed and position are assumed to be 0
     * @ENSURE properly initialised, get<arg> = <arg>, get typename = Truck, get limits / len = stdTruckLimits / -len, get <acc/spd/pos> = 0, NOT update ready
     */
    Truck(RoadSystem* environment, const string& licensePlate, Road* currentRoad);
    
    /**
     * Maximal constructor
     * @ENSURE properly initialised, get<arg> = <arg>, get typename = Truck, get limits / len = stdTruckLimits / -len, NOT update ready
     */
    Truck(RoadSystem* environment, const string& licensePlate, Road* currentRoad, int acceleration, int speed, unsigned int position);
};


#endif //LNJPSE_CAR_H
