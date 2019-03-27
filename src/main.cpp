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

int main()
{
    XmlParser xmlp;
    RoadSystem* rs = xmlp.parseRoadSystem("../IO/single_road.xml");

    Serialiser print (rs);
    
    cout << print;

    return 0;
}
