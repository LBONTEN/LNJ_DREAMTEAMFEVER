/* Created by Joren Van Borm & Lenny Bontenakel
 */

#ifndef LNJPSE_PROJECT_CARTESTS_H
#define LNJPSE_PROJECT_CARTESTS_H

#include "../RoadSystem.h"
#include "../TypedVehicles.h"
#include "../Road.h"

class SoloCar : public testing::Test {
protected:
    SoloCar() :
        testCar(new Car(NULL, "I-M_4 C4R", NULL))
    {}

public:
    virtual ~SoloCar()
    {
        delete testCar;
    }

protected:
    
    Car* testCar;
};


TEST_F(SoloCar, INIT_Default)
{
    delete testCar;
    testCar = new Car();
    
    EXPECT_FALSE(testCar->properlyInitialised());
    EXPECT_TRUE(testCar->getTypeName() == "Car");
}

TEST_F(SoloCar, INIT_Base)
{
    delete testCar;
    testCar = new Car(NULL, "ALT_L1_PL4T", NULL);
    
    EXPECT_TRUE(testCar->properlyInitialised());
    EXPECT_EQ("Car", testCar->getTypeName());
    
    EXPECT_FALSE(testCar->updateReady());
    
    EXPECT_EQ((RoadSystem*) NULL, testCar->getEnv());
    EXPECT_EQ((Road*) NULL, testCar->getCurrentRoad());
    
    EXPECT_EQ(0, testCar->getAcceleration());
    EXPECT_EQ(0, testCar->getSpeed());
    EXPECT_EQ((unsigned int) 0, testCar->getPosition());
}

TEST_F(SoloCar, INIT_Full)
{
    delete testCar;
    testCar = new Car(NULL, "ALT_L1_PL4T", NULL, 1, 2, 3);
    
    EXPECT_TRUE(testCar->properlyInitialised());
    EXPECT_TRUE(testCar->getTypeName() == "Car");
    
    EXPECT_FALSE(testCar->updateReady());
    
    EXPECT_TRUE(testCar->getEnv() == NULL);
    EXPECT_TRUE(testCar->getCurrentLane() == NULL);
    
    EXPECT_TRUE(testCar->getAcceleration() == 1);
    EXPECT_TRUE(testCar->getSpeed() == 2);
    EXPECT_TRUE(testCar->getPosition() == 3);
}

TEST_F(SoloCar, UPDATE_Null)
{
    testCar->prepUpdate();
    EXPECT_TRUE(testCar->updateReady());
    
    testCar->execUpdate();
    EXPECT_FALSE(testCar->updateReady());
    
    testCar->prepUpdate();
    testCar->cancelPrep();
    EXPECT_FALSE(testCar->updateReady());
}


class InSystemCar : public testing::Test {
protected:
    InSystemCar() :
            system(new RoadSystem()),
            road(new Road("4n_I-m Rd", 200, stdCarLimits.maxSpd+50)),
            testCar(new Car(system, "I-M_4 C4R", road))
    {
        road->getLanes()[0]->addVehicle(testCar);
    }
    
    virtual ~InSystemCar()
    {
        delete(system);
    }

protected:
    
    RoadSystem* system;
    Road* road;
    Car* testCar;
};

TEST_F(InSystemCar, UPDATE_Base)
{
    system->activate();
    
    testCar->prepUpdate();
    testCar->execUpdate();
    
    EXPECT_TRUE(testCar->getAcceleration() == stdCarLimits.maxAcc);
    EXPECT_TRUE(testCar->getSpeed() == 0);
    EXPECT_TRUE(testCar->getPosition() == 0);

    testCar->prepUpdate();
    testCar->execUpdate();

    EXPECT_TRUE(testCar->getAcceleration() == stdCarLimits.maxAcc);
    EXPECT_TRUE(testCar->getSpeed() == stdCarLimits.maxAcc);
    EXPECT_TRUE(testCar->getPosition() == 0);

    testCar->prepUpdate();
    testCar->execUpdate();

    EXPECT_TRUE(testCar->getAcceleration() == stdCarLimits.maxAcc);
    EXPECT_TRUE(testCar->getSpeed() == 2 * stdCarLimits.maxAcc);
    EXPECT_TRUE(testCar->getPosition() == (unsigned int) stdCarLimits.maxAcc);
}

