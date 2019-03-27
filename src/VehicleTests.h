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
class VehicleTest: public testing::Test
{
protected:
    VehicleTest() :
    limits(0, 5, -1, 1),
    testVeh(NULL, "BASE_VEH", 3, &limits, NULL) {}
    
    ~VehicleTest() {}
    
    VehicleLimits limits;
    SubVehicle testVeh;
};


TEST_F(VehicleTest, INIT_Default) {
    testVeh = SubVehicle();
    EXPECT_FALSE(testVeh.properlyInitialised());
}

TEST_F(VehicleTest, INIT_Base) {
    EXPECT_TRUE(testVeh.properlyInitialised());
}

#endif //LNJPSE_VEHICLETESTS_H
