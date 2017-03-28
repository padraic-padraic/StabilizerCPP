//
// Created by Padraic Calpin on 24/03/2017.
//

#include "lib/SymplecticPauli.h"
#include "lib/StabilizerGroup.h"
#include <unordered_set>


StabilizerGroup::StabilizerGroup() {
    generators = PauliSet();
    members = PauliSet();
}

StabilizerGroup::StabilizerGroup(std::vector<SymplecticPauli> generators) {
    auto i = generators.begin();
    for ( ; i!=generators.end(); i++){
        this->add(*i);
    }
}

int StabilizerGroup::order(){
    return this->members.size();
}

void StabilizerGroup::generate(const SymplecticPauli& element) {
    std::pair<PauliSet::iterator, bool> out_pair;
    for (auto i=this->members.begin(); i!=this->members.end(); i++){
        out_pair = this->members.insert((*i)*element);
        if (out_pair.second){
            this->generate(*out_pair.first);
        }
    }
    return;
}

void StabilizerGroup::add(const SymplecticPauli& element) {
    std::pair<PauliSet::iterator, bool> out_pair;
    out_pair = this->members.insert(element);
    if (out_pair.second){
        this->generators.insert(element);
        this->generate(element);
    }
    return;
}

const PauliSet StabilizerGroup::Generators() {
    return this->generators;
}

const int StabilizerGroup::nGenerators(){
    return this->generators.size();
}
