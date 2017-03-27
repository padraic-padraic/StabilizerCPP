//
// Created by Padraic Calpin on 24/03/2017.
//

#include "boost/dynamic_bitset.hpp"
#include "SymplecticPauli.h"

using namespace boost;

SymplecticPauli::SymplecticPauli(){
    nQubits = 0;
    xBits = dynamic_bitset<> ();
    zBits = dynamic_bitset<> ();
}
SymplecticPauli::SymplecticPauli(bInt nQubits, bInt xNum, bInt zNum) {
    xBits =  dynamic_bitset<> (nQubits);
    zBits = dynamic_bitset<> (nQubits);
    for (bInt i = 0; i < xBits.size(); i++) {
        xBits[i] = xNum / (2 ^ i);
        zBits[i] = zNum / (2 ^ i);
    }
}

SymplecticPauli::SymplecticPauli(bInt nQubits, dynamic_bitset &xbits, dynamic_bitset &zbits){
    xBits=xbits;
   zBits=zbits;
}

SymplecticPauli::operator*(SymplecticPauli &p2) {
    dynamic_bitset<> newX = this->xBits^p2.xBits;
    dynamic_bitset<> newZ = this->zBits^p2.zBits;
    return SymplecticPauli(this->nQubits, newX, newZ);
}

dynamic_bitset SymplecticPauli::XBits() const {
    return this->xBits;
}

dynamic_bitset SymplecticPauli::ZBits() const {
    return  this->zBits;
}

bool commutivityTest(SymplecticPauli& p1, SymplecticPauli& p2) {
    unsigned long total= ((p1.XBits()^p2.ZBits()).count() +
                         (p1.ZBits()^p2.XBits()).count());
    return (total%2)==0;
}
