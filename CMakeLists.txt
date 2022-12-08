cmake_minimum_required(VERSION 3.10.2)

# Set project name and version
project(butterfly VERSION "1.2")

# Add app specific macros
configure_file(${CMAKE_SOURCE_DIR}/config/app.h.in app.h)

# Set C++11 as standard
set(CMAKE_CXX_STANDARD 11)

# Set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -Wconversion")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")                                       # compiler flag for static linking only

# Add build options
option(UNITTESTS "Enable Unittests" OFF)
option(LOGGING "Enable Logging" OFF)

# Set binary output path
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# Set OpenSSL and Boost library settings
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
set(OPENSSL_USE_STATIC_LIBS TRUE)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    message("Using the Linux Toolchain")

    # Find required OpenSSL and Boost packages
    find_package(OpenSSL REQUIRED)
    find_package(Boost 1.45.0 COMPONENTS filesystem)
    find_package(Threads REQUIRED)
    #find_package(SQLite3 REQUIRED)

    # Add the header files
    include_directories(include)
    include_directories(${PROJECT_BINARY_DIR})

    # Add the source files
    file(GLOB_RECURSE SOURCE_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")
    # Remove SQL Sources for now
    list(REMOVE_ITEM SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/sqlDatabase.cpp ${CMAKE_SOURCE_DIR}/src/aesKeyDatabase.cpp ${CMAKE_SOURCE_DIR}/src/os/windows/main.cpp)

    # Enable Boost Logging
    if(LOGGING)
        MESSAGE("Enabled Boost LOGGING Interface")
        find_package(Boost 1.45.0 COMPONENTS log log_setup REQUIRED)
        add_definitions(-DLOGGING)
    else()
        MESSAGE(STATUS "Disabled Boost LOGGING Interface")
    endif()

    # Enable Unittests and include test folder as a subdirectory
    if(UNITTESTS)
        MESSAGE("Enabled Unittests")
        # Set the Library Output Directory
        set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
        # Create library libbfly for UnitTests
        add_library (bfly ${SOURCE_FILES})
        # Enable the testing
        enable_testing()
        add_subdirectory(test)
    else()
        MESSAGE(STATUS "Disabled Unittests")
    endif()

    # Build the executable
    if(Boost_FOUND)
        add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})
        target_link_libraries(${CMAKE_PROJECT_NAME} ${OPENSSL_LIBRARIES} ${Boost_LIBRARIES} Threads::Threads -ldl)
        #target_link_libraries(${CMAKE_PROJECT_NAME} OpenSSL::SSL ${SQLite3_LIBRARIES} ${Boost_LIBRARIES})
    else()
        message(FATAL_ERROR "Boost Library filesystem not found!")
    endif()

elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    message("Using the Windows Toolchain")
    add_executable(${CMAKE_PROJECT_NAME} src/os/windows/main.cpp)

elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    message("Using the Darwin Toolchain")

else()
    message("Platform is not supported!")
endif()
