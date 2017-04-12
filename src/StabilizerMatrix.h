//
// Created by Padraic Calpin on 12/04/2017.
//

#ifndef STABILIZERCPP_STABILIZERMATRIX_H
#define STABILIZERCPP_STABILIZERMATRIX_H

#include "SymplecticPauli.h"

typedef std::vector<SymplecticPauli>::size_type SMIndex;

class StabilizerMatrix {
private:
    unsigned int nQubits;
    std::vector<SymplecticPauli> generators;
    void rowSwap(SMIndex i, SMIndex j);
    void rowMult(SMIndex i, SMIndex j);
public:
    StabilizerMatrix();
    StabilizerMatrix(unsigned int NQubits);
    StabilizerMatrix(std::vector<SymplecticPauli> paulis);
    StabilizerMatrix(unsigned int NQubits, std::vector<SymplecticPauli> paulis);
//    StabilizerMatrix(StabilizerMatrix& m);
    void toCanonicalForm();
    bool linearlyIndependent() const;

};

bool operator==(const StabilizerMatrix& m1, const StabilizerMatrix& m2);
bool operator!=(const StabilizerMatrix& m1, const StabilizerMatrix& m2);


#endif //STABILIZERCPP_STABILIZERMATRIX_H
