include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


set( TEST_FILES basicCheck.cpp test_SymplecticPauli.cpp)
add_executable(aTest ${TEST_FILES})

target_link_libraries(aTest gtest;gtest_main)
target_link_libraries(aTest symplectic_stabilizer)