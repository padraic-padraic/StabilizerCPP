cmake_minimum_required(VERSION 2.7)
project(StabilizerCPP)

set(CMAKE_CXX_STANDARD 11)

MESSAGE(${CMAKE_SOURCE_DIR})
set(NO_BOOST_CMAKE TRUE)
find_package(BOOST REQUIRED COMPONENTS dynamic_bitset)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake;${CMAKE_MODULE_PATH}")
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})
include_directories( ${CMAKE_SOURCE_DIR}/src/lib )
include_directories(src)
add_subdirectory(src)
add_subdirectory(test)
include(ctest)
enable_testing()

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set( TEST_FILES test/tests/test_SymplecticPauli.cpp test/tests/test_StabilizerGroup.cpp)
add_executable(aTest ${TEST_FILES})
target_link_libraries(aTest gtest gtest_main)
target_link_libraries(aTest symplectic_stabilizer)
add_test(unit test/tests/aTest)


set(SOURCE_FILES src/main.cpp )
add_executable(StabilizerCPP ${SOURCE_FILES})
target_link_libraries(StabilizerCPP symplectic_stabilizer;${Boost_LIBRARIES})
