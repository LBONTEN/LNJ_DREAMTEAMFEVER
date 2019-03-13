/* Van Borm Joren & Bontenakel Lenny's
 *
 *  Software Engineering Project
 *  Ultimate Traffic Simulator
 */

#include <iostream>
#include <fstream>

#include "./tinystuff/tinyxml.h"
#include "RoadSystem.h"
#include "Vehicle.h"
#include "XMLParser.h"

int main() {
    XmlParser xmlp;
    RoadSystem rs = *xmlp.parseRoadSystem("single_connection_n_cars.xml");

    cout << "heyya" << endl;

    return 0;
}
