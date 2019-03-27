//
// Created by Joren Van Borm on 2019-03-27.
//

#ifndef LNJPSE_PROJECT_SERIALISER_H
#define LNJPSE_PROJECT_SERIALISER_H


#include "RoadSystem.h"

enum mode {manual, file, automatic};

class Serialiser {
public:
    Serialiser(RoadSystem* simulation);

private:
    RoadSystem* simulation;
};


#endif //LNJPSE_PROJECT_SERIALISER_H
