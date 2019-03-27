//
// Created by Joren Van Borm on 2019-03-27.
//

#ifndef LNJPSE_VEHICLETESTS_H
#define LNJPSE_VEHICLETESTS_H

#include <gtest/gtest.h>
#include "Car.h"
#include "Vehicle.h"


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
 * Test fixture for all base Vehicle tests
 */
class SoloVehicleTest: public testing::Test {
protected:
    SoloVehicleTest() :
    limits(-10, 10, 0, 50),
    testVeh(new SubVehicle(NULL, "BASE_VEH", 3, &limits, NULL)) {}
    
    ~SoloVehicleTest() {
        delete testVeh;
    }
    
    VehicleLimits limits;
    SubVehicle* testVeh;
};


///--- constructor tests ---///

TEST_F(SoloVehicleTest, INIT_Default)
{
    delete testVeh;
    testVeh = new SubVehicle();
    EXPECT_FALSE(testVeh->properlyInitialised());
}

TEST_F(SoloVehicleTest, INIT_Base)
{
    delete testVeh;
    limits = VehicleLimits( -1, 3, -5, 160);
    testVeh = new SubVehicle(NULL, "ALT_VEH", 4, &limits, NULL);
    
    EXPECT_TRUE(testVeh->properlyInitialised());
    
    EXPECT_EQ(testVeh->getEnv(), nullptr);
    EXPECT_EQ(testVeh->getLicensePlate(), "ALT_VEH");
    EXPECT_EQ(testVeh->getLen(), 4);
    EXPECT_EQ(testVeh->getLimits(), &limits);
    EXPECT_EQ(testVeh->getCurrentRoad(), nullptr);
    
    EXPECT_EQ(testVeh->getAcceleration(), 0);
    EXPECT_EQ(testVeh->getSpeed(), 0);
    EXPECT_EQ(testVeh->getPosition(), 0);
}

TEST_F(SoloVehicleTest, INIT_Full)
{
    delete testVeh;
    limits = VehicleLimits( -1, 3, -5, 160);
    testVeh = new SubVehicle(NULL, "ALT_VEH", 4, &limits, NULL, 1, 2, 3);
    
    EXPECT_TRUE(testVeh->properlyInitialised());
    
    EXPECT_EQ(testVeh->getEnv(), nullptr);
    EXPECT_EQ(testVeh->getLicensePlate(), "ALT_VEH");
    EXPECT_EQ(testVeh->getLen(), 4);
    EXPECT_EQ(testVeh->getLimits(), &limits);
    EXPECT_EQ(testVeh->getCurrentRoad(), nullptr);
    
    EXPECT_EQ(testVeh->getAcceleration(), 1);
    EXPECT_EQ(testVeh->getSpeed(), 2);
    EXPECT_EQ(testVeh->getPosition(), 3);
}


///--- setter & getter tests ---/// TODO: move these to be in a roadsystem

TEST_F(SoloVehicleTest, SETGET_HappyDay)
{
    testVeh->setLicensePlate(" HeY4_");
    EXPECT_EQ(testVeh->getLicensePlate(), " HeY4_");
    
    testVeh->setAcceleration(3);
    EXPECT_EQ(testVeh->getAcceleration(), 3);
    
    testVeh->setSpeed(50);
    EXPECT_EQ(testVeh->getSpeed(), 50);
    
    // setPosition & setCurrentRoad require existence of a Road
    
    // setEnv requires existence of a RoadSystem
}

#endif //LNJPSE_VEHICLETESTS_H
