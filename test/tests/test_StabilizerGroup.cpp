//
// Created by Padraic Calpin on 10/04/2017.
//

#include "gtest/gtest.h"
#include "lib/SymplecticPauli.h"
#include "lib/StabilizerGroup.h"

class SGTest : public ::testing::Test{
protected:
    SymplecticPauli p1, p2, p3;
    std::vector<SymplecticPauli> gens;
    void SetUp() {
        p1 = SymplecticPauli(2,0,1);
        p2 = SymplecticPauli(2,0,2);
        p3 = SymplecticPauli(2,1,0);

        gens = std::vector<SymplecticPauli> {p1,p2};
    }
};

TEST_F(SGTest, DefaultConstructor){
    StabilizerGroup g;
    ASSERT_EQ(g.nGenerators(), 0);
    ASSERT_EQ(g.order(), 0);
}

TEST_F(SGTest, VectorConstructor){
    StabilizerGroup g(gens);
    ASSERT_EQ(g.order(), 4); //2 Independent generators => 2^2 elements
    ASSERT_EQ(g.nGenerators(), 2);
}

TEST_F(SGTest, InitializerConstructor){
    StabilizerGroup g({p1, p2});
    ASSERT_EQ(g.order(), 4);
    ASSERT_EQ(g.nGenerators(), 2);
}

TEST_F(SGTest, GeneratorIndependence){
    StabilizerGroup g({p1, p2, p1});
    ASSERT_NE(g.nGenerators(), 3);
    ASSERT_EQ(g.order(), 4);
    g = StabilizerGroup({p1,SymplecticPauli(2,0,0)});
    ASSERT_NE(g.order(), 4);
}

TEST_F(SGTest, Equality){
    StabilizerGroup g({p1,p2});
    StabilizerGroup g2(gens);
    ASSERT_TRUE(g==g2);
    StabilizerGroup g3({p1, p3});
    ASSERT_TRUE(g!=g3);
}

TEST_F(SGTest, Inclusion){
    StabilizerGroup g({p1, p2});
    ASSERT_TRUE(g.contains(p1));
    ASSERT_FALSE(g.contains(p3));
}
