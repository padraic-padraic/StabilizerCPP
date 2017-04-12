project(symplectic_stabilizer)

include_directories( ${CMAKE_SOURCE_DIR}/src/lib )
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
set(LIB_FILES SymplecticPauli.cpp StabilizerGroup.cpp utils.cpp PauliMatrices.cpp lib/PauliMatrices.h StabilizerMatrix.cpp StabilizerMatrix.h)
add_library(symplectic_stabilizer ${LIB_FILES})
target_link_libraries(symplectic_stabilizer gtest gtest_main)