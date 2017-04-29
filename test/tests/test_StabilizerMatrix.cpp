//
// Created by Padraic Calpin on 19/04/2017.
//

#include "gtest/gtest.h"
#include "lib/SymplecticPauli.h"

#define TEST_FRIENDS \
    friend class SMTest_RowSwap_Test; \
    friend class SMTest_RowMult_Test;

#include "lib/StabilizerMatrix.h"

class SMTest : public ::testing::Test{
protected:
    SymplecticPauli p1, p2, p3, p4;
    std::vector<SymplecticPauli> gens;
    void SetUp() {
        p1 = SymplecticPauli(2,0,1);
        p2 = SymplecticPauli(2,0,2);
        p3 = SymplecticPauli(2,0,3);
        p4 = SymplecticPauli(2,1,0);

        gens = std::vector<SymplecticPauli> {p1,p2};
    }
};

TEST_F(SMTest, DefaultConstuctor){
    StabilizerMatrix m;
    ASSERT_EQ(m.NQubits(), 0);
    ASSERT_EQ(m.Generators().size(), 0);
}

TEST_F(SMTest, SizeConstructor){
    StabilizerMatrix m(2);
    ASSERT_EQ(m.NQubits(), 2);
    ASSERT_EQ(m.Generators().size(), 2);
}

TEST_F(SMTest, VectorConstructor){
    StabilizerMatrix m(gens);
    ASSERT_EQ(m.NQubits(), 2);
    ASSERT_EQ(m.Generators().size(), 2);
    ASSERT_EQ(m.Generators()[0], p1);
    ASSERT_EQ(m.Generators()[1], p2);
}

TEST_F(SMTest, InitializerConstructor){
    StabilizerMatrix m({p1,p2});
    ASSERT_EQ(m.NQubits(), 2);
    ASSERT_EQ(m.Generators().size(), 2);
    ASSERT_EQ(m.Generators()[0], p1);
    ASSERT_EQ(m.Generators()[1], p2);
}

TEST_F(SMTest, DoubleConstructor){
    StabilizerMatrix m(2, gens);
    ASSERT_EQ(m.NQubits(), 2);
    ASSERT_EQ(m.Generators().size(), 2);
    ASSERT_EQ(m.Generators()[0], p1);
    ASSERT_EQ(m.Generators()[1], p2);
}

TEST_F(SMTest, Equality){
    StabilizerMatrix m1({p1,p2});
    StabilizerMatrix m2(gens);
    ASSERT_EQ(m1,m2);
    StabilizerMatrix m3({p1,p4});
    ASSERT_NE(m1,m3);
}

TEST_F(SMTest, RowSwap){
    StabilizerMatrix m({p1,p2,p3});
    m.rowSwap(0,2);
    ASSERT_EQ(m.Generators()[0], p3);
    ASSERT_EQ(m.Generators()[2], p1);
}

TEST_F(SMTest, RowMult){
    StabilizerMatrix m(gens);
    m.rowMult(0,1);
    ASSERT_EQ(m.Generators()[1], p3);
}

TEST_F(SMTest, CanonicalForm){
    StabilizerMatrix m1({p1,p2});
    StabilizerMatrix m2({p1,p3});
    m1.toCanonicalForm();
    m2.toCanonicalForm();
    ASSERT_EQ(m1,m2);
}

TEST_F(SMTest, LinearIndependence){
    StabilizerMatrix m1({SymplecticPauli(3,0,1),SymplecticPauli(3,0,2),SymplecticPauli(3,0,3)});
    m1.toCanonicalForm();
    ASSERT_FALSE(m1.linearlyIndependent());
    StabilizerMatrix m2(gens);
    m2.toCanonicalForm();
    ASSERT_TRUE(m2.linearlyIndependent());
}