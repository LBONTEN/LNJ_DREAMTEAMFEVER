/* created by Van Borm Joren & Bontenakel Lenny
 */

#include "RoadSystem.h"
#include "./tinystuff/tinyxml.h"
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

    for(TiXmlElement* elem = root; elem != NULL; elem = elem->NextSiblingElement())
    {
        if(elem->ValueTStr() == "BAAN")
        {
            roadLookUp.insert(pair<string, Road*>()  );
        }
        if(elem->ValueTStr() == "VOERTUIG")
        {

        }

        for(TiXmlNode* child = elem->FirstChildElement(); child != NULL; child = elem->IterateChildren(child))
        {
            
        }
    }
    return true;
}