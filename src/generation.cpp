//
// Created by Padraic Calpin on 21/04/2017.
//

#include <algorithm>
#include <functional>
#include <iostream>
#include <random>
#include <string>
#include "lib/generation.h"
#include "lib/utils.h"

std::vector<StabilizerMatrix> getStabilizerGroups(unsigned int nQubits, unsigned int nStates, bool realOnly,
                                                  bool verbose){
    unsigned int target, getAll=0;
    if (nStates > nStabilizers(nQubits)/uiPow(2,nQubits)){
        target = nStabilizers(nQubits)/uiPow(2,nQubits);
        getAll = 1;
    }
    else {
        target = nStates;
    }
    unsigned int generatorIndex = 0;
    std::vector<StabilizerMatrix> groups;
    if (getAll==1) {std::vector<SymplecticPauli> paulis;
    for (unsigned int i=1; i<uiPow(2,2*nQubits); i++){
        paulis.push_back(SymplecticPauli(nQubits, i));
    }
    std::random_shuffle(paulis.begin(), paulis.end());
    std::vector<bool> mask = getMaskArray(paulis.size(), nQubits);
    std::vector<SymplecticPauli> generatorCandidates(nQubits);
    do {
        StabilizerMatrix candidate;
        for(std::vector<bool>::size_type i=0; i<mask.size(); i++){
            if (mask[i]){
                generatorCandidates[generatorIndex] = paulis[i];
                generatorIndex++;
            }
        }
        generatorIndex = 0;
        if (realOnly){
            if (!std::all_of(generatorCandidates.begin(), generatorCandidates.end(), [](SymplecticPauli& p){
                    return p.isReal();
                }) )
            {
                continue;
            }
        }
        if (!commutivityTest(generatorCandidates)){ continue; }
        candidate = StabilizerMatrix(generatorCandidates);
        candidate.toCanonicalForm();
        if (!candidate.linearlyIndependent()){
            continue;
        }
        if (groups.size()==0){
            groups.push_back(candidate);
            if (verbose){
                std::cout << "Found " + std::to_string(groups.size()) + " groups so far." << std::endl;
            }continue;
        }
        if (std::none_of(groups.begin(), groups.end(), [&candidate](StabilizerMatrix& g){return candidate==g;})){
            groups.push_back(candidate);if (verbose){
                std::cout << "Found " + std::to_string(groups.size()) + " groups so far." << std::endl;
            }
        }
        if (groups.size()==target){
            break;
        }
    } while(std::next_permutation(mask.begin(), mask.end()));} else {
        do {
            StabilizerMatrix candidate(nQubits);
            candidate.random();
            candidate.toCanonicalForm();
            if (!candidate.linearlyIndependent()) {
                continue;
            }
            if (realOnly) {
                if (!std::all_of(candidate.Generators().cbegin(), candidate.Generators().cend(), [](const SymplecticPauli &p) {
                    return p.isReal();
                })) {
                    continue;
                }
            }
            if (groups.size() == 0) {
                groups.push_back(candidate);
                continue;
            }
            if (std::none_of(groups.begin(), groups.end(),
                             [&candidate](StabilizerMatrix &g) { return candidate == g; })) {
                groups.push_back(candidate);
            }
        } while (groups.size() < target);
    }
    return groups;
}

std::vector<StabilizerMatrix> getStabilizerGroups(unsigned int nQubits, bool realOnly, bool verbose){
    return getStabilizerGroups(nQubits, nStabilizers(nQubits), realOnly, verbose);
}

VectorList getStabilizerStates(std::vector<StabilizerMatrix> groups, unsigned int nStates, bool verbose){
    unsigned int nQubits = groups[0].NQubits();
    unsigned int nStabs, nPos;
    nStabs = nStabilizers(nQubits);
    nPos = nStabs/uiPow(2, nQubits);
    Eigen::VectorXcd placeholder;
    VectorList states;
    reseedMt();
    auto rand_phase = std::bind(std::uniform_int_distribution<unsigned int>(1,uiPow(2,nQubits)),
                                mt);
    if (nStates <= nPos){
        auto rand_real = std::bind(std::uniform_real_distribution<double>(0,1),
                                   mt);
        for (auto i=groups.begin(); i!=groups.end(); i++){
            if (rand_real() > 0.5){
                i->setPhase(rand_phase());
            }
            placeholder = i->stabilizerState();
            states.push_back(placeholder);
            if (verbose){
                std::cout << "Got " + std::to_string(states.size()) + " states so far." << std::endl;
            }
        }
    }
    else if (nStates > nPos && nStates < nStabs){
        unsigned int gIndex;
        for (auto i=groups.cbegin(); i!=groups.cend(); i++){
            placeholder = i->stabilizerState();
            states.push_back(placeholder);
            if (verbose){
                std::cout << "Got " + std::to_string(states.size()) + " states so far." << std::endl;
            }
        }
        for (unsigned int i=0; i< (nStates-nPos); i++){
            groups[i].setPhase(rand_phase()); //Uhh what about duplicates? Groups shuffle anyway so...
            placeholder = groups[i].stabilizerState();
            states.push_back(placeholder);
            if (verbose){
                std::cout << "Got " + std::to_string(states.size()) + " states so far." << std::endl;
            }
        }
    }
    else {
        for (unsigned int i=1; i<(uiPow(2,nQubits)+1); i++){
            for (auto g = groups.begin(); g!=groups.end(); g++){
                g->setPhase(i);
                placeholder = g->stabilizerState();
                states.push_back(placeholder);
                if (verbose){
                    std::cout << "Got " + std::to_string(states.size()) + " states so far." << std::endl;
                }
            }
        }
    }
    return states;
}

