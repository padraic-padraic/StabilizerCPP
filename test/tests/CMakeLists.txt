include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(aTest test_SymplecticPauli.cpp)

target_link_libraries(aTest gtest gtest_main)
target_link_libraries(aTest symplectic_stabilizer)