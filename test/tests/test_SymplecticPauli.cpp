//
// Created by Padraic Calpin on 10/04/2017.
//

#include "gtest/gtest.h"
#include "lib/SymplecticPauli.h"
#include <string>

class SPUnaryTests : public ::testing::Test {
protected:
    unsigned int NQUBITS=4;
    unsigned int XNUM = 6;
    unsigned int ZNUM = 5;
    unsigned int NUM = 101; // == XNUM*(2^4) + ZNUM;
};

TEST_F(SPUnaryTests, DefaultConstructor){
    SymplecticPauli p;
    EXPECT_EQ(p.NQubits(), 0);
    EXPECT_EQ(p.XBits().size(), 0);
    EXPECT_EQ(p.ZBits().size(), 0);
}

TEST_F(SPUnaryTests, LengthConstructor){
    SymplecticPauli p(NQUBITS);
    EXPECT_EQ(p.NQubits(), NQUBITS);
    EXPECT_EQ(p.XBits().size(),NQUBITS);
    EXPECT_EQ(p.ZBits().size(),NQUBITS);
}

TEST_F(SPUnaryTests, TwoNumberConstructor){
    SymplecticPauli p(NQUBITS, XNUM, ZNUM);
    EXPECT_EQ(p.XBits().to_ulong(), XNUM);
    EXPECT_EQ(p.ZBits().to_ulong(), ZNUM);
}

TEST_F(SPUnaryTests, OneNumberConstructor){
    SymplecticPauli p(NQUBITS, NUM);
    EXPECT_EQ(p.XBits().to_ulong(), XNUM);
    EXPECT_EQ(p.ZBits().to_ulong(), ZNUM);
}

TEST_F(SPUnaryTests, HashCheck){
    SymplecticPauli p(NQUBITS, NUM);
    std::string expected = std::to_string(NQUBITS) + std::to_string(XNUM) + std::to_string(ZNUM);
    ASSERT_EQ(std::hash<std::string>{}(expected), PauliHash{}(p));
}