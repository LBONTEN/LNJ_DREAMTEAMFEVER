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
     * @ENSURE(properlyInitialised())
     * @ENSURE(getVectorOfVehicles().empty())
     * @ENSURE(getVectorOfRoads().empty())
     * @ENSURE(!simulationActive() && timeActive() == 0)
     */
    RoadSystem();
    
    /**
     * initialise a simulation w/ roads & vehicles loaded
     * @ENSURE(properlyInitialised())
     * @ENSURE(getVectorOfVehicles() == vehicles)
     * @ENSURE(getVectorOfRoads() == roads)
     * @ENSURE(!simulationActive() && timeActive() == 0)
     */
    RoadSystem(const vector<Road*>& roads, const vector<Vehicle*>& vehicles);
    
    /**
     * destructor
     * (note: destroys all contained vehicles & roads)
     */
    virtual ~RoadSystem();
    
    /**
     * updates are suppressed when false
     * limits editing of the simulation when true
     * @REQUIRE(properlyInitialised())
     */
    bool simulationActive() const;
    
    /**
     * check whether there are any cars in the simulation
     * @REQUIRE(properlyInitialised())
     */
    bool empty() const;
    
    /**
     * the amount of simulated time the simulation hes been active.
     * returns 0 if simulation not active
     * @REQUIRE(properlyInitialised())
     */
    unsigned long timeActive() const;
    
    /**
     * query function to check pre- (&post-) conditions
     */
    bool properlyInitialised() const;
    
    /**
     * start the simulation
     * this prevents direct editing of the elements within, but enables advancing the simulation
     * @REQUIRE(properlyInitialised())
     * @ENSURE(simulationActive())
     */
    void activate();
    
    /**
     * automatically execute all actions necessary to advance the simulation by one second
     * (note: vehicles leaving the simulation will be destroyed)
     * @REQUIRE(properlyInitialised())
     * @REQUIRE(simulationActive())
     */
    void advanceSimulation();
    
    /**
     * automatically run the simulation until it is empty
     * (warning: cannot be interrupted from within the program & may be an infinite loop)
     * @REQUIRE(properlyInitialised())
     * @ENSURE(empty())
     * @ENSURE(simulationActive())
     */
    void untilEmpty();
     
     /**
      * automatically run the simulation for a set amount of simulated time
      * (or until it is empty)
      * @REQUIRE(properlyInitialised())
      * @ENSURE(empty() || iteration >= seconds)
      * @ENSURE(simulationActive())
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
     * @REQUIRE(properlyInitialised())
     * @ENSURE(getVectorOfRoads() == vectorOfRoads
     */
    void setVectorOfRoads(const vector<Road*>& vectorOfRoads);
    
    /**
     * setter functions
     * @REQUIRE(properlyInitialised())
     * @ENSURE(getVectorOfVehicles() == vectorOfVehicles
     */
    void setVectorOfVehicles(const vector<Vehicle*>& vectorOfVehicles);
    
    /**
     * querry to check whether a given vehicle/road exists in the system
     * (note: quite slow, look into using maps / sets for speed-up)
     * @REQUIRE(properlyInitialised())
     */
    bool contains(const Vehicle* querry) const;
    bool contains(const Road* querry) const;
    
    /**
     * add function
     * @REQUIRE(properlyInitialised())
     * @ENSURE(contains(newVehicle))
     */
    void addVehicle(Vehicle* newVehicle);
    
    /**
     * add function
     * @REQUIRE(properlyInitialised())
     * @ENSURE(contains(newRoad))
     */
    void addRoad(Road* newRoad);
    
    /**
     * remove function
     * (note: quite slow, look into using maps / sets for speed-up)
     * warning: does NOT de-allocate associated memory
     * @REQUIRE(properlyInitialised())
     * @ENSURE(!contains(oldRoad))
     */
    void removeRoad(Road* oldRoad);
    
    /**
     * remove function
     * (note: quite slow, look into using maps / sets for speed-up)
     * warning: does NOT de-allocate associated memory
     * @REQUIRE(properlyInitialised())
     * @ENSURE(!contains(oldVehicle))
     */
    void removeVehicle(Vehicle* oldVeh);

private:
    vector<Road*> vectorOfRoads;
    vector<Vehicle*> vectorOfVehicles;
    
    bool active;
    
    unsigned long time;
    
    RoadSystem* selfPtr;
};

#endif //LNJPSE_ROADSYSTEM_H
