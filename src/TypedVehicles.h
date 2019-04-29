//
// Created by Joren Van Borm & Lenny Bontenakel
//

#ifndef LNJPSE_CAR_H
#define LNJPSE_CAR_H


#include "DefaultVehicle.h"


///--- global variables (declarations) ---///

extern const unsigned int stdMotorCycleLength;
extern const VehicleLimits stdMotorCycleLimits;

extern const unsigned int stdCarLength;
extern const VehicleLimits stdCarLimits;

extern const unsigned int stdBusLength;
extern const VehicleLimits stBusLimits;

extern const unsigned int stdTruckLength;
extern const VehicleLimits stdTruckLimits;


///--- Classes ---///

class MotorCycle : public DefaultVehicle {
public:
    /**
     * Default constructor
     * @ENSURE NOT properly initialised, get typename = MotorCycle
     */
    MotorCycle();
    
    /**
     * Minimal constructor
     * Acceleration, speed and position are assumed to be 0
     * @ENSURE properly initialised, get<arg> = <arg>, get typename = MotorCycle, get <acc/spd/pos> = 0, NOT update ready
     */
    MotorCycle(RoadSystem* environment, const string& licensePlate, Road* currentRoad);
    
    /**
     * Maximal constructor
     * @ENSURE properly initialised, get<arg> = <arg>, get typename = MotorCycle, NOT update ready
     */
    MotorCycle(RoadSystem* environment, const string& licensePlate, Road* currentRoad, int acceleration, int speed, unsigned int position);
};

class Car: public DefaultVehicle {
public:
    /**
     * Default constructor
     * @ENSURE NOT properly initialised, get typename = Car
     */
    Car();
    
    /**
     * Minimal constructor
     * Acceleration, speed and position are assumed to be 0
     * @ENSURE properly initialised, get<arg> = <arg>, get typename = Car, get <acc/spd/pos> = 0, NOT update ready
     */
    Car(RoadSystem* environment, const string& licensePlate, Road* currentRoad);
    
    /**
     * Maximal constructor
     * @ENSURE properly initialised, get<arg> = <arg>, get typename = Car, NOT update ready
     */
    Car(RoadSystem* environment, const string& licensePlate, Road* currentRoad, int acceleration, int speed, unsigned int position);
};

class Bus: public DefaultVehicle {
public:
    /**
     * Default constructor
     * @ENSURE NOT properly initialised, get typename = Bus
     */
    Bus();
    
    /**
     * Minimal constructor
     * Acceleration, speed and position are assumed to be 0
     * @ENSURE properly initialised, get<arg> = <arg>, get typename = Bus, get <acc/spd/pos> = 0, NOT update ready
     */
    Bus(RoadSystem* environment, const string& licensePlate, Road* currentRoad);
    
    /**
     * Maximal constructor
     * @ENSURE properly initialised, get<arg> = <arg>, get typename = Bus, NOT update ready
     */
    Bus(RoadSystem* environment, const string& licensePlate, Road* currentRoad, int acceleration, int speed, unsigned int position);
    
    /**
     * Upate acceleration, speed and position (and possibly currentRoad)
     * stops for bus stops
     * @REQUIRE properly initialised, update prepared, simulation active
     * @ENSURE get<acc/spd/pos> is within limits, minimum distance is respected, update NOT ready
     */
    virtual void execUpdate();

private:
    int busStopCooldown;
};

class Truck: public DefaultVehicle {
public:
    /**
     * Default constructor
     * @ENSURE NOT properly initialised, get typename = Truck
     */
    Truck();
    
    /**
     * Minimal constructor
     * Acceleration, speed and position are assumed to be 0
     * @ENSURE properly initialised, get<arg> = <arg>, get typename = Truck, get <acc/spd/pos> = 0, NOT update ready
     */
    Truck(RoadSystem* environment, const string& licensePlate, Road* currentRoad);
    
    /**
     * Maximal constructor
     * @ENSURE properly initialised, get<arg> = <arg>, get typename = Truck, NOT update ready
     */
    Truck(RoadSystem* environment, const string& licensePlate, Road* currentRoad, int acceleration, int speed, unsigned int position);
};


#endif //LNJPSE_CAR_H
