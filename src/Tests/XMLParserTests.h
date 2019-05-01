/* Created by Joren Van Borm & Lenny Bontenakel
 */

#ifndef LNJPSE_PROJECT_XMLPARSERTESTS_H
#define LNJPSE_PROJECT_XMLPARSERTESTS_H


#include "../RoadSystem.h"
#include "../XMLParser.h"
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
    system = parser->parseRoadSystem("../src/Tests/test_in/disconnected_roads_empty.xml");
    
    ASSERT_FALSE(system == (RoadSystem*) NULL) << "Failed to open file, please check path";
    
    vector<Road*> parsedRoads = system->getVectorOfRoads();
    
    EXPECT_EQ((unsigned long) 2, parsedRoads.size());
    
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
    EXPECT_EQ((int) (100 / 3.6), E19->getSpeedLimit());
    EXPECT_EQ((unsigned int) 2000, E19->getLength());
    EXPECT_EQ((Road*) NULL, E19->getConnection());
    
    EXPECT_EQ("E42", E42->getName());
    EXPECT_EQ((int) (300 / 3.6), E42->getSpeedLimit());
    EXPECT_EQ((unsigned int) 1025, E42->getLength());
    EXPECT_EQ((Road*) NULL, E42->getConnection());
}

TEST_F(ParseTest, BASE_Car)
{
    system = parser->parseRoadSystem("../src/Tests/test_in/disconnected_roads.xml");
    
    ASSERT_FALSE(system == (RoadSystem*) NULL) << "Failed to open file, please check path";
    
    vector<Road*> parsedRoads = system->getVectorOfRoads();
    vector<Vehicle*> parsedVehs = system->getVectorOfVehicles();
    
    ASSERT_EQ((unsigned long) 3, parsedVehs.size());
    
    for (unsigned long vehIndex = 0; vehIndex < parsedVehs.size(); ++vehIndex)
    {
        const Vehicle* veh = parsedVehs[vehIndex];
        
        ASSERT_TRUE(veh->properlyInitialised());
        
        if (veh->getLicensePlate() == "1THK180")
        {
            EXPECT_EQ("Car", veh->getTypeName());
            EXPECT_EQ((unsigned int) 10, veh->getPosition());
            EXPECT_EQ(0, veh->getSpeed());
            
            const Road* road = veh->getCurrentRoad();
            ASSERT_NE((Road*) NULL, road);
            EXPECT_EQ("E19", road->getName());
            EXPECT_EQ(veh, road->getLanes()[0]->getVehicle("1THK180"));
            
            EXPECT_EQ(system, veh->getEnv());
            EXPECT_TRUE(system->contains(veh));
        }
        else if (veh->getLicensePlate() == "W0LHH")
        {
            EXPECT_EQ("Car", veh->getTypeName());
            EXPECT_EQ((unsigned int) 100, veh->getPosition());
            EXPECT_EQ(int (10/3.6), veh->getSpeed());

            const Road* road = veh->getCurrentRoad();
            ASSERT_NE((Road*) NULL, road);
            EXPECT_EQ("E42", road->getName());
            EXPECT_EQ(veh, road->getLanes()[0]->getVehicle("W0LHH"));
    
            EXPECT_EQ(system, veh->getEnv());
            EXPECT_TRUE(system->contains(veh));
        }
        else if (veh->getLicensePlate() == "651BUF")
        {
            EXPECT_EQ("Car", veh->getTypeName());
            EXPECT_EQ((unsigned int) 0, veh->getPosition());
            EXPECT_EQ(0, veh->getSpeed());
    
            const Road* road = veh->getCurrentRoad();
            ASSERT_NE((Road*) NULL, road);
            EXPECT_EQ("E19", road->getName());
            EXPECT_EQ(veh, road->getLanes()[0]->getVehicle("651BUF"));
    
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
    system = parser->parseRoadSystem("../src/Tests/test_in/tree_connection.xml");
    
    ASSERT_FALSE(system == (RoadSystem*) NULL) << "Failed to open file, please check path";
    
    vector<Road*> parsedRoads = system->getVectorOfRoads();
    
    ASSERT_EQ((unsigned long) 3, parsedRoads.size());
    
    for (unsigned long rdIndex = 0; rdIndex < parsedRoads.size(); ++rdIndex)
    {
        const Road* road = parsedRoads[rdIndex];
        
        if (road->getName() == "E19")
        {
            EXPECT_NE((Vehicle*) NULL, road->getLanes()[0]->getVehicle("651BUF"));
            
            ASSERT_NE((Road*) NULL, road->getConnection());
            EXPECT_EQ("E313", road->getConnection()->getName());
        }
        else if (road->getName() == "E313")
        {
            EXPECT_NE((Vehicle*) NULL, road->getLanes()[0]->getVehicle("1OUT00"));
    
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
    system = parser->parseRoadSystem("../src/Tests/test_in/loop_connection.xml");
    
    ASSERT_FALSE(system == (RoadSystem*) NULL) << "Failed to open file, please check path";
    
    vector<Road*> parsedRoads = system->getVectorOfRoads();
    
    ASSERT_EQ((unsigned long) 2, parsedRoads.size());
    
    for (unsigned long rdIndex = 0; rdIndex < parsedRoads.size(); ++rdIndex)
    {
        const Road* road = parsedRoads[rdIndex];
        
        if (road->getName() == "E19")
        {
            EXPECT_NE((Vehicle*) NULL, road->getLanes()[0]->getVehicle("651BUF"));
            
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

TEST_F(ParseTest, TYPES_All)
{
    system = parser->parseRoadSystem("../src/Tests/test_in/linear_types.xml");
    
    ASSERT_FALSE(system == (RoadSystem*) NULL) << "Failed to open file, please check path";
    
    vector<Vehicle*> parsedVehs = system->getVectorOfVehicles();
    
    ASSERT_EQ((unsigned long) 4, parsedVehs.size());
    
    for (unsigned long vehIndex = 0; vehIndex < parsedVehs.size(); ++vehIndex)
    {
        const Vehicle* veh = parsedVehs[vehIndex];
        
        ASSERT_TRUE(veh->properlyInitialised());
        
        if (veh->getLicensePlate() == "651BUF")
        {
            EXPECT_EQ("Car", veh->getTypeName());
            
            EXPECT_EQ(&stdCarLimits, veh->getLimits());
            EXPECT_EQ(stdCarLength, veh->getLen());
        }
        else if (veh->getLicensePlate() == "1OUT00")
        {
            EXPECT_EQ("Truck", veh->getTypeName());
    
            EXPECT_EQ(&stdTruckLimits, veh->getLimits());
            EXPECT_EQ(stdTruckLength, veh->getLen());
        }
        else if (veh->getLicensePlate() == "420PUF")
        {
            EXPECT_EQ("MotorCycle", veh->getTypeName());
        
            EXPECT_EQ(&stdMotorCycleLimits, veh->getLimits());
            EXPECT_EQ(stdMotorCycleLength, veh->getLen());
        }
        else if (veh->getLicensePlate() == "1337")
        {
            EXPECT_EQ("Bus", veh->getTypeName());
        
            EXPECT_EQ(&stdBusLimits, veh->getLimits());
            EXPECT_EQ(stdBusLength, veh->getLen());
        }
        else
        {
            ADD_FAILURE() << "Unexpected licence plate " << veh->getLicensePlate();
        }
    }
}


///--- Traffic signal parsing ---///

TEST_F(ParseTest, SIGNAL_All)
{
    system = parser->parseRoadSystem("../src/Tests/test_in/linear_signs.xml");
    
    ASSERT_FALSE(system == (RoadSystem*) NULL) << "Failed to open file, please check path";
    
    vector<Road*> parsedRoads = system->getVectorOfRoads();
    
    ASSERT_EQ((unsigned long) 1, parsedRoads.size());
    
    const vector<RoadSign*> parsedSigns = parsedRoads[0]->getAllSigns();
    
    ASSERT_EQ(4, parsedSigns.size());
    
    for (unsigned long signNr = 0; signNr < parsedSigns.size(); ++signNr)
    {
        RoadSign* currSign = parsedSigns[signNr];
        
        switch (currSign->getType())
        {
            case trafficLight :
            {
                ASSERT_FALSE(currSign->getRoad() == (Road*) NULL);
                EXPECT_EQ("E313", currSign->getRoad()->getName());
                
                EXPECT_EQ(1500, currSign->getPosition());
                
                EXPECT_EQ(currSign, (RoadSign*) parsedRoads[0]->getTrafficLightOnPosition(currSign->getPosition(), true));
                
                break;
            }
            case zoneStart :
            {
                ASSERT_FALSE(currSign->getRoad() == (Road*) NULL);
                EXPECT_EQ("E313", currSign->getRoad()->getName());
    
                Zone* zone = parsedRoads[0]->getZoneStartOnPosition(currSign->getPosition(), true);
                
                EXPECT_EQ(currSign, (RoadSign*) zone);
                
                switch (currSign->getPosition())
                {
                    case 3000 :
                    {
                        EXPECT_EQ(int (120 / 3.6), zone->getNewSpeedLimit());
                        break;
                    }
                    case 150 :
                    {
                        EXPECT_EQ(int (90 / 3.6), zone->getNewSpeedLimit());
                        break;
                    }
                    default :
                    {
                        ADD_FAILURE() << "unsexpected zone at " << currSign->getPosition();
                    }
                }
                
                break;
            }
            case busStop :
            {
                ASSERT_FALSE(currSign->getRoad() == (Road*) NULL);
                EXPECT_EQ("E313", currSign->getRoad()->getName());
    
                EXPECT_EQ(0, currSign->getPosition());
    
                EXPECT_EQ(currSign, (RoadSign*) parsedRoads[0]->getBusStopOnPosition(currSign->getPosition(), true));
                
                break;
            }
            default:
            {
                ADD_FAILURE() << "unexpected roadsign type " << currSign->getType();
            }
        }
    }
}


#endif //LNJPSE_PROJECT_XMLPARSERTESTS_H