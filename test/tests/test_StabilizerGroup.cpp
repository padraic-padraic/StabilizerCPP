//
// Created by Padraic Calpin on 10/04/2017.
//

#include "gtest/gtest.h"
#include "lib/SymplecticPauli.h"
#include "lib/StabilizerGroup.h"

class SGTest : public ::testing::Test{
protected:
    SymplecticPauli p1, p2;
    void SetUp() {
        p1 = SymplecticPauli(2,0,1);
        p2 = SymplecticPauli(2,0,2);
    }
};

TEST_F(SGTest, DefaultConstructor){
    StabilizerGroup g;
    ASSERT_EQ(g.order(), 0);
}