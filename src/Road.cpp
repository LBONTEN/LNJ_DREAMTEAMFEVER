/* created by Van Borm Joren & Bontenakel Lenny
 */

#include "./tinystuff/tinyxml.h"
#include "Road.h"

Road::Road(TiXmlNode* input)
{
    if(input->ValueTStr() == "naam")
    {
        name = string(input->FirstChild()->ToText()->Value());
    }
    if(input->ValueTStr() == "snelheidslimiet")
    {
        maximumSpeed = atoi(input->FirstChild()->ToText()->Value());
    }
    if(input->ValueTStr() == "lengte")
    {
        length = atoi(input->FirstChild()->ToText()->Value());
    }
}