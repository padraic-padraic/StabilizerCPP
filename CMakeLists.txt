cmake_minimum_required(VERSION 2.8)
project(StabilizerCPP)

### C++ Settings ###
set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_EXTENSIONS  0) Required by gtest
set(CMKE_CXX_STANDARD_REQUIRED 1)
###

###Setup CMAKE Options###
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake")
###

### Settings for finding BOOST#
set(Boost_NO_BOOST_CMAKE TRUE)
find_package(Boost COMPONENTS REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()
###

###Settings for finding EIGEN
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})
###

### Setup Project###
add_subdirectory(src)
add_subdirectory(test)

###

###Build Options
option(BUILD_TESTING "Build the unit tests." OFF)
###

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

if(BUILD_TESTING)
    include(CTest)
    enable_testing()
    set( TEST_FILES test/tests/test_SymplecticPauli.cpp test/tests/test_GroupGeneration.cpp test/tests/test_StabilizerMatrix.cpp)
    add_executable(do_tests ${TEST_FILES})
    target_link_libraries(do_tests gtest gtest_main)
    target_link_libraries(do_tests symplectic_stabilizer)
    add_test(unit do_tests)
endif()

include_directories(${CMAKE_SOURCE_DIR}/src/lib )
include_directories(src)
set(SOURCE_FILES src/main.cpp )
add_executable(StabilizerCPP ${SOURCE_FILES})
target_link_libraries(StabilizerCPP ${Boost_LIBRARIES} symplectic_stabilizer )
