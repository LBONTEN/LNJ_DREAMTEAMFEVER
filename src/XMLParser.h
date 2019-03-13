/* created by Van Borm Joren & Bontenakel Lenny
 */

#include "./tinystuff/tinyxml.h"
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

    const TiXmlElement &operator[](int index)
    {
        return *tags[index];
    }
    
    const TiXmlNode&operator[](int index, string key)
    {

    }

private:
    vector<TiXmlElement*> tags;
};

#endif //DAPIZZAPROJECT_XMLPARSER_H
