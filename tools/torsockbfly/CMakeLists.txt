cmake_minimum_required(VERSION 3.10)
project(torsockbfly)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)

# Set binary output path
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# Include the header files
include_directories(include)

add_executable(torsockbfly src/main.cpp src/socket.cpp src/torSocket.cpp)
