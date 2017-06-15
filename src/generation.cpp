//
// Created by Padraic Calpin on 21/04/2017.
//

#include <functional>
#include <random>
#include "lib/generation.h"
#include "lib/utils.h"

std::vector<StabilizerMatrix> getStabilizerGroups(unsigned int nQubits, unsigned int nGroups){
    unsigned int target;
    if (nGroups > nStabilizers(nQubits)/uiPow(2,nQubits)){
        target = nStabilizers(nQubits)/uiPow(2,nQubits);
    }
    else {
        target = nGroups;
    }
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
        if (groups.size()==target){
            break;
        }
    } while(std::next_permutation(mask.begin(), mask.end()));
    return groups;
}

std::vector<StabilizerMatrix> getStabilizerGroups(unsigned int nQubits){
    return getStabilizerGroups(nQubits, nStabilizers(nQubits));
}

VectorList getStabilizerStates(unsigned int nQubits, unsigned int nStates){
    unsigned int nStabs, nPos;
    nStabs = nStabilizers(nQubits);
    nPos = nStabs/uiPow(2, nQubits);
    std::vector<StabilizerMatrix> groups;
    groups = getStabilizerGroups(nQubits, nStates);
    Eigen::VectorXcd placeholder;
    VectorList states;
    std::mt19937::result_type seed = time(0);
    auto rand_phase = std::bind(std::uniform_int_distribution<unsigned int>(1,uiPow(2,nQubits)),
                                std::mt19937(seed));
    if (nStates < nPos){
        auto rand_real = std::bind(std::uniform_real_distribution<double>(0,1),
                                   std::mt19937(seed));
        for (auto i=groups.begin(); i!=groups.end(); i++){
            if (rand_real() > 0.5){
                i->setPhase(rand_phase());
            }
            placeholder = i->stabilizerState();
            states.push_back(placeholder);
        }
    }
    else if (nStates > nPos && nStates < nStabs){
        auto rand_group = std::bind(std::uniform_int_distribution<unsigned int>(1,groups.size()),
                                    std::mt19937(seed));
        unsigned int gIndex;
        for (auto i=groups.cbegin(); i!=groups.cend(); i++){
            placeholder = i->stabilizerState();
            states.push_back(placeholder);
        }
        for (unsigned int i=0; i< (nStates-nPos); i++){
            gIndex = rand_group();
            groups[gIndex].setPhase(rand_phase());
            placeholder = groups[gIndex].stabilizerState();
            states.push_back(placeholder);
        }
    }
    else {
        for (unsigned int i=0; i<(uiPow(2,nQubits)+1); i++){
            for (auto g = groups.begin(); g!=groups.end(); g++){
                g->setPhase(i);
                placeholder = g->stabilizerState();
                states.push_back(placeholder);
            }
        }
    }
    return states;
}

VectorList getStabilizerStates(unsigned int nQubits){
    return getStabilizerStates(nQubits, nStabilizers(nQubits));
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