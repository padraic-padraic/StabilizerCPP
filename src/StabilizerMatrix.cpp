//
// Created by Padraic Calpin on 12/04/2017.
//

#include <algorithm>
#include <exception>
#include <string>
#include <vector>
#include "lib/SymplecticPauli.h"
#include "StabilizerMatrix.h"

StabilizerMatrix::StabilizerMatrix() {
    nQubits=0;
    generators = std::vector<SymplecticPauli>();
    phase = 0;
}

StabilizerMatrix::StabilizerMatrix(unsigned int NQubits) {
    nQubits = NQubits;
    generators = std::vector<SymplecticPauli>(nQubits);
    phase = 0;
}

StabilizerMatrix::StabilizerMatrix(std::vector<SymplecticPauli> paulis) {
    nQubits = static_cast<unsigned int>(paulis.size());
    generators = std::vector<SymplecticPauli>(paulis);
    phase = 0;
}

StabilizerMatrix::StabilizerMatrix(std::initializer_list<SymplecticPauli> paulis) {
    nQubits = paulis.size();
    generators = std::vector<SymplecticPauli>();
    for(auto i=paulis.begin(); i!=paulis.end(); i++){
        generators.push_back(*i);
    }
    phase = 0;
}

StabilizerMatrix::StabilizerMatrix(unsigned int NQubits, std::vector<SymplecticPauli> paulis) {
    if (NQubits != static_cast<unsigned int>(paulis.size())){
        throw std::invalid_argument("A full Stabilizer Group on "+ std::to_string(NQubits) +
                                    "Qubits must have that many generators, not" + std::to_string(paulis.size()));
    }
    nQubits = NQubits;
    generators = std::vector<SymplecticPauli>(paulis);
    phase = 0;
}

StabilizerMatrix::StabilizerMatrix(std::vector<unsigned int> pauliNums){
    nQubits = pauliNums.size();
    SymplecticPauli placeholder;
    generators = std::vector<SymplecticPauli>();
    for (auto i=pauliNums.cbegin(); i!= pauliNums.cend(); i++){
        placeholder.setNum(*i);
        generators.push_back(placeholder);
    }
    phase = 0;
}

const unsigned int& StabilizerMatrix::NQubits() const {
    return this->nQubits;
}

const std::vector<SymplecticPauli>& StabilizerMatrix::Generators() const{
    return this->generators;
}

void StabilizerMatrix::rowSwap(SMIndex i, SMIndex j) {
    std::swap(this->generators[i], this->generators[j]);
}

void StabilizerMatrix::rowMult(SMIndex i, SMIndex j){
    this->generators[j] = (this->generators[i]*this->generators[j]);
}

void StabilizerMatrix::toCanonicalForm() {
    unsigned int i=0;
    for (unsigned int j =0; j<this->nQubits; j++) {
        for (unsigned int k = i; k < this->nQubits; k++) {
            if (this->generators[k].isXY(j)) {
                this->rowSwap(i, k);
                for (unsigned int m = 0; m < this->nQubits; m++) {
                    if ((m != i) && (this->generators[m].isXY(j))) {
                        this->rowMult(i, m);
                    }
                }
                i++;
                break;
            } else {
                continue;
            }
        }
    }
    for (unsigned int j=0; j<this->nQubits; j++){
        for (unsigned int k=i; k<this->nQubits; k++){
            if (this->generators[k].isZ(j)){
                this->rowSwap(i, k);
                for(unsigned int m=0; m<this->nQubits; m++){
                    if((m!=i)&&(this->generators[m].isZY(j))) {
                        this->rowMult(i, m);
                    }
                }
                i++;
                break;
            } else {
                continue;
            }
        }
    }
//    std::sort(this->generators.begin(), this->generators.end());
    return;
}

void StabilizerMatrix::setPhase(unsigned int p) {
    this->phase = p;
}

bool StabilizerMatrix::linearlyIndependent() const {
    return std::none_of(this->generators.cbegin(), this->generators.cend(), [](const SymplecticPauli p) {
        return p.isIdentity();
    });
}

bool StabilizerMatrix::isReal() const {
    return std::all_of(this->generators.cbegin(), this->generators.cend(), [](const SymplecticPauli p){
        return p.isReal();
    });
}

bool operator==(const StabilizerMatrix& m1, const StabilizerMatrix& m2){
    for (unsigned int i=0; i<m1.NQubits(); i++){
        if (m1.Generators()[i] != m2.Generators()[i]){
            return false;
        }
    }
    return true;
}

bool operator!=(const StabilizerMatrix& m1, const StabilizerMatrix& m2){
    return !(m1==m2);
}

std::string StabilizerMatrix::toString() const{
    std::string out;
    out = "GROUP\n";
    for(auto i = this->generators.cbegin(); i!=this->generators.cend(); i++){
        out += (*i).toString();
        out += "\n";
    }
    out += "ENDGROUP\n\n";
    return out;
}


std::ostream& operator<<(std::ostream& os, const StabilizerMatrix& m){
    os << m.toString();
    return os;
}

Eigen::MatrixXcd StabilizerMatrix::projector() const{
    dynamic_bitset<> phasebits(this->nQubits, this->phase);
    unsigned int dim = uiPow(2, this->nQubits);
    Eigen::MatrixXcd out(dim,dim), _identity(dim,dim), pauli(dim,dim);
    _identity = identity(dim);
    out = identity(dim);
    for(unsigned int i=0; i<this->generators.size(); i++){
        pauli = (this->generators[i]).toMatrix();
        if (phasebits[i] ==1){
            out = out *(_identity - pauli);
        } else {
            out = out * (_identity + pauli);
        }
        out = 0.5 * out;
    }
    return out;
}

Eigen::VectorXcd StabilizerMatrix::stabilizerState() const{
    unsigned int dim = uiPow(2, this->nQubits);
    Eigen::VectorXd::Index i;
    Eigen::MatrixXcd projector(dim, dim);
    Eigen::VectorXcd state(dim);
    Eigen::SelfAdjointEigenSolver<Eigen::MatrixXcd> eigenSystem;
    projector = this->projector();
    eigenSystem.compute(projector);
    eigenSystem.eigenvalues().maxCoeff(&i);
    state = eigenSystem.eigenvectors().col(i);
    return state;
}
