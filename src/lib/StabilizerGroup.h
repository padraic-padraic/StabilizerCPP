//
// Created by Padraic Calpin on 24/03/2017.
//

#ifndef STABILIZERCPP_STABILIZERGROUP_H
#define STABILIZERCPP_STABILIZERGROUP_H

#include "SymplecticPauli.h"
#include <set>
#include <vector>


class StabilizerGroup {
    std::set<SymplecticPauli> generators;
    std::set<SymplecticPauli> members;
    void generate(SymplecticPauli);
public:
    StabilizerGroup();
    StabilizerGroup(std::vector<SymplecticPauli> generators);
    int order();
    void add(SymplecticPauli element);
};


#endif //STABILIZERCPP_STABILIZERGROUP_H
