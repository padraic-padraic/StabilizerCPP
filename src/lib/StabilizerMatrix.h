//
// Created by Padraic Calpin on 12/04/2017.
//

#ifndef STABILIZERCPP_STABILIZERMATRIX_H
#define STABILIZERCPP_STABILIZERMATRIX_H

#include <initializer_list>
#include <iostream>
#include <fstream>
#include <vector>
#include "Eigen/Dense"
#include "Eigen/Eigenvalues"
#include "Eigen/StdVector"
#include "SymplecticPauli.h"

#ifndef TEST_FRIENDS
#define TEST_FRIENDS
#endif

typedef std::vector<SymplecticPauli>::size_type SMIndex;

class StabilizerMatrix {
private:
    unsigned int nQubits;
    std::vector<SymplecticPauli> generators;
    void rowSwap(SMIndex i, SMIndex j);
    void rowMult(SMIndex i, SMIndex j);
    TEST_FRIENDS;
public:
    StabilizerMatrix();
    StabilizerMatrix(unsigned int NQubits);
    StabilizerMatrix(std::vector<SymplecticPauli> paulis);
    StabilizerMatrix(std::initializer_list<SymplecticPauli> paulis);
    StabilizerMatrix(unsigned int NQubits, std::vector<SymplecticPauli> paulis);
//    StabilizerMatrix(StabilizerMatrix& m);
    void toCanonicalForm();
    bool linearlyIndependent() const;
    const unsigned int& NQubits() const;
    const std::vector<SymplecticPauli>& Generators() const;
    Eigen::MatrixXcd projector() const;
    Eigen::VectorXcd stabilizerState() const;
};

bool operator==(const StabilizerMatrix& m1, const StabilizerMatrix& m2);
bool operator!=(const StabilizerMatrix& m1, const StabilizerMatrix& m2);

std::ostream& operator<<(std::ostream& os, const StabilizerMatrix&m);


#endif //STABILIZERCPP_STABILIZERMATRIX_H
