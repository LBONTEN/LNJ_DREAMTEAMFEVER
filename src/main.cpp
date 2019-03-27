/* Van Borm Joren & Bontenakel Lenny's
 *
 *  Software Engineering Project
 *  Ultimate Traffic Simulator
 */

#include <iostream>
#include <fstream>
#include "RoadSystem.h"
#include "XMLParser.h"

int main()
{
    XmlParser xmlp;
    RoadSystem* rs = xmlp.parseRoadSystem("../IO/single_connection_n_cars.xml");

    Road* veh = rs->getVectorOfRoads()[1];

    cout << veh->getName() << endl;

    return 0;
}
