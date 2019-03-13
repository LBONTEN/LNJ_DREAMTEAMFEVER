/* created by Van Borm Joren & Bontenakel Lenny
 */

#include "./tinystuff/tinyxml.h"
#include <string>
#include <map>
using namespace std;

class RoadSystem;

#ifndef DAPIZZAPROJECT_XMLPARSER_H
#define DAPIZZAPROJECT_XMLPARSER_H
class XmlParser
{
public:

    XmlParser();

    RoadSystem* parseRoadSystem(const string& filename);

};

#endif //DAPIZZAPROJECT_XMLPARSER_H
