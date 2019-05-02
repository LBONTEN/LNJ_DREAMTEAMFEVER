//
// Created by Joren Van Borm on 2019-05-01.
//

#ifndef LNJPSE_PROJECT_OUTPUTTESTS_H
#define LNJPSE_PROJECT_OUTPUTTESTS_H


#include <gtest/gtest.h>
#include <fstream>
#include <string>
#include "fileHelpers.h"
#include "../RoadSystem.h"
#include "../Output.h"
#include "../Road.h"
#include "../TypedVehicles.h"
#include "../RoadSigns.h"


class OutputTest : public testing::Test {
protected:
    OutputTest() :
        system(new RoadSystem),
        printer(new Output(system)),
        basePath("../src/Tests/"),
        outPath("test_out_real/"),
        checkPath("test_out_expected/")
    {}
    
    virtual void SetUp()
    {
        ASSERT_TRUE(DirectoryExists(basePath+outPath));
        ASSERT_TRUE(DirectoryExists(basePath+checkPath));
        
        EXPECT_EQ(classic, printer->style);
        printer->style=classic;
    }
    
    virtual ~OutputTest()
    {
        delete printer;
        delete system;
    }

    RoadSystem* system;
    Output* printer;
    ofstream result;
    
    std::string basePath;
    std::string outPath;
    std::string checkPath;
};

// test taken from http://ansymore.uantwerpen.be/system/files/uploads/courses/SE1BAC/TicTacToe21.zip
// Tests the compare files
TEST_F(OutputTest, FileCompare) {
    ofstream myfile;
    myfile.open((basePath+outPath+"file1.txt").c_str());
    myfile.close();
    myfile.open((basePath+outPath+"file2.txt").c_str());
    myfile.close();
    
    EXPECT_TRUE(FileExists(basePath+outPath+"file1.txt"));
    EXPECT_TRUE(FileExists(basePath+outPath+"file2.txt"));
    EXPECT_TRUE(FileIsEmpty(basePath+outPath+"file1.txt"));
    EXPECT_TRUE(FileIsEmpty(basePath+outPath+"file2.txt"));
    
    
    //compare 2 empty files
    EXPECT_TRUE(FileCompare(basePath+outPath+"file1.txt", basePath+outPath+"file2.txt"));
    EXPECT_TRUE(FileCompare(basePath+outPath+"file2.txt", basePath+outPath+"file1.txt"));
    
    //compare an empty and a non-empty files
    myfile.open((basePath+outPath+"file1.txt").c_str());
    myfile << "xxx" << endl << "yyy";
    myfile.close();
    EXPECT_TRUE(FileExists(basePath+outPath+"file1.txt"));
    EXPECT_FALSE(FileIsEmpty(basePath+outPath+"file1.txt"));
    EXPECT_FALSE(FileCompare(basePath+outPath+"file1.txt", basePath+outPath+"file2.txt"));
    EXPECT_FALSE(FileCompare(basePath+outPath+"file2.txt", basePath+outPath+"file1.txt"));
    
    //compare two equal files
    myfile.open((basePath+outPath+"file2.txt").c_str());
    myfile << "xxx" << endl << "yyy";
    myfile.close();
    EXPECT_TRUE(FileExists(basePath+outPath+"file2.txt"));
    EXPECT_FALSE(FileIsEmpty(basePath+outPath+"file2.txt"));
    EXPECT_TRUE(FileCompare(basePath+outPath+"file1.txt", basePath+outPath+"file2.txt"));
    EXPECT_TRUE(FileCompare(basePath+outPath+"file2.txt", basePath+outPath+"file1.txt"));
    
    //compare 2 non-empty files which are off by a character in the middle
    myfile.open((basePath+outPath+"file2.txt").c_str());
    myfile << "xxx" << endl << "xyy";
    myfile.close();
    EXPECT_FALSE(FileCompare(basePath+outPath+"file1.txt", basePath+outPath+"file2.txt"));
    EXPECT_FALSE(FileCompare(basePath+outPath+"file2.txt", basePath+outPath+"file1.txt"));
    
    //compare 2 non-empty files where one is one character shorter than the other
    myfile.open((basePath+outPath+"file2.txt").c_str());
    myfile << "xxx" << endl << "yy";
    myfile.close();
    EXPECT_FALSE(FileCompare(basePath+outPath+"file1.txt", basePath+outPath+"file2.txt"));
    EXPECT_FALSE(FileCompare(basePath+outPath+"file2.txt", basePath+outPath+"file1.txt"));
    
    //compare existing against non existing file
    EXPECT_FALSE(
            FileCompare(basePath+outPath+"file1.txt", "../src/Tests/test_out_real/nonexisting.txt"));
    EXPECT_FALSE(
            FileCompare("../src/Tests/test_out_real/nonexisting.txt", basePath+outPath+"file1.txt"));
}

