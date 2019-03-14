/* created by Van Borm Joren & Bontenakel Lenny
 */

#include <map>
#include "Road.h"

#ifndef LNJ_PIZZA_PROJECT_ROADSYSTEM_H
#define LNJ_PIZZA_PROJECT_ROADSYSTEM_H
using namespace std;


class RoadSystem
{
public:
    
    RoadSystem(vector<Road*> roads, vector<Vehicle*> vehicles): roadIt(roads), vehicleIt(vehicles) {}

    bool simulationActive() {return false;} //TODO: actually implement this function

private:
    vector<Road*> roadIt;
    vector<Vehicle*> vehicleIt;
//    bool simulationActive;
//    bool is_empty();
//
//    void load_simulation();
//    void dump_simulation();
//    void advance_simulation();
};

#endif //LNJ_PIZZA_PROJECT_ROADSYSTEM_H
