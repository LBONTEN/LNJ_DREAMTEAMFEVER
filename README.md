# LNJ_PSE_2018-2019
Lenny and Joren's Software Engineering Project. 

## Design
- RoadSystem contains a set of roads & vehicles.
At each step of the simulation, each vehicle in the system is stepped as well. This is done in a two step process: first all vehicles gather the required information about the system, then all cars update their own information accordingly. This prevents being dependent on the order in wich vehicles are updated.

- Roads contain a set of vehicles (a subset of those of the system) by their licence plate (and by their position on the road), as well as some attributes such as length and connections, a name and a pointer to the roadsystem it is a part of.
Roads do not change over time, thus they need not be stepped in the simulation.

- Vehicles contain a series of attributes such as acceleration, speed and position, as well as a licence plate (used as a UUID), the street they're on (by name) and a pointer to the roadsystem it is a part of.
At each step of the simulation, the vehicle's acceleration, speed and position (and possibly the road it's on) are updated.