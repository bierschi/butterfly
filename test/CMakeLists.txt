
# set c++ standard
set(CMAKE_CXX_STANDARD 11)

# Find and include GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Add the header files
include_directories(include)

# Add the source files
file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp "${CMAKE_SOURCE_DIR}/test/src/*.cpp")
set(SOURCES ${TEST_SOURCES})

add_executable(${CMAKE_PROJECT_NAME}_unittests ${TEST_SOURCES})
add_test(NAME ${CMAKE_PROJECT_NAME}_unittests COMMAND ${CMAKE_PROJECT_NAME}_unittests)
target_link_libraries(${CMAKE_PROJECT_NAME}_unittests gtest gtest_main pthread Boost::filesystem Boost::regex Boost::log OpenSSL::SSL)