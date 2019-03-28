/*
 *  Created by Joren Van Borm & Lenny Bontenakel
 */

#include <gtest/gtest.h>
#include "Road.h"

#ifndef LNJPSE_PROJECT_ROADTESTS_H
#define LNJPSE_PROJECT_ROADTESTS_H


Road testRoad ("D222", 500, 70, NULL);

EXPECT_TRUE(testRoad.name == "D222");
EXPECT_TRUE(testRoad.length == 500);
EXPECT_TRUE(testRoad.maximumSpeed == 70);


#endif //LNJPSE_PROJECT_ROADTESTS_H
