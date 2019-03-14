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

    RoadSystem() {}
    RoadSystem(vector<Road*> roads, vector<Vehicle*> vehicles): vectorOfRoads(roads), vectorOfVehicles(vehicles) {}

    /*
     * setRoadIt / setVehicleIt:
     *      completely replace vectorOfRoads / vectorOfVehicles vector by another vector containing Vehicles / Roads
     *
     * pushVehicle / pushRoad:
     *      push a single Vehicle / Road in the back of vectorOfVehicles / vectorOfRoads
     */
    void setRoadIt(vector<Road*> newVector) { vectorOfRoads = newVector; }
    void setVehicleIt(vector<Vehicle*> newVector) { vectorOfVehicles = newVector; }
    void pushVehicle( Vehicle& newVehicle) { vectorOfVehicles.push_back(&newVehicle); }
    void pushRoad(Road& newRoad) { vectorOfRoads.push_back(&newRoad); }

    bool simulationActive() {return false;} //TODO: actually implement this function

private:
    vector<Road*> vectorOfRoads;
    vector<Vehicle*> vectorOfVehicles;
//    bool simulationActive;
//    bool is_empty();
//
//    void load_simulation();
//    void dump_simulation();
//    void advance_simulation();
};

#endif //LNJ_PIZZA_PROJECT_ROADSYSTEM_H
