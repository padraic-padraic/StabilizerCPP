//
// Created by Padraic Calpin on 24/03/2017.
//

#include "SymplecticPauli.h"
#include "StabilizerGroup.h"
#include <unordered_set>


StabilizerGroup::StabilizerGroup() {
    generators = std::unordered_set<SymplecticPauli, PauliHash>();
    members = std::unordered_set<SymplecticPauli, PauliHash>();
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

void StabilizerGroup::generate(SymplecticPauli& element) {
    std::pair<std::unordered_set<SymplecticPauli, PauliHash>::iterator, bool> out_pair;
    for (auto i=this->members.begin(); i!=this->members.end(); i++){
        out_pair = this->members.insert(element);
        if (out_pair.second){
            this->generate(*out_pair.first);
        }
    }
    return;
}

void StabilizerGroup::add(SymplecticPauli& element) {
    std::pair<std::unordered_set<SymplecticPauli, PauliHash>::iterator, bool> out_pair;
    out_pair = this->members.insert(element);
    if (out_pair.second){
        this->generators.insert(element);
        this->generate(element);
    }
    return;
}