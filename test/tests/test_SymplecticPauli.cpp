//
// Created by Padraic Calpin on 10/04/2017.
//

#include "gtest/gtest.h"

class SPConstructTests : public ::testing::Test {
protected:
    unsigned int NQUBITS=4;
    unsigned int XNUM = 6;
    unsigned int ZNUM = 5;
    unsigned int NUM = 101; // == XNUM*(2^4) + ZNUM;
};

TEST_F(SPConstructTests, DefaultConstructor){
}