/* Created by Joren Van Borm & Lenny Bontenakel
 */

#include "../RoadSystem.h"
#include <gtest/gtest.h>

#ifndef LNJPSE_PROJECT_ROADSYSTEMTESTS_H
#define LNJPSE_PROJECT_ROADSYSTEMTESTS_H

class RoadSystemTest : public testing::Test
{
protected:

    RoadSystemTest() :
    testSystem(new RoadSystem())
    {}

    ~RoadSystemTest() { delete testSystem; }

    RoadSystem* testSystem;
    vector<Vehicle*> testVehics;
    vector<Road*> testRoads;
};


TEST_F(RoadSystemTest, CONSTRUCOR_TESTS)
{
    Road* road1 = new Road("A32", 1200, 70, 2);
    Road* road2 = new Road("Y76", 2100, 90, 4, road1);
    Road* road3 = new Road("G09", 500, 50, 1, road2);
    vector<Road*> roadsVec;
    roadsVec.push_back(road1);
    roadsVec.push_back(road2);
    roadsVec.push_back(road3);

    MotorCycle* vehic1 = new MotorCycle(NULL, "TEST1", road1);
    Car* vehic2 = new Car(NULL, "TEST2", road2);
    Bus* vehic3 = new Bus(NULL, "TEST3", road3);
    vector<Vehicle*> vehicleVec;
    vehicleVec.push_back(vehic1);
    vehicleVec.push_back(vehic2);
    vehicleVec.push_back(vehic3);

    delete testSystem;

    testSystem = new RoadSystem(roadsVec, vehicleVec);

    vector<Road*> roadsVec2;
    roadsVec2.push_back(road1);
    roadsVec2.push_back(road2);
    roadsVec2.push_back(road3);
    EXPECT_EQ(roadsVec2, testSystem->getVectorOfRoads());

    vector<Vehicle*> vehicleVec2;
    vehicleVec2.push_back(vehic1);
    vehicleVec2.push_back(vehic2);
    vehicleVec2.push_back(vehic3);
    EXPECT_EQ(vehicleVec2, testSystem->getVectorOfVehicles());

    for(vector<Vehicle*>::const_iterator i = testSystem->getVectorOfVehicles().begin();
        i != testSystem->getVectorOfVehicles().end();
        i++)
    {
        EXPECT_EQ((*i)->getEnv(), testSystem);
    }

    EXPECT_TRUE(testSystem->contains(road1));
    EXPECT_TRUE(testSystem->contains(road2));
    EXPECT_TRUE(testSystem->contains(road3));
    EXPECT_TRUE(testSystem->contains(vehic1));
    EXPECT_TRUE(testSystem->contains(vehic2));
    EXPECT_TRUE(testSystem->contains(vehic3));

    EXPECT_FALSE(testSystem->simulationActive());
}

