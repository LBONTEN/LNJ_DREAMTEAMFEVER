/* created by Joren Van Borm & Lenny Bontenakel
 */

#ifndef LNJ_PIZZA_PROJECT_VEHICLE_H
#define LNJ_PIZZA_PROJECT_VEHICLE_H

#include <string>
#include <map>
#include <vector>
using namespace std;


/// Forward declarations for other files ///

class RoadSystem;

class Road;


/// Forward declarations for this file ///

class Vehicle;


/// Actual definitions of classes ///

struct VehicleSnap {
    VehicleSnap();
    VehicleSnap(Vehicle* source);
    
    string licensePlate;
    int acceleration;
    int speed;
    int position;
};


struct SimulationInfo {
public:
    SimulationInfo() : prepared(false), nextCarCopy() {}
    
    bool prepared;
    VehicleSnap nextCarCopy;
};


class Vehicle {
public:
    /**
     * Default constructor
     * ENSURE NOT properly initialised
     */
    Vehicle();
    
    /**
     * Minimal constructor
     * Acceleration, speed and position are assumed to be 0
     * ENSURE properly initialised
     */
    Vehicle(RoadSystem* environment, const string& licensePlate, Road* currentRoad);
    
    /**
     * Maximal constructor
     * ENSURE properly initialised
     */
    Vehicle(RoadSystem* environment, const string& licensePlate, Road* currentRoad, int acceleration, int speed, int position);
    
    /**
     * Funtion purely to check pre- and postconditions
     */
    bool properlyInitialised();
    bool updateReady();
    
    /**
     * In case changes need to happen between preparing and updating, use this for safety
     * REQUIRE properly initialised
     * ENSURE update not prepared
     */
     void cancelPrep();
    
    /**
     * Gather the required information for updating
     * REQUIRE properly initialised
     * ENSURE update prepared
     */
    void prepUpdate();
    
    /**
     * Upate acceleration, speed and position (and possibly currentRoad)
     * REQUIRE properly initialised, update prepared, simulation active
     * ENSURE TODO: find a good postcondition here
     */
    void execUpdate();
    
    /**
     * Setter functions
     * REQUIRE simulation not started, properly initialised
     * ENSURE get<attr> = <arg>
     */
    void setLicensePlate(const string& licensePlate);
    void setRoad(Road* newRoad);
    void setAcceleration(int acceleration);
    void setSpeed(int speed);
    void setPosition(int position);

    /**
     * Getter functions
     * REQUIRE properly initialised
     */
    RoadSystem* getEnv();
    string getLicensePlate();
    Road* getCurrentRoad();
    int getAcceleration();
    int getSpeed();
    int getPosition();

protected:
    virtual void stepAcceleration();
    virtual void stepSpeed();
    virtual void stepPosition();
    
    Vehicle* nextCar();
    
    void hardSetLicencePlate(const string& licencePlate) {Vehicle::licensePlate = licencePlate;}
    void hardSetRoad(Road* newRoad) {Vehicle::currentRoad = newRoad;}
    void hardSetAcceleration(int acceleration) {Vehicle::acceleration = acceleration;}
    void hardSetSpeed(int speed) {Vehicle::speed = speed;}
    void hardSetPosition(int position) {Vehicle::position = position;}
    
    SimulationInfo snapShot;
    
private:
    string licensePlate;
    Road* currentRoad;
    int acceleration;
    int speed;
    int position;

    RoadSystem* environment;
    Vehicle* selfPtr;
};

#endif //LNJ_PIZZA_PROJECT_VEHICLE_H
