cmake_minimum_required(VERSION 3.6)
project(DAPIZZAPROJECT)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-Wall -Werror -O2")
set(CMAKE_EXE_LINKER_FLAGS -pthread)

# Set include dir
include_directories(./gtest/include ../bin)

# Set Library dir
link_directories(./gtest/lib)

# Set source files for RELEASE target
set(RELEASE_SOURCE_FILES ./tinystuff/tinystr.cpp ./tinystuff/tinyxml.cpp ./tinystuff/tinyxmlerror.cpp ./tinystuff/tinyxmlparser.cpp main.cpp)

# Set source files for DEBUG target
set(DEBUG_SOURCE_FILES ./tinystuff/tinystr.cpp ./tinystuff/tinyxml.cpp ./tinystuff/tinyxmlerror.cpp ./tinystuff/tinyxmlparser.cpp main.cpp)

# Create RELEASE target
add_executable(PIZZA_EXE ${RELEASE_SOURCE_FILES})

# Create DEBUG target
add_executable(PIZZA_DEBUG ${DEBUG_SOURCE_FILES})
