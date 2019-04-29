/* Van Borm Joren & Bontenakel Lenny's
 *
 *  Software Engineering Project
 *  Ultimate Traffic Simulator
 */

#include <iostream>
#include <fstream>
#include "RoadSystem.h"
#include "XMLParser.h"
#include "Output.h"

int main(int argc, char** argv)
{
    if (argc < 2) {
        cerr << "No source file given" << std::endl;
        return 1;
    }
    
    XmlParser xmlp;
    RoadSystem* rs = xmlp.parseRoadSystem(argv[1]);
    Output print (rs);
    print.style = text_graphic;
    
    std::cout << "Initial situation:" << std::endl;
    std::cout << print << "~====~" << std::endl;
    
    rs->activate();
    
    while (!rs->empty())
    {
        rs->advanceSimulation();
        if (rs->timeActive() % 10 == 0)
        {
            std::cout << "After " << rs->timeActive() << " iterations" << std::endl;
            
            print.textGraphicPrint(std::cout, 100) << endl;
            
            const vector<Vehicle*> tmp = rs->getVectorOfVehicles();
            for (vector<Vehicle*>::const_iterator it = tmp.begin(); it != tmp.end(); it++)
            {
                cout << (*it)->getTypeName() << " : " << "a=" << (*it)->getAcceleration() << " v=" << (*it)->getSpeed() << " x=" << (*it)->getPosition() << std::endl;
            }
            
            std::cout << "~====~" << std::endl;
        }
    }
    
    std::cout << "Situation after simulation: (took " << print.simulation->timeActive() << " seconds)" << std::endl;
    std::cout << print << "~====~" << std::endl;

    return 0;
}
