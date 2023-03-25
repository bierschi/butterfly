
# Set C++11 as standard
set(CMAKE_CXX_STANDARD 11)

# Find and include GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Add the header files
include_directories(include)

# Add the stubs source files
file(GLOB_RECURSE STUBS_SOURCES LIST_DIRECTORIES false *.h *.cpp "${CMAKE_SOURCE_DIR}/test/stubs/*.cpp")
set(SOURCES ${STUBS_SOURCES})
list(REMOVE_ITEM SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/torSocket.cpp ${CMAKE_SOURCE_DIR}/src/browser.cpp ${CMAKE_SOURCE_DIR}/src/connManager.cpp)

# Add the test source files
file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp "${CMAKE_SOURCE_DIR}/test/*.cpp" "${CMAKE_SOURCE_DIR}/test/crypto/*.cpp")
set(SOURCES ${TEST_SOURCES})

# Build the unittest executable
add_executable(${CMAKE_PROJECT_NAME}UnitTests ${TEST_SOURCES} ${STUBS_SOURCES})
add_test(NAME ${CMAKE_PROJECT_NAME}UnitTests COMMAND ${CMAKE_PROJECT_NAME}UnitTests)

# Link libs to the target
target_link_libraries(${CMAKE_PROJECT_NAME}UnitTests bfly gtest gtest_main ${OPENSSL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES} -ldl)
