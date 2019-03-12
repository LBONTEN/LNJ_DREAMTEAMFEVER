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
    inputFileName = "../IO/" + inputFileName;

    if(!inputfile.LoadFile(inputFileName.c_str()))
    {
        return false;
    }
    TiXmlElement* root = inputfile.FirstChildElement();
    if(root == NULL)
    {
        inputfile.Clear();
        return false;
    }

    for(TiXmlElement* elem = root; elem != NULL; elem = elem->NextSiblingElement())
    {
        if(elem->ValueTStr() == "BAAN")
        {
            elem.
        }
        if(elem->ValueTStr() == "VOERTUIG")
        {

        }

        for(TiXmlNode* child = elem->FirstChildElement(); child != NULL; child = elem->IterateChildren(child))
        {
            std::cout << child->Value() << endl;
        }
    }
    return true;
}





int main() {
    ReadXML("single_connection_n_cars.xml");

    return 0;
}
