//
// Created by Padraic Calpin on 24/03/2017.
//

#ifndef STABILIZERCPP_SYMPLECTICPAULI_H
#define STABILIZERCPP_SYMPLECTICPAULI_H

#include "boost/dynamic_bitset.hpp"
#include <iostream>

using namespace boost;

typedef dynamic_bitset<>::size_type bInt;

class SymplecticPauli {
public:
    SymplecticPauli();
    SymplecticPauli(unsigned int NQubits);
    SymplecticPauli(unsigned int NQubits, unsigned int xNum, unsigned int zNum);
    SymplecticPauli(unsigned int NQubits, unsigned int Num);
    SymplecticPauli(const SymplecticPauli& p_copy);

    unsigned int NQubits() const;
    dynamic_bitset<> XBits() const;
    dynamic_bitset<> ZBits() const;

    unsigned long toUlong() const;

    SymplecticPauli operator *(const SymplecticPauli& p2) const;
    SymplecticPauli& operator *=(const SymplecticPauli& p2);

    inline bool operator ==(const SymplecticPauli& p2);
    inline bool operator !=(const SymplecticPauli& p2);
    inline bool operator <(const SymplecticPauli& p2);
    inline bool operator >(const SymplecticPauli& p2);

private:
    bInt nQubits;
    dynamic_bitset<> xBits;
    dynamic_bitset<> zBits;
};

bool commutivityTest(SymplecticPauli& p1, SymplecticPauli& p2);

bool operator==(const SymplecticPauli& p1, const SymplecticPauli& p2);
bool operator!=(const SymplecticPauli& p1, const SymplecticPauli& p2);


bool operator<(const SymplecticPauli& p1, const SymplecticPauli& p2);
bool operator>(const SymplecticPauli& p1, const SymplecticPauli& p2);

std::ostream& operator<<(std::ostream& os, const SymplecticPauli& p);

struct PauliHash {
    size_t operator()(const SymplecticPauli &p) const;
};

#endif //STABILIZERCPP_SYMPLECTICPAULI_H
