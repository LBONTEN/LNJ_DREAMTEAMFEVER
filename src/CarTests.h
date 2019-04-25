//
// Created by Joren Van Borm on 2019-03-28.
//

#ifndef LNJPSE_PROJECT_CARTESTS_H
#define LNJPSE_PROJECT_CARTESTS_H

#include "RoadSystem.h"
#include "Car.h"
#include "Road.h"

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
    EXPECT_TRUE(testCar->getTypeName() == "Car");
    
    EXPECT_FALSE(testCar->updateReady());
    
    EXPECT_TRUE(testCar->getEnv() == NULL);
    EXPECT_TRUE(testCar->getCurrentRoad() == NULL);
    
    EXPECT_TRUE(testCar->getAcceleration() == 0);
    EXPECT_TRUE(testCar->getSpeed() == 0);
    EXPECT_TRUE(testCar->getPosition() == 0);
}

TEST_F(SoloCar, INIT_Full)
{
    delete testCar;
    testCar = new Car(NULL, "ALT_L1_PL4T", NULL, 1, 2, 3);
    
    EXPECT_TRUE(testCar->properlyInitialised());
    EXPECT_TRUE(testCar->getTypeName() == "Car");
    
    EXPECT_FALSE(testCar->updateReady());
    
    EXPECT_TRUE(testCar->getEnv() == NULL);
    EXPECT_TRUE(testCar->getCurrentRoad() == NULL);
    
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
            road(new Road("4n_I-m Rd", 200, stdCarLimits.maxSpd+50, system)),
            testCar(new Car(system, "I-M_4 C4R", road))
    {}
    
    virtual ~InSystemCar()
    {
        delete(testCar);
        delete(road);
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
    EXPECT_TRUE(testCar->getPosition() == stdCarLimits.maxAcc);
}

TEST_F(InSystemCar, UPDATE_Complex)
{
    Car* otherCar = new Car(system, "0h-lok4 cR", road, 0, 0, 1000);
    
    system->addVehicle(otherCar);
    road->addVehicle(otherCar);
    
    system->activate();
    
    while(otherCar->getPosition() - otherCar->getLen() - testCar->getPosition() < minimumSpace) {
        
        int actualD = otherCar->getPosition() - otherCar->getLen() - testCar->getPosition();
        int idealD = 0.75 * testCar->getSpeed() + otherCar->getLen() + minimumSpace;
        
        int expectedAcc = 0.5 * (actualD - idealD);
        expectedAcc = min(expectedAcc, stdCarLimits.maxAcc);
        expectedAcc = max(expectedAcc, stdCarLimits.minAcc);
        
        testCar->prepUpdate();
        testCar->execUpdate();
    
        EXPECT_TRUE(testCar->getAcceleration() == expectedAcc);
    }
    
    delete otherCar;
}

#endif //LNJPSE_PROJECT_CARTESTS_H
