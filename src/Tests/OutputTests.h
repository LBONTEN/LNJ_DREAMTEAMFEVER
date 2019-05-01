//
// Created by Joren Van Borm on 2019-05-01.
//

#ifndef LNJPSE_PROJECT_OUTPUTTESTS_H
#define LNJPSE_PROJECT_OUTPUTTESTS_H


#include <gtest/gtest.h>
#include <fstream>
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
        printer(new Output(system))
    {}
    
    virtual ~OutputTest()
    {
        delete printer;
        delete system;
    }

    RoadSystem* system;
    Output* printer;
};

// test taken from http://ansymore.uantwerpen.be/system/files/uploads/courses/SE1BAC/TicTacToe21.zip
// Tests the compare files
TEST_F(OutputTest, FileCompare) {
    ASSERT_TRUE(DirectoryExists("../src/Tests/test_out_real"));
    
    ofstream myfile;
    myfile.open("../src/Tests/test_out_real/file1.txt");
    myfile.close();
    myfile.open("../src/Tests/test_out_real/file2.txt");
    myfile.close();
    
    EXPECT_TRUE(FileExists("../src/Tests/test_out_real/file1.txt"));
    EXPECT_TRUE(FileExists("../src/Tests/test_out_real/file2.txt"));
    EXPECT_TRUE(FileIsEmpty("../src/Tests/test_out_real/file1.txt"));
    EXPECT_TRUE(FileIsEmpty("../src/Tests/test_out_real/file2.txt"));
    
    
    //compare 2 empty files
    EXPECT_TRUE(FileCompare("../src/Tests/test_out_real/file1.txt", "../src/Tests/test_out_real/file2.txt"));
    EXPECT_TRUE(FileCompare("../src/Tests/test_out_real/file2.txt", "../src/Tests/test_out_real/file1.txt"));
    
    //compare an empty and a non-empty files
    myfile.open("../src/Tests/test_out_real/file1.txt");
    myfile << "xxx" << endl << "yyy";
    myfile.close();
    EXPECT_TRUE(FileExists("../src/Tests/test_out_real/file1.txt"));
    EXPECT_FALSE(FileIsEmpty("../src/Tests/test_out_real/file1.txt"));
    EXPECT_FALSE(FileCompare("../src/Tests/test_out_real/file1.txt", "../src/Tests/test_out_real/file2.txt"));
    EXPECT_FALSE(FileCompare("../src/Tests/test_out_real/file2.txt", "../src/Tests/test_out_real/file1.txt"));
    
    //compare two equal files
    myfile.open("../src/Tests/test_out_real/file2.txt");
    myfile << "xxx" << endl << "yyy";
    myfile.close();
    EXPECT_TRUE(FileExists("../src/Tests/test_out_real/file2.txt"));
    EXPECT_FALSE(FileIsEmpty("../src/Tests/test_out_real/file2.txt"));
    EXPECT_TRUE(FileCompare("../src/Tests/test_out_real/file1.txt", "../src/Tests/test_out_real/file2.txt"));
    EXPECT_TRUE(FileCompare("../src/Tests/test_out_real/file2.txt", "../src/Tests/test_out_real/file1.txt"));
    
    //compare 2 non-empty files which are off by a character in the middle
    myfile.open("../src/Tests/test_out_real/file2.txt");
    myfile << "xxx" << endl << "xyy";
    myfile.close();
    EXPECT_FALSE(FileCompare("../src/Tests/test_out_real/file1.txt", "../src/Tests/test_out_real/file2.txt"));
    EXPECT_FALSE(FileCompare("../src/Tests/test_out_real/file2.txt", "../src/Tests/test_out_real/file1.txt"));
    
    //compare 2 non-empty files where one is one character shorter than the other
    myfile.open("../src/Tests/test_out_real/file2.txt");
    myfile << "xxx" << endl << "yy";
    myfile.close();
    EXPECT_FALSE(FileCompare("../src/Tests/test_out_real/file1.txt", "../src/Tests/test_out_real/file2.txt"));
    EXPECT_FALSE(FileCompare("../src/Tests/test_out_real/file2.txt", "../src/Tests/test_out_real/file1.txt"));
    
    //compare existing against non existing file
    EXPECT_FALSE(
            FileCompare("../src/Tests/test_out_real/file1.txt", "../src/Tests/test_out_real/nonexisting.txt"));
    EXPECT_FALSE(
            FileCompare("../src/Tests/test_out_real/nonexisting.txt", "../src/Tests/test_out_real/file1.txt"));
}

TEST_F(OutputTest, ROAD_Base)
{
    system->addRoad(new Road("E0", 60, 33));
    
    
}


#endif //LNJPSE_PROJECT_OUTPUTTESTS_H
