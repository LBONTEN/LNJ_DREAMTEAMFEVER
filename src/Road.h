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
    
    int getLength() const { return length; }
    
    Road* getConnection() {
        if (connections.empty()) {
            return NULL;
        }
        
        return connections[0];
    }

private:
    string name;
    int length;
    int maximumSpeed;
    vector<Road*> connections;
    vector<Vehicle*> vehicles;


//    bool is_free();

};

#endif //LNJ_PIZZA_PROJECT_ROAD_H
