//
// Created by Padraic Calpin on 12/04/2017.
//

#ifndef STABILIZERCPP_STABILIZERMATRIX_H
#define STABILIZERCPP_STABILIZERMATRIX_H

#include <initializer_list>
#include <iostream>
#include <vector>
#include "gtest/gtest_prod.h"
#include "Eigen/Dense"
#include "Eigen/StdVector"
#include "SymplecticPauli.h"


typedef std::vector<SymplecticPauli>::size_type SMIndex;

class StabilizerMatrix {
private:
    unsigned int nQubits;
    std::vector<SymplecticPauli> generators;
    void rowSwap(SMIndex i, SMIndex j);
    void rowMult(SMIndex i, SMIndex j);
    FRIEND_TEST(GeneratorTest, test_generators_commute);
    FRIEND_TEST(GeneratorTest, test_loaded_generators);
    FRIEND_TEST(SMTest, RowSwap);
    FRIEND_TEST(SMTest, RowMult);
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
};

bool operator==(const StabilizerMatrix& m1, const StabilizerMatrix& m2);
bool operator!=(const StabilizerMatrix& m1, const StabilizerMatrix& m2);

std::ostream& operator<<(std::ostream& os, const StabilizerMatrix&m);

std::vector<StabilizerMatrix> getStabilizerGroups(unsigned int nQubits);
StabilizerMatrix loadGroup(std::ifstream& is);
std::vector<StabilizerMatrix> groupsFromFile(std::string& filePath);

#endif //STABILIZERCPP_STABILIZERMATRIX_H
