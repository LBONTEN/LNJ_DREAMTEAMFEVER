//
// Created by Joren Van Borm on 2019-06-18.
//

#ifndef LNJPSE_PROJECT_LOGGERTESTS_H
#define LNJPSE_PROJECT_LOGGERTESTS_H

#include "../Logger.h"
#include "fileHelpers.h"
#include <fstream>
#include <string>
#include <gtest/gtest.h>

/**
 * Test fixture for logging
 * (uses a seperate Logger instance)
 */
class LogTest: public testing::Test {
protected:
    LogTest() :
        testLog(NULL),
        testOut(),
        basePath("../src/Tests/"),
        outPath("test_out_real/"),
        checkPath("test_out_expected/"),
        prefix("LOG_")
    {
    }
    
    ~LogTest()
    {
        delete testLog;
    }
    
    logging::Logger* testLog;
    
    std::ofstream testOut;
    
    std::string basePath;
    std::string outPath;
    std::string checkPath;
    std::string prefix;
};

TEST_F(LogTest, GENERIC_Log)
{
    testLog = new logging::GenericLogger(&testOut);
    testOut.open(basePath + outPath + prefix + "GENERIC_Log.txt");
    
    *testLog << "Logging string literal\n";
    
    *testLog << std::string ("Logging std::string\n");
    
    *testLog << "Logging multiline\n"
                "\tlog entry\n";
    
    *testLog << "Logging one line "; *testLog << "in multiple operations\n";
    
    *testLog << "Logging an unfinished line";
    
    testOut.close();
    
    EXPECT_TRUE(FileCompare(basePath + outPath + prefix + "GENERIC_Log.txt", basePath + checkPath + prefix + "GENERIC_Log.txt"));
}

TEST_F(LogTest, GENERIC_Recall)
{
    testLog = new logging::GenericLogger(&testOut);
    
    *testLog << "Normal log entry\n";
    EXPECT_EQ("Normal log entry\n", testLog->getLastLine());
    
    *testLog << "Logging multiline\n"
                "\tlog entry\n";
    EXPECT_EQ("\tlog entry\n", testLog->getLastLine());
    
    *testLog << "Logging one line "; *testLog << "in multiple operations\n";
    EXPECT_EQ("Logging one line in multiple operations\n", testLog->getLastLine());
    
    *testLog << "Logging an unfinished line";
    EXPECT_EQ("Logging an unfinished line", testLog->getLastLine());
}


TEST_F(LogTest, NULL)
{
    testLog = new logging::NullLogger;
    
    *testLog << "Any log entry\n";
    EXPECT_EQ("", testLog->getLastLine());
}

#endif //LNJPSE_PROJECT_LOGGERTESTS_H
