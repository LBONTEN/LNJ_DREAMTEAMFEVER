/* Van Borm Joren & Bontenakel Lenny's
 *
 *  Software Engineering Project
 *  Ultimate Traffic Simulator
 */

#include <iostream>
#include <fstream>
#include "RoadSystem.h"
#include "XMLParser.h"
#include "Serialiser.h"

int main(int argc, char** argv)
{
    if (argc < 2) {
        cerr << "No source file given" << std::endl;
        return 1;
    }
    
    XmlParser xmlp;
    RoadSystem* rs = xmlp.parseRoadSystem(argv[1]);
    Serialiser print (rs);
    
    cout << "Initial situation:" << std::endl;
    cout << print << "~====~" << std::endl;
    
    rs->untilEmpty();
    
    cout << "Situation after simulation: (took " << print.simulation->timeActive() << " seconds)" << std::endl;
    cout << print << "~====~" << std::endl;

    return 0;
}
