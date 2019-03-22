cmake_minimum_required(VERSION 3.6)
project(DAPIZZAPROJECT)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-Wall -Werror -O2")
set(CMAKE_EXE_LINKER_FLAGS -pthread)

# Set include dir
include_directories(./pugiXml)

# Set Library dir
link_directories(pugiXml)

# Source files shared between all build targets
set(SHARED_SOURCE_FILES
        ./pugiXml/pugixml.cpp
        Vehicle.cpp
        RoadSystem.cpp
        Road.cpp
        XMLParser.cpp
        Car.cpp Exceptions.cpp Exceptions.h)

# Set source files for RELEASE target
set(RELEASE_SOURCE_FILES
        main.cpp)

# Set source files for DEBUG target
set(DEBUG_SOURCE_FILES
        tests.cpp)

# Create RELEASE target
add_executable(PIZZA_EXE ${RELEASE_SOURCE_FILES} ${SHARED_SOURCE_FILES})

# Create DEBUG target
add_executable(PIZZA_DEBUG ${DEBUG_SOURCE_FILES} ${SHARED_SOURCE_FILES})
