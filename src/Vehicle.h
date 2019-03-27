/* created by Joren Van Borm & Lenny Bontenakel
 */

#ifndef LNJPSE_VEHICLE_H
#define LNJPSE_VEHICLE_H

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
    VehicleSnap(const string& licensePlate, int acceleration, unsigned int speed, int position, int length);
    
    string licensePlate;
    int acceleration;
    unsigned int speed;
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
     * ENSURE properly initialised, get <param> = param, get <acc/spd/pos> = 0
     */
    Vehicle(RoadSystem* environment, const string& licensePlate, int length, const VehicleLimits* limits,  Road* currentRoad);
    
    /**
     * Maximal constructor
     * ENSURE properly initialised, get <param> = param
     */
    Vehicle(RoadSystem* environment, const string& licensePlate, int length, const VehicleLimits* limits, Road* currentRoad, int acceleration, int speed, int position);
    
    virtual ~Vehicle();
    
    /**
     * Funtion purely to check pre- and postconditions
     */
    bool properlyInitialised() const;
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
    RoadSystem* getEnv() const ;
    string getLicensePlate() const ;
    Road* getCurrentRoad() const ;
    int getAcceleration() const ;
    int getSpeed() const ;
    int getPosition() const ;
    int getLen() const ;
    const VehicleLimits* getLimits();

    /** operator <
     *
     *  OUT:
     *      True when left hand side is smaller than right hand side
     *
     *  Précondition:
     *      Must be properly initialised
     */
    bool operator < (const Vehicle& vehic) const;

protected:
    Vehicle* nextCar();
    
    void hardSetLicencePlate(const string& licencePlate) { Vehicle::licensePlate = licencePlate; }
    void hardSetRoad(Road* newRoad) { Vehicle::currentRoad = newRoad; }
    void hardSetAcceleration(int acceleration) { Vehicle::acceleration = acceleration; }
    void hardSetSpeed(int speed) { Vehicle::speed = speed; }
    void hardSetPosition(int position) { Vehicle::position = position; }
    void hardSetLen(int cm) { Vehicle::len = cm; }
    
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

#endif //LNJPSE_VEHICLE_H
