//
// Created by Joren Van Borm on 2019-03-27.
//

#include "Output.h"
#include "Vehicle.h"
#include "Road.h"
#include "RoadSigns.h"
#include <vector>
#include <cmath>


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
           << prefix << "\t-> Speed limit: " << source->getSpeedLimit() << std::endl
           << prefix << "\t-> length: " << source->getLength() << std::endl;
}


///--- functions from Output class ---///

ostream& Output::classicPrint(ostream& target) const
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

Output::Output(RoadSystem* simulation) : simulation(simulation), style(classic) {}


///--- overloaded stream operator ---///
ostream& operator<<(ostream& target, const Output& print)
{
    switch (print.style)
    {
        case classic:
            return print.classicPrint(target);
    
        case text_graphic:
            return print.textGraphicPrint(target);
    }
    return target;
}

ostream& Output::textGraphicPrint(ostream& target, unsigned int maxChar) const
{
    const vector<Road*>& rdVec = simulation->getVectorOfRoads();
    
    // find the longest road to determine scale
    unsigned int longestD = 0;
    unsigned long longestName = 0;
    for (unsigned long rdNum = 0; rdNum < rdVec.size(); ++rdNum)
    {
        longestD =  (rdVec[rdNum]->getLength() > longestD) ? rdVec[rdNum]->getLength() : longestD;
        longestName = (rdVec[rdNum]->getName().size() > longestName) ? rdVec[rdNum]->getName().size() : longestName;
    }
    unsigned int metresPerChar = max((unsigned int) (longestD / maxChar), (unsigned int) 1);
    
    target << "\n -~=| Scaling at " << metresPerChar << " metres / char |=~- \n" << endl;
    
    // print each road
    for (unsigned long rdNum = 0; rdNum < rdVec.size(); ++rdNum)
    {
        Road* currRd = rdVec[rdNum];
        
        const vector<Lane*>& lanes = currRd->getLanes();
        
        // construct the edge string (includes traffic signaling)
        string rdEdge (ceil((double)currRd->getLength() / metresPerChar), '=');
        RoadSign* sign = currRd->getSignOnPosition(0, true);
        while (sign)
        {
            switch (sign->getType())
            {
                case trafficLight :
                {
                    rdEdge.at(sign->getPosition() / metresPerChar) = 'L';
                    break;
                }
                case busStop :
                {
                    rdEdge.at(sign->getPosition() / metresPerChar) = 'H';
                    break;
                }
                case zoneStart :
                {
                    rdEdge.at(sign->getPosition() / metresPerChar) = 'Z';
                    break;
                }
            }
            
            // get first sign starting from next char
            sign = currRd->getSignOnPosition(((sign->getPosition()/metresPerChar)+1)*metresPerChar, false);
        }
        
        // print road "header"
        target << currRd->getName() << string (longestName-currRd->getName().size()+1, ' ') << "| " << rdEdge;
        if (currRd->getConnection())
        {
            target << " ->" << currRd->getConnection()->getName();
        }
        target << endl;
        
        // print each lane
        for (unsigned int laneNr = lanes.size()-1; laneNr < lanes.size(); --laneNr) // slightly weird for-loop on account of signedness
        {
            Lane* currLn = lanes[laneNr];
            
            string rdLane (ceil((double)currRd->getLength() / metresPerChar), ' ');
            
            Vehicle* veh = currLn->getCarOnPosition(0, true);
            while (veh)
            {
                if (veh->getTypeName() == "MotorCycle") rdLane.at(veh->getPosition() / metresPerChar) = 'M';
                else if (veh->getTypeName() == "Car") rdLane.at(veh->getPosition() / metresPerChar) = 'A';
                else if (veh->getTypeName() == "Bus") rdLane.at(veh->getPosition() / metresPerChar) = 'B';
                else if (veh->getTypeName() == "Truck") rdLane.at(veh->getPosition() / metresPerChar) = 'V';
                else rdLane[veh->getPosition()] = '?';
    
                // set veh to first veh starting from next char
                veh = currLn->getCarOnPosition(((veh->getPosition()/metresPerChar)+1)*metresPerChar, false);
            }
    
            target << string(longestName+1, ' ') << "| " << rdLane << endl;
            
            if (laneNr > 0)
            {
                target << string(longestName+1, ' ') << "| " << string(ceil((double)currRd->getLength() / metresPerChar), '-') << endl;
            }
        }
        
        target << string(longestName+1, ' ') << "| " << rdEdge << endl;
    
        if (rdNum <= rdVec.size()-1)
        {
            target << endl;
        }
    }
    
    return target;
}