TEST_F(InSystemCar, UPDATE_Follow)
{
    Car* otherCar = new Car(system, "0h-lok4 cR", road, 0, 0, 200);
    
    system->addVehicle(otherCar);
    road->getLanes()[0]->addVehicle(otherCar);
    
    system->activate();
    
    while(otherCar->getPosition() - otherCar->getLen() - testCar->getPosition() > minimumSpace)
    {
        testCar->prepUpdate();
        
        int actualD = otherCar->getPosition() - otherCar->getLen() - testCar->getPosition();
        int idealD = 0.75 * 3.6 * testCar->getSpeed() + minimumSpace;
        
        int expectedAcc = 0.5 * (actualD - idealD);
    
        if (testCar->getCurrentRoad() and testCar->getSpeed()+expectedAcc > road->getSpeedLimit())
        {
            expectedAcc = road->getSpeedLimit() - testCar->getSpeed();
        }
        if (testCar->getSpeed()+expectedAcc > testCar->getLimits()->maxSpd)
        {
            expectedAcc = testCar->getLimits()->maxSpd - testCar->getSpeed();
        }
        if (testCar->getSpeed()+expectedAcc < testCar->getLimits()->minSpd)
        {
            expectedAcc = testCar->getLimits()->minSpd - testCar->getSpeed();
        }
        expectedAcc = min(expectedAcc, stdCarLimits.maxAcc);
        expectedAcc = max(expectedAcc, stdCarLimits.minAcc);
        
        testCar->execUpdate();
        
        EXPECT_EQ(expectedAcc, testCar->getAcceleration());
    }
    
}

TEST_F(InSystemCar, UPDATE_Zone)
{
    ASSERT_LT(stdCarLimits.minAcc, 0) << "test won't work with these stdCarLimits";
    ASSERT_GE(stdCarLimits.maxSpd+stdCarLimits.minAcc-2, stdCarLimits.minSpd) << "test won't work with these stdCarLimits";
    
    road->addZone(new Zone(100, road, stdCarLimits.maxSpd+stdCarLimits.minAcc-2));
    
    testCar->setSpeed(stdCarLimits.maxSpd);
    
    system->activate();
    
    while (testCar->getPosition() < 100)
    {
        testCar->prepUpdate();
        testCar->execUpdate();
    }
    
    EXPECT_EQ(stdCarLimits.maxSpd, testCar->getSpeed());
    EXPECT_EQ(stdCarLimits.minAcc, testCar->getAcceleration());
    
    while (testCar->getCurrentRoad() != NULL)
    {
        testCar->prepUpdate();
        testCar->execUpdate();
    }
    
    EXPECT_EQ(stdCarLimits.maxSpd+stdCarLimits.minAcc-2, testCar->getSpeed());
}

