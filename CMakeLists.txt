cmake_minimum_required(VERSION 3.10.2)
project(ransomware)

# set c++ standard
set(CMAKE_CXX_STANDARD 14)

# set binary output path
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# Add the header files
include_directories(include)

# Add the source files
file(GLOB_RECURSE SOURCE_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")

# build the executable
add_executable(ransomware main.cpp ${SOURCE_FILES})