/* Created by Joren Van Borm & Lenny Bontenakel
 */

#ifndef LNJPSE_PROJECT_XMLPARSERTESTS_H
#define LNJPSE_PROJECT_XMLPARSERTESTS_H


#include "../RoadSystem.h"
#include "../XMLParser.h"
#include "../Output.h"
#include "fileHelpers.h"
#include <gtest/gtest.h>
#include <algorithm>
#include <fstream>


/**
 * Test fixture for input parsing
 */
class ParseTest: public testing::Test {
protected:
    ParseTest() :
        system(NULL),
        parser(new XmlParser()),
        printer(NULL),
        testOut(new ofstream()),
        basePath("../src/Tests/"),
        outPath("test_out_real/"),
        checkPath("test_out_expected/"),
        prefix("PARSE_")
    {
    }
    
    virtual void SetUp()
    {
        ASSERT_TRUE(DirectoryExists(basePath+outPath));
        ASSERT_TRUE(DirectoryExists(basePath+checkPath));
    }
    
    ~ParseTest() {
        delete system;
        delete parser;
        delete printer;
    }
    
    RoadSystem* system;
    XmlParser* parser;
    
    Output* printer;
    ofstream* testOut;
    
    std::string basePath;
    std::string outPath;
    std::string checkPath;
    std::string prefix;
};


///--- Basic parsing ---///

TEST_F(ParseTest, BASE_Road)
{
    system = parser->parseRoadSystem("../src/Tests/test_in/disconnected_roads_empty.xml");
    ASSERT_FALSE(system == (RoadSystem*) NULL) << "Failed to open file, please check path";
    
    printer = new Output(system);
    testOut->open(basePath + outPath + prefix + "BASE_Road.txt");
    *testOut << *printer;
    testOut->close();
    EXPECT_TRUE(FileCompare(basePath+checkPath+prefix+"BASE_Road.txt", basePath + outPath + prefix + "BASE_Road.txt"));
}

TEST_F(ParseTest, BASE_Car)
{
    system = parser->parseRoadSystem("../src/Tests/test_in/disconnected_roads.xml");
    ASSERT_FALSE(system == (RoadSystem*) NULL) << "Failed to open file, please check path";
    
    printer = new Output(system);
    testOut->open(basePath + outPath + prefix + "BASE_Car.txt");
    *testOut << *printer;
    testOut->close();
    EXPECT_TRUE(FileCompare(basePath+checkPath+prefix+"BASE_Car.txt", basePath + outPath + prefix + "BASE_Car.txt"));
}


///--- Road network parsing ---///

TEST_F(ParseTest, NETWORK_Tree)
{
    system = parser->parseRoadSystem("../src/Tests/test_in/tree_connection.xml");
    ASSERT_FALSE(system == (RoadSystem*) NULL) << "Failed to open file, please check path";
    
    printer = new Output(system);
    testOut->open(basePath + outPath + prefix + "NETWORK_Tree.txt");
    *testOut << *printer;
    testOut->close();
    EXPECT_TRUE(FileCompare(basePath+checkPath+prefix+"NETWORK_Tree.txt", basePath + outPath + prefix + "NETWORK_Tree.txt"));
}

TEST_F(ParseTest, NETWORK_Loop)
{
    system = parser->parseRoadSystem("../src/Tests/test_in/loop_connection.xml");
    ASSERT_FALSE(system == (RoadSystem*) NULL) << "Failed to open file, please check path";
    
    printer = new Output(system);
    testOut->open(basePath + outPath + prefix + "NETWORK_Loop.txt");
    *testOut << *printer;
    testOut->close();
    EXPECT_TRUE(FileCompare(basePath+checkPath+prefix+"NETWORK_Loop.txt", basePath + outPath + prefix + "NETWORK_Loop.txt"));
}


///--- Typed vehicles parsing ---///

TEST_F(ParseTest, TYPES_All)
{
    system = parser->parseRoadSystem("../src/Tests/test_in/linear_types.xml");
    ASSERT_FALSE(system == (RoadSystem*) NULL) << "Failed to open file, please check path";
    
    printer = new Output(system);
    testOut->open(basePath + outPath + prefix + "TYPES_All.txt");
    *testOut << *printer;
    testOut->close();
    EXPECT_TRUE(FileCompare(basePath+checkPath+prefix+"TYPES_All.txt", basePath + outPath + prefix + "TYPES_All.txt"));
}


///--- Traffic signal parsing ---///

TEST_F(ParseTest, SIGNAL_All)
{
    system = parser->parseRoadSystem("../src/Tests/test_in/linear_signs.xml");
    ASSERT_FALSE(system == (RoadSystem*) NULL) << "Failed to open file, please check path";
    
    printer = new Output(system);
    testOut->open(basePath + outPath + prefix + "SIGNAL_All.txt");
    *testOut << *printer;
    testOut->close();
    EXPECT_TRUE(FileCompare(basePath+checkPath+prefix+"SIGNAL_All.txt", basePath + outPath + prefix + "SIGNAL_All.txt"));
}


TEST_F(ParseTest, false1Test)
{
    system = parser->parseRoadSystem("../src/Tests/test_in/false1.xml");
    EXPECT_TRUE(system->getVectorOfRoads().empty());
}


TEST_F(ParseTest, false2Test)
{
    system = parser->parseRoadSystem("../src/Tests/test_in/false2.xml");

    EXPECT_EQ(system->getVectorOfRoads().size(), (unsigned  int) 1);
    EXPECT_EQ(system->getVectorOfVehicles().size(), (unsigned  int) 1);

    for(std::vector<Vehicle*>::const_iterator i = system->getVectorOfVehicles().begin(), end = system->getVectorOfVehicles().end(); i < end; i++)
    {
        EXPECT_NE((*i)->getLicensePlate(), "1THK180");
        EXPECT_NE((*i)->getLicensePlate(), "651BUF");
    }
}


TEST_F(ParseTest, false3Test)
{
    system = parser->parseRoadSystem("../src/Tests/test_in/false3.xml");

    EXPECT_TRUE(system->getVectorOfRoads().empty());
    EXPECT_TRUE(system->getVectorOfVehicles().empty());
}


TEST_F(ParseTest, false4Test)
{
    ASSERT_DEATH(system = parser->parseRoadSystem("../src/Tests/test_in/false4.xml"), ".*(Xml file must have leading ROOT tag.).*");
}

#endif //LNJPSE_PROJECT_XMLPARSERTESTS_H