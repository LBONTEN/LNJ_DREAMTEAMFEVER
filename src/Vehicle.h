/* created by Joren Van Borm & Lenny Bontenakel
 */

#ifndef LNJ_PIZZA_PROJECT_VEHICLE_H
#define LNJ_PIZZA_PROJECT_VEHICLE_H

#include <string>
#include <map>
#include <vector>
using namespace std;

class RoadSystem;

class Road; // must forward declare to prevent circular dependency

class Vehicle {
public:
    // Constructor
    Vehicle();

    // Destructor
    ~Vehicle();

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
    Vehicle(RoadSystem* environment, const string& licensePlate, Road* currentRoad, double acceleration, double speed, double position);
    
    /**
     * As advertised on the box
     */
    bool properlyInitialised();
    
    /**
     * Setter functions
     * REQUIRE simulation not started
     * ENSURE get<attr> = <arg>
     */
    void setLicensePlate(const string& licensePlate) {Vehicle::licensePlate = licensePlate;}
    void setCurrentRoad(Road* currentRoad) {Vehicle::currentRoad = currentRoad;}
    void setAcceleration(double acceleration) {Vehicle::acceleration = acceleration;}
    void setSpeed(double speed) {Vehicle::speed = speed;}
    void setPosition(double position) {Vehicle::position = position;}

    /**
     * Getter functions
     * REQUIRE properly initialised
     */
    string getLicensePlate() { return licensePlate; }
    Road* getCurrentRoad() { return currentRoad; }
    double getAcceleration() { return acceleration; }
    double getSpeed() { return speed; }
    double getPosition() { return position; }

    /**
     * Advance acceleration, speed and position
     * REQUIRE properly initialised
     * ENSURE get<attr> respects simulation rules
     */
    void update();

protected:
    virtual void stepAcceleration();
    virtual void stepSpeed();
    virtual void stepPosition();
    
    void hardSetCurrentRoad(Road* currentRoad) {Vehicle::currentRoad = currentRoad;}
    void hardSetAcceleration(double acceleration) {Vehicle::acceleration = acceleration;}
    void hardSetSpeed(double speed) {Vehicle::speed = speed;}
    void hardSetPosition(double position) {Vehicle::position = position;}

private:
    map<string, Vehicle*> VehicleLookUp;
    vector<Vehicle*> VehicleIt;

    string licensePlate;
    Road* currentRoad;
    double acceleration;
    double speed;
    double position;

    RoadSystem* environment;
    Vehicle* selfPtr;
};

#endif //LNJ_PIZZA_PROJECT_VEHICLE_H
