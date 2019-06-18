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
class Lane;


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
    VehicleSnap(const string& licensePlate, int acceleration, int speed, unsigned int position, unsigned int length);
    
    string licensePlate;
    unsigned int acceleration;
    unsigned int speed;
    unsigned int position;
    unsigned int length;
};


struct SimulationInfo {
public:
    SimulationInfo() : prepared(false), nextVehCopy(NULL) {}
    virtual ~SimulationInfo() {delete nextVehCopy;}
    
    void setNextVeh(Vehicle* vehicle);
    
    bool prepared;
    VehicleSnap* nextVehCopy;
};


class Vehicle {
public:
    /**
     * Default constructor
     * @ENSURE(!properlyInitialised())
     */
    Vehicle();
    
    /**
     * Minimal constructor
     * Acceleration, speed and position are assumed to be 0
     * @REQUIRE(limits != NULL)
     * @ENSURE(properlyInitialised())
     * @ENSURE(getEnv()==environment &&
           getLicensePlate()==licensePlate &&
           getLen()==length &&
           getLimits()==limits &&
           getCurrentRoad() == currentRoad,
           "Car constructor failed to assign variable(s)")
     * @ENSURE(getAcceleration()==0 &&
           getSpeed()==0 &&
           getPosition()==0,
     */
    Vehicle(RoadSystem* environment, const string& licensePlate, unsigned int length, const VehicleLimits* limits,  Road* currentRoad);
    
    /**
     * Maximal constructor
     * @REQUIRE(limits != NULL)
     * @ENSURE(properlyInitialised())
     * @ENSURE(getEnv()==environment &&
           getLicensePlate()==licensePlate &&
           getLen()==length &&
           getLimits()==limits &&
           getCurrentRoad() == currentRoad,
           "Car constructor failed to assign variable(s)")
     * @ENSURE(getAcceleration()==acceleration &&
           getSpeed()==speed &&
           getPosition()==position,
     */
    Vehicle(RoadSystem* environment, const string& licensePlate, unsigned int length, const VehicleLimits* limits, Road* currentRoad, int acceleration,  int speed, unsigned int position);
    
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
     * Setter function
     * @REQUIRE(properlyInitialised())
     * @REQUIRE(getEnv() == NULL || !getEnv()->simulationActive()
     * @ENSURE(getLicensePlate() == licensePlate)
     */
    void setLicensePlate(const string& licensePlate);
    
    /**
     * Setter function
     * @REQUIRE(properlyInitialised())
     * @REQUIRE(getEnv() == NULL || !getEnv()->simulationActive()
     * @ENSURE(getAcceleration() == acceleration) (after clamping acceleration between acceleration limits)
     */
    void setAcceleration(int acceleration);
    
    /**
     * Setter function
     * @REQUIRE(properlyInitialised())
     * @REQUIRE(getEnv() == NULL || !getEnv()->simulationActive()
     * @ENSURE(getSpeed() == speed) (after clamping speed between speed limits)
     */
    void setSpeed(int speed);
    
    /**
     * Setter function
     * @REQUIRE(properlyInitialised())
     * @REQUIRE(getEnv() == NULL || !getEnv()->simulationActive()
     * @ENSURE(getPosition() == position) (after clamping speed between speed limits & the road's max speed (if any))
     */
    void setPosition(unsigned int position);
    
    /**
     * Setter function
     * @REQUIRE(properlyInitialised())
     * @REQUIRE(getEnv() == NULL || !getEnv()->simulationActive()
     * @ENSURE(getLen() == len)
     */
    void setLen(unsigned int len);
    
    /**
     * Setter function
     * @REQUIRE(properlyInitialised())
     * @REQUIRE(getEnv() == NULL || !getEnv()->simulationActive()
     * @ENSURE(getEnv() == env)
     */
    void setEnv(RoadSystem* env);
    
    void setRoad(Road* newRoad);
    
    /**
     * Special case of a setter function
     * @REQUIRE(properlyInitialised())
     * @REQUIRE(getEnv() == NULL || !getEnv()->simulationActive()
     * @ENSURE ENSURE(getCurrentLane() == newLane, "Failed to set lane")
     */
    void setLane (Lane* newLane);

    /**
     * Getter function
     * @REQUIRE(properlyInitialised())
     */
    RoadSystem* getEnv() const ;
    
    /**
     * Getter function
     * @REQUIRE(properlyInitialised())
     */
    string getLicensePlate() const ;
    
    /**
     * Getter function
     * @REQUIRE(properlyInitialised())
     */
    Road* getCurrentRoad() const ;
    
    /**
     * Getter function
     * @REQUIRE(properlyInitialised())
     */
    Lane* getCurrentLane() const ;
    
    /**
     * Getter function
     * @REQUIRE(properlyInitialised())
     */
    int getAcceleration() const ;
    
    /**
     * Getter function
     * @REQUIRE(properlyInitialised())
     */
    int getSpeed() const ;
    
    /**
     * Getter function
     * @REQUIRE(properlyInitialised())
     */
    unsigned int getPosition() const ;

    /**
     * special case of getter function
     * does not require anything
     */
    const string& getTypeName() const;
    
    /**
     * special case of getter function
     * does not require anything
     */
    unsigned int getLen() const ;
    
    /**
     * special case of getter function
     * does not require anything
     */
    const VehicleLimits* getLimits() const;

    /**
     * get the next vehicle on the current road (NULL if none exist)
     * @REQUIRE properly initialised
     */
    Vehicle* nextVeh();

protected:
    void hardSetLicencePlate(const string& licencePlate) { Vehicle::licensePlate = licencePlate; }
    void hardSetLane(Lane* newLane) { Vehicle::currentLane = newLane; }
    void hardSetAcceleration(int acceleration) { Vehicle::acceleration = acceleration; }
    void hardSetSpeed(int speed) { Vehicle::speed = speed; }
    void hardSetPosition(unsigned int position) { Vehicle::position = position; }
    void hardSetLen(unsigned int len) { Vehicle::len = len; }
    void hardSetEnv(RoadSystem* env) { Vehicle::environment = env; }
    
    const VehicleLimits* limits;
    
    string typeName;

private:
    string licensePlate;
    Lane* currentLane;
    int acceleration;
    int speed;
    unsigned int position;
    unsigned int len;

    RoadSystem* environment;
    Vehicle* selfPtr;
};

#endif //LNJPSE_VEHICLE_H
