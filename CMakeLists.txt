cmake_minimum_required(VERSION 3.10.2)

# Set project name and version
project(butterfly VERSION "1.0")

# Add app specific macros
configure_file(${CMAKE_SOURCE_DIR}/config/app.h.in app.h)

# Set c++11 as standard
set(CMAKE_CXX_STANDARD 11)

# Set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -Wconversion")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra")

# Add build options
option(UNITTESTS "Enable Unittests" OFF)

# Find required Boost, OpenSSL and Threads packages
find_package(Threads)
find_package(OpenSSL REQUIRED)
find_package(Boost 1.45.0 COMPONENTS filesystem regex log log_setup REQUIRED)

# Set boost library settings
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

# Set binary output path
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# Add the header files
include_directories(include)
include_directories(${PROJECT_BINARY_DIR})

# Add the source files
file(GLOB_RECURSE SOURCE_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")

# Enable Unittests and include test folder as a subdirectory
if(UNITTESTS)
    MESSAGE("Enabled Unittests")
    enable_testing()
    add_subdirectory(test)
else()
    MESSAGE("Disabled Unittests")
endif()

# Build the executable
if(Boost_FOUND)
    add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})
    target_link_libraries(${CMAKE_PROJECT_NAME} OpenSSL::SSL ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES})
else()
    message("Bosst Libraries not found!")
endif()

