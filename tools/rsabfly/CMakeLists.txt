cmake_minimum_required(VERSION 3.10)
project(rsabfly)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)

# Set binary output path
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# Find required OpenSSL package
find_package(OpenSSL REQUIRED)

# Include the header files
include_directories(include)

add_executable(rsabfly src/main.cpp src/rsa.cpp src/argumentParser.cpp)

target_link_libraries(rsabfly OpenSSL::SSL)
