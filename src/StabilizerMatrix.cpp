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

StabilizerMatrix::StabilizerMatrix(std::initializer_list<SymplecticPauli> paulis) {
    nQubits = paulis.size();
    generators = std::vector<SymplecticPauli>();
    for(auto i=paulis.begin(); i!=paulis.end(); i++){
        generators.push_back(*i);
    }
}

StabilizerMatrix::StabilizerMatrix(unsigned int NQubits, std::vector<SymplecticPauli> paulis) {
    if (NQubits != static_cast<unsigned int>(paulis.size())){
        throw std::invalid_argument("A full Stabilizer Group on "+ std::to_string(NQubits) +
                                    "Qubits must have that many generators, not" + std::to_string(paulis.size()));
    }
    nQubits = NQubits;
    generators = std::vector<SymplecticPauli>(paulis);
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
    for (unsigned int j =0; j<this->nQubits; j++){
        for(unsigned int k=i; k<this->nQubits; k++){
            if (this->generators[k].isXY(j)){
                this->rowSwap(i, k);
                for (unsigned int m=0; m<this->nQubits; m++){
                    if ((m!=i)&&(this->generators[m].isXY(j))){
                        this->rowMult(i, m);
                    }
                }
                i++;
            } else {
                continue;
            }
        }
    }
    for (unsigned int j=0; j<this->nQubits; j++){
        for (unsigned int k=i; k<this->nQubits; k++){
            if (this->generators[k].isZY(j)){
                this->rowSwap(i, k);
                for(unsigned int m=0; m<this->nQubits; m++){
                    if((m!=i)&&(this->generators[m].isZY(j))) {
                        this->rowMult(i, m);
                    }
                }
                i++;
            } else {
                continue;
            }
        }
    }
//    std::sort(this->generators.begin(), this->generators.end());
    return;
}

bool StabilizerMatrix::linearlyIndependent() const {
    return std::none_of(this->generators.cbegin(), this->generators.cend(), [](const SymplecticPauli p) {
                                                                            return p.isIdentity();
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

std::ostream& operator<<(std::ostream& os, const StabilizerMatrix& m){
    std::cout << "GROUP" << std::endl;
    for(auto i=m.Generators().cbegin(); i!=m.Generators().cend(); i++){
        os << (*i) << std::endl;
    }
    os << "ENDGROUP"<< std::endl;
    os << "\n\n";
    return os;
}

std::vector<StabilizerMatrix> getStabilizerGroups(unsigned int nQubits){
    unsigned int generatorIndex = 0;
    std::vector<StabilizerMatrix> groups;
    std::vector<SymplecticPauli> elements;
    for (unsigned int i=1; i<uiPow(2,2*nQubits); i++){
        elements.push_back(SymplecticPauli(nQubits, i));
    }
    std::vector<bool> mask = getMaskArray(elements.size(), nQubits);
    std::vector<SymplecticPauli> generatorCandidates(nQubits);
    do {
        StabilizerMatrix candidate;
        for(std::vector<bool>::size_type i=0; i<mask.size(); i++){
            if (mask[i]){
                generatorCandidates[generatorIndex] = elements[i];
                generatorIndex++;
            }
        }
        generatorIndex = 0;
        if (!commutivityTest(generatorCandidates)){ continue; }
        candidate = StabilizerMatrix(generatorCandidates);
        candidate.toCanonicalForm();
        if (!candidate.linearlyIndependent()){
            continue;
        }
        if (groups.size()==0){
            groups.push_back(candidate);
            continue;
        }
        if (std::none_of(groups.begin(), groups.end(), [&candidate](StabilizerMatrix& g){return candidate==g;})){
            groups.push_back(candidate);
        }
    } while(std::next_permutation(mask.begin(), mask.end()));
    return groups;
}
