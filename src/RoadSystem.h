/* created by Van Borm Joren & Bontenakel Lenny
 */

#include "Road.h"

#ifndef LNJ_PIZZA_PROJECT_ROADSYSTEM_H
#define LNJ_PIZZA_PROJECT_ROADSYSTEM_H

class RoadSystem
{
    vector<Road*> roads;

    void load_simulation();
    void dump_simulation();
    void advance_simulation();
    bool is_empty();
};

#endif //LNJ_PIZZA_PROJECT_ROADSYSTEM_H