TEST_F(OutputTest, ROAD_Base)
{
    system->addRoad(new Road("E0", 1605, 33));
    
    result.open((basePath+outPath+"ROAD_BASE_0.txt").c_str());
    result << (*printer);
    result.close();
    EXPECT_TRUE(FileCompare(basePath+checkPath+"ROAD_Base_0.txt", basePath+outPath+"ROAD_Base_0.txt"));
    
    result.open((basePath+outPath+"ROAD_BASE_0.txt").c_str());
    printer->classicPrint(result);
    result.close();
    EXPECT_TRUE(FileCompare(basePath+checkPath+"ROAD_Base_0.txt", basePath+outPath+"ROAD_Base_0.txt"));
    
    printer->style = text_graphic;
    
    result.open((basePath+outPath+"ROAD_BASE_1.txt").c_str());
    result << (*printer);
    result.close();
    EXPECT_TRUE(FileCompare(basePath+checkPath+"ROAD_Base_1.txt", basePath+outPath+"ROAD_Base_1.txt"));
    
    result.open((basePath+outPath+"ROAD_BASE_1.txt").c_str());
    printer->textGraphicPrint(result);
    result.close();
    EXPECT_TRUE(FileCompare(basePath+checkPath+"ROAD_Base_1.txt", basePath+outPath+"ROAD_Base_1.txt"));
    
    result.open((basePath+outPath+"ROAD_BASE_2.txt").c_str());
    printer->textGraphicPrint(result, 40);
    result.close();
    EXPECT_TRUE(FileCompare(basePath+checkPath+"ROAD_Base_2.txt", basePath+outPath+"ROAD_Base_2.txt"));
}

TEST_F(OutputTest, Road_Network)
{
    Road* baseRd = new Road("E00", 1605, 33);
    
    system->addRoad(new Road("E1", 3007, 25, 1, baseRd));
    system->addRoad(baseRd);
    system->addRoad(new Road("E2", 200, 40, 1, baseRd));
    
    result.open((basePath+outPath+"ROAD_NETWORK_0.txt").c_str());
    result << (*printer);
    result.close();
    EXPECT_TRUE(FileCompare(basePath+checkPath+"ROAD_Network_0.txt", basePath+outPath+"ROAD_Network_0.txt"));
    
    printer->style = text_graphic;
    
    result.open((basePath+outPath+"ROAD_NETWORK_1.txt").c_str());
    result << (*printer);
    result.close();
    EXPECT_TRUE(FileCompare(basePath+checkPath+"ROAD_Network_1.txt", basePath+outPath+"ROAD_Network_1.txt"));
}

TEST_F(OutputTest, ROAD_Lanes)
{
    system->addRoad(new Road("E1", 3007, 25, 1));
    system->addRoad(new Road("E3", 2024, 30, 5));
    system->addRoad(new Road("E2", 200, 40, 2));
    
    result.open((basePath+outPath+"ROAD_LANES_0.txt").c_str());
    result << (*printer);
    result.close();
    EXPECT_TRUE(FileCompare(basePath+checkPath+"ROAD_Lanes_0.txt", basePath+outPath+"ROAD_Lanes_0.txt"));
    
    printer->style = text_graphic;
    
    result.open((basePath+outPath+"ROAD_LANES_1.txt").c_str());
    result << (*printer);
    result.close();
    EXPECT_TRUE(FileCompare(basePath+checkPath+"ROAD_Lanes_1.txt", basePath+outPath+"ROAD_Lanes_1.txt"));
}

