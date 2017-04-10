//
// Created by Padraic Calpin on 24/03/2017.
//

#ifndef STABILIZERCPP_STABILIZERGROUP_H
#define STABILIZERCPP_STABILIZERGROUP_H

#include "gtest/gtest_prod.h"
#include "SymplecticPauli.h"
#include <initializer_list>
#include <unordered_set>
#include <vector>

typedef std::unordered_set<SymplecticPauli, PauliHash> PauliSet;

class StabilizerGroup {
private:
    PauliSet generators;
    PauliSet members;
    void generate(const SymplecticPauli& element);
    FRIEND_TEST(GenratorTest, test_generators_commute);
public:
    StabilizerGroup();
    StabilizerGroup(std::vector<SymplecticPauli> generators);
    StabilizerGroup(std::initializer_list<SymplecticPauli> gens);
    int order() const;
    void add(const SymplecticPauli& element);
    const PauliSet Generators();
    const int nGenerators();
    bool contains(const SymplecticPauli& p) const;
    bool operator ==(const StabilizerGroup& g2) const;
    bool operator !=(const StabilizerGroup& g2) const;
};

std::vector<StabilizerGroup> getStabilizerGroups(unsigned int nQubits);

#endif //STABILIZERCPP_STABILIZERGROUP_H
