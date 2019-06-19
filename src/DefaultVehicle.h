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
     * Does NOT create a properly initialised vehicle
     * @ENSURE(typeName == "Car");
     * + the pre- & postconditions from the corresponding method in Vehicle
     */
    DefaultVehicle();
    
    /**
     * Minimal constructor
     * Acceleration, speed and position are assumed to be 0
     * @REQUIRE(typeName == "MotorCycle" || typeName == "Car" || typeName == "Bus" || typeName == "Truck",
     * @ENSURE(this->typeName == typeName);
     * @ENSURE(!updateReady());
     * + the pre- & postconditions from the corresponding method in Vehicle
     */
    DefaultVehicle(RoadSystem* environment, const string& licensePlate, Road* currentRoad,
            std::string typeName, unsigned int len, const VehicleLimits* limits);
    
    /**
     * Maximal constructor
     * Acceleration, speed and position are assumed to be 0
     * @REQUIRE(typeName == "MotorCycle" || typeName == "Car" || typeName == "Bus" || typeName == "Truck",
     * @ENSURE(this->typeName == typeName);
     * @ENSURE(!updateReady());
     * + the pre- & postconditions from the corresponding method in Vehicle
     */
    DefaultVehicle(RoadSystem* environment, const string& licensePlate, Road* currentRoad, int acceleration, int speed, unsigned int position,
            std::string typeName, unsigned int len, const VehicleLimits* limits);
    
    
    /**
     * Funtion purely to check pre- and postconditions
     * @REQUIRE REQUIRE(properlyInitialised())
     */
    virtual bool updateReady();
    
    /**
     * In case changes need to happen between preparing and updating, use this for safety
     * @REQUIRE REQUIRE(properlyInitialised())
     * @ENSURE ENSURE(!updateReady())
     */
    virtual void cancelPrep();
    
    /**
     * Gather the required information for updating
     * @REQUIRE REQUIRE(properlyInitialised())
     * @ENSURE ENSURE(updateReady())
     */
    virtual void prepUpdate();
    
    /**
     * Upate acceleration, speed and position (and possibly currentRoad)
     * Note: tries to respect speed limits, but does not guaranty it
     * see specification for more info
     * @REQUIRE(properlyInitialised());
     * @REQUIRE(updateReady());
     * @REQUIRE(getEnv() == NULL || getEnv()->simulationActive());
     * @ENSURE(limits->minAcc <= getAcceleration() && getAcceleration() <= limits->maxAcc);
     * @ENSURE(0 <= getPosition() && (getCurrentRoad()==NULL || getPosition() <= getCurrentRoad()->getLength()));
     * @ENSURE(!updateReady());
     */
    virtual void execUpdate();

protected:
    void fullStop(unsigned int distance);
    bool willStop();
    bool willStop(int acceleration);
    
    void stepAcceleration();
    void stepSpeed();
    void stepPosition();
    
    SimulationInfo snapShot;
};


#endif //LNJPSE_PROJECT_DEFAULTVEHICLE_H
