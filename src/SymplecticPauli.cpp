//
// Created by Padraic Calpin on 24/03/2017.
//

#include "boost/dynamic_bitset.hpp"
#include "lib/SymplecticPauli.h"
#include "lib/utils.h"

using namespace boost;

SymplecticPauli::SymplecticPauli(){
    nQubits = 0;
    xBits = dynamic_bitset<> (0);
    zBits = dynamic_bitset<> (0);
}

SymplecticPauli::SymplecticPauli(unsigned int NQubits){
    nQubits = NQubits;
    xBits = dynamic_bitset<> (NQubits);
    zBits = dynamic_bitset<> (NQubits);
}

SymplecticPauli::SymplecticPauli(unsigned int NQubits, unsigned int xNum, unsigned int zNum) {
    nQubits = NQubits;
    xBits =  dynamic_bitset<> (nQubits, xNum);
    zBits = dynamic_bitset<> (nQubits, zNum);
}

SymplecticPauli::SymplecticPauli(unsigned int NQubits, unsigned int Num) {
    unsigned int bnum, base=uiPow(2,NQubits);
    nQubits = NQubits;
    bnum = Num % base;
    zBits = dynamic_bitset<>(NQubits, bnum);
    Num >>= NQubits;
    bnum = Num % base;
    xBits = dynamic_bitset<>(NQubits, bnum);
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
    if (this->NQubits() != p2.NQubits()){
        throw "Cannot compare Paulis on diffrent numbers of qubits.";
    }
    return this->toUlong() < p2.toUlong();
}

inline bool SymplecticPauli::operator>(const SymplecticPauli &p2) {
    return !((*this).operator<(p2));
}

bool operator <(const SymplecticPauli& p1, const SymplecticPauli& p2){
    if (p1.NQubits() != p2.NQubits()){
        throw "Cannot compare Paulis on diffrent numbers of qubits.";
    }
    return p1.toUlong() < p2.toUlong();
}

bool operator>(const SymplecticPauli& p1, const SymplecticPauli& p2){
    return !(p1<p2);
}

inline bool SymplecticPauli::operator==(const SymplecticPauli& p2) {
    if (this->nQubits != p2.nQubits) { return false; }
    return this->toUlong() == p2.toUlong();
}

inline bool SymplecticPauli::operator!=(const SymplecticPauli& p2){
    return !((*this).operator==(p2));
}

bool operator ==(const SymplecticPauli& p1, const SymplecticPauli& p2){
    if (p1.NQubits() != p2.NQubits()) { return false; }
    return p1.toUlong() == p2.toUlong();
}

bool operator !=(const SymplecticPauli& p1, const SymplecticPauli& p2){
    return !(p1==p2);
}

unsigned int SymplecticPauli::NQubits() const{
    return static_cast<unsigned int>(this->nQubits);
}

dynamic_bitset<> SymplecticPauli::XBits() const {
    return this->xBits;
}

dynamic_bitset<> SymplecticPauli::ZBits() const {
    return  this->zBits;
}

unsigned long SymplecticPauli::toUlong() const {
    unsigned long out= this->xBits.to_ulong();
    out <<= this->NQubits();
    out += this->zBits.to_ulong();
    return out;
}

bool SymplecticPauli::commutes(const SymplecticPauli &p2) const {
    if (this->nQubits != p2.nQubits){
        throw "Cannot test commutivity of operators on different number of qubits";
    }
    unsigned long total = ((this->xBits^p2.zBits).count() +
                         (this->zBits^p2.xBits).count());
    return (total%2)==0;
}

bool commutivityTest(std::vector<SymplecticPauli>& paulis){
    for(auto i = paulis.begin(); i!=paulis.end(); i++){
        for (auto j=i+1; j!=paulis.end(); j++){
            if (!(*i).commutes(*j)){return false;}
        }
    }
    return true;
}

std::ostream& operator<<(std::ostream& os, const SymplecticPauli& p){
    os << p.NQubits() << "\t" << "X: " << p.XBits().to_ulong() << "  Z: " << p.ZBits().to_ulong();
    return os;
}

size_t PauliHash::operator()(const SymplecticPauli &p) const{
    std::string temp = std::to_string(p.NQubits()) +
                       std::to_string(p.XBits().to_ulong())+
                       std::to_string(p.ZBits().to_ulong());
    return std::hash<std::string>{}(temp);
}
