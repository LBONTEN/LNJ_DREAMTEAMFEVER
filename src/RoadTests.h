/*
 *  Created by Joren Van Borm & Lenny Bontenakel
 */

#include <gtest/gtest.h>
#include "Road.h"

#ifndef LNJPSE_PROJECT_ROADTESTS_H
#define LNJPSE_PROJECT_ROADTESTS_H


class RoadTests : public  testing::Test
{
protected:

    RoadTests() :
    testRoad( new Road("D222", 1000, 70, NULL))
    {}

    Road* testRoad;
};

TEST_F(RoadTests, CONSTRUCTOR_TEST)
{
    EXPECT_TRUE(testRoad->getName() == "D222");
    EXPECT_TRUE(testRoad->getLength() == 1000);
    EXPECT_TRUE(testRoad->getMaximumSpeed() == 70);
    EXPECT_TRUE(testRoad->properlyInitialised());
}

TEST_F(RoadTests, CONNECTION_TEST)
{
    Road *newConnection = new Road("NewConnection", 10000, 90, NULL);

    testRoad->setConnection(newConnection);
    EXPECT_TRUE(testRoad->getConnections()[0] == newConnection);

    testRoad->removeConnection(newConnection);
    EXPECT_FALSE(testRoad->getConnections()[0] == newConnection);
    EXPECT_TRUE(testRoad->getConnections().empty());

    testRoad->setConnection(newConnection);
    EXPECT_TRUE(testRoad->getConnections()[0] == newConnection);

    delete (newConnection);
    EXPECT_FALSE(testRoad->getConnections()[0] == newConnection);
    EXPECT_TRUE(testRoad->getConnections().empty());
}

TEST_F(RoadTests, VEHICLE_TEST)
{
    Car* vehic1 = new Car(NULL, "def-456", testRoad, 0, 60, 300);
    Car* vehic2 = new Car(NULL, "abc-123", testRoad, 0, 50, 100);

    EXPECT_TRUE(testRoad->isFree());

    testRoad->addVehicle(vehic1);

    EXPECT_TRUE(testRoad->getVehicles().size() == 1);
    EXPECT_FALSE(testRoad->isFree());

    testRoad->addVehicle(vehic2);

    EXPECT_TRUE(testRoad->getVehicles().size() == 2);

    EXPECT_TRUE(testRoad->getCarOnPosition(0, true) == vehic2);
    EXPECT_TRUE(testRoad->getCarOnPosition(0, false) == vehic2);
    EXPECT_TRUE(testRoad->getCarOnPosition(300, true) == vehic1);
    EXPECT_TRUE(testRoad->getCarOnPosition(100, false) == vehic1);

    EXPECT_TRUE(testRoad->remainingSpace() > 0);
    int before = testRoad->remainingSpace();

    testRoad->removeVehicle(vehic2);

    int after = testRoad->remainingSpace();

    EXPECT_TRUE(before < after);

    EXPECT_FALSE(testRoad->isFree());
    testRoad->removeVehicle(vehic1);
    EXPECT_TRUE(testRoad->isFree());

}



#endif //LNJPSE_PROJECT_ROADTESTS_H
