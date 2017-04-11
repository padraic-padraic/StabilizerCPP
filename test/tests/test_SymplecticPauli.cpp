//
// Created by Padraic Calpin on 10/04/2017.
//

#include "gtest/gtest.h"
#include "lib/SymplecticPauli.h"
#include "lib/utils.h"
#include <string>

class SPUnaryTests : public ::testing::Test {
protected:
    unsigned int NQUBITS=4;
    unsigned int XNUM = 6;
    unsigned int ZNUM = 5;
    unsigned int NUM = 101; // == XNUM*(2^4) + ZNUM;
    std::string expected = std::to_string(NQUBITS) + std::to_string(XNUM) + std::to_string(ZNUM);
};

TEST_F(SPUnaryTests, DefaultConstructor){
    SymplecticPauli p;
    std::cout << p.NQubits() << p.XBits() << p.ZBits() << std::endl;
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

TEST_F(SPUnaryTests, CopyConstructor){
    SymplecticPauli p(NQUBITS, NUM);
    SymplecticPauli p2(p);
    EXPECT_EQ(p.NQubits(),p2.NQubits());
    EXPECT_EQ(p.toUlong(), p2.toUlong());
}

TEST_F(SPUnaryTests, StringConstructor){
    SymplecticPauli expected(NQUBITS, NUM);
    SymplecticPauli p("IYXZ");
    ASSERT_EQ(p.NQubits(), expected.NQubits());
    ASSERT_EQ(p.XBits().to_ulong(), expected.XBits().to_ulong());
    ASSERT_EQ(p.ZBits().to_ulong(), expected.ZBits().to_ulong());
}

TEST_F(SPUnaryTests, Setters){
    SymplecticPauli p;
    p.setNQubits(NQUBITS);
    ASSERT_EQ(p.NQubits(), NQUBITS);
    ASSERT_EQ(p.XBits().size(), NQUBITS);
    ASSERT_EQ(p.ZBits().size(), NQUBITS);
    p.setX(XNUM);
    ASSERT_EQ(p.XBits().to_ulong(), XNUM);
    p.setZ(ZNUM);
    ASSERT_EQ(p.ZBits().to_ulong(), ZNUM);
    SymplecticPauli p2(NQUBITS);
    p2.setNum(NUM);
    ASSERT_EQ(p2.XBits().to_ulong(), XNUM);
    ASSERT_EQ(p2.ZBits().to_ulong(), ZNUM);
    ASSERT_EQ(p2.toUlong(), NUM);
}

TEST_F(SPUnaryTests, Exceptions){
    SymplecticPauli p(NQUBITS, NUM), p2(3,1,0);
    ASSERT_THROW(p*p2, std::length_error);
    ASSERT_THROW(p.commutes(p2), std::length_error);
    SymplecticPauli p3;
    ASSERT_THROW(p*p3, std::invalid_argument);
}

TEST_F(SPUnaryTests, UlongForm){
    SymplecticPauli p(NQUBITS, NUM);
    ASSERT_EQ(p.toUlong(), NUM);
}

TEST_F(SPUnaryTests, HashCheck){
    SymplecticPauli p(NQUBITS, NUM);
    ASSERT_EQ(std::hash<std::string>{}(expected), PauliHash{}(p));
}

TEST_F(SPUnaryTests, ToString){
    SymplecticPauli p(NQUBITS, NUM);
    std::string test = "IYXZ";
    std::string out = p.toString();
    ASSERT_EQ(test, out);
}

TEST_F(SPUnaryTests, ToMatrix){
    SymplecticPauli p(2, 2, 3);
    Eigen::MatrixXcd expected(4,4);
    expected << 0.,0.,-1.*I,0.,
                0.,0.,0.,1.*I,
                1.*I,0.,0.,0.,
                0.,-1.*I,0.,0.;
    EXPECT_EQ(p.toMatrix(), expected);
}

class SPBinaryTests : public ::testing::Test{
protected:
    void SetUp() {
        p1 = SymplecticPauli(4, 6, 5);// == IYXZ
        p2 = SymplecticPauli(4, 5, 5);// == IYIY
        p3 = SymplecticPauli(4, 3, 3);// == IIYY
    }
    SymplecticPauli p1, p2,p3;
};

TEST_F(SPBinaryTests, Commutation) {
    EXPECT_FALSE(p1.commutes(p2));
    EXPECT_TRUE(p2.commutes(p3));
    EXPECT_TRUE(p1.commutes(p3));
    std::vector<SymplecticPauli> pauli1 {p1,p2,p3};
    EXPECT_FALSE(commutivityTest(pauli1));
    std::vector<SymplecticPauli> pauli2 {SymplecticPauli(2,0,1),SymplecticPauli(2,0,0), SymplecticPauli(2,2,0)};
    EXPECT_TRUE(commutivityTest(pauli2));
}

TEST_F(SPBinaryTests, Equality) {
    ASSERT_TRUE(p1 == p1);
    ASSERT_FALSE(p1 != p1);
    ASSERT_TRUE(p1 != p2);
    ASSERT_FALSE(p1 == p2);
}

TEST_F(SPBinaryTests, Ordering) {
    ASSERT_GT(p1, p2);
    ASSERT_LT(p2, p1);
    ASSERT_LT(p3,p2);
}

TEST_F(SPBinaryTests, Multiply) {
    SymplecticPauli product(4,3,0);
    SymplecticPauli product2(p1);
    product2 *=p2;
    ASSERT_EQ(product, p1*p2);
    ASSERT_EQ(product, product2);
}
