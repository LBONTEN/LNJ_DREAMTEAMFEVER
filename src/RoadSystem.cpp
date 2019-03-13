/* created by Van Borm Joren & Bontenakel Lenny
 */

#include "RoadSystem.h"
#include "Road.h"
#include <string>

bool RoadSystem::readXML(string fileName)
{
    TiXmlDocument inputfile;
    fileName = "../IO/" + fileName;

    if(!inputfile.LoadFile(fileName.c_str()))
    {
        return false;
    }
    TiXmlElement* root = inputfile.FirstChildElement();
    if(root == NULL)
    {
        inputfile.Clear();
        return false;
    }

    map<string, Road*> roads;
    for( TiXmlElement* elem = root; elem != NULL; elem = elem->NextSiblingElement())
    {
        if(elem->ValueTStr() == "BAAN")
        {
            for(TiXmlNode* child = elem->FirstChildElement(); child != NULL; child = elem->IterateChildren(child))
            {
                Road nRoad;
                nRoad = Road(*child);
            }
        }
    }
    return true;
}