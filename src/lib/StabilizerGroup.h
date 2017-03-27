//
// Created by Padraic Calpin on 24/03/2017.
//

#ifndef STABILIZERCPP_STABILIZERGROUP_H
#define STABILIZERCPP_STABILIZERGROUP_H

#include "SymplecticPauli.h"
#include <unordered_set>
#include <vector>


class StabilizerGroup {
    std::unordered_set<SymplecticPauli, PauliHash> generators;
    std::unordered_set<SymplecticPauli, PauliHash> members;
    void generate(SymplecticPauli& element);
public:
    StabilizerGroup();
    StabilizerGroup(std::vector<SymplecticPauli> generators);
    int order();
    void add(SymplecticPauli& element);
};


#endif //STABILIZERCPP_STABILIZERGROUP_H
