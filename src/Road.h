/* created by Van Borm Joren & Bontenakel Lenny
 */

#include "Vehicle.h"
#include <vector>

#ifndef LNJ_PIZZA_PROJECT_ROAD_H
#define LNJ_PIZZA_PROJECT_ROAD_H

class Road
{

public:
    Road(string name, int length, int maxSpeed): name(name), length(length), maximumSpeed(maxSpeed) {}
    ~Road();

    void setConnections(Road* newConnection) { connections.push_back(newConnection); }

private:
    string name;
    int length;
    int maximumSpeed;
    vector<Road*> connections;

//    bool is_free();

};

#endif //LNJ_PIZZA_PROJECT_ROAD_H
