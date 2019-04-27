//
// Created by Joren Van Borm on 2019-04-25.
//

#ifndef LNJPSE_PROJECT_IOTESTS_H
#define LNJPSE_PROJECT_IOTESTS_H


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


///--- xml input tests ---///

TEST_F(ParseTest, BASE_MonoRoad)
{
    system = parser->parseRoadSystem("../IO/TEST_IO/disconnected_roads.xml");
    
    vector<Road*> parsedRoads = system->getVectorOfRoads();
    
    EXPECT_EQ((unsigned int) 2, parsedRoads.size());
    
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
    EXPECT_EQ(100, E19->getSpeedLimit());
    EXPECT_EQ((unsigned int) 2000, E19->getLength());
    EXPECT_EQ((Road*) NULL, E19->getConnection());
    
    EXPECT_EQ("E42", E42->getName());
    EXPECT_EQ(300, E42->getSpeedLimit());
    EXPECT_EQ((unsigned int) 1025, E42->getLength());
    EXPECT_EQ((Road*) NULL, E42->getConnection());
}

#endif //LNJPSE_PROJECT_IOTESTS_H