/* created by Van Borm Joren & Bontenakel Lenny
 */

#include "Vehicle.h"
#include <vector>

#ifndef LNJ_PIZZA_PROJECT_ROAD_H
#define LNJ_PIZZA_PROJECT_ROAD_H

class Road
{

public:

    Road(string name, int length, int maxSpeed): name(name), length(length), maximumSpeed(maxSpeed) {
    }
    ~Road();

    void pushConnections(Road* newConnection) { connections.push_back(newConnection); }
    void pushVehicle(Vehicle* newVehicle) { vehicles.push_back(newVehicle); }

    const string& getName() { return name; }



private:
    string name;
    int length;
    int maximumSpeed;
    vector<Road*> connections;
    vector<Vehicle*> vehicles;


//    bool is_free();

};

#endif //LNJ_PIZZA_PROJECT_ROAD_H
