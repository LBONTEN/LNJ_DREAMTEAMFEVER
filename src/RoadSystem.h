/* created by Van Borm Joren & Bontenakel Lenny
 */

#include "Road.h"
#include <ostream>


#ifndef LNJPSE_ROADSYSTEM_H
#define LNJPSE_ROADSYSTEM_H


using namespace std;

class RoadSystem
{
public:

    /**
     * initialise an empty simulation
     * @ENSURE properly initialised, get<roads/vehicles> = {}
     */
    RoadSystem();
    
    /**
     * initialise a simulation w/ roads & vehicles loaded
     * @ENSURE properly initialised, get<roads/vehicles> = <roads/vehicles>
     */
    RoadSystem(const vector<Road*>& roads, const vector<Vehicle*>& vehicles);
    
    virtual ~RoadSystem();
    
    /**
     * updates are supressed when false
     * limits editing of the simulation when true
     */
    bool simulationActive();
    
    /**
     * check whether there are any cars in the simulation
     * @REQUIRE properly initialised
     */
    bool empty();
    
    /**
     * start the simulation
     * this prevents direct editing of the elements within, but enables advancing the simulation
     * @REQUIRE properly initialised
     * @ENSURE simulation active
     */
    void activate();
    
    /**
     * automatically execute all actions necessary to advance the simulation by one second
     * @REQUIRE properly initialised, simulation active
     */
    void advanceSimulation();
    
    /**
     * automatically run the simulation until it is empty
     * (warning: cannot be interrupted from within the program & may be an infinite loop)
     * @REQUIRE properly initialised
     * @ENSURE empty, simulation active
     */
    void untilEmpty();
     
     /**
      * automatically run the simulation for a set amount of simulated time
      * (or until it is empty)
      * @REQUIRE properly initialised
      * @ENSURE simulation active
      */
     void untilTime(unsigned long seconds);
     
    /**
     * getter functions
     * @REQUIRE properly initialised
     */
    const vector<Road*>& getVectorOfRoads() const;
    const vector<Vehicle*>& getVectorOfVehicles() const;
    
    /**
     * setter functions
     * @REQUIRE properly initialised
     * @ENSURE get<attr> = <attr>
     */
    void setVectorOfRoads(const vector<Road*>& vectorOfRoads);
    void setVectorOfVehicles(const vector<Vehicle*>& vectorOfVehicles);
    
    /**
     * querry to check whether a given vehicle/road exists in the system
     * (note: quite slow, look into using maps / sets for speed-up)
     * @REQUIRE properly initialised
     */
    bool has(Vehicle* querry);
    bool has(Road* querry);
    
    /**
     * add functions
     * @REQUIRE properly initialised
     * @ENSURE has <road/vehicle>
     */
    void addVehicle( Vehicle* newVehicle);
    void addRoad(Road* newRoad);
    
    /**
     * remove functions
     * (note: quite slow, look into using maps / sets for speed-up)
     * @REQUIRE properly initialised
     * @ENSURE NOT has <road/vehicle>
     */
    void removeRoad(Road* oldRoad);
    void removeVehicle(Vehicle* oldVeh);

private:
    vector<Road*> vectorOfRoads;
    vector<Vehicle*> vectorOfVehicles;
    
    bool active;
};

#endif //LNJPSE_ROADSYSTEM_H
