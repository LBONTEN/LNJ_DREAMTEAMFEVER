//
// Created by Joren Van Borm on 2019-03-27.
//

#ifndef LNJPSE_VEHICLETESTS_H
#define LNJPSE_VEHICLETESTS_H

#include <gtest/gtest.h>
#include "Car.h"
#include "Vehicle.h"
#include "RoadSystem.h"
#include "Road.h"


/**
 * helper class w/ empty definitions for pure virtual members of Vehicle
 * (for testing only)
 */
class SubVehicle : public Vehicle {
public:
    SubVehicle() : Vehicle() {}
    
    SubVehicle(RoadSystem* environment, const string& licensePlate, int length, const VehicleLimits* limits,
               Road* currentRoad) :
               Vehicle(environment, licensePlate, length, limits, currentRoad) {}
    
    SubVehicle(RoadSystem* environment, const string& licensePlate, int length, const VehicleLimits* limits,
               Road* currentRoad, int acceleration, int speed, int position) :
               Vehicle(environment, licensePlate, length, limits, currentRoad, acceleration, speed, position) {}
    
    virtual bool updateReady() {return false;}
    
    virtual void cancelPrep() {}
    
    virtual void prepUpdate() {}
    
    virtual void execUpdate() {}
};


/**
 * Test fixture for base Vehicle tests without any state around it
 */
class SoloVehicle: public testing::Test {
protected:
    SoloVehicle() :
    limits(-10, 10, 0, 50),
    testVeh(new SubVehicle(NULL, "BASE_VEH", 3, &limits, NULL)) {}
    
    ~SoloVehicle() {
        delete testVeh;
    }
    
    VehicleLimits limits;
    SubVehicle* testVeh;
};


///--- constructor tests ---///

TEST_F(SoloVehicle, INIT_Default)
{
    delete testVeh;
    testVeh = new SubVehicle();
    EXPECT_FALSE(testVeh->properlyInitialised());
}

TEST_F(SoloVehicle, INIT_Base)
{
    delete testVeh;
    limits = VehicleLimits( -1, 3, -5, 160);
    testVeh = new SubVehicle(NULL, "ALT_VEH", 4, &limits, NULL);
    
    EXPECT_TRUE(testVeh->properlyInitialised());
    
    EXPECT_TRUE(testVeh->getEnv() == NULL);
    EXPECT_TRUE(testVeh->getLicensePlate() == "ALT_VEH");
    EXPECT_TRUE(testVeh->getLen() == 4);
    EXPECT_TRUE(testVeh->getLimits() == &limits);
    EXPECT_TRUE(testVeh->getCurrentRoad() == NULL);
    
    EXPECT_TRUE(testVeh->getAcceleration() == 0);
    EXPECT_TRUE(testVeh->getSpeed() == 0);
    EXPECT_TRUE(testVeh->getPosition() == 0);
}

TEST_F(SoloVehicle, INIT_Full)
{
    delete testVeh;
    limits = VehicleLimits( -1, 3, -5, 160);
    testVeh = new SubVehicle(NULL, "ALT_VEH", 4, &limits, NULL, 1, 2, 3);
    
    EXPECT_TRUE(testVeh->properlyInitialised());
    
    EXPECT_TRUE(testVeh->getEnv() == NULL);
    EXPECT_TRUE(testVeh->getLicensePlate() == "ALT_VEH");
    EXPECT_TRUE(testVeh->getLen() == 4);
    EXPECT_TRUE(testVeh->getLimits() == &limits);
    EXPECT_TRUE(testVeh->getCurrentRoad() == NULL);
    
    EXPECT_TRUE(testVeh->getAcceleration() == 1);
    EXPECT_TRUE(testVeh->getSpeed() == 2);
    EXPECT_TRUE(testVeh->getPosition() == 3);
}


/**
 * Test fixture for Vehicle tests in an (empty) system
 */
class InSystemVehicle: public testing::Test {
protected:
    InSystemVehicle() :
            limits(-10, 10, 0, 50),
            system(new RoadSystem()),
            road(new Road("MT_RD", 20, 60, system)),
            testVeh(new SubVehicle(system, "BASE_VEH", 3, &limits, road))
    {
        system->addRoad(road);
        system->addVehicle(testVeh);
        road->addVehicle(testVeh);
    }
    
    ~InSystemVehicle() {
        delete testVeh;
        delete road;
        delete system;
    }
    
    VehicleLimits limits;
    RoadSystem* system;
    Road* road;
    SubVehicle* testVeh;
};


///--- setter & getter tests ---///

TEST_F(InSystemVehicle, SETGET_HappyDay)
{
    testVeh->setLicensePlate(" HeY4_");
    EXPECT_TRUE(testVeh->getLicensePlate() == " HeY4_");
    
    testVeh->setAcceleration(3);
    EXPECT_TRUE(testVeh->getAcceleration() == 3);
    
    testVeh->setSpeed(50);
    EXPECT_TRUE(testVeh->getSpeed() == 50);
    
    testVeh->setPosition(5);
    EXPECT_TRUE(testVeh->getPosition() == 5);
    
    testVeh->setRoad(NULL);
    EXPECT_TRUE(testVeh->getCurrentRoad() == NULL);
    EXPECT_TRUE(road->getVehicle(testVeh->getLicensePlate()) == NULL);
}

TEST_F(InSystemVehicle, SETGET_Limits)
{
    testVeh->setAcceleration(limits.minAcc-1);
    EXPECT_TRUE(testVeh->getAcceleration() == limits.minAcc);
    
    testVeh->setAcceleration(limits.maxAcc+1);
    EXPECT_TRUE(testVeh->getAcceleration() == limits.maxAcc);
    
    testVeh->setSpeed(limits.minSpd-1);
    EXPECT_TRUE(testVeh->getSpeed() == limits.minSpd);
    
    testVeh->setSpeed(limits.maxSpd+1);
    EXPECT_TRUE(testVeh->getSpeed() == limits.maxSpd);
    
    limits.maxSpd = road->getMaximumSpeed() + 5;
    
    testVeh->setSpeed(limits.maxSpd-1);
    EXPECT_TRUE(testVeh->getSpeed() == road->getMaximumSpeed());
    
    testVeh->setPosition(-1);
    EXPECT_TRUE(testVeh->getPosition() == 0);
    
    testVeh->setPosition(road->getLength()+10);
    EXPECT_TRUE(testVeh->getPosition() == road->getLength());
}



#endif //LNJPSE_VEHICLETESTS_H
