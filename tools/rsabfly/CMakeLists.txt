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

# Add the source files
#file(GLOB_RECURSE SOURCE_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")

add_executable(rsabfly src/main.cpp src/rsa.cpp)
add_executable(rsa_crypto_example src/main_crypto_example.cpp src/rsa_crypto_example.cpp)

target_link_libraries(rsabfly OpenSSL::SSL)
target_link_libraries(rsa_crypto_example OpenSSL::SSL)