TEST_F(InSystemCar, UPDATE_Light)
{
    TrafficLight* light1 = new TrafficLight(100, road, 0);
    TrafficLight* light2 = new TrafficLight(180, road, 35);
    
    road->addTrafficLight(light1);
    road->addTrafficLight(light2);
    
    ASSERT_EQ(orange, light1->getState());
    ASSERT_EQ(green, light2->getState());
    
    system->activate();
    
    while (testCar->getPosition() < light1->getPosition())
    {
        testCar->prepUpdate();
    
        int expectedAcc = stdCarLimits.maxAcc;
        
        int idealD = 0.75 * 3.6 * testCar->getSpeed() + minimumSpace;
        unsigned int dToLight = light1->getPosition() - testCar->getPosition();
        
        if (dToLight <= 0) {
            testCar->execUpdate();
            break;
        }
        
        if (dToLight < (unsigned int) 2*idealD) expectedAcc = - (testCar->getSpeed()*testCar->getSpeed() / dToLight);
        
        if (testCar->getSpeed()+expectedAcc > stdCarLimits.maxSpd) expectedAcc = stdCarLimits.maxSpd - testCar->getSpeed();
        
        testCar->execUpdate();
        
        EXPECT_EQ(expectedAcc, testCar->getAcceleration());
    }
    
    EXPECT_EQ(light1->getPosition(), testCar->getPosition());
    EXPECT_EQ(0, testCar->getSpeed());
    EXPECT_EQ(0, testCar->getAcceleration());
    
    light1->updateState(35);
    
    ASSERT_EQ(green, light1->getState());
    
    while (testCar->getCurrentRoad() != NULL)
    {
        testCar->prepUpdate();
    
        int expectedAcc = stdCarLimits.maxAcc;
        if (testCar->getSpeed()+expectedAcc > stdCarLimits.maxSpd) expectedAcc = stdCarLimits.maxSpd - testCar->getSpeed();
    
        testCar->execUpdate();
        
        EXPECT_EQ(expectedAcc, testCar->getAcceleration());
    }
}

TEST_F(InSystemCar, UPDATE_BusStop)
{
    Road* road2 = new Road("4l5_rD", 200, stdCarLimits.maxSpd+50);
    
    BusStop* stop1 = new BusStop(100, road);
    BusStop* stop2 = new BusStop(100, road2);
    
    Vehicle* bus = new Bus(system, "BUS_VEH", road2);
    
    system->addRoad(road2);
    
    road->addBusstop(stop1);
    road2->addBusstop(stop2);
    
    road2->getLanes()[0]->addVehicle(bus);
    
    system->activate();
    
    while (testCar->getCurrentRoad() != NULL)
    {
        testCar->prepUpdate();
        
        int expectedAcc = stdCarLimits.maxAcc;
        if (testCar->getSpeed()+expectedAcc > stdCarLimits.maxSpd) expectedAcc = stdCarLimits.maxSpd - testCar->getSpeed();
        
        testCar->execUpdate();
        
        EXPECT_EQ(expectedAcc, testCar->getAcceleration());
    }
    
    while (bus->getPosition() < stop2->getPosition())
    {
        bus->prepUpdate();
    
        int expectedAcc = stdBusLimits.maxAcc;
    
        int idealD = 0.75 * 3.6 * bus->getSpeed() + minimumSpace;
        unsigned int dToLight = stop2->getPosition() - bus->getPosition();
    
        if (dToLight <= 0) {
            bus->execUpdate();
            break;
        }
    
        if (dToLight < (unsigned int) 2*idealD) expectedAcc = - (bus->getSpeed()*bus->getSpeed() / dToLight);
    
        if (bus->getSpeed()+expectedAcc > stdBusLimits.maxSpd) expectedAcc = stdBusLimits.maxSpd - bus->getSpeed();
    
        bus->execUpdate();
    
        EXPECT_EQ(expectedAcc, bus->getAcceleration());
    }
    
    EXPECT_EQ(stop2->getPosition(), bus->getPosition());
    EXPECT_EQ(0, bus->getSpeed());
    EXPECT_EQ(0, bus->getAcceleration());
    
    for (int timeAtStop=1; timeAtStop < 30; ++timeAtStop)
    {
        bus->prepUpdate();
        bus->execUpdate();
    
        EXPECT_EQ(stop2->getPosition(), bus->getPosition());
        EXPECT_EQ(0, bus->getSpeed());
        EXPECT_EQ(0, bus->getAcceleration());
    }
    
    while (bus->getCurrentRoad() != NULL)
    {
        bus->prepUpdate();
        
        int expectedAcc = stdBusLimits.maxAcc;
        if (bus->getSpeed()+expectedAcc > stdBusLimits.maxSpd) expectedAcc = stdBusLimits.maxSpd - bus->getSpeed();
        
        bus->execUpdate();
        
        EXPECT_EQ(expectedAcc, bus->getAcceleration());
    }
}

#endif //LNJPSE_PROJECT_CARTESTS_H
