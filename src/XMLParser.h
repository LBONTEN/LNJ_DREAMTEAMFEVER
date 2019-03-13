/* created by Van Borm Joren & Bontenakel Lenny
 */

#include "./tinystuff/tinyxml.h"
#include "RoadSystem.h"
#include <string>
#include <vector>
using namespace std;

#ifndef DAPIZZAPROJECT_XMLPARSER_H
#define DAPIZZAPROJECT_XMLPARSER_H

class XmlParser
{
public:
    XmlParser(const string &);

    ~XmlParser();

    RoadSystem* parseRoadSystem(const string& filename);


private:
    vector<TiXmlElement*> tags;
};

#endif //DAPIZZAPROJECT_XMLPARSER_H
