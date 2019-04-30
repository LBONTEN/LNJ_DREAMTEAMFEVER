//
// Created by Joren Van Borm on 2019-03-27.
//

#include "Output.h"
#include "Vehicle.h"
#include "Road.h"
#include "RoadSigns.h"

#include <vector>


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


///--- functions from Serialiser class ---///

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
    
    target << "-~=| Scaling at " << metresPerChar << " metres / char |=~-" << endl;
    
    // print each road
    for (unsigned long rdNum = 0; rdNum < rdVec.size(); ++rdNum)
    {
        Road* currRd = rdVec[rdNum];
        
        const vector<Lane*>& lanes = currRd->getLanes();
        
        // construct the edge string (includes traffic signaling)
        string rdEdge (currRd->getLength() / metresPerChar, '=');
        RoadSign* sign = currRd->getSignOnPosition(0, true);
        while (sign)
        {
            // TODO: get correct letter to represent type
            rdEdge.at(sign->getPosition() / metresPerChar) = 'S';
            
            sign = currRd->getSignOnPosition(sign->getPosition(), false);
        }
        
        // print road "header"
        target << currRd->getName() << string (longestName-currRd->getName().size()+1, ' ') << "| " << rdEdge;
        if (currRd->getConnection())
        {
            target << " ->" << currRd->getConnection()->getName();
        }
        target << endl;
        
        // print each lane
        for (unsigned int laneNr = 0; laneNr < lanes.size(); ++laneNr)
        {
            Lane* currLn = lanes[laneNr];
            
            string rdLane (currRd->getLength() / metresPerChar, ' ');
            
            Vehicle* veh = currLn->getCarOnPosition(0, true);
            while (veh)
            {
                if (veh->getTypeName() == "MotorCycle") rdLane.at(veh->getPosition() / metresPerChar) = 'M';
                else if (veh->getTypeName() == "Car") rdLane.at(veh->getPosition() / metresPerChar) = 'A';
                else if (veh->getTypeName() == "Bus") rdLane.at(veh->getPosition() / metresPerChar) = 'B';
                else if (veh->getTypeName() == "Truck") rdLane.at(veh->getPosition() / metresPerChar) = 'V';
                else rdLane[veh->getPosition()] = '?';
                
                veh = currLn->getCarOnPosition(veh->getPosition(), false);
            }
    
            target << string(longestName+1, ' ') << "| " << rdLane << endl;
            
            if (laneNr + 1 < lanes.size())
            {
                target << string(longestName+1, ' ') << "| " << string(currRd->getLength() / metresPerChar, '-') << endl;
            }
    
            /*
            // print each step of the lane
            unsigned int currPos = 0;
            do {
                Vehicle* foundVeh = lanes[laneNr]->getCarOnPosition(currPos, true);
        
                if (foundVeh and foundVeh->getPosition() < currPos+metresPerChar)
                {
                    if (foundVeh->getTypeName() == "MotorCycle") target << 'M';
                    else if (foundVeh->getTypeName() == "Car") target << 'A';
                    else if (foundVeh->getTypeName() == "Bus") target << 'B';
                    else if (foundVeh->getTypeName() == "Truck") target << 'V';
                    else target << '?';
                }
                else
                {
                    target << ' ';
                }
        
                currPos += metresPerChar;
            }
            while (currPos <= currRd->getLength());
             */
        }
        
        target << string(longestName+1, ' ') << "| " << rdEdge << endl;
    
        if (rdNum <= rdVec.size()-1)
        {
            target << endl;
        }
    }
    
    return target;
}
