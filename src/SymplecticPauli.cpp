//
// Created by Padraic Calpin on 24/03/2017.
//

#include "boost/dynamic_bitset.hpp"
#include "SymplecticPauli.h"

#include <exception>
#include <string>
#include <functional>

using namespace boost;

SymplecticPauli::SymplecticPauli(){
    nQubits = 0;
    xBits = dynamic_bitset<> (0);
    zBits = dynamic_bitset<> (0);
}

SymplecticPauli::SymplecticPauli(bInt NQubits){
    nQubits = NQubits;
    xBits = dynamic_bitset<> (NQubits);
    zBits = dynamic_bitset<> (NQubits);
}

SymplecticPauli::SymplecticPauli(bInt NQubits, int xNum, int zNum) {
    nQubits = NQubits;
    xBits =  dynamic_bitset<> (nQubits, xNum);
    zBits = dynamic_bitset<> (nQubits, zNum);
}

SymplecticPauli::SymplecticPauli(bInt NQubits, dynamic_bitset<> &xbits, dynamic_bitset<> &zbits){
    nQubits=NQubits;
    xBits=xbits;
    zBits=zbits;
}

SymplecticPauli& SymplecticPauli::operator *=(SymplecticPauli &p2) {
    if (this->nQubits!=p2.nQubits){
        throw "Pauli operators must act on the same number of qubits.";
    }
    this->xBits = this->xBits^p2.xBits;
    this->zBits = this->zBits^p2.zBits;
    return *this;
}

SymplecticPauli SymplecticPauli::operator *(SymplecticPauli &p2){
    SymplecticPauli p(this->nQubits, this->xBits, this->zBits);
    p *= p2;
    return p;
}

inline bool SymplecticPauli::operator==(const SymplecticPauli& p2){
    if (this->nQubits != p2.nQubits) { return false; }
    if (this->xBits != p2.xBits) { return false; }
    return (this->zBits == p2.zBits);
}

bool operator ==(const SymplecticPauli& p1, const SymplecticPauli& p2){
    if (p1.NQubits() != p2.NQubits()) { return false; }
    if (p1.XBits() != p2.XBits()) { return false; }
    return (p1.ZBits() == p2.ZBits());
}

bInt SymplecticPauli::NQubits() const{
    return this->nQubits;
}

dynamic_bitset<> SymplecticPauli::XBits() const {
    return this->xBits;
}

dynamic_bitset<> SymplecticPauli::ZBits() const {
    return  this->zBits;
}

bool commutivityTest(SymplecticPauli& p1, SymplecticPauli& p2) {
    unsigned long total = ((p1.XBits()^p2.ZBits()).count() +
                         (p1.ZBits()^p2.XBits()).count());
    return (total%2)==0;
}

size_t PauliHash::operator()(const SymplecticPauli &p) const{
    std::string temp = std::to_string(p.NQubits()) +
                       std::to_string(p.XBits().to_ulong())+
                       std::to_string(p.ZBits().to_ulong());
    return std::hash<std::string>()(temp);
}