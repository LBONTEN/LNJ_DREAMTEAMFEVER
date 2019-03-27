//
// Created by Joren Van Borm on 2019-03-27.
//

#ifndef LNJPSE_PROJECT_SERIALISER_H
#define LNJPSE_PROJECT_SERIALISER_H


#include "RoadSystem.h"

enum printStyle {classic};

struct Serialiser {
    Serialiser(RoadSystem* simulation);
    
    friend ostream& operator>>(const Serialiser& print, ostream& target);
    
    RoadSystem* simulation;
    printStyle style;
    
    ostream& classicPrint(ostream& target) const;
};


#endif //LNJPSE_PROJECT_SERIALISER_H
