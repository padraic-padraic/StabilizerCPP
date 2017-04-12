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
}

StabilizerMatrix::StabilizerMatrix(unsigned int NQubits) {
    nQubits = NQubits;
    generators = std::vector<SymplecticPauli>(nQubits);
}

StabilizerMatrix::StabilizerMatrix(std::vector<SymplecticPauli> paulis) {
    nQubits = static_cast<unsigned int>(paulis.size());
    generators = std::vector<SymplecticPauli>(paulis);
}

StabilizerMatrix::StabilizerMatrix(unsigned int NQubits, std::vector<SymplecticPauli> paulis) {
    if (NQubits != static_cast<unsigned int>(paulis.size())){
        throw std::invalid_argument("A full Stabilizer Group on "+ std::to_string(NQubits) +
                                    "Qubits must have that many generators, not" + std::to_string(paulis.size()));
    }
    nQubits = NQubits;
    generators = std::vector<SymplecticPauli>(paulis);
}

void StabilizerMatrix::rowSwap(SMIndex i, SMIndex j) {
    std::iter_swap(this->generators.begin()+i, this->generators.begin()+j);
}

void StabilizerMatrix::toCanonicalForm() {
    return;
}

bool StabilizerMatrix::linearlyIndependent() const {
    return std::none_of(this->generators.cbegin(), this->generators.cend(), [](const SymplecticPauli p) {
                                                                            return p.isIdentity();
    });
}