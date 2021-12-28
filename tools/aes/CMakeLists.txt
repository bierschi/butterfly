cmake_minimum_required(VERSION 3.10)
project(aesbfly)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)

# Set binary output path
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# Find required OpenSSL package
find_package(OpenSSL REQUIRED)

# Include the header files
include_directories(include)

add_executable(aesbfly src/main.cpp src/aes.cpp)

target_link_libraries(aesbfly OpenSSL::SSL)