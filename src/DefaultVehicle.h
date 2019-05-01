//
// Created by Joren Van Borm on 2019-04-26.
//

#ifndef LNJPSE_PROJECT_DEFAULTVEHICLE_H
#define LNJPSE_PROJECT_DEFAULTVEHICLE_H


#include "Vehicle.h"


class DefaultVehicle : public Vehicle {
public:
    /**
     * Default constructor
     * @ENSURE NOT properly initialised, get typename = Car
     */
    DefaultVehicle();
    
    /**
     * Minimal constructor
     * Acceleration, speed and position are assumed to be 0
     * @REQUIRE typeName is a valid vehicle type (MotorCycle, Car, Truck)
     * @ENSURE properly initialised, get<arg> = <arg>, get typename = Car, get <acc/spd/pos> = 0, NOT update ready
     */
    DefaultVehicle(RoadSystem* environment, const string& licensePlate, Road* currentRoad,
            std::string typeName, unsigned int len, const VehicleLimits* limits);
    
    /**
     * Maximal constructor
     * @REQUIRE typeName is a valid vehicle type (MotorCycle, Car, Truck)
     * @ENSURE properly initialised, get<arg> = <arg>, get typename = Car, NOT update ready
     */
    DefaultVehicle(RoadSystem* environment, const string& licensePlate, Road* currentRoad, int acceleration, int speed, unsigned int position,
            std::string typeName, unsigned int len, const VehicleLimits* limits);
    
    
    /**
     * Funtion purely to check pre- and postconditions
     * @REQUIRE properly initialised
     */
    virtual bool updateReady();
    
    /**
     * In case changes need to happen between preparing and updating, use this for safety
     * @REQUIRE properly initialised
     * @ENSURE update not ready
     */
    virtual void cancelPrep();
    
    /**
     * Gather the @REQUIREd information for updating
     * @REQUIRE properly initialised
     * @ENSURE update ready
     */
    virtual void prepUpdate();
    
    /**
     * Upate acceleration, speed and position (and possibly currentRoad)
     * Note: tries to respect speed limits, but does not guaranty it
     * @REQUIRE properly initialised, update prepared, simulation active
     * @ENSURE get<acc/pos> is within limits minimum distance is respected, update NOT ready
     */
    virtual void execUpdate();

protected:
    void fullStop(unsigned int distance);
    
    void stepAcceleration();
    void stepSpeed();
    void stepPosition();
    
    SimulationInfo snapShot;
};


#endif //LNJPSE_PROJECT_DEFAULTVEHICLE_H
