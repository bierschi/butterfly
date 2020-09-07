cmake_minimum_required(VERSION 3.10.2)
project(ransomware)

# set c++ standard
set(CMAKE_CXX_STANDARD 11)

# set boost library settings
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

# find required Boost, OpenSSL and Threads packages
ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)
find_package(Boost 1.45.0 COMPONENTS filesystem regex log REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Threads)

# set binary output path
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# add the header files
include_directories(include)

# add the source files
file(GLOB_RECURSE SOURCE_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")

# include test folder as a subdirectory
enable_testing()
add_subdirectory(test)

# build the executable
if(Boost_FOUND)
    add_executable(ransomware main.cpp ${SOURCE_FILES})
    target_link_libraries(ransomware Boost::filesystem Boost::regex Boost::log OpenSSL::SSL ${CMAKE_THREAD_LIBS_INIT})
endif()

