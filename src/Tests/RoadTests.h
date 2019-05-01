/*
 *  Created by Joren Van Borm & Lenny Bontenakel
 */

#include <gtest/gtest.h>
#include <cstdlib>
#include "../Road.h"

#ifndef LNJPSE_PROJECT_ROADTESTS_H
#define LNJPSE_PROJECT_ROADTESTS_H


class RoadTests : public  testing::Test
{
protected:

    RoadTests() :
    testRoad(new Road("D222", 1000, 70, 2))
    {}

    ~RoadTests() { delete testRoad; }

    Road* testRoad;
};

TEST_F(RoadTests, CONSTRUCTOR_TEST)
{
    EXPECT_TRUE(testRoad->getName() == "D222");
    EXPECT_TRUE(testRoad->getLength() == 1000);
    EXPECT_TRUE(testRoad->getSpeedLimit() == 70);
    EXPECT_TRUE(testRoad->getLanes().size() == 2);
    EXPECT_TRUE(testRoad->properlyInitialised());
}


TEST_F(RoadTests, CONNECTION_TEST)
{
    Road *newConnection = new Road("NewConnection", 10000, 90);

    testRoad->setConnection(newConnection);
    EXPECT_TRUE(testRoad->getConnection() == newConnection);

    testRoad->clearConnection();
    EXPECT_TRUE(testRoad->getConnection() == NULL);

    delete newConnection;
}


TEST_F(RoadTests, VEHICLE_TEST)
{
    Car* vehic1 = new Car(NULL, "def-456", testRoad, 0, 60, 300);
    Car* vehic2 = new Car(NULL, "abc-123", testRoad, 0, 50, 100);

    EXPECT_TRUE(testRoad->isFree());

    testRoad->getLanes()[0]->addVehicle(vehic1);

    EXPECT_TRUE(testRoad->getLanes()[0]->getVehicles().size() == 1);
    EXPECT_TRUE(testRoad->getLanes()[0]->getVehicle("def-456") == vehic1);
    EXPECT_FALSE(testRoad->isFree());

    testRoad->getLanes()[0]->addVehicle(vehic2);

    EXPECT_TRUE(testRoad->getLanes()[0]->getVehicles().size() == 2);
    EXPECT_TRUE(testRoad->getLanes()[0]->getVehicle("abc-123") == vehic2);

    EXPECT_EQ(testRoad->getLanes()[0]->getCarOnPosition(300, true), vehic1);
    EXPECT_EQ(testRoad->getLanes()[0]->getCarOnPosition(100, true), vehic2);
    EXPECT_EQ(testRoad->getLanes()[0]->getCarOnPosition(0, false), vehic2);
    EXPECT_EQ(testRoad->getLanes()[0]->getCarOnPosition(0, true), vehic2);
    EXPECT_TRUE(testRoad->getLanes()[0]->getCarOnPosition(1000, false) == NULL);
    EXPECT_TRUE(testRoad->getLanes()[0]->getCarOnPosition(1000, true) == NULL);
    EXPECT_EQ(testRoad->getLanes()[0]->getCarOnPosition(100, false), vehic1);

    EXPECT_TRUE(testRoad->getLanes()[0]->calculateRemainingSpace() > 0);
    int before = testRoad->getLanes()[0]->calculateRemainingSpace();
    testRoad->getLanes()[0]->removeVehicle(vehic2);
    int after = testRoad->getLanes()[0]->calculateRemainingSpace();
    EXPECT_TRUE(before < after);

    EXPECT_FALSE(testRoad->isFree());
    testRoad->getLanes()[0]->removeVehicle(vehic1);
    EXPECT_TRUE(testRoad->isFree());
}

TEST_F(RoadTests, ROADSIGN_TESTS)
{
    srand(time(NULL));
    unsigned int position;
    unsigned int extraVar;

    position = (unsigned) rand() % testRoad->getLength();
    extraVar = (unsigned) rand();
    testRoad->addZone(new Zone(position, testRoad, extraVar));
    Zone* testZone = new Zone(250, testRoad, extraVar);
    testRoad->addZone(testZone);

    position = (unsigned) rand() % testRoad->getLength();
    extraVar = (unsigned) rand();
    testRoad->addTrafficLight(new TrafficLight(position, testRoad, extraVar));
    TrafficLight* testLight = new TrafficLight(500, testRoad, extraVar);
    testRoad->addTrafficLight(testLight);

    position = (unsigned) rand() % testRoad->getLength();
    testRoad->addBusstop(new BusStop(position, testRoad));
    BusStop* testStop = new BusStop(750, testRoad);
    testRoad->addBusstop(testStop);

    EXPECT_EQ(testRoad->getAllSigns().size(), (unsigned long) 6);
    EXPECT_EQ(testRoad->getZones().size(), (unsigned long) 2);
    EXPECT_EQ(testRoad->getTrafficLights().size(), (unsigned long) 2);
    EXPECT_EQ(testRoad->getBusStops().size(), (unsigned long) 2);

    EXPECT_EQ(testRoad->getSignOnPosition(250, true), testZone);
    EXPECT_EQ(testRoad->getTrafficLightOnPosition(500, true), testLight);
    EXPECT_EQ(testRoad->getBusStopOnPosition(750, true), testStop);

}

#endif //LNJPSE_PROJECT_ROADTESTS_H
