//
// Created by Padraic Calpin on 24/03/2017.
//

#ifndef STABILIZERCPP_SYMPLECTICPAULI_H
#define STABILIZERCPP_SYMPLECTICPAULI_H

#include "boost/dynamic_bitset.hpp"
#include "Eigen/Dense"
#include <iostream>
#include <string>
#include "PauliMatrices.h"

using namespace boost;

typedef dynamic_bitset<>::size_type bInt;

class SymplecticPauli {
public:
    SymplecticPauli();
    SymplecticPauli(unsigned int NQubits);
    SymplecticPauli(unsigned int NQubits, unsigned int xNum, unsigned int zNum);
    SymplecticPauli(unsigned int NQubits, unsigned int Num);
    SymplecticPauli(const SymplecticPauli& p_copy);
    SymplecticPauli(std::string pauliLiterals);

    unsigned int NQubits() const;
    const dynamic_bitset<>& XBits() const;
    const dynamic_bitset<>& ZBits() const;
    void setNQubits(unsigned int num);
    void setX(unsigned int num);
    void setZ(unsigned int num);
    void setNum(unsigned int num);
    bool isXY(bInt index) const;
    bool isZY(bInt index) const;
    bool isIdentity() const;

    unsigned long toUlong() const;

    bool commutes(const SymplecticPauli &p2) const;

    std::string toString() const;
    Eigen::MatrixXcd toMatrix() const;

    SymplecticPauli operator *(const SymplecticPauli& p2) const;
    SymplecticPauli& operator *=(const SymplecticPauli& p2);

private:
    bInt nQubits;
    dynamic_bitset<> xBits;
    dynamic_bitset<> zBits;
    bool isNull() const;
};

bool commutivityTest(std::vector<SymplecticPauli>&);

bool operator==(const SymplecticPauli& p1, const SymplecticPauli& p2);
bool operator!=(const SymplecticPauli& p1, const SymplecticPauli& p2);


bool operator<(const SymplecticPauli& p1, const SymplecticPauli& p2);
bool operator>(const SymplecticPauli& p1, const SymplecticPauli& p2);

std::ostream& operator<<(std::ostream& os, const SymplecticPauli& p);

struct PauliHash {
    size_t operator()(const SymplecticPauli &p) const;
};

#endif //STABILIZERCPP_SYMPLECTICPAULI_H
