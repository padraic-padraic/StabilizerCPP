//
// Created by Padraic Calpin on 21/04/2017.
//

#ifndef STABILIZERCPP_GENERATION_H
#define STABILIZERCPP_GENERATION_H

#include <fstream>
#include <iostream>
#include <vector>
#include "Eigen/Dense"
#include "Eigen/Eigenvalues"
#include "Eigen/StdVector"
#include "StabilizerMatrix.h"

typedef std::vector<Eigen::VectorXcd, Eigen::aligned_allocator<Eigen::VectorXcd> > VectorList;

std::vector<StabilizerMatrix> getStabilizerGroups(unsigned int nQubits, bool realOnly=false);
std::vector<StabilizerMatrix> getStabilizerGroups(unsigned int nQubits, unsigned int nStates, bool realOnly=false);
VectorList getStabilizerStates(std::vector<StabilizerMatrix> groups, unsigned int nStates);
VectorList getStabilizerStates(unsigned int nqubits, bool realOnly=false);
VectorList getStabilizerStates(unsigned int nQubits, unsigned int nStates, bool realOnly=false);
StabilizerMatrix loadGroup(std::ifstream& is);
std::vector<StabilizerMatrix> groupsFromFile(std::string& filePath);
void saveGroups(std::string& filePath, std::vector<StabilizerMatrix> groups);
void writeState(std::ofstream& os, Eigen::VectorXcd& state);
void saveStates(std::string& filePath, VectorList& states);
void saveStates(std::string& filePath, std::vector<StabilizerMatrix>& groups);
Eigen::VectorXcd loadState(std::ifstream& is);
VectorList statesFromFile(std::string filePath);

#endif //STABILIZERCPP_GENERATION_H
