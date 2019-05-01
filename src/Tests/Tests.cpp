//
// Created by Joren Van Borm & Lenny Bontenakel
//

/// Tests for debug target go here ///

#include "VehicleTests.h"
#include "RoadTests.h"
#include "CarTests.h"
#include "XMLParserTests.h"
#include <iostream>
#include <gtest/gtest.h>

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
