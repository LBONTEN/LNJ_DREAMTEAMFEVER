//
// Created by Joren Van Borm on 2019-06-17.
//

#ifndef LNJPSE_PROJECT_LOGGER_H
#define LNJPSE_PROJECT_LOGGER_H

#include <iostream>
#include <string>

// based on the "service locator" pattern discussed here:
// http://gameprogrammingpatterns.com/service-locator.html

namespace logging
{
    /// Abstract interface for logs
    class Logger {
    public:
        virtual ~Logger(){};
        
        virtual void operator<<(std::string str)=0;
        virtual void operator<<(const char* str)=0;
        
        virtual std::string getLastLine()=0;
    };


/// global Logger var
    extern Logger* globalLog;

/*
/// use to gain acces to (or set) the global log
class LogLocator {
public:
    /// @ENSURE (result != null)
    static Logger* getLogger();
    
    /// set the logger provided by the class
    /// @REQUIRE (log != NULL)
    /// @ENSURE (getLogger() == log)
    static void provide(Logger* log);

private:
    static Logger* providedLog;
};
 */


/// logs to any ostream
    class GenericLogger : public Logger{
    public:
        ///@REQUIRE (target != NULL)
        GenericLogger(std::ostream* target);
        
        virtual ~GenericLogger();
        
        virtual void operator<<(std::string str);
        virtual void operator<<(const char* str);
        
        virtual std::string getLastLine();
    
    private:
        std::ostream* target;
        std::string lastLine;
    };


/// logs to nowhere at all
    class NullLogger : public Logger
    {
    public:
        virtual ~NullLogger();
        
        virtual void operator<<(std::string str);
        virtual void operator<<(const char* str);
        
        virtual std::string getLastLine();
    };
}


#endif //LNJPSE_PROJECT_LOGGER_H
