//
// Created by Padraic Calpin on 24/03/2017.
//

#include "lib/SymplecticPauli.h"
#include "lib/StabilizerGroup.h"
#include "lib/utils.h"


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

StabilizerGroup::StabilizerGroup(std::initializer_list<SymplecticPauli> gens) {
    for(auto i=gens.begin(); i!=gens.end(); i++){
        this->add(*i);
    }
}

int StabilizerGroup::order() const{
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

bool StabilizerGroup::contains(const SymplecticPauli &p) const {
    return this->members.find(p)!=this->members.end();
}

bool StabilizerGroup::operator==(const StabilizerGroup &g2) const{
    return this->order() == g2.order() && std::all_of(this->members.begin(), this->members.end(), [&g2](const SymplecticPauli p){return g2.contains(p);});
}

bool StabilizerGroup::operator!=(const StabilizerGroup &g2) const{
    return !((*this).operator==(g2));
}

std::vector<StabilizerGroup> getStabilizerGroups(unsigned int nQubits){
    unsigned int generatorIndex = 0;
    std::vector<StabilizerGroup> groups;
    std::vector<SymplecticPauli> elements;
    for (unsigned int i=1; i<uiPow(2,2*nQubits); i++){
        elements.push_back(SymplecticPauli(nQubits, i));
    }
    std::vector<bool> mask = getMaskArray(elements.size(), nQubits);
    std::vector<SymplecticPauli> generatorCandidates(nQubits);
    do {
        StabilizerGroup candidate;
        for(std::vector<bool>::size_type i=0; i<mask.size(); i++){
            if (mask[i]){
                generatorCandidates[generatorIndex] = elements[i];
                generatorIndex++;
            }
        }
        generatorIndex = 0;
        if (!commutivityTest(generatorCandidates)){ continue; }
        candidate = StabilizerGroup(generatorCandidates);
        if (candidate.nGenerators()!=nQubits){
            continue;
        }
        if (groups.size()==0){
            groups.push_back(candidate);
            continue;
        }
        if (std::none_of(groups.begin(), groups.end(), [&candidate](StabilizerGroup& g){return candidate==g;})){
            groups.push_back(candidate);
        }
    } while(std::next_permutation(mask.begin(), mask.end()));
    return groups;
}

inline std::ostream& operator<<(std::ostream& os, const StabilizerGroup& g){
    for (auto i=g.generators.begin(); i!=g.generators.end(); i++){
        os << (*i).toString();
    }
    return os;
}

StabilizerGroup loadGroup(std::ifstream& is){
    std::string line;
    StabilizerGroup g;
    SymplecticPauli p;
    std::getline(is, line);
    do {
        if(!(line.empty())) {
            p = SymplecticPauli(line);
            g.add(p);
        }
        std::getline(is, line);
    } while(line != "ENDGROUP");
    return g;
}

std::vector<StabilizerGroup> groupsFromFile(std::string& filePath){
    std::ifstream is(filePath);
    if (!(is.good())){
        throw std::invalid_argument("This path, " +filePath + " is NO GOOD.");
    }
    std::string line;
    std::vector<StabilizerGroup> groups;
    while(std::getline(is, line)){
        if (line=="GROUP"){
            groups.push_back(loadGroup(is)); //Winds forward until an ENDGROUP block is found
        }
        continue; //Winds forward until the next GROUP block is found
    }
    is.close();
    return groups;
}