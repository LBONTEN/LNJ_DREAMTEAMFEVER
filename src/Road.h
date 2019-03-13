/* created by Van Borm Joren & Bontenakel Lenny
 */

#include "Vehicle.h"
#include <vector>

#ifndef LNJ_PIZZA_PROJECT_ROAD_H
#define LNJ_PIZZA_PROJECT_ROAD_H

class Road
{

public:
    Road(TiXmlNode input);
    ~Road();

private:
    string name;
    double length;
    int maximumSpeed;
    vector<Road*> connections;
    vector<Vehicle*> occupying_vehicles;
    bool is_free();

};

#endif //LNJ_PIZZA_PROJECT_ROAD_H
