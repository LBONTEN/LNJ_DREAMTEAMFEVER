/* created by Joren Van Borm & Lenny Bontenakel
 */

#ifndef LNJ_PIZZA_PROJECT_VEHICLE_H
#define LNJ_PIZZA_PROJECT_VEHICLE_H

#include <string>
using namespace std;

class RoadSystem; // must forward declare to prevent circular dependency

class Vehicle
{
public:
    /**
     * Setter functions
     * REQUIRE simulation not started
     * ENSURE get<attr> = <arg>
     */
    void setLicensePlate(const string &license_plate) {Vehicle::licensePlate = license_plate;}
    void setCurrentRoad(const string &current_road) {Vehicle::currentRoad = current_road;}
    void setAcceleration(double acceleration) {Vehicle::acceleration = acceleration;}
    void setSpeed(double speed) {Vehicle::speed = speed;}
    void setPosition(double position) {Vehicle::position = position;}

    /**
     * Getter functions
     * REQUIRE properly initialised
     */
    string getLicensePlate() { return licensePlate; }
    string getCurrentRoad() { return currentRoad; }
    double getAcceleration() { return acceleration; }
    double getSpeed() { return speed; }
    double getPosition() { return position; }

    /**
     * Advance acceleration, speed and position
     * REQUIRE properly initialised
     * ENSURE get<attr> respects simulation rules
     */
    void stepAttributes();

protected:
    virtual void stepAcceleration();
    virtual void stepSpeed();
    virtual void stepPosition();

private:
    string licensePlate;
    string currentRoad;
    double acceleration;
    double speed;
    double position;

    Vehicle* selfPtr; // used to check proper initialisation
    RoadSystem* environment; // needed to look up info about e.g. current road
};

#endif //LNJ_PIZZA_PROJECT_VEHICLE_H
