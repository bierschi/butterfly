
# Set c++11 as standard
set(CMAKE_CXX_STANDARD 11)

# Find and include GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Add the header files
include_directories(include)

# Add the test source files
file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp "${CMAKE_SOURCE_DIR}/test/src/*.cpp")
set(SOURCES ${TEST_SOURCES})

# Add the main source files
file(GLOB_RECURSE SOURCE_FILES "${CMAKE_SOURCE_DIR}/src/crypto/*.cpp" "${CMAKE_SOURCE_DIR}/src/*.cpp")
list(REMOVE_ITEM SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/main.cpp ${CMAKE_SOURCE_DIR}/src/sqlDatabase.cpp ${CMAKE_SOURCE_DIR}/src/aesKeyDatabase.cpp)

# Build the unittest executable
add_executable(${CMAKE_PROJECT_NAME}_unittests ${TEST_SOURCES} ${SOURCE_FILES})
add_test(NAME ${CMAKE_PROJECT_NAME}_unittests COMMAND ${CMAKE_PROJECT_NAME}_unittests)

# Link libs to the target
target_link_libraries(${CMAKE_PROJECT_NAME}_unittests gtest gtest_main OpenSSL::SSL ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES})
#target_link_libraries(${CMAKE_PROJECT_NAME}_unittests gtest gtest_main OpenSSL::SSL ${CMAKE_THREAD_LIBS_INIT} ${SQLite3_LIBRARIES} ${Boost_LIBRARIES})