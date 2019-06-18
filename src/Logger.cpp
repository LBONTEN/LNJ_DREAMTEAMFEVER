//
// Created by Joren Van Borm on 2019-06-17.
//

#include "Logger.h"
#include "design_by_contract.h"

#include <fstream>


/// LogLocator

Logger* LogLocator::providedLog = new NullLogger();

Logger* LogLocator::getLogger()
{
    ENSURE (providedLog != NULL, "Attempting to log to unset log");
    return LogLocator::providedLog;
}

void LogLocator::provide(Logger* log)
{
    REQUIRE (log != NULL, "cannot set log to null");
    delete log;
    LogLocator::providedLog = log;
    ENSURE (getLogger() == log, "failed to set logger");
}


/// Generic logger

GenericLogger::GenericLogger(std::ostream* target) : target(target)
{
    REQUIRE(target != NULL, "Logger requires valid ostream");
    lastLine = "";
}

GenericLogger::~GenericLogger()
{
}

void GenericLogger::operator<<(std::string str)
{
    (*target) << str;
    
    if (lastLine.empty() or lastLine.at(lastLine.size()-1) == '\n')
    {
        lastLine = str;
    }
    else
    {
        lastLine += str;
    }
}

void GenericLogger::operator<<(const char* str)
{
    (*this) << std::string (str);
}

std::string GenericLogger::getLastLine()
{
    return lastLine;
}


/// NullLogger

NullLogger::~NullLogger()
{
}

void NullLogger::operator<<(std::string str)
{
}

void NullLogger::operator<<(const char* str)
{
}

std::string NullLogger::getLastLine()
{
    return "";
}
