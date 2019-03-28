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
     * @ENSURE NOT properly initialised
     */
    Vehicle();
    
    /**
     * Minimal constructor
     * Acceleration, speed and position are assumed to be 0
     * @REQURE <limits> != NULL
     * @ENSURE properly initialised, get <param> = param, get <acc/spd/pos> = 0
     */
    Vehicle(RoadSystem* environment, const string& licensePlate, int length, const VehicleLimits* limits,  Road* currentRoad);
    
    /**
     * Maximal constructor
     * @REQURE <limits> != NULL
     * @ENSURE properly initialised, get <param> = param
     */
    Vehicle(RoadSystem* environment, const string& licensePlate, int length, const VehicleLimits* limits, Road* currentRoad, int acceleration, int speed, int position);
    
    /**
     * destructor
     * @ENSURE  currentroad & environment do not contain <this>
     */
    virtual ~Vehicle();
    
    /**
     * Funtion purely to check pre- and postconditions
     */
    bool properlyInitialised() const;
    virtual bool updateReady()=0;
    
    /**
     * In case changes need to happen between preparing and updating, use this for safety
     * @REQUIRE properly initialised
     * @ENSURE update not prepared
     */
    virtual void cancelPrep()=0;
    
    /**
     * Gather the @REQUIREd information for updating
     * @REQUIRE properly initialised
     * @ENSURE update prepared
     */
    virtual void prepUpdate()=0;
    
    /**
     * Upate acceleration, speed and position (and possibly currentRoad)
     * @REQUIRE properly initialised, update prepared, simulation active
     * @ENSURE get<acc/spd/pos> is within limits
     */
    virtual void execUpdate()=0;
    
    /**
     * Setter functions
     * @REQUIRE simulation not started, properly initialised
     * @ENSURE get<attr> = <arg>, (where applicable) get <attr> is within the defined limits (this has higher priority)
     */
    void setLicensePlate(const string& licensePlate);
    void setAcceleration(int acceleration);
    void setSpeed(int speed);
    void setPosition(int position);
    void setLen(int len);
    
    /**
     * Special case of a setter function
     * @REQUIRE simulation not started, properly initialised
     * @ENSURE get<attr> = <arg>, previous road does not contain vehicle
     */
    void setRoad(Road* newRoad);

    /**
     * Getter functions
     * @REQUIRE properly initialised
     */
    RoadSystem* getEnv() const ;
    string getLicensePlate() const ;
    Road* getCurrentRoad() const ;
    int getAcceleration() const ;
    int getSpeed() const ;
    int getPosition() const ;
    int getLen() const ;
    const VehicleLimits* getLimits();
    
    /**
     * special case of getter function
     * does not require anything
     */
    const string& getTypeName() const;
    
    /**
     * get the next vehicle on the current road (NULL if none exist)
     * @REQUIRE properly initialised
     */
    Vehicle* nextVeh();

protected:
    void hardSetLicencePlate(const string& licencePlate) { Vehicle::licensePlate = licencePlate; }
    void hardSetRoad(Road* newRoad) { Vehicle::currentRoad = newRoad; }
    void hardSetAcceleration(int acceleration) { Vehicle::acceleration = acceleration; }
    void hardSetSpeed(int speed) { Vehicle::speed = speed; }
    void hardSetPosition(int position) { Vehicle::position = position; }
    void hardSetLen(int len) { Vehicle::len = len; }
    
    const VehicleLimits* limits;
    
    string typeName;

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
