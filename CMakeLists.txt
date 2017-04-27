cmake_minimum_required(VERSION 2.8)
MESSAGE("${CMAKE_CXX_COMPILER_ID}")
### C++ Settings ###
set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_EXTENSIONS  0) Required by gtest
set(CMKE_CXX_STANDARD_REQUIRED 1)
###

###Setup CMAKE Options###
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out)
set(CACHE BUILD_SHARED_LIBS OFF STRING "Turn on to build a dynamic library, or off for static.")
option(BUILD_SUPERBUILD "Build StabilizerCPP and all dependencies" OFF)
option(BUILD_TESTING "Build the unit tests." ON)

###

if(BUILD_SUPERBUILD)
    project(StabilizerCPP-superbuild)
    MESSAGE("Doin' a SuperBuild")
    #TODO: Actually implement SuperBuild *-*
else()
    project(StabilizerCPP)
    ### Settings for finding BOOST#
    set(Boost_NO_BOOST_CMAKE TRUE)
    find_package(Boost REQUIRED)
    if(Boost_FOUND)
        include_directories(${Boost_INCLUDE_DIRS})
    endif()
    ###
    ###Settings for finding EIGEN
    find_package(Eigen3 REQUIRED)
    include_directories(${EIGEN3_INCLUDE_DIR})
    ###
endif()

###Build Options
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Can be built in Release, Debug or RelWithDebInfo" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Release" "Debug" "RelWithDebInfo")
endif()
###

### Setup Project###
add_subdirectory(test)
add_subdirectory(src)
###
if(BUILD_TESTING)
    include(CTest)
    enable_testing()
    include_directories( ${CMAKE_SOURCE_DIR}/src)
    include_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
    set( TEST_FILES test/tests/test_SymplecticPauli.cpp test/tests/test_GroupGeneration.cpp test/tests/test_StabilizerMatrix.cpp)
    add_executable(do_tests ${TEST_FILES})
    set_target_properties(do_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
    target_link_libraries(do_tests gtest gtest_main)
    target_link_libraries(do_tests symplectic_stabilizer)
    add_test(unit do_tests)
endif()


set(SOURCE_FILES src/main.cpp )
add_executable(StabilizerCPP ${SOURCE_FILES})
target_link_libraries(StabilizerCPP ${Boost_LIBRARIES} symplectic_stabilizer )
