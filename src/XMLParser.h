/* created by Van Borm Joren & Bontenakel Lenny
 */

#include "./tinystuff/tinyxml.h"
#include <string>
#include <map>
using namespace std;

class RoadSystem;

#ifndef DAPIZZAPROJECT_XMLPARSER_H
#define DAPIZZAPROJECT_XMLPARSER_H

class Parser
{
public:
    Parser();
    ~Parser();

    virtual RoadSystem* parseRoadSystem(const string& filename);

};

class XmlParser: public Parser
{
public:

    XmlParser();
    ~XmlParser();
    virtual RoadSystem* parseRoadSystem(const string& filename);

private:

};

#endif //DAPIZZAPROJECT_XMLPARSER_H
