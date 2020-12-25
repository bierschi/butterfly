
# set c++ standard
set(CMAKE_CXX_STANDARD 11)

# Find and include GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Add the header files
include_directories(include)

# Add the source files
file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp "${CMAKE_SOURCE_DIR}/src/*.cpp")
set(SOURCES ${TEST_SOURCES})

add_executable(ransomware_unittests ${TEST_SOURCES})
add_test(NAME ransomware_unittests COMMAND ransomware_unittests)
target_link_libraries(ransomware_unittests gtest gtest_main pthread Boost::filesystem Boost::regex OpenSSL::SSL)