//
// Created by Padraic Calpin on 24/03/2017.
//

#ifndef STABILIZERCPP_SYMPLECTICPAULI_H
#define STABILIZERCPP_SYMPLECTICPAULI_H

#include "boost/dynamic_bitset.hpp"

using namespace boost;

typedef dynamic_bitset<>::size_type bInt;

class SymplecticPauli {
public:
    SymplecticPauli();
    SymplecticPauli(bInt nQubits);
    SymplecticPauli(bInt nQubits, bInt xNum, bInt zNum);
    SymplecticPauli(bInt nQubits,  dynamic_bitset<>& xBits, dynamic_bitset<>& zBits);
    dynamic_bitset<> XBits() const;
    dynamic_bitset<> ZBits() const;

    SymplecticPauli operator *(SymplecticPauli& p1, SymplecticPauli& p2);

private:
    bInt nQubits;
    dynamic_bitset<> xBits;
    dynamic_bitset<> zBits;
};

bool commutivityTest(SymplecticPauli& p1, SymplecticPauli& p2);

#endif //STABILIZERCPP_SYMPLECTICPAULI_H