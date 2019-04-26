//
// Created by Joren Van Borm on 2019-04-25.
//

#ifndef LNJPSE_PROJECT_XMLPARSERTESTS_H
#define LNJPSE_PROJECT_XMLPARSERTESTS_H


#include "RoadSystem.h"
#include "XMLParser.h"
#include <algorithm>


/**
 * Test fixture for input parsing
 */
class ParseTest: public testing::Test {
protected:
    ParseTest() :
        system(NULL),
        parser(new XmlParser())
    {
    
    }
    
    ~ParseTest() {
        delete system;
        delete parser;
    }
    
    RoadSystem* system;
    XmlParser* parser;
};


///--- Basic parsing ---///

TEST_F(ParseTest, BASE_Road)
{
    system = parser->parseRoadSystem("../IO/TEST_IO/disconnected_roads_empty.xml");
    
    vector<Road*> parsedRoads = system->getVectorOfRoads();
    
    EXPECT_EQ(2, parsedRoads.size());
    
    EXPECT_TRUE(parsedRoads[0]->properlyInitialised());
    EXPECT_TRUE(parsedRoads[1]->properlyInitialised());
    
    Road* E19;
    Road* E42;
    
    if (parsedRoads[0]->getName() == "E19")
    {
        E19 = parsedRoads[0];
        E42 = parsedRoads[1];
    }
    else
    {
        E19 = parsedRoads[1];
        E42 = parsedRoads[0];
    }
    
    EXPECT_EQ("E19", E19->getName());
    EXPECT_EQ(100, E19->getMaximumSpeed());
    EXPECT_EQ(2000, E19->getLength());
    EXPECT_EQ((Road*) NULL, E19->getConnection());
    
    EXPECT_EQ("E42", E42->getName());
    EXPECT_EQ(300, E42->getMaximumSpeed());
    EXPECT_EQ(1025, E42->getLength());
    EXPECT_EQ((Road*) NULL, E42->getConnection());
}

TEST_F(ParseTest, BASE_Car)
{
    system = parser->parseRoadSystem("../IO/TEST_IO/disconnected_roads.xml");
    
    vector<Road*> parsedRoads = system->getVectorOfRoads();
    vector<Vehicle*> parsedVehs = system->getVectorOfVehicles();
    
    ASSERT_EQ(3, parsedVehs.size());
    
    for (unsigned long vehIndex = 0; vehIndex < parsedVehs.size(); ++vehIndex)
    {
        const Vehicle* veh = parsedVehs[vehIndex];
        
        ASSERT_TRUE(veh->properlyInitialised());
        
        if (veh->getLicensePlate() == "1THK180")
        {
            EXPECT_EQ("Car", veh->getTypeName());
            EXPECT_EQ(10, veh->getPosition());
            EXPECT_EQ(0, veh->getSpeed());
            
            const Road* road = veh->getCurrentRoad();
            ASSERT_NE((Road*) NULL, road);
            EXPECT_EQ("E19", road->getName());
            EXPECT_EQ(veh, road->getVehicle("1THK180"));
            
            EXPECT_EQ(system, veh->getEnv());
            EXPECT_TRUE(system->contains(veh));
        }
        else if (veh->getLicensePlate() == "W0LHH")
        {
            EXPECT_EQ("Car", veh->getTypeName());
            EXPECT_EQ(100, veh->getPosition());
            EXPECT_EQ((int) 10*3.6, veh->getSpeed());
    
            const Road* road = veh->getCurrentRoad();
            ASSERT_NE((Road*) NULL, road);
            EXPECT_EQ("E42", road->getName());
            EXPECT_EQ(veh, road->getVehicle("W0LHH"));
    
            EXPECT_EQ(system, veh->getEnv());
            EXPECT_TRUE(system->contains(veh));
        }
        else if (veh->getLicensePlate() == "651BUF")
        {
            EXPECT_EQ("Car", veh->getTypeName());
            EXPECT_EQ(0, veh->getPosition());
            EXPECT_EQ(0, veh->getSpeed());
    
            const Road* road = veh->getCurrentRoad();
            ASSERT_NE((Road*) NULL, road);
            EXPECT_EQ("E19", road->getName());
            EXPECT_EQ(veh, road->getVehicle("651BUF"));
    
            EXPECT_EQ(system, veh->getEnv());
            EXPECT_TRUE(system->contains(veh));
        }
        else
        {
            ADD_FAILURE() << "Unexpected licence plate " << veh->getLicensePlate();
        }
    }
}


///--- Road network parsing ---///

TEST_F(ParseTest, NETWORK_Tree)
{
    system = parser->parseRoadSystem("../IO/TEST_IO/tree_connection.xml");
    
    vector<Road*> parsedRoads = system->getVectorOfRoads();
    
    ASSERT_EQ(3, parsedRoads.size());
    
    for (unsigned long rdIndex = 0; rdIndex < parsedRoads.size(); ++rdIndex)
    {
        const Road* road = parsedRoads[rdIndex];
        
        if (road->getName() == "E19")
        {
            EXPECT_NE((Vehicle*) NULL, road->getVehicle("651BUF"));
            
            ASSERT_NE((Road*) NULL, road->getConnection());
            EXPECT_EQ("E313", road->getConnection()->getName());
        }
        else if (road->getName() == "E313")
        {
            EXPECT_NE((Vehicle*) NULL, road->getVehicle("1OUT00"));
    
            EXPECT_EQ((Road*) NULL, road->getConnection());
        }
        else if (road->getName() == "E42")
        {
            ASSERT_NE((Road*) NULL, road->getConnection());
            EXPECT_EQ("E313", road->getConnection()->getName());
        }
        else
        {
            ADD_FAILURE() << "Unexpected road " << road->getName();
        }
    }
}

TEST_F(ParseTest, NETWORK_Loop)
{
    system = parser->parseRoadSystem("../IO/TEST_IO/loop_connection.xml");
    
    vector<Road*> parsedRoads = system->getVectorOfRoads();
    
    ASSERT_EQ(2, parsedRoads.size());
    
    for (unsigned long rdIndex = 0; rdIndex < parsedRoads.size(); ++rdIndex)
    {
        const Road* road = parsedRoads[rdIndex];
        
        if (road->getName() == "E19")
        {
            EXPECT_NE((Vehicle*) NULL, road->getVehicle("651BUF"));
            
            ASSERT_NE((Road*) NULL, road->getConnection());
            EXPECT_EQ("E313", road->getConnection()->getName());
        }
        else if (road->getName() == "E313")
        {
            ASSERT_NE((Road*) NULL, road->getConnection());
            EXPECT_EQ("E19", road->getConnection()->getName());
        }
        else
        {
            ADD_FAILURE() << "Unexpected road " << road->getName();
        }
    }
}


///--- Typed vehicles parsing ---///

TEST_F(ParseTest, TYPES_Bike)
{

}

TEST_F(ParseTest, TYPES_Bus)
{

}

TEST_F(ParseTest, TYPES_Truck)
{

}


///--- Traffic signal parsing ---///

TEST_F(ParseTest, SIGNAL_Zone)
{

}

TEST_F(ParseTest, SIGNAL_Stop)
{

}

TEST_F(ParseTest, SIGNAL_Light)
{

}


#endif //LNJPSE_PROJECT_XMLPARSERTESTS_H