/* created by Van Borm Joren & Bontenakel Lenny
 */


#include "Vehicle.h"
#include "Car.h"
#include "design_by_contract.h"

#include <vector>
#include <list>

class RoadSystem;

#ifndef LNJPSE_PROJECT_ROAD_H
#define LNJPSE_PROJECT_ROAD_H

extern const unsigned int minimumSpace;

class Road {
public:

    /***********************
     *    ~Constructor~    *
     ***********************/

    Road(string name, unsigned int length, unsigned int maxSpeed, RoadSystem* environment);

    /*******************
     *    ~Setters~    *
     *******************/


    void setConnection(Road *newConnection);
    void addVehicle(Vehicle* newVehicle);


    /*******************
     *    ~Getters~    *
     *******************/


    unsigned int getLength() const;
    const string& getName() const;
    const vector<Road*>& getConnections() const;
    const list<Vehicle*>& getVehicles() const;
    Road* getConnection() const;
    Vehicle* getVehicle(string licensePlate) const;
    
    unsigned int getMaximumSpeed() const;
    
    /*************************
    *    ~Public members~    *
    **************************/

    void removeVehicle(const Vehicle* vehicToRemove);
    void removeConnection(const Road* connectionToRemove);
    bool properlyInitialised() const;
    unsigned int remainingSpace() const;
    bool isFree() const;
    Vehicle* getCarOnPosition(unsigned int position, bool inclusive) const;
    bool checkIfClosest(const Vehicle& vehicToCheck, unsigned int position) const;

private:
    RoadSystem* environment;
    string name;
    unsigned int length;
    unsigned int maximumSpeed;
    vector<Road*> connections;
    list<Vehicle*> vehicles;

};

#endif //LNJPSE_PROJECT_ROAD_H
