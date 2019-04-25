//
// Created by Joren Van Borm on 2019-03-27.
//

#ifndef LNJPSE_PROJECT_OUTPUT_H
#define LNJPSE_PROJECT_OUTPUT_H


#include "RoadSystem.h"

enum printStyle {classic};

struct Output {
    Output(RoadSystem* simulation);
    
    friend ostream& operator<<(ostream& target, const Output& print);
    
    RoadSystem* simulation;
    printStyle style;
    
    ostream& classicPrint(ostream& target) const;
};


#endif //LNJPSE_PROJECT_OUTPUT_H