TEST_F(RoadSystemTest, GET_SET_TESTS)
{
    Road* road1 = new Road("A32", 1200, 70, 2);
    Road* road2 = new Road("Y76", 2100, 90, 4, road1);
    Road* road3 = new Road("G09", 500, 50, 1, road2);
    vector<Road*> roadsVec;
    roadsVec.push_back(road1);
    roadsVec.push_back(road2);
    roadsVec.push_back(road3);

    MotorCycle* vehic1 = new MotorCycle(NULL, "TEST1", road1);
    Car* vehic2 = new Car(NULL, "TEST2", road2);
    Bus* vehic3 = new Bus(NULL, "TEST3", road3);
    vector<Vehicle*> vehicleVec;
    vehicleVec.push_back(vehic1);
    vehicleVec.push_back(vehic2);
    vehicleVec.push_back(vehic3);

    testSystem->setVectorOfRoads(roadsVec);
    testSystem->setVectorOfVehicles(vehicleVec);

    EXPECT_TRUE(testSystem->contains(road1));
    EXPECT_TRUE(testSystem->contains(road2));
    EXPECT_TRUE(testSystem->contains(road3));
    EXPECT_TRUE(testSystem->contains(vehic1));
    EXPECT_TRUE(testSystem->contains(vehic2));
    EXPECT_TRUE(testSystem->contains(vehic3));

    testSystem->removeRoad(road3);
    EXPECT_FALSE(testSystem->contains(road3));
    EXPECT_NE(testSystem->getVectorOfRoads(), roadsVec);
    testSystem->removeRoad(road2);
    EXPECT_FALSE(testSystem->contains(road2));
    EXPECT_NE(testSystem->getVectorOfRoads(), roadsVec);
    testSystem->removeRoad(road1);
    EXPECT_FALSE(testSystem->contains(road1));
    EXPECT_NE(testSystem->getVectorOfRoads(), roadsVec);
    EXPECT_TRUE(testSystem->getVectorOfRoads().empty());

    testSystem->removeVehicle(vehic1);
    EXPECT_FALSE(testSystem->contains(vehic1));
    EXPECT_NE(testSystem->getVectorOfVehicles(), vehicleVec);
    testSystem->removeVehicle(vehic2);
    EXPECT_FALSE(testSystem->contains(vehic2));
    EXPECT_NE(testSystem->getVectorOfVehicles(), vehicleVec);
    testSystem->removeVehicle(vehic3);
    EXPECT_FALSE(testSystem->contains(vehic3));
    EXPECT_NE(testSystem->getVectorOfVehicles(), vehicleVec);
    EXPECT_TRUE(testSystem->getVectorOfVehicles().empty());

    testSystem->addRoad(road1);
    EXPECT_TRUE(testSystem->contains(road1));
    EXPECT_FALSE(testSystem->getVectorOfRoads().empty());
    testSystem->addRoad(road2);
    EXPECT_TRUE(testSystem->contains(road2));
    EXPECT_FALSE(testSystem->getVectorOfRoads().empty());
    testSystem->addRoad(road3);
    EXPECT_TRUE(testSystem->contains(road3));
    EXPECT_FALSE(testSystem->getVectorOfRoads().empty());
    EXPECT_EQ(testSystem->getVectorOfRoads(), roadsVec);

    testSystem->addVehicle(vehic1);
    EXPECT_TRUE(testSystem->contains(vehic1));
    EXPECT_FALSE(testSystem->getVectorOfVehicles().empty());
    testSystem->addVehicle(vehic2);
    EXPECT_TRUE(testSystem->contains(vehic2));
    EXPECT_FALSE(testSystem->getVectorOfVehicles().empty());
    testSystem->addVehicle(vehic3);
    EXPECT_TRUE(testSystem->contains(vehic3));
    EXPECT_FALSE(testSystem->getVectorOfVehicles().empty());
    EXPECT_EQ(testSystem->getVectorOfVehicles(), vehicleVec);

    EXPECT_FALSE(testSystem->simulationActive());
}

TEST_F(RoadSystemTest, UPDATE_TESTS)
{
    Road* road1 = new Road("A32", 1200, 70, 2);
    Road* road2 = new Road("Y76", 2100, 90, 4, road1);
    Road* road3 = new Road("G09", 500, 50, 1, road2);
    vector<Road*> roadsVec;
    roadsVec.push_back(road1);
    roadsVec.push_back(road2);
    roadsVec.push_back(road3);

    MotorCycle* vehic1 = new MotorCycle(NULL, "TEST1", road1);
    Car* vehic2 = new Car(NULL, "TEST2", road2);
    Bus* vehic3 = new Bus(NULL, "TEST3", road3);
    vector<Vehicle*> vehicleVec;
    vehicleVec.push_back(vehic1);
    vehicleVec.push_back(vehic2);
    vehicleVec.push_back(vehic3);

    testSystem->setVectorOfRoads(roadsVec);
    testSystem->setVectorOfVehicles(vehicleVec);

    testSystem->activate();

    EXPECT_EQ(testSystem->timeActive(), (unsigned long) 0);

    for(int i = 0; i < 100; i++)
    {
        testSystem->advanceSimulation();
    }

    EXPECT_EQ(testSystem->timeActive(), (unsigned long) 100);
}

#endif //LNJPSE_PROJECT_ROADSYSTEMTESTS_H