TEST_F(OutputTest, VEH_Base)
{
    Road* baseRd = new Road("E1", 3007, 25, 1);
    
    Vehicle* veh1 = new Car(system, "R4X3R", baseRd);
    Vehicle* veh2 = new Car(system, "L3NB01", baseRd, 0, 1, 300);
    
    baseRd->getLanes()[0]->addVehicle(veh1);
    baseRd->getLanes()[0]->addVehicle(veh2);
    
    system->addRoad(baseRd);
    
    system->addVehicle(veh1);
    system->addVehicle(veh2);
    
    result.open((basePath+outPath+"VEH_Base_0.txt").c_str());
    result << (*printer);
    result.close();
    EXPECT_TRUE(FileCompare(basePath+checkPath+"VEH_Base_0.txt", basePath+outPath+"VEH_Base_0.txt"));
    
    printer->style = text_graphic;
    
    result.open((basePath+outPath+"VEH_Base_1.txt").c_str());
    result << (*printer);
    result.close();
    EXPECT_TRUE(FileCompare(basePath+checkPath+"VEH_Base_1.txt", basePath+outPath+"VEH_Base_1.txt"));
}

TEST_F(OutputTest, VEH_Types)
{
    Road* baseRd = new Road("E1", 3007, 25, 1);
    
    Vehicle* veh1 = new MotorCycle(system, "R4X3R", baseRd);
    Vehicle* veh2 = new Truck(system, "L3NB01", baseRd, 0, 1, 300);
    Vehicle* veh3 = new Car(system, "N3170Y", baseRd, 0, 1, 1000);
    Vehicle* veh4 = new Bus(system, "1234", baseRd, 0, 1, 2500);
    
    baseRd->getLanes()[0]->addVehicle(veh1);
    baseRd->getLanes()[0]->addVehicle(veh2);
    baseRd->getLanes()[0]->addVehicle(veh3);
    baseRd->getLanes()[0]->addVehicle(veh4);
    
    system->addRoad(baseRd);
    
    system->addVehicle(veh1);
    system->addVehicle(veh2);
    system->addVehicle(veh3);
    system->addVehicle(veh4);
    
    result.open((basePath+outPath+"VEH_Types_0.txt").c_str());
    result << (*printer);
    result.close();
    EXPECT_TRUE(FileCompare(basePath+checkPath+"VEH_Types_0.txt", basePath+outPath+"VEH_Types_0.txt"));
    
    printer->style = text_graphic;
    
    result.open((basePath+outPath+"VEH_Types_1.txt").c_str());
    result << (*printer);
    result.close();
    EXPECT_TRUE(FileCompare(basePath+checkPath+"VEH_Types_1.txt", basePath+outPath+"VEH_Types_1.txt"));
}

TEST_F(OutputTest, SIGN_All)
{
    Road* baseRd = new Road("E1", 3007, 25, 1);
    
    system->addRoad(baseRd);
    
    baseRd->addTrafficLight(new TrafficLight(420, baseRd, 0));
    
    baseRd->addZone(new Zone(1500, baseRd, 20));
    
    baseRd->addBusstop(new BusStop(30, baseRd));
    
    // subject to change
    result.open((basePath+outPath+"SIGN_ALL_0.txt").c_str());
    result << (*printer);
    result.close();
    EXPECT_TRUE(FileCompare(basePath+checkPath+"SIGN_All_0.txt", basePath+outPath+"SIGN_All_0.txt"));
    
    printer->style = text_graphic;
    
    result.open((basePath+outPath+"SIGN_All_1.txt").c_str());
    result << (*printer);
    result.close();
    EXPECT_TRUE(FileCompare(basePath+checkPath+"SIGN_All_1.txt", basePath+outPath+"SIGN_All_1.txt"));
}


#endif //LNJPSE_PROJECT_OUTPUTTESTS_H
