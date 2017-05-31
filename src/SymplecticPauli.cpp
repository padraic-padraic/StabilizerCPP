//
// Created by Padraic Calpin on 24/03/2017.
//

#include "boost/dynamic_bitset.hpp"
#include "boost/exception/to_string.hpp"
#include "Eigen/Dense"
#include "lib/PauliMatrices.h"
#include "lib/SymplecticPauli.h"
#include "lib/utils.h"
#include <algorithm>
#include <exception>
#include <functional>


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

SymplecticPauli::SymplecticPauli(std::string pauliLiterals) {
    nQubits = pauliLiterals.length();
    xBits = boost::dynamic_bitset<> (nQubits);
    zBits = boost::dynamic_bitset<> (nQubits);
    bInt counter = 0;
    for (auto c=pauliLiterals.crbegin(); c!=pauliLiterals.crend(); c++){
        switch (*c) {
            case 'I':
                xBits[counter]=0; zBits[counter]=0;
                break;
            case 'X':
                xBits[counter]=1; zBits[counter]=0;
                break;
            case 'Y':
                xBits[counter]=1; zBits[counter]=1;
                break;
            case 'Z':
                xBits[counter]=0; zBits[counter]=1;
                break;
        }
        counter++;
    }
}

void SymplecticPauli::setX(unsigned int num) {
    if (num > uiPow(2, this->nQubits)){
        throw std::out_of_range("The X/Z numbers cannot be larger than 2**n_qubits");
    }
    boost::dynamic_bitset<> _new(this->nQubits, num);
    this->xBits.swap(_new);
    return;
}

void SymplecticPauli::setZ(unsigned int num){
    if (num > uiPow(2, this->nQubits)){
        throw std::out_of_range("The X/Z numbers cannot be larger than 2**n_qubits");
    }
    boost::dynamic_bitset<> _new(this->nQubits, num);
    this->zBits.swap(_new);
    return;
}

void SymplecticPauli::setNQubits(unsigned int num) {
    this->nQubits = num;
    if (this->xBits.size()!=num){
        this->xBits.resize(num);
    }
    if (this->zBits.size()!=num){
        this->zBits.resize(num);
    }
    return;
}

void SymplecticPauli::setNum(unsigned int num) {
    if (num > uiPow(2, 2*this->nQubits)){
        throw std::out_of_range("The ulong form cannot be larger than 2**(2*n_qubits)");
    }
    unsigned int bnum, base=uiPow(2, this->nQubits);
    bnum = num % base;
    dynamic_bitset<> _newz(this->nQubits, bnum);
    this->zBits.swap(_newz);
    num >>= this->nQubits;
    bnum = num % base;
    dynamic_bitset<> _newx(this->nQubits, bnum);
    this->xBits.swap(_newx);
}

bool SymplecticPauli::isNull() const{
    if (this->nQubits==0 || this->xBits.size()==0 || this->zBits.size()==0){
        return true;
    }
    return false;
}

SymplecticPauli& SymplecticPauli::operator *=(const SymplecticPauli &p2) {
    if (this->isNull() || p2.isNull()){
        throw std::invalid_argument("One of the Pauli operators has not been properly initialized");
    }
    if (this->nQubits!=p2.nQubits){
        throw std::length_error("Cannot perform operations between Pauli Matrices on different numbers of qubits");
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

bool operator <(const SymplecticPauli& p1, const SymplecticPauli& p2){
    if (p1.NQubits() != p2.NQubits()){
        throw std::length_error("Cannot perform operations between Pauli Matrices on different numbers of qubits");
    }
    return (p1.toUlong() < p2.toUlong());
}

bool operator>(const SymplecticPauli& p1, const SymplecticPauli& p2){
    return !(p1<p2);
}

bool operator ==(const SymplecticPauli& p1, const SymplecticPauli& p2){
    return (p1.NQubits() == p2.NQubits()) && (p1.toUlong() == p2.toUlong());
}

bool operator !=(const SymplecticPauli& p1, const SymplecticPauli& p2){
    return !(p1==p2);
}

unsigned int SymplecticPauli::NQubits() const{
    return this->nQubits;
}

const dynamic_bitset<>& SymplecticPauli::XBits() const {
    return this->xBits;
}

const dynamic_bitset<>& SymplecticPauli::ZBits() const {
    return this->zBits;
}

const unsigned int SymplecticPauli::X() const {
    return dynamic_cast<unsigned int> (this->xBits.to_ulong());
}

const unsigned int SymplecticPauli::Z() const {
    return dynamic_cast<unsigned int> (this->zBits.to_ulong());
}

unsigned long SymplecticPauli::toUlong() const {
    unsigned long out= this->xBits.to_ulong();
    out <<= this->NQubits();
    out += this->zBits.to_ulong();
    return out;
}

bool SymplecticPauli::isXY(bInt index) const {
    return (this->xBits[index]==1);
}

bool SymplecticPauli::isZY(bInt index) const {
    return (this->zBits[index]==1);
}

bool SymplecticPauli::isIdentity() const {
    for(bInt index=0; index<this->xBits.size(); index++){
        if ((this->xBits[index]!=0)||(this->zBits[index]!=0)){
            return false;
        }
    }
    return true;
}

bool SymplecticPauli::commutes(const SymplecticPauli &p2) const {
    if (this->nQubits != p2.nQubits){
        throw std::length_error("Cannot perform operations between Pauli Matrices on different numbers of qubits");
    }
    unsigned long total = ((this->xBits&p2.zBits).count() +
                         (this->zBits&p2.xBits).count());
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

std::string SymplecticPauli::toString() const{
    std::string out;
    if (this->isNull()){
        out = "";
    }
    for(bInt i=0; i<this->NQubits(); i++){
        if (this->xBits[i]&this->zBits[i]){out= "Y" + out;}
        else if(this->xBits[i]&!(this->zBits[i])){out= "X" + out;}
        else if(!(this->xBits[i])&this->zBits[i]){out= "Z" + out;}
        else {out= "I" + out;}
    }
    return out;
}

Eigen::MatrixXcd SymplecticPauli::toMatrix() const{
    if (this->isNull()){
        Eigen::MatrixXcd out(1,1);
        out(1,1) = 0.;
        return out;
    }
    MatrixList paulis;
    for (bInt i=0; i<this->nQubits; i++){
        if (this->xBits[i]&this->zBits[i]){ paulis.push_back(Y);}
        else if(this->xBits[i]&!(this->zBits[i])){ paulis.push_back(X); }
        else if(!(this->xBits[i])&this->zBits[i]){ paulis.push_back(Z); }
        else {paulis.push_back(Id);}
    }
    std::reverse(paulis.begin(), paulis.end()); // Required due to definition of the bitarray [] operator, which is least
                                                // ->most significant and contrary to how we tend to reason about binary numbers.
    return tensor(paulis);
}

std::ostream& operator<<(std::ostream& os, const SymplecticPauli& p){
    os << p.toString();
    return os;
}

size_t PauliHash::operator()(const SymplecticPauli &p) const{
    std::string temp = boost::to_string(p.NQubits()) +
                       boost::to_string(p.XBits().to_ulong())+
                       boost::to_string(p.ZBits().to_ulong());
    return std::hash<std::string>()(temp);
}
