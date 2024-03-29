cmake_minimum_required(VERSION 3.6)
project(LNJPSE_Project)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-Wall -Werror") # -Wall -Werror -O2
set(CMAKE_EXE_LINKER_FLAGS -pthread)

# Set include dir
include_directories(pugiXml gtest/include)

# Set Library dir
link_directories(pugiXml gtest/lib)

# Specify folder where executables are located
set(PROJECT_BINARY_DIR ../bin)

# Changes executable output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

# Source files shared between all build targets
set(SHARED_SOURCE_FILES
        pugiXml/pugixml.cpp
        Vehicle.cpp
        RoadSystem.cpp
        Road.cpp
        XMLParser.cpp
        TypedVehicles.cpp
        Output.cpp
        DefaultVehicle.cpp
        RoadSigns.cpp
        Logger.cpp)

# Set source files for RELEASE target
set(RELEASE_SOURCE_FILES
        main.cpp)

# Set source files for DEBUG target
set(DEBUG_SOURCE_FILES
        Tests/fileHelpers.cpp
        Tests/Tests.cpp Tests/LoggerTests.h)

# Create RELEASE target
add_executable(LNJPSE ${RELEASE_SOURCE_FILES} ${SHARED_SOURCE_FILES})

# Create DEBUG target
add_executable(LNJPSE_DEBUG ${DEBUG_SOURCE_FILES} ${SHARED_SOURCE_FILES})

# Link library
target_link_libraries(LNJPSE_DEBUG gtest)
