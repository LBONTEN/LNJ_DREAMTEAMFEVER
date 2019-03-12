/* created by Van Borm Joren & Bontenakel Lenny
 */

#include "Vehicle.h"
#include <vector>

#ifndef LNJ_PIZZA_PROJECT_ROAD_H
#define LNJ_PIZZA_PROJECT_ROAD_H

class Road
{

public:
    Road(const TiXmlElement& input);
    ~Road();

private:
    string name;
    double length;
    double maximumSpeed;
    vector<string*> connections;
    vector<Vehicle*> occupying_vehicles;
    bool is_free();

};

#endif //LNJ_PIZZA_PROJECT_ROAD_H
