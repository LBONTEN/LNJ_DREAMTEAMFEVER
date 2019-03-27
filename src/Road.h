/* created by Van Borm Joren & Bontenakel Lenny
 */

#include "Vehicle.h"
#include "design_by_contract.h"
#include <vector>
#include <list>


#ifndef LNJ_PIZZA_PROJECT_ROAD_H
#define LNJ_PIZZA_PROJECT_ROAD_H

extern const unsigned int minimumSpace;

class Road {
public:

    /***********************
     *    ~Constructor~    *
     ***********************/

    Road(string name, int length, int maxSpeed);


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


    /*************************
    *    ~Public members~    *
    **************************/


    bool properlyInitialised() const;
    int remainingSpace() const;
    bool isFree() const;
    const Vehicle& getCarOnPosition(unsigned int position) const;

private:
    string name;
    int length;
    int maximumSpeed;
    vector<Road*> connections;
    list<Vehicle*> vehicles;

};

#endif //LNJ_PIZZA_PROJECT_ROAD_H
