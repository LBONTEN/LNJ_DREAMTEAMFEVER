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

struct VehicleLimits {
    VehicleLimits(int minAcc, int maxAcc, int minSpd, int maxSpd) :
        minAcc(minAcc),
        maxAcc(maxAcc),
        minSpd(minSpd),
        maxSpd(maxSpd) {}
    
    int minAcc;
    int maxAcc;
    
    int minSpd;
    int maxSpd;
};

struct VehicleSnap {
    VehicleSnap();
    VehicleSnap(Vehicle* source);
    VehicleSnap(const string& licensePlate, int acceleration, int speed, int position, int length);
    
    string licensePlate;
    int acceleration;
    int speed;
    int position;
    int length;
};


struct SimulationInfo {
public:
    SimulationInfo() : prepared(false), nextCarCopy(NULL) {}
    virtual ~SimulationInfo() {delete nextCarCopy;}
    
    void setNextCar(Vehicle* vehicle);
    
    bool prepared;
    VehicleSnap* nextCarCopy;
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
    Vehicle(RoadSystem* environment, const string& licensePlate, int length, const VehicleLimits* limits,  Road* currentRoad);
    
    /**
     * Maximal constructor
     * ENSURE properly initialised
     */
    Vehicle(RoadSystem* environment, const string& licensePlate, int length, const VehicleLimits* limits, Road* currentRoad, int acceleration, int speed, int position);
    
    /**
     * Funtion purely to check pre- and postconditions
     */
    bool properlyInitialised();
    virtual bool updateReady()=0;
    
    /**
     * In case changes need to happen between preparing and updating, use this for safety
     * REQUIRE properly initialised
     * ENSURE update not prepared
     */
    virtual void cancelPrep()=0;
    
    /**
     * Gather the required information for updating
     * REQUIRE properly initialised
     * ENSURE update prepared
     */
    virtual void prepUpdate()=0;
    
    /**
     * Upate acceleration, speed and position (and possibly currentRoad)
     * REQUIRE properly initialised, update prepared, simulation active
     * ENSURE get<acc/spd/pos> is within limits
     */
    virtual void execUpdate()=0;
    
    /**
     * Setter functions
     * REQUIRE simulation not started, properly initialised
     * ENSURE get<attr> = <arg>, (where applicable) <attr> is within the defined limits
     */
    void setLicensePlate(const string& licensePlate);
    void setRoad(Road* newRoad);
    void setAcceleration(int acceleration);
    void setSpeed(int speed);
    void setPosition(int position);
    void setLen(int cm);

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
    int getLen();

protected:
    Vehicle* nextCar();
    
    void hardSetLicencePlate(const string& licencePlate) {Vehicle::licensePlate = licencePlate;}
    void hardSetRoad(Road* newRoad) {Vehicle::currentRoad = newRoad;}
    void hardSetAcceleration(int acceleration) {Vehicle::acceleration = acceleration;}
    void hardSetSpeed(int speed) {Vehicle::speed = speed;}
    void hardSetPosition(int position) {Vehicle::position = position;}
    void hardSetLen(int cm) {Vehicle::len = cm;}
    
    const VehicleLimits* limits;
    
private:
    string licensePlate;
    Road* currentRoad;
    int acceleration;
    int speed;
    int position;
    int len;

    RoadSystem* environment;
    Vehicle* selfPtr;
};

#endif //LNJ_PIZZA_PROJECT_VEHICLE_H
