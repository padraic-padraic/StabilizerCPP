project(symplectic_stabilizer)

include_directories( ${CMAKE_SOURCE_DIR}/src/lib )
set(LIB_FILES SymplecticPauli.cpp StabilizerGroup.cpp utils.cpp PauliMatrices.cpp lib/PauliMatrices.h)
add_library(symplectic_stabilizer ${LIB_FILES})