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

    Car* testCar;
};


TEST_F(SoloCar, INIT_Default)
{
    delete testCar;
    testCar = new Car();
    
    EXPECT_FALSE(testCar->properlyInitialised());
    EXPECT_EQ(testCar->getTypeName(), "Car");
}

TEST_F(SoloCar, INIT_Base)
{
    delete testCar;
    testCar = new Car(NULL, "ALT_L1_PL4T", NULL);
    
    EXPECT_TRUE(testCar->properlyInitialised());
    EXPECT_EQ(testCar->getTypeName(), "Car");
    
    EXPECT_FALSE(testCar->updateReady());
    
    EXPECT_TRUE(testCar->getEnv() == NULL);
    EXPECT_TRUE(testCar->getCurrentRoad() == NULL);
    
    EXPECT_EQ(testCar->getAcceleration(), 0);
    EXPECT_EQ(testCar->getSpeed(), 0);
    EXPECT_EQ(testCar->getPosition(), 0);
}

TEST_F(SoloCar, INIT_Full)
{
    delete testCar;
    testCar = new Car(NULL, "ALT_L1_PL4T", NULL, 1, 2, 3);
    
    EXPECT_TRUE(testCar->properlyInitialised());
    EXPECT_EQ(testCar->getTypeName(), "Car");
    
    EXPECT_FALSE(testCar->updateReady());
    
    EXPECT_TRUE(testCar->getEnv() == NULL);
    EXPECT_TRUE(testCar->getCurrentRoad() == NULL);
    
    EXPECT_EQ(testCar->getAcceleration(), 1);
    EXPECT_EQ(testCar->getSpeed(), 2);
    EXPECT_EQ(testCar->getPosition(), 3);
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

#endif //LNJPSE_PROJECT_CARTESTS_H
