//
// Created by Joren Van Borm on 2019-03-19.
//

#ifndef DAPIZZAPROJECT_EXCEPTIONS_H
#define DAPIZZAPROJECT_EXCEPTIONS_H

#include <exception>

///--- pure virtual base class for all custom exceptions ---///

class RoadSimException: public std::exception {
public:
    RoadSimException();
    
    virtual const char* what() const throw()=0;
};


#endif //DAPIZZAPROJECT_EXCEPTIONS_H