VectorList getStabilizerStates(unsigned int nQubits, unsigned int nStates, bool realOnly, bool verbose){
    std::vector<StabilizerMatrix> groups = getStabilizerGroups(nQubits, nStates, realOnly, verbose);
    return getStabilizerStates(groups, nStates, verbose);
}

VectorList getStabilizerStates(unsigned int nQubits, bool realOnly, bool verbose){
    return getStabilizerStates(nQubits, nStabilizers(nQubits), realOnly, verbose);
}

StabilizerMatrix loadGroup(std::ifstream& is){
    std::string line;
    std::vector<SymplecticPauli> ps;
    std::getline(is, line);
    do {
        if(!(line.empty())) {
            ps.push_back(SymplecticPauli(line));
        }
        std::getline(is, line);
    } while(line != "ENDGROUP");
    StabilizerMatrix g(ps);
    g.toCanonicalForm();
    return g;
}

std::vector<StabilizerMatrix> groupsFromFile(std::string& filePath){
    std::ifstream is(filePath);
    if (!(is.good())){
        throw std::invalid_argument("This path, " +filePath + " is NO GOOD.");
    }
    std::string line;
    std::vector<StabilizerMatrix> groups;
    while(std::getline(is, line)){
        if (line=="GROUP"){
            groups.push_back(loadGroup(is)); //Winds forward until an ENDGROUP block is found
        }
        continue; //Winds forward until the next GROUP block is found
    }
    is.close();
    return groups;
}

void saveGroups(std::string& filePath, std::vector<StabilizerMatrix> groups){
    std::ofstream os(filePath);
    if (!(os.good())){
        throw std::invalid_argument("Couldn't open path "+ filePath + " for output.");
    }
    for(auto i=groups.cbegin(); i!=groups.cend(); i++){
        os << *i << std::endl;
    }
}

void writeState(std::ofstream& os, Eigen::VectorXcd& state){
    os << "STATE" << std::endl;
    os << state << std::endl;
    os << "ENDSTATE" << std::endl;
    os <<"\n"<<std::endl;
}

void saveStates(std::string& filePath, VectorList& states){
    std::ofstream os(filePath);
    for(auto i=states.begin(); i!=states.end(); i++){
        writeState(os, *i);
    }
}

void saveStates(std::string& filePath, std::vector<StabilizerMatrix>& groups){
    std::ofstream os(filePath);
    Eigen::VectorXcd state(uiPow(2, groups[0].NQubits()));
    for(auto i=groups.cbegin(); i!=groups.cend(); i++){
        state = i->projector();
        writeState(os, state);
        os << std::endl;
    }
}

Eigen::VectorXcd loadState(std::ifstream& is){
    cd placeholder;
    std::vector<cd> coeffs;
    std::string line;
    std::istringstream iss;
    std::getline(is, line);
    do {
        if(!(line.empty())) {
            iss = std::istringstream(line);
            iss >> placeholder;
            coeffs.push_back(placeholder);
        }
        std::getline(is, line);
    } while(line != "ENDSTATE");
    Eigen::VectorXcd v(coeffs.size());
    for(auto i=0; i<coeffs.size(); i++){
        v(i)=coeffs[i];
    }
    return v;
}

VectorList statesFromFile(std::string filePath){
    std::ifstream is(filePath);
    if (!(is.good())){
        throw std::invalid_argument("This path, " +filePath + " is NO GOOD.");
    }
    std::string line;
    VectorList states;
    while(std::getline(is, line)){
        if (line=="STATE"){
            states.push_back(loadState(is)); //Winds forward until an ENDSTATE block is found
        }
        continue; //Winds forward until the next STATE block is found
    }
    is.close();
    return states;
}