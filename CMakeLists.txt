cmake_minimum_required(VERSION 3.7)
project(StabilizerCPP)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp src/StabilizerGroup.cpp src/StabilizerGroup.h src/SymplecticPauli.cpp src/SymplecticPauli.h)
add_executable(StabilizerCPP ${SOURCE_FILES})