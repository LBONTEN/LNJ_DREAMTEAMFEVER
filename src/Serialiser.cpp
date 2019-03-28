//
// Created by Joren Van Borm on 2019-03-27.
//

#include "Serialiser.h"
#include "Vehicle.h"
#include "Road.h"


///--- helper functions ---///

const char* emptyStr = "";

void printVehicle(Vehicle* source, ostream& target, const char* prefix=emptyStr)
{
    target << prefix << "Vehicle: " << source->getTypeName() << " (" << source->getLicensePlate() << ")" << std::endl
           << prefix << "\t-> Road: " << source->getCurrentRoad()->getName() << std::endl
           << prefix << "\t-> Position: " << source->getPosition() << std::endl
           << prefix << "\t-> Speed: " << source->getSpeed() << std::endl;
}

void printRoad(Road* source, ostream& target, const char* prefix=emptyStr)
{
    target << prefix << "Road: " << source->getName() << std::endl
           << prefix << "\t-> Speed limit: " << source->getMaximumSpeed() << std::endl
           << prefix << "\t-> length: " << source->getLength() << std::endl;
}


///--- functions from Serialiser class ---///

ostream& Serialiser::classicPrint(ostream& target) const
{
    
    for (vector<Road*>::const_iterator currentRd = simulation->getVectorOfRoads().begin();
         currentRd < simulation->getVectorOfRoads().end();
         currentRd++)
    {
        printRoad(*currentRd, target);
        target << std::endl;
    }
    
    target << std::endl;
    
    for (vector<Vehicle*>::const_iterator currentVeh = simulation->getVectorOfVehicles().begin();
         currentVeh < simulation->getVectorOfVehicles().end();
         currentVeh++)
    {
        printVehicle(*currentVeh, target);
        target << std::endl;
    }
    
    return target;
}

Serialiser::Serialiser(RoadSystem* simulation) : simulation(simulation), style(classic) {}


///--- overloaded stream operator ---///
ostream& operator<<(ostream& target, const Serialiser& print)
{
    switch (print.style)
    {
        case classic:
            return print.classicPrint(target);
    }
    return target;
}