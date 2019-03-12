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
#include "Road.h"

bool ReadXML(std::string inputFileName)
{
    TiXmlDocument inputfile;

    if(!inputfile.LoadFile(inputFileName.c_str()))
    {
        std::cerr << "InputFile not found" << endl;
        return false;
    }
    TiXmlElement* root = inputfile.FirstChildElement();
    if(root == NULL)
    {
        std::cerr << "Input invalid" << endl;
        inputfile.Clear();
        return false;
    }
    std::cout << root->Value() << endl;

    TiXmlElement* element = root->NextSiblingElement();
    for(TiXmlElement* elem = element; elem != NULL; elem = elem->NextSiblingElement())
    {
        std::cout << elem->Value() << endl;
    }
    return true;
}





int main() {
    ReadXML("single_connection_n_cars.xml");

    return 0;
}
