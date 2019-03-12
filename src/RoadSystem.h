/* created by Van Borm Joren & Bontenakel Lenny
 */

#include <map>
#include "Road.h"

#ifndef LNJ_PIZZA_PROJECT_ROADSYSTEM_H
#define LNJ_PIZZA_PROJECT_ROADSYSTEM_H
using namespace std;


class RoadSystem
{
public:
    bool readXML(string fileName);

private:
    map<string, Road*> roadLookUp;
    vector<Road*> roadIt;

    void load_simulation();
    void dump_simulation();
    void advance_simulation();
    bool is_empty();


};

#endif //LNJ_PIZZA_PROJECT_ROADSYSTEM_H
