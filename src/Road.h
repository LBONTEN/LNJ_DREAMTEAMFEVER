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

    Road(string name, int length, int maxSpeed, RoadSystem* environment);


    /***********************
     *    ~Destructor~     *
     ***********************/

    ~Road();

    /*******************
     *    ~Setters~    *
     *******************/


    void setConnection(Road *newConnection);
    void addVehicle(Vehicle* newVehicle);


    /*******************
     *    ~Getters~    *
     *******************/


    int getLength() const;
    const string& getName() const;
    const vector<Road*>& getConnections() const;
    const list<Vehicle*>& getVehicles() const;
    Road* getConnection() const;
    Vehicle* getVehicle(string licensePlate) const;
    
    int getMaximumSpeed() const;
    
    /*************************
    *    ~Public members~    *
    **************************/

    void removeVehicle(const Vehicle* vehicToRemove);
    void removeConnection(const Road* connectionToRemove);
    bool properlyInitialised() const;
    int remainingSpace() const;
    bool isFree() const;
    Vehicle* getCarOnPosition(unsigned int position, bool inclusive) const;
    bool checkIfClosest(const Vehicle& vehicToCheck, int position) const;

private:
    RoadSystem* environment;
    string name;
    int length;
    int maximumSpeed;
    vector<Road*> connections;
    list<Vehicle*> vehicles;

};

#endif //LNJPSE_PROJECT_ROAD_H
