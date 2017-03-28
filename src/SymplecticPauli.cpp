//
// Created by Padraic Calpin on 24/03/2017.
//

#include "boost/dynamic_bitset.hpp"
#include "lib/SymplecticPauli.h"

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

SymplecticPauli::SymplecticPauli(bInt NQubits, int Num) {
    nQubits = NQubits;
    zBits = dynamic_bitset<>(Num&(2^NQubits));
    Num >>= NQubits;
    xBits = dynamic_bitset<>(Num&(2^NQubits));
}

SymplecticPauli::SymplecticPauli(const SymplecticPauli& p){
    nQubits = p.nQubits;
    xBits = dynamic_bitset<>(p.xBits);
    zBits = dynamic_bitset<>(p.zBits);
}

SymplecticPauli& SymplecticPauli::operator *=(const SymplecticPauli &p2) {
    if (this->nQubits!=p2.nQubits){
        throw "Pauli operators must act on the same number of qubits.";
    }
    this->xBits = this->xBits^p2.xBits;
    this->zBits = this->zBits^p2.zBits;
    return *this;
}

SymplecticPauli SymplecticPauli::operator *(const SymplecticPauli &p2) const{
    SymplecticPauli p(*this);
    p *= p2;
    return p;
}

inline bool SymplecticPauli::operator<(const SymplecticPauli& p2) {
    unsigned long x1, x2, z1, z2;
    x1 = this->xBits.to_ulong();
    x2 = p2.xBits.to_ulong();
    z1 = this->zBits.to_ulong();
    z2 = p2.zBits.to_ulong();
    if (this->nQubits != p2.nQubits) { return (this->nQubits < p2.nQubits); }
    if (x1!=x2) { return (x1<x2); }
    return (z1<z2);
}

inline bool SymplecticPauli::operator>(const SymplecticPauli &p2) {
    return !((*this).operator<(p2));
}

bool operator <(const SymplecticPauli& p1, const SymplecticPauli& p2){
    unsigned long x1, x2, z1, z2;
    x1 = p1.XBits().to_ulong();
    x2 = p2.XBits().to_ulong();
    z1 = p1.ZBits().to_ulong();
    z2 = p2.ZBits().to_ulong();
    if (p1.NQubits() != p2.NQubits()) { return (p1.NQubits() < p2.NQubits()); }
    if (x1!=x2) { return (x1<x2); }
    return (z1<z2);
}

bool operator>(const SymplecticPauli& p1, const SymplecticPauli& p2){
    return !(p1<p2);
}

inline bool SymplecticPauli::operator==(const SymplecticPauli& p2){
    if (this->nQubits != p2.nQubits) { return false; }
    if (this->xBits != p2.xBits) { return false; }
    return (this->zBits == p2.zBits);
}

inline bool SymplecticPauli::operator!=(const SymplecticPauli& p2){
    return !((*this).operator==(p2));
}

bool operator ==(const SymplecticPauli& p1, const SymplecticPauli& p2){
    if (p1.NQubits() != p2.NQubits()) { return false; }
    if (p1.XBits() != p2.XBits()) { return false; }
    return (p1.ZBits() == p2.ZBits());
}

bool operator !=(const SymplecticPauli& p1, const SymplecticPauli& p2){
    return !(p1==p2);
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